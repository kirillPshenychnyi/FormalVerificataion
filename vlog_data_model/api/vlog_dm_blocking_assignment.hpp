#ifndef __VLOG_DM_BLOCKING_ASSIGNMENT_HPP__
#define __VLOG_DM_BLOCKING_ASSIGNMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct BinaryOperator;

/***************************************************************************/

struct BlockingAssignment
	:	public Statement
{

/***************************************************************************/

	virtual BinaryOperator const & getAssignment() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BLOCKING_ASSIGNMENT_HPP__
