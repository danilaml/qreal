#include "HMLuaVisitor.h"

#include "qrtext/core/ast/node.h"
#include "qrtext/core/ast/expression.h"

#include "qrtext/lua/types/boolean.h"
#include "qrtext/lua/types/float.h"
#include "qrtext/lua/types/integer.h"
#include "qrtext/lua/types/nil.h"
#include "qrtext/lua/types/number.h"
#include "qrtext/lua/types/string.h"
#include "qrtext/lua/types/table.h"

#include "qrtext/lua/ast/assignment.h"
#include "qrtext/lua/ast/unaryMinus.h"
#include "qrtext/lua/ast/identifier.h"
#include "qrtext/lua/ast/addition.h"

#include <iostream>

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

void HMLuaVisitor::visit(const ast::UnaryMinus &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	QSharedPointer<core::ast::Expression> operand = as<core::ast::Expression>(node.operand());
	QSharedPointer<HMTypeVariable> operandTypeVariable = mTypeVars.value(operand);
	//addConstraint(operandTypeVariable, mInteger);
	//addConstraint(operandTypeVariable, mFloat);
	for (QSharedPointer<core::types::TypeExpression> constraint : mTypeConstraints.value(operandTypeVariable)->values()) {
		 addConstraint(hm, constraint);
	}
}

void HMLuaVisitor::visit(const ast::Addition &node)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
	QSharedPointer<core::ast::Expression> leftOperand = as<core::ast::Expression>(node.leftOperand());
	QSharedPointer<HMTypeVariable> leftTypeVariable = mTypeVars.value(leftOperand);
	addConstraint(leftTypeVariable, mInteger);
	addConstraint(leftTypeVariable, mFloat);
	QSharedPointer<core::ast::Expression> rightOperand = as<core::ast::Expression>(node.rightOperand());
	QSharedPointer<HMTypeVariable> rightTypeVariable = mTypeVars.value(rightOperand);
	addConstraint(rightTypeVariable, mInteger);
	addConstraint(rightTypeVariable, mFloat);
	if (mTypeVars.value(leftOperand)->isResolved() && mTypeVars.value(leftOperand)->finalType() == mInteger
			&& mTypeVars.value(rightOperand)->isResolved() && mTypeVars.value(rightOperand)->finalType() == mInteger)
	{
		addConstraint(hm, mInteger);
	} else {
		addConstraint(hm, mFloat);
	}
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

void HMLuaVisitor::visit(const ast::FieldInitialization &node)
{
//	visit(as<ast::FieldInitialization>(node)->value());
//	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
//	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
//	addConstraint(hm, type(as<ast::FieldInitialization>(node)->value()));
	Q_UNUSED(node);
}

void HMLuaVisitor::visit(const ast::TableConstructor &node)
{
//	auto tableConstructor = as<ast::TableConstructor>(node);
//	auto elementType = tableConstructor->initializers().isEmpty()
//			? any()
//			: type(tableConstructor->initializers().first());
//	auto tableType = QSharedPointer<HMTypeVariable>(new types::Table(elementType, tableConstructor->initializers().size()));
//	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
//	mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
//	addConstraint(hm, tableType);
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

void HMLuaVisitor::visit(const ast::Identifier &node)
{
	std::cout << node.name().toStdString() << std::endl;
	if (hasDeclaration(node.name())) {
//		auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
		mTypeVars.insert(as<core::ast::Expression>(mNode), mTypeVars.value(as<ast::Expression>(mIdentifierDeclarations.value(node.name()))));
//		QSharedPointer<core::ast::Expression> operand = as<core::ast::Expression>(declaration(node.name()));
//		QSharedPointer<HMTypeVariable> operandTypeVariable = mTypeVars.value(operand);
//		for (QSharedPointer<core::types::TypeExpression> constraint : mTypeConstraints.value(operandTypeVariable)->values()) {
//			addConstraint(hm, constraint);
//		}
	} else {
//		auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
//		mTypeVars.insert(as<core::ast::Expression>(mNode), hm);
//		addConstraint(hm, );
		addDeclaration(node.name(), mNode);
	}
}

void HMLuaVisitor::visit(const ast::Assignment &node)
{
	auto valueTypeVariable = mTypeVars.value(node.value());
	QSharedPointer<ast::Expression> variable = node.variable();
	QSharedPointer<HMTypeVariable> typeVariableForVariable = mTypeVars.value(variable);
	for (QSharedPointer<core::types::TypeExpression> constraint : mTypeConstraints.value(valueTypeVariable)->values()) {
		 addConstraint(typeVariableForVariable, constraint);
	}
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

bool HMLuaVisitor::hasDeclaration(const QString &identifierName) const
{
	return mIdentifierDeclarations.contains(identifierName);
}

QSharedPointer<core::ast::Node> HMLuaVisitor::declaration(const QString &identifierName) const
{
	return mIdentifierDeclarations.value(identifierName);
}

void HMLuaVisitor::addDeclaration(const QString &identifierName, const QSharedPointer<core::ast::Node> &declaration)
{
	auto hm = QSharedPointer<HMTypeVariable>(new HMTypeVariable(getNewId()));
	mTypeVars.insert(as<core::ast::Expression>(declaration), hm);
	mTypeConstraints.insert(hm, QSharedPointer<ConstrainSet>(new ConstrainSet()));
	mIdentifierDeclarations.insert(identifierName, declaration);
}
