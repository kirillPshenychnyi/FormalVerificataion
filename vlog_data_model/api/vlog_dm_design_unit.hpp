#ifndef __VLOG_DM_DESIGN_UNIT_HPP__
#define __VLOG_DM_DESIGN_UNIT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\api\vlog_dm_named.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct DesignUnit
	:	public DeclarationsContainer
	,	public Named
{

/***************************************************************************/

	typedef
		std::unique_ptr< DesignUnit >
		Ptr;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DESIGN_UNIT_HPP__
