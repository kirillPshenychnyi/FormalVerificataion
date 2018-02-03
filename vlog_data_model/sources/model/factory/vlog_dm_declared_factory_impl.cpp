#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_port_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_variable_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

PortPtr
DeclaredFactoryImpl::newPort( 
		Declaration const & _declaration
	,	std::unique_ptr< Type > _type
	,	std::string const & _name
	,	Location const & _location
	,	PortDirection::Direction _direction
	,	std::unique_ptr< Dimension > _dimension 
	) const
{	
	return
		std::make_unique< PortImpl >(
				_declaration
			,	std::move( _type )
			,	_name
			,	_location
			,	std::move( _dimension )
			,	_direction
		);
}

/***************************************************************************/

VariablePtr
DeclaredFactoryImpl::newVariable ( 
		VlogDM::Declaration const & _declaration
	,	std::unique_ptr< Type > _type
	,	std::string const & _name
	,	Location const & _location
	,	bool _isSigned
	,	std::unique_ptr< Dimension > _dimension
	) const
{
	return
		std::make_unique< VariableImpl >(
				_declaration
			,	std::move( _type )
			,	_name
			,	_location
			,	std::move( _dimension )
			,	_isSigned
		);
}

/***************************************************************************/

}