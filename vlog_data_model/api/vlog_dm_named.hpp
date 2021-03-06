#ifndef __VLOG_DM_NAMED_HPP__
#define __VLOG_DM_NAMED_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct Named
	:	public boost::noncopyable
{
	/***************************************************************************/
		
	virtual ~Named() {} 

	virtual std::string const & getName() const = 0;

	/***************************************************************************/
};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_NAMED_HPP__
