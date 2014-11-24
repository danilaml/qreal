#include "HMLuaVisitor.h"

using namespace qrtext;
using namespace lua;

HMLuaVisitor::HMLuaVisitor()
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
