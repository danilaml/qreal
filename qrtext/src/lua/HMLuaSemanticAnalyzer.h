#pragma once

#include "qrtext/src/hm/HMSemanticAnalyzer.h"
#include "qrtext/src/lua/HMLuaVisitor.h"

#include "qrtext/declSpec.h"

namespace qrtext {
namespace lua {
namespace details {

class QRTEXT_EXPORT HMLuaSemanticAnalyzer : public HMSemanticAnalyzer
{
public:
//	HMLuaSemanticAnalyzer(QSharedPointer<GeneralizationsTableInterface> const &generalizationsTable
//	                   , QList<Error> &errors);
	HMLuaSemanticAnalyzer(QList<Error> &errors);

	QSharedPointer<core::ast::Node> analyze(QSharedPointer<core::ast::Node> const &root);

	QSharedPointer<types::TypeExpression> type(QSharedPointer<core::ast::Node> const &expression) const;


private:
	void solveConstraints();
	QSharedPointer<core::types::TypeExpression> solveConstraints(QSharedPointer<HMTypeVariable> &type);
	bool isOfBaseType(QSharedPointer<core::types::TypeExpression> &expr) const;
	QSharedPointer<core::types::TypeExpression> unify(QSharedPointer<core::types::TypeExpression> &leftexpr
                                                      , QSharedPointer<core::types::TypeExpression> &rightexpr);
	void substitute(QSharedPointer<HMTypeVariable> &type, QSharedPointer<HMTypeVariable> &with);

	HMLuaVisitor mVisitor;
	QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> mVarTypes;
	QHash<QSharedPointer<HMTypeVariable>, QSet<QSharedPointer<core::types::TypeExpression>>> mTypeConstraints;


};

}
}
}
