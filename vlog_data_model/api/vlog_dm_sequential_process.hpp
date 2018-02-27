#ifndef __VLOG_DM_SEQUENTIAL_PROCESS_HPP__
#define __VLOG_DM_SEQUENTIAL_PROCESS_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_process.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Statement;

/***************************************************************************/

struct SequentialProcess
	:	public Process
{

/***************************************************************************/

	virtual Statement const & getStatement () const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_SEQUENTIAL_PROCESS_HPP__
