#ifndef __AEP_MAIN_CONTAINER_BOOTSTRAPPER_HPP__
#define __AEP_MAIN_CONTAINER_BOOTSTRAPPER_HPP__

/***************************************************************************/

#include "hypodermic\Hypodermic.h"

/***************************************************************************/

namespace AepMain {

/***************************************************************************/

class ContainerBootstrapper
{

/***************************************************************************/

public:

/***************************************************************************/

	ContainerBootstrapper();
	
	Hypodermic::Container & takeContainer();

/***************************************************************************/

private:

/***************************************************************************/

	std::shared_ptr< Hypodermic::Container > m_container;

/***************************************************************************/

};

/***************************************************************************/

inline
Hypodermic::Container & 
ContainerBootstrapper::takeContainer() 
{
	return *m_container;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MAIN_CONTAINER_BOOTSTRAPPER_HPP__
