#ifndef __VLOG_DM_PROCESS_VISITOR_HPP__
#define __VLOG_DM_PROCESS_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ContinuousAssignment;
struct SequentialProcess;

/***************************************************************************/

struct ProcessVisitor
	:	boost::noncopyable
{

/***************************************************************************/

	virtual void visit( ContinuousAssignment const & _assign ) = 0;

	virtual void visit( SequentialProcess const & _assign ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PROCESS_VISITOR_HPP__
