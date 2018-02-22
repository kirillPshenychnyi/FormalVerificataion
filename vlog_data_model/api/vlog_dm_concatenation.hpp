#ifndef __VLOG_DM_CONCATENATION_HPP__
#define __VLOG_DM_CONCATENATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Concatenation
	:	public Expression
{

/***************************************************************************/

	virtual int getExpressionsCount() const = 0;

	virtual Expression const & getExpression( int _idx ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONCATENATION_HPP__
