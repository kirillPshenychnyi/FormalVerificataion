#ifndef __VLOG_DM_RANGE_HPP__
#define __VLOG_DM_RANGE_HPP__

/***************************************************************************/

#include "api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct RangeVisitor;

/***************************************************************************/

struct Range
	:	public Located
{

/***************************************************************************/

	virtual ~Range() {}

	virtual void accept( RangeVisitor const & _visitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_RANGE_HPP__
