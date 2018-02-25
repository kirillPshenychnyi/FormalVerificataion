#ifndef __VLOG_DM_ACCESSOR_IMPL_HPP__
#define __VLOG_DM_ACCESSOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

#include "common_tools\collections\tools_collection_utils.hpp"

#include <boost\functional\hash\hash.hpp>

#include <boost\unordered_set.hpp>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

	typedef
		Tools::Collections::NamedHasher< Writable::DesignUnitPtr >
		DesignUnitHasher;

	typedef
		Tools::Collections::NamedComparator< Writable::DesignUnitPtr >
		DesignUnitComparator;

	typedef
		boost::unordered_set< 
				Writable::DesignUnitPtr
			,	DesignUnitHasher
			,	DesignUnitComparator 
		>
		UnitsSet;

/***************************************************************************/

public:

/***************************************************************************/

	Accessor();

	void addUnit( Writable::DesignUnitPtr _unit ) override;

	boost::optional< DesignUnit const & > findUnit( 
		std::string const& _unitName 
	) const override;

	Writable::DesignUnit & getCurrentImportedUnit() override;

	void reset() override;
		
	void regenerateProcess( 
			std::ostream & _stream
		,	Process const & _process 
	) const override;

/***************************************************************************/

	Writable::DesignUnitFactory const& getDesignUnitFactory() override;

	Writable::DeclarationFactory const& getDeclarationFactory() override;

	Writable::DeclaredFactory const& getDeclaredFactory() override;

	Writable::ItemsFactory const& getItemsFactory() override;

	Writable::ExpressionFactory const& getExpressionFactory() override;

	Writable::TypeFactory const& getTypeFactory() override;

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _TFactory > 
	std::unique_ptr< _TFactory > getFactory() const;

/***************************************************************************/

	UnitsSet m_unitsSet;

	Writable::DesignUnit * m_currentImportedUnit;

	std::unique_ptr< Writable::DesignUnitFactory > m_designUnitFactory;

	std::unique_ptr< Writable::DeclarationFactory > m_declarationFactory;

	std::unique_ptr< Writable::DeclaredFactory > m_declaredFactory;

	std::unique_ptr< Writable::ItemsFactory > m_itemsFactory;

	std::unique_ptr< Writable::ExpressionFactory > m_expressionFactory;

	std::unique_ptr< Writable::TypeFactory > m_typeFactory;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_ACCESSOR_IMPL_HPP__

