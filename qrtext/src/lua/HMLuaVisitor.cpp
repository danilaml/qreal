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

QHash<QSharedPointer<HMTypeVariable>, QSet<QSharedPointer<core::types::TypeExpression> > > HMLuaVisitor::getTypeConstraints() const
{
	return mTypeConstraints;
}

int HMLuaVisitor::getNewId()
{
	return i++;
}
