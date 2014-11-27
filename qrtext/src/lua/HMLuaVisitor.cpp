#include "HMLuaVisitor.h"

#include "qrtext/lua/types/boolean.h"
#include "qrtext/lua/types/float.h"
#include "qrtext/lua/types/function.h"
#include "qrtext/lua/types/integer.h"
#include "qrtext/lua/types/nil.h"
#include "qrtext/lua/types/number.h"
#include "qrtext/lua/types/string.h"
#include "qrtext/lua/types/table.h"

using namespace qrtext;
using namespace lua;

HMLuaVisitor::HMLuaVisitor() : i(0)
{
}

QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> HMLuaVisitor::getTypeVars() const
{
	return mTypeVars;
}

QHash<QSharedPointer<HMTypeVariable>, QSet<QSharedPointer<core::types::TypeExpression> > > HMLuaVisitor::getTypeConstraints() const
{
	return mTypeConstraints;
}

int HMLuaVisitor::getNewId()
{
	return i++;
}

	virtual void visit(ast::Number const &node)
{
	QSet<QSharedPointer<core::types::TypeExpression> > value = new QSet<QSharedPointer<lua::types::Number> >;
	value.insert(core::wrap(new types::Integer()));
	value.insert(core::wrap(new types::Float()));
	HMLuaVisitor::mTypeConstraints.insert(QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId)), value);
}
//	virtual void visit(ast::UnaryMinus const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::Not const &node)                 { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseNegation const &node)     { Q_UNUSED(node); }
//	virtual void visit(ast::Length const &node)              { Q_UNUSED(node); }
//	virtual void visit(ast::LogicalAnd const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::LogicalOr const &node)           { Q_UNUSED(node); }
//	virtual void visit(ast::Addition const &node)            { Q_UNUSED(node); }
//	virtual void visit(ast::Subtraction const &node)         { Q_UNUSED(node); }
//	virtual void visit(ast::Multiplication const &node)      { Q_UNUSED(node); }
//	virtual void visit(ast::Division const &node)            { Q_UNUSED(node); }
//	virtual void visit(ast::IntegerDivision const &node)     { Q_UNUSED(node); }
//	virtual void visit(ast::Modulo const &node)              { Q_UNUSED(node); }
//	virtual void visit(ast::Exponentiation const &node)      { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseAnd const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseOr const &node)           { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseXor const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseLeftShift const &node)    { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseRightShift const &node)   { Q_UNUSED(node); }
//	virtual void visit(ast::Concatenation const &node)       { Q_UNUSED(node); }
//	virtual void visit(ast::Equality const &node)            { Q_UNUSED(node); }
//	virtual void visit(ast::LessThan const &node)            { Q_UNUSED(node); }
//	virtual void visit(ast::LessOrEqual const &node)         { Q_UNUSED(node); }
//	virtual void visit(ast::Inequality const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::GreaterThan const &node)         { Q_UNUSED(node); }
//	virtual void visit(ast::GreaterOrEqual const &node)      { Q_UNUSED(node); }
	virtual void visit(ast::IntegerNumber const &node)
{

}
	virtual void visit(ast::FloatNumber const &node)         { Q_UNUSED(node); }
//	virtual void visit(ast::FieldInitialization const &node) { Q_UNUSED(node); }
//	virtual void visit(ast::TableConstructor const &node)    { Q_UNUSED(node); }
	virtual void visit(ast::String const &node)              { Q_UNUSED(node); }
//	virtual void visit(ast::True const &node)                { Q_UNUSED(node); }
//	virtual void visit(ast::False const &node)               { Q_UNUSED(node); }
//	virtual void visit(ast::Nil const &node)                 { Q_UNUSED(node); }
//	virtual void visit(ast::Identifier const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::FunctionCall const &node)        { Q_UNUSED(node); }
//	virtual void visit(ast::MethodCall const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::Assignment const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::Block const &node)               { Q_UNUSED(node); }
//	virtual void visit(ast::IndexingExpression const &node)  { Q_UNUSED(node); }
