#ifndef __TOOLS_ORDERED_MAPPING_HPP__
#define __TOOLS_ORDERED_MAPPING_HPP__

/***************************************************************************/

#include <unordered_map>
#include <vector>		
#include <cassert>

/***************************************************************************/

namespace Tools {
namespace Collections {

/***************************************************************************/

template < 
		typename _Key
	,	typename _Value 
	,	typename _Hasher = std::hash< _Key >
	,	typename _Comparator = std::equal_to< _Key >
	,	typename _KeyKiller = std::identity< _Key >
	,	typename _ValueKiller = std::identity< _Value >
	>
class OrderedMapping
{

/***************************************************************************/

	typedef
		std::pair< _Key, _Value > 
		value_type;
	
	typedef 
		_Key 
		key_type;

	typedef
		std::vector< value_type >
		Vector;

	typedef
		std::unordered_map< _Key, _Value, _Hasher, _Comparator >
		Map;

	typedef
		typename Map::const_iterator
		iterator;

/***************************************************************************/

public:

/***************************************************************************/

	Map const & asMap() const
	{
		return m_map;
	}

	Vector const & asVector() const
	{
		return m_vector;
	}

/***************************************************************************/

	iterator begin() const
	{
		return m_vector.begin();
	}

	iterator end() const
	{
		return m_vector.end();
	}

/***************************************************************************/

	_Value const & operator [] ( int _idx ) const
	{
		assert( _idx >= 0 && _idx < m_vector.size() );

		return m_vector[ _idx ].second();
	}

/***************************************************************************/

	bool hasKey( key_type const & _key ) const
	{	
		return m_map.find( _key ) != m_map.end();
	}

/***************************************************************************/

	iterator findByKey( key_type _key ) const
	{
		return m_map.find( _key );
	}

/***************************************************************************/

	bool add( _Key const & _key, _Value & _value )
	{
		value_type value = std::make_pair( _key, _value );

		bool insertResult = m_map.insert( value ).second;

		if( !insertResult )
			return false;

		m_vector.push_back( value );

		return true;
	}

/***************************************************************************/

	void clear()
	{
		_ValueKiller valueKiller;
		_KeyKiller keyKiller;

		for( value_type value : m_vector )
		{
			keyKiller( value->first );
			valueKiller( value->second );
		}

		m_map.clear();
		m_vector.clear();
	}

/***************************************************************************/

	int size() const
	{
		return m_vector.size();
	}

/***************************************************************************/

private:

/***************************************************************************/

	Vector m_vector;

	Map m_map;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__TOOLS_ORDERED_MAPPING_HPP__

