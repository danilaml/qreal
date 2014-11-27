#include "HMLuaVisitor.h"

using namespace qrtext;
using namespace lua;

HMLuaVisitor::HMLuaVisitor() : i(0)
{
}

QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> HMLuaVisitor::getTypeVars() const
{
	return mTypeVars;
}

QHash<QSharedPointer<HMTypeVariable>, QSharedPointer<HMLuaVisitor::ConstrainSet> > HMLuaVisitor::getTypeConstraints() const
{
	return mTypeConstraints;
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
