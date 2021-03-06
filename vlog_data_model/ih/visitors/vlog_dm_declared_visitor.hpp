#ifndef __VLOG_DM_DECLARED_VISITOR_HPP__
#define __VLOG_DM_DECLARED_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Port;
struct Variable;

/***************************************************************************/

DECLARE_VISITORS( Declared, Port, Variable )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARED_VISITOR_HPP__
