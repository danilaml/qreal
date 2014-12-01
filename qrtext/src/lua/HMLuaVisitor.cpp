#include "HMLuaVisitor.h"

#include "qrtext/core/ast/node.h"
#include "qrtext/core/ast/expression.h"

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
	mBoolean = core::wrap(new types::Boolean());
	mFloat = core::wrap(new types::Float());
	mInteger = core::wrap(new types::Integer());
	mNil = core::wrap(new types::Nil());
	mString = core::wrap(new types::String());
}

void HMLuaVisitor::setCurrentNode(const QSharedPointer<core::ast::Node> &node)
{
	mNode = node;
}

QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> HMLuaVisitor::getTypeVars() const
{
	return mTypeVars;
}

QHash<QSharedPointer<HMTypeVariable>, QSharedPointer<HMLuaVisitor::ConstrainSet> > HMLuaVisitor::getTypeConstraints() const
{
	return mTypeConstraints;
}

void HMLuaVisitor::visit(const ast::IntegerNumber &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mInteger);
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::FloatNumber &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mFloat);
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::String &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mString);
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::True &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mBoolean);
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::False &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mBoolean);
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::Nil &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	addConstraint(hm, mNil);
	Q_UNUSED(node);
}

int HMLuaVisitor::getNewId()
{
	return i++;
}

void HMLuaVisitor::addConstraint(QSharedPointer<HMTypeVariable> &to, QSharedPointer<core::types::TypeExpression> &constraint)
{
	if (!mTypeConstraints.contains(to)) {
		mTypeConstraints.insert(to, QSharedPointer<ConstrainSet>(new ConstrainSet()));
	}
	mTypeConstraints.value(to)->insert(constraint);
}
