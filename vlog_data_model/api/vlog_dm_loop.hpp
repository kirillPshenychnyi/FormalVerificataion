#ifndef __VLOG_DM_LOOP_HPP__
#define __VLOG_DM_LOOP_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Loop
	:	public Statement
{

/***************************************************************************/

	virtual Statement const & getLoopStatement() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_LOOP_HPP__
