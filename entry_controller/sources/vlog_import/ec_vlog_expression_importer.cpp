#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_concatenation.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ExpressionImporter::ExpressionImporter( 
		VlogDM::IAccessor & _vlogDm 
	,	VlogDM::Writable::DesignUnit const & _targetUnit
	)
	:	BaseImporter( _vlogDm )
	,	m_targetUnit( _targetUnit )
{
}

/***************************************************************************/

VlogDM::ExpressionPtr
ExpressionImporter::importExpression( 
	Verilog2001Parser::ExpressionContext & _expression 
)
{
	acceptEachChildContext( _expression );

	createExpression();

	return std::move( m_result );
}

/***************************************************************************/

VlogDM::RangePtr 
ExpressionImporter::importRange( 
	Verilog2001Parser::Range_expressionContext & _rangeExpression 
)
{
	acceptEachChildContext( _rangeExpression );

	createExpression();

	return 
		getVlogDataModel().getItemsFactory().newExpressionRange( 
			std::move( m_result )
		);
}

/***************************************************************************/

void
ExpressionImporter::createExpression()
{
	using namespace VlogDM;

	if( m_result )
		return;

	if( m_topNodes.empty() )
	{
		m_result = getLastContext().getValidOperand();

		return;
	}

	BinaryOperatoInfo & lastContex = getLastContext();

	if( ExpressionPtr validOperand = lastContex.getValidOperand() )
	{
		m_topNodes.push_back( std::move( validOperand ) );
		m_operators.push_back( lastContex.m_operator );
	}

	Writable::ExpressionFactory const & expressionFactory 
			= getVlogDataModel().getExpressionFactory();

	if( m_topNodes.size() == 1 )
	{
		ExpressionPtr operand = std::move( m_topNodes.front() );
		Location const & location = operand->getLocation();

		if( m_operators.empty() )
			m_result = std::move( operand );
		else 
		{
			assert( m_operators.size() == 1 );

			m_result = 
				expressionFactory.newUnaryOperator(
						std::move( operand )
					,	m_operators.front()
					,	location
				);
		}
	
		return;
	}

	auto buildTopBinaryNodes
		=	[ this ]( Operands & _primaryNodes )
			{
				BinaryOperatoInfo info( m_operators.front() );
				Operands binaryNodes;

				m_operators.pop_front();
				const int topNodesCount = _primaryNodes.size();

				for( int i = 0; i < topNodesCount; ++i )
				{
					info.addOperand( std::move( _primaryNodes[ i ] ) );

					if( info.canConstructBinaryOperator() )
						binaryNodes.push_back( createBinaryOperator( info ) );
				}

				if( ExpressionPtr lastOperand = info.getValidOperand() )
				{
					assert( m_operators.size() == 1 );

					info.addOperand( std::move( binaryNodes.back() ) );
					info.addOperand( std::move( lastOperand ) );
					info.m_operator = m_operators.front();

					binaryNodes.pop_back();					
					binaryNodes.push_back( createBinaryOperator( info ) );
				}

				_primaryNodes = std::move( binaryNodes );
			};

	while( true )
	{
		buildTopBinaryNodes( m_topNodes );
		
		if( m_topNodes.size() == 1 )
		{
			m_result = std::move( m_topNodes.front() );
			break;
		}
	}
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createBinaryOperator( BinaryOperatoInfo & _info )
{
	using namespace VlogDM;
			
	Writable::ExpressionFactory const & expressionFactory 
		=	getVlogDataModel().getExpressionFactory();

	ExpressionPtr binaryOp
		=	expressionFactory.newBinaryOperator(
					std::move( _info.m_leftOperand )
				,	std::move( _info.m_rightOperand )
				,	_info.m_operator
			);

	_info.clear();

	return binaryOp;
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createUnaryOperator( BinaryOperatoInfo & _info )
{
	using namespace VlogDM;
			
	Writable::ExpressionFactory const & expressionFactory 
		=	getVlogDataModel().getExpressionFactory();

	Location const & location = _info.m_leftOperand->getLocation();

	ExpressionPtr unaryOp
		=	expressionFactory.newUnaryOperator(
					_info.getValidOperand()
				,	_info.m_operator
				,	location
			);

	return unaryOp;
}

/***************************************************************************/

void
ExpressionImporter::processLastContext()
{
	using namespace VlogDM;

	BinaryOperatoInfo & lastContext = getLastContext();

	if( lastContext.canConstructBinaryOperator() )
	{
		m_topNodes.push_back( createBinaryOperator( lastContext ) );

		m_contexts.pop_back();
	}
	else if( lastContext.canConstructUnaryOperator() )
	{
		ExpressionPtr unaryOp = createUnaryOperator( lastContext );

		m_contexts.pop_back();

		if( !m_contexts.empty() )
			m_contexts.back().addOperand( std::move( unaryOp ) );
		else 
			m_topNodes.push_back( std::move( unaryOp ) );
	}
}

/***************************************************************************/

ExpressionImporter::BinaryOperatoInfo &
ExpressionImporter::getLastContext()
{
	if( m_contexts.empty() )
		m_contexts.push_back( BinaryOperatoInfo() );

	return m_contexts.back();
}

/***************************************************************************/

void 
ExpressionImporter::reset()
{
	m_contexts.clear();
	m_operators.clear();
	m_topNodes.clear();
	m_result.reset();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitTerm( Verilog2001Parser::TermContext * ctx )
{
	acceptEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitPrimary( Verilog2001Parser::PrimaryContext * ctx )
{
	using namespace VlogDM;

	acceptEachChildContext( *ctx );

	processLastContext();

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	using namespace VlogDM;

	BinaryOperatoInfo & lastContext = getLastContext();

	if( !Operator::isUnary( lastContext.m_operator ) )
		acceptEachChildContext( *ctx );
	else 
	{
		Writable::ExpressionFactory const & expressionFactory 
			=	getVlogDataModel().getExpressionFactory();

		ExpressionImporter expressionImporter( getVlogDataModel(), m_targetUnit );
		
		lastContext.addOperand( expressionImporter.importExpression( *ctx ) );
	}

	processLastContext();

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitBinary_operator(
	Verilog2001Parser::Binary_operatorContext * ctx
)
{
	BinaryOperatoInfo & lastContext = getLastContext();

	if( lastContext.m_operator != VlogDM::Operator::Kind::Unknown )
		m_operators.push_back( lastContext.m_operator );

	lastContext.m_operator
		= VlogDM::Operator::fromString( ctx->getText().c_str() );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitUnary_operator( Verilog2001Parser::Unary_operatorContext * ctx )
{
	m_contexts.push_back( 
		BinaryOperatoInfo( VlogDM::Operator::fromString( ctx->getText().c_str() ) ) 
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitNumber( Verilog2001Parser::NumberContext * ctx )
{
	getLastContext().addOperand( 
		getVlogDataModel().getExpressionFactory().newPrimaryLiteral(
				createLocation( *ctx )
			,	ctx->getText() 
		) 
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitSimple_hierarchical_identifier( 
	Verilog2001Parser::Simple_hierarchical_identifierContext * ctx 
)
{
	using namespace VlogDM;

	IAccessor & vlogDM = getVlogDataModel();

	auto declared = m_targetUnit.findDeclared( ctx->getText() );

	IdentifierImporter idImporter( getVlogDataModel(), m_targetUnit );

	idImporter.importId( *ctx );

	getLastContext().addOperand( 
			vlogDM.getExpressionFactory().newPrimaryIdentifier( 
					idImporter.takeId( 0 )
			)
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
ExpressionImporter::visitConcatenation(
	Verilog2001Parser::ConcatenationContext * ctx
) 
{
	using namespace VlogDM;

	struct ContactItemExtractor
		:	public BaseImporter
	{
		ContactItemExtractor( 
				IAccessor & _vlogDm
			,	Writable::DesignUnit const & _targetUnit
		)
		:	BaseImporter( _vlogDm )
		,	m_importer( _vlogDm, _targetUnit )
		{}
		
		ExpressionPtr extract( antlr4::tree::ParseTree & _tree )
		{
			m_importer.reset();
			m_extractedExpession.reset();

			_tree.accept( this );

			return std::move( m_extractedExpession );
		}

		antlrcpp::Any visitExpression(
			Verilog2001Parser::ExpressionContext * ctx
		) override
		{	
			m_extractedExpession 
				= std::move( m_importer.importExpression( *ctx ) );

			return antlrcpp::Any();
		}
		
		ExpressionImporter m_importer;
		ExpressionPtr m_extractedExpession;
	};

	auto concat 
		= getVlogDataModel().getExpressionFactory().newConcatenation( createLocation( *ctx ) );

	ContactItemExtractor extractor( getVlogDataModel(), m_targetUnit );

	forEachChildContext( 
			*ctx
		,	[ & ]( antlr4::tree::ParseTree & _tree )
			{
				if( ExpressionPtr item = extractor.extract( _tree ) )
					concat->addExpression( std::move( item ) );
			}
	);

	m_result = std::move( concat );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}