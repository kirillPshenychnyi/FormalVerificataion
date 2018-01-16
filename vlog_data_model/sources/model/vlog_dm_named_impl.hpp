#ifndef __VLOG_DM_NAMED_IMPL_HPP__
#define __VLOG_DM_NAMED_IMPL_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
template< typename _BaseType >
class NamedImpl
	:	public _BaseType
{

/***************************************************************************/
		
public:
		
/***************************************************************************/
		
	NamedImpl( std::string const & _name )
		:	m_name( _name )
	{}
		
	std::string const & getName() const override;

/***************************************************************************/
		
private:

/***************************************************************************/
			
	const std::string m_name;

/***************************************************************************/
};

/***************************************************************************/

template< typename _BaseType >
inline 
std::string const & 
NamedImpl< _BaseType >::getName() const
{
	return m_name;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_NAMED_IMPL_HPP__

