#ifndef __VLOG_DM_EXPRESSION_VISITOR_HPP__
#define __VLOG_DM_EXPRESSION_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct PrimaryLiteral;
struct PrimaryIdentifier;
struct BinaryOperator;

/***************************************************************************/

struct ExpressionVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( const PrimaryLiteral& _literal ) = 0;

	virtual void visit( const BinaryOperator& _operator ) = 0;
	 
	virtual void visit( const PrimaryIdentifier& _id ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct ExpressionDefaultVisitor
	:	public ExpressionVisitor
{

/***************************************************************************/

	void visit( const PrimaryLiteral& _literal ) override {}

	void visit( const BinaryOperator& _operator ) override {}

	void visit( const PrimaryIdentifier& _id ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_VISITOR_HPP__
