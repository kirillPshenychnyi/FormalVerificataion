#ifndef __VLOG_DM_PRIMARY_LITERAL_HPP__
#define __VLOG_DM_PRIMARY_LITERAL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct PrimaryLiteral
	:	public Expression
{

/***************************************************************************/

	virtual std::string const& getValue() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_PRIMARY_LITERAL_HPP__
