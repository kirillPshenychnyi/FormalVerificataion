#ifndef __AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__
#define __AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckersFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::unique_ptr< OvlOneHotCheckerBuilder > newOvlOneHotChecker(
			std::string const & _instanceName
		,	std::string const & _fileName
		,	int _suspectLine
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__
