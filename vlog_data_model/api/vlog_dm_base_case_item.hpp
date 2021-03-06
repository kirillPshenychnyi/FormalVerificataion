#ifndef __VLOG_DM_BASE_CASE_ITEM_HPP__
#define __VLOG_DM_BASE_CASE_ITEM_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Statement;
struct CaseItemVisitor;

/***************************************************************************/

struct BaseCaseItem
	:	public Located
{

/***************************************************************************/

	virtual Statement const & getStatement() const = 0;

	virtual void accept( CaseItemVisitor & _itemVisitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BASE_CASE_ITEM_HPP__
