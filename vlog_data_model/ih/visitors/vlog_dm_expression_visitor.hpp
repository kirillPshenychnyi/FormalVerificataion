#ifndef __VLOG_DM_EXPRESSION_VISITOR_HPP__
#define __VLOG_DM_EXPRESSION_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct PrimaryLiteral;

/***************************************************************************/

struct ExpressionVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( const PrimaryLiteral& _literal ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct ExpressionDefaultVisitor
	:	public ExpressionVisitor
{

/***************************************************************************/

	void visit( const PrimaryLiteral& _literal ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_VISITOR_HPP__
