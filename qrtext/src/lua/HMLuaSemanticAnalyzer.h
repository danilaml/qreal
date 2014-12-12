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
	explicit HMLuaSemanticAnalyzer(QList<Error> &errors);

	QSharedPointer<core::ast::Node> analyze(QSharedPointer<core::ast::Node> const &root);

	QSharedPointer<core::types::TypeExpression> type(QSharedPointer<core::ast::Node> const &expression) const;

	/// Registers external (intrinsic for a language) function in interpreter.
	/// @param name - name of a function.
	/// @param type - type of a function.
	void addIntrinsicFunction(QString const &name, QSharedPointer<types::Function> const &type);


private:
	void analyzeNode(QSharedPointer<core::ast::Node> const &node) override;
	void solveConstraints();
	QSharedPointer<core::types::TypeExpression> solveConstraints(QSharedPointer<HMTypeVariable> &type);
	bool isOfBaseType(QSharedPointer<core::types::TypeExpression> &expr) const;
	QSharedPointer<core::types::TypeExpression> unify(QSharedPointer<core::types::TypeExpression> &leftexpr, QSharedPointer<core::types::TypeExpression> &rightexpr);
	QSharedPointer<core::types::TypeExpression> unify(QSharedPointer<core::types::TypeExpression> &leftexpr, QSharedPointer<HMTypeVariable> &rightexpr);
	void substitute(QSharedPointer<HMTypeVariable> &type, QSharedPointer<HMTypeVariable> &with);

	HMLuaVisitor mVisitor;
	QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> mVarTypes;
	QHash<QSharedPointer<HMTypeVariable>, QSharedPointer<HMLuaVisitor::ConstrainSet>> mTypeConstraints;
	QHash<QString, QSharedPointer<types::Function>> mIntrinsicFunctions;

};

}
}
}
