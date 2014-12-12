#pragma once

#include <QSharedPointer>

#include "qrtext/lua/types/function.h"

#include "qrtext/lua/luaAstVisitorInterface.h"
#include "qrtext/core/types/typeExpression.h"
#include "qrtext/src/hm/HMTypeVariable.h"

namespace qrtext {
namespace lua {

class HMLuaVisitor : public LuaAstVisitorInterface
{
public:
	typedef QSet<QSharedPointer<core::types::TypeExpression>> ConstrainSet;
	HMLuaVisitor();

	void setCurrentNode(const QSharedPointer<core::ast::Node> &node);
	QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> getTypeVars() const;
	QHash<QSharedPointer<HMTypeVariable>, QSharedPointer<ConstrainSet>> getTypeConstraints() const;

//	virtual void visit(ast::Number const &node)              { Q_UNUSED(node); }
	virtual void visit(ast::UnaryMinus const &node);
//	virtual void visit(ast::Not const &node)                 { Q_UNUSED(node); }
//	virtual void visit(ast::BitwiseNegation const &node)     { Q_UNUSED(node); }
//	virtual void visit(ast::Length const &node)              { Q_UNUSED(node); }
//	virtual void visit(ast::LogicalAnd const &node)          { Q_UNUSED(node); }
//	virtual void visit(ast::LogicalOr const &node)           { Q_UNUSED(node); }
	virtual void visit(ast::Addition const &node);
	virtual void visit(ast::Subtraction const &node);
	virtual void visit(ast::Multiplication const &node);
	virtual void visit(ast::Division const &node);
	virtual void visit(ast::IntegerDivision const &node);
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
	virtual void visit(ast::IntegerNumber const &node);
	virtual void visit(ast::FloatNumber const &node);
	virtual void visit(ast::FieldInitialization const &node);
//	virtual void visit(ast::TableConstructor const &node)    { Q_UNUSED(node); }
	virtual void visit(ast::String const &node);
	virtual void visit(ast::True const &node);
	virtual void visit(ast::False const &node);
	virtual void visit(ast::Nil const &node);
	virtual void visit(ast::Identifier const &node);
//	virtual void visit(ast::FunctionCall const &node)        { Q_UNUSED(node); }
//	virtual void visit(ast::MethodCall const &node)          { Q_UNUSED(node); }
	virtual void visit(ast::Assignment const &node);
//	virtual void visit(ast::Block const &node)               { Q_UNUSED(node); }
//	virtual void visit(ast::IndexingExpression const &node)  { Q_UNUSED(node); }

private:
	int getNewId();
	void addConstraint(QSharedPointer<HMTypeVariable> &to, QSharedPointer<core::types::TypeExpression> &constraint);

	/// Returns true, if given identifier was declared (or seen before).
	bool hasDeclaration(QString const &identifierName) const;

	/// Returns expression where given identifier was declared or encountered first.
	QSharedPointer<core::ast::Node> declaration(QString const &identifierName) const;

	/// Adds declaration of a given identifier to identifiers table.
	void addDeclaration(QString const &identifierName, QSharedPointer<core::ast::Node> const &declaration);

	int i;
	QSharedPointer<core::ast::Node> mNode; //current node
	QHash<QSharedPointer<core::ast::Expression>, QSharedPointer<HMTypeVariable>> mTypeVars;
	QHash<QSharedPointer<HMTypeVariable>, QSharedPointer<ConstrainSet>> mTypeConstraints;
	QHash<QString, QSharedPointer<core::ast::Node>> mIdentifierDeclarations;
	QHash<QString, QSharedPointer<types::Function>> mIntrinsicFunctions;

	QSharedPointer<core::types::TypeExpression> mBoolean;
	QSharedPointer<core::types::TypeExpression> mFloat;
	QSharedPointer<core::types::TypeExpression> mInteger;
	QSharedPointer<core::types::TypeExpression> mNil;
	QSharedPointer<core::types::TypeExpression> mString;

};

}
}
