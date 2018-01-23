#ifndef __VLOG_DM_LOCATED_HPP__
#define __VLOG_DM_LOCATED_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct Location;

/***************************************************************************/
	
struct Located
	:	public boost::noncopyable
{
	
/***************************************************************************/
	
	virtual Location const & getLocation () const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_LOCATED_HPP__