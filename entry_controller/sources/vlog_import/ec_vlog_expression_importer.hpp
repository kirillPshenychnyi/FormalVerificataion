#ifndef __EC_VLOG_EXPRESSION_IMPORTER_HPP__
#define __EC_VLOG_EXPRESSION_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_operator.hpp"

#include <list>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class ExpressionImporter
	:	public BaseImporter
{

	struct BinaryOperatoInfo
	{
		BinaryOperatoInfo( 
			VlogDM::Operator::Kind _operator = VlogDM::Operator::Kind::Unknown
		)
		:	m_operator( _operator )
		{}

		void clear()
		{
			m_leftOperand.reset();
			m_rightOperand.reset();
			m_operator = VlogDM::Operator::Kind::Unknown;
		}

		void addOperand( VlogDM::ExpressionPtr _expression )
		{
			if( !m_leftOperand )
				m_leftOperand = std::move( _expression );
			else 
				m_rightOperand = std::move( _expression );
		}

		VlogDM::ExpressionPtr getValidOperand()
		{
			return 
				m_leftOperand 
				?	std::move( m_leftOperand ) 
				:	std::move( m_rightOperand );
		}

		bool canConstructBinaryOperator()
		{
			return m_leftOperand && m_rightOperand;
		}

		bool canConstructUnaryOperator()
		{
			return m_leftOperand && VlogDM::Operator::isUnary( m_operator );
		}

		VlogDM::ExpressionPtr m_leftOperand;
		VlogDM::ExpressionPtr m_rightOperand;
		VlogDM::Operator::Kind m_operator;
	};

/***************************************************************************/

	typedef
		std::vector< VlogDM::ExpressionPtr >
		Operands;

	typedef
		std::list < VlogDM::Operator::Kind >
		Operators;

	typedef
		std::vector< BinaryOperatoInfo >
		OperatorContexts;

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionImporter( VlogDM::IAccessor & _vlogDm );

	VlogDM::ExpressionPtr importExpression( 
		Verilog2001Parser::ExpressionContext & _expression
	);

	VlogDM::RangePtr importRange(
		Verilog2001Parser::Range_expressionContext & _rangeExpression
	);

/***************************************************************************/

private:

/***************************************************************************/

	void createExpression();

	VlogDM::ExpressionPtr createBinaryOperator( BinaryOperatoInfo & _info );

	VlogDM::ExpressionPtr createUnaryOperator( BinaryOperatoInfo & _info );

	VlogDM::ConcatPtr createConcat(
		Verilog2001Parser::ConcatenationContext & _concateContext 
	);

	void processLastContext();

	BinaryOperatoInfo & getLastContext();

	void reset();

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitSimple_hierarchical_identifier(
			Verilog2001Parser::Simple_hierarchical_identifierContext * ctx
	) override;

	antlrcpp::Any visitTerm( Verilog2001Parser::TermContext * ctx ) override;

	antlrcpp::Any visitPrimary( Verilog2001Parser::PrimaryContext * ctx ) override;

	antlrcpp::Any visitExpression( 
		Verilog2001Parser::ExpressionContext * ctx 
	) override;

	antlrcpp::Any visitBinary_operator( 
		Verilog2001Parser::Binary_operatorContext * ctx 
	) override;

	antlrcpp::Any visitUnary_operator(
		Verilog2001Parser::Unary_operatorContext * ctx
	) override;

	antlrcpp::Any visitNumber( 
		Verilog2001Parser::NumberContext * ctx 
	) override;

	antlrcpp::Any visitConcatenation(
		Verilog2001Parser::ConcatenationContext * ctx
	) override;

	antlrcpp::Any visitMultiple_concatenation(
		Verilog2001Parser::Multiple_concatenationContext *ctx 
	);

/***************************************************************************/

private:

/***************************************************************************/

	OperatorContexts m_contexts;

	Operands m_topNodes;

	Operators m_operators;

	VlogDM::ExpressionPtr m_result;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_EXPRESSION_IMPORTER_HPP__