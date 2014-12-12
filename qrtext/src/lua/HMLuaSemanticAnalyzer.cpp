#include "qrtext/src/lua/HMLuaSemanticAnalyzer.h"

#include "qrtext/src/lua/luaGeneralizationsTable.h"

#include "qrtext/src/hm/HMTypeVariable.h"
#include "qrtext/core/types/any.h"

#include "qrtext/lua/types/boolean.h"
#include "qrtext/lua/types/float.h"
#include "qrtext/lua/types/function.h"
#include "qrtext/lua/types/integer.h"
#include "qrtext/lua/types/nil.h"
#include "qrtext/lua/types/number.h"
#include "qrtext/lua/types/string.h"
#include "qrtext/lua/types/table.h"

#include "qrtext/lua/ast/assignment.h"
#include "qrtext/lua/ast/block.h"
#include "qrtext/lua/ast/fieldInitialization.h"
#include "qrtext/lua/ast/functionCall.h"
#include "qrtext/lua/ast/identifier.h"
#include "qrtext/lua/ast/indexingExpression.h"
#include "qrtext/lua/ast/tableConstructor.h"

#include "qrtext/lua/ast/unaryMinus.h"
#include "qrtext/lua/ast/not.h"
#include "qrtext/lua/ast/length.h"
#include "qrtext/lua/ast/bitwiseNegation.h"

#include "qrtext/lua/ast/addition.h"
#include "qrtext/lua/ast/subtraction.h"
#include "qrtext/lua/ast/multiplication.h"
#include "qrtext/lua/ast/division.h"
#include "qrtext/lua/ast/integerDivision.h"
#include "qrtext/lua/ast/exponentiation.h"
#include "qrtext/lua/ast/modulo.h"
#include "qrtext/lua/ast/bitwiseAnd.h"
#include "qrtext/lua/ast/bitwiseXor.h"
#include "qrtext/lua/ast/bitwiseOr.h"
#include "qrtext/lua/ast/bitwiseRightShift.h"
#include "qrtext/lua/ast/bitwiseLeftShift.h"
#include "qrtext/lua/ast/concatenation.h"
#include "qrtext/lua/ast/lessThan.h"
#include "qrtext/lua/ast/greaterThan.h"
#include "qrtext/lua/ast/lessOrEqual.h"
#include "qrtext/lua/ast/greaterOrEqual.h"
#include "qrtext/lua/ast/equality.h"
#include "qrtext/lua/ast/inequality.h"
#include "qrtext/lua/ast/logicalAnd.h"
#include "qrtext/lua/ast/logicalOr.h"

#include "qrtext/lua/ast/integerNumber.h"
#include "qrtext/lua/ast/floatNumber.h"
#include "qrtext/lua/ast/true.h"
#include "qrtext/lua/ast/false.h"
#include "qrtext/lua/ast/nil.h"
#include "qrtext/lua/ast/string.h"

#include <iostream>

using namespace qrtext::lua::details;
using namespace qrtext::core;

HMLuaSemanticAnalyzer::HMLuaSemanticAnalyzer(QList<Error> &errors)
	: HMSemanticAnalyzer(QSharedPointer<GeneralizationsTableInterface>(new LuaGeneralizationsTable()), errors)
{
//	mBoolean = core::wrap(new types::Boolean());
//	mFloat = core::wrap(new types::Float());
//	mInteger = core::wrap(new types::Integer());
//	mNil = core::wrap(new types::Nil());
//	mString = core::wrap(new types::String());
}

QSharedPointer<ast::Node> HMLuaSemanticAnalyzer::analyze(const QSharedPointer<ast::Node> &root)
{
	if (!root) {
		return root;
	}

	analyzeNode(root);

	mVarTypes = mVisitor.getTypeVars();
	mTypeConstraints = mVisitor.getTypeConstraints();

	solveConstraints();

	return root;
}


QSharedPointer<types::TypeExpression> HMLuaSemanticAnalyzer::type(const QSharedPointer<ast::Node> &expression) const
{
	auto castedExpression = as<ast::Expression>(expression);
	std::cout << mVarTypes.count() << std::endl;
	if (mVarTypes.contains(castedExpression)) {
		std::cout << "return type " << mTypeConstraints.value(mVarTypes.value(castedExpression))->values().at(0)->toString().toStdString() << std::endl;
		return mTypeConstraints.value(mVarTypes.value(castedExpression))->values().at(0); // for now
	} else {
		std::cout << "return type Any" << std::endl;
		return core::wrap(new core::types::Any());
	}
}

void HMLuaSemanticAnalyzer::addIntrinsicFunction(const QString &name, const QSharedPointer<types::Function> &type)
{
	mIntrinsicFunctions.insert(name, type);
}

void HMLuaSemanticAnalyzer::solveConstraints()
{
	for (auto type : mTypeConstraints.keys()) {
		solveConstraints(type);
	}
}

QSharedPointer<types::TypeExpression> HMLuaSemanticAnalyzer::solveConstraints(QSharedPointer<HMTypeVariable> &type)
{
	auto constraints = mTypeConstraints.value(type)->values();

	std::cout << constraints.at(0)->toString().toStdString() << std::endl;

	if (constraints.isEmpty()) {
//		reportError(operation, QObject::tr("Type mismatch."));
	}
	QSharedPointer<core::types::TypeExpression> unifiedType = any();
	for (auto c : constraints) {
		unifiedType = unify(unifiedType, c);
	}
	std::cout << "return type " << unifiedType->toString().toStdString() << std::endl;
	return unifiedType;
}

bool HMLuaSemanticAnalyzer::isOfBaseType(QSharedPointer<core::types::TypeExpression> &expr) const
{
	return !(expr->is<HMTypeVariable>() || expr->is<core::types::Any>());
}

QSharedPointer<types::TypeExpression> HMLuaSemanticAnalyzer::unify(QSharedPointer<core::types::TypeExpression> &leftexpr
                                                                   , QSharedPointer<core::types::TypeExpression> &rightexpr)
{
	if (rightexpr->is<HMTypeVariable>()) {
		auto rightvar = as<HMTypeVariable>(rightexpr);
		return unify(leftexpr, rightvar);
	} else if (leftexpr->is<core::types::Any>()) {
		return rightexpr;
	} else if (isOfBaseType(leftexpr)) {
		if (generalizationsTable().isGeneralization(leftexpr, rightexpr) || rightexpr->is<core::types::Any>()) {
			return leftexpr; // right or left? right is more general one
//			return rightexpr;
		} else {
			return leftexpr;
			//report error? type mismatch?
		}
	} else {
		return rightexpr; //not needed?
	}
}

QSharedPointer<types::TypeExpression> HMLuaSemanticAnalyzer::unify(QSharedPointer<core::types::TypeExpression> &leftexpr
                                                                   , QSharedPointer<HMTypeVariable> &rightexpr)
{
	if (leftexpr->is<core::types::Any>()) {
		return rightexpr;
	} else if (isOfBaseType(leftexpr)) {
		return leftexpr;
	} else {
		return rightexpr; // rewrite this.
	}
}

void HMLuaSemanticAnalyzer::substitute(QSharedPointer<HMTypeVariable> &type, QSharedPointer<HMTypeVariable> &with)
{
	//TODO: implement substitution
}

void HMLuaSemanticAnalyzer::analyzeNode(QSharedPointer<core::ast::Node> const &node)
{
	for (auto child : node->children()) {
		if (!child.isNull()) {
			analyzeNode(child);
		}
	}
//	std::cout << "return type "
	mVisitor.setCurrentNode(node);
	node->accept(mVisitor);
}

//void HMLuaSemanticAnalyzer::addIntrinsicFunction(QString const &name, QSharedPointer<types::Function> const &type)
//{
//	mIntrinsicFunctions.insert(name, type);
//}

//void HMLuaSemanticAnalyzer::analyzeNode(QSharedPointer<core::ast::Node> const &node)
//{
//	if (node->is<ast::Assignment>()) {
//		auto assignment = as<ast::Assignment>(node);
//		constrainAssignment(assignment, assignment->variable(), assignment->value());
//	} else if (node->is<ast::Identifier>()) {
//		auto identifier = as<ast::Identifier>(node);
//		if (hasDeclaration(identifier->name())) {
//			unify(identifier, declaration(identifier->name()));
//		} else {
//			assign(identifier, any());
//			addDeclaration(identifier->name(), identifier);
//		}
//	} else if (node->is<ast::IntegerNumber>()) {
//		assign(node, mInteger);
//	} else if (node->is<ast::FloatNumber>()) {
//		assign(node, mFloat);
//	} else if (node->is<ast::True>() || node->is<ast::False>()) {
//		assign(node, mBoolean);
//	} else if (node->is<ast::String>()) {
//		assign(node, mString);
//	} else if (node->is<ast::Nil>()) {
//		assign(node, mNil);
//	} else if (node->is<ast::UnaryOperator>()) {
//		analyzeUnaryOperator(node);
//	} else if (node->is<ast::BinaryOperator>()) {
//		analyzeBinaryOperator(node);
//	} else if (node->is<ast::FunctionCall>()) {
//		analyzeFunctionCall(node);
//	} else if (node->is<ast::FieldInitialization>()) {
//		assign(node, type(as<ast::FieldInitialization>(node)->value()));
//	} else if (node->is<ast::TableConstructor>()) {
//		auto tableConstructor = as<ast::TableConstructor>(node);
//		auto elementType = tableConstructor->initializers().isEmpty()
//				? any()
//				: type(tableConstructor->initializers().first());

//		auto tableType = core::wrap(new types::Table(elementType, tableConstructor->initializers().size()));

//		assign(node, tableType);
//	} else if (node->is<ast::IndexingExpression>()) {
//		auto indexingExpression = as<ast::IndexingExpression>(node);
//		auto table = indexingExpression->table();
//		if (type(table)->is<types::Table>()) {
//			auto tableElementType = as<types::Table>(type(table))->elementType();
//			assign(node, tableElementType);
//		} else {
//			/// It's a table, but we see it for the first time so know nothing about it.
//			auto elementType = QSharedPointer<core::types::TypeVariable>(new core::types::TypeVariable());
//			constrain(table, table, { core::wrap(new types::Table(elementType, -1)) });
//			assign(node, elementType);
//		}
//	} else if (node->is<ast::Block>()) {
//		// do nothing.
//	} else {
//		reportError(node, QObject::tr("This construction is not supported by semantic analysis"));
//	}
//}

//void HMLuaSemanticAnalyzer::analyzeUnaryOperator(QSharedPointer<core::ast::Node> const &node)
//{
//	auto operand = as<core::ast::UnaryOperator>(node)->operand();
//	if (node->is<ast::UnaryMinus>()) {
//		constrain(node, operand, {mInteger, mFloat});
//		unify(node, operand);
//	} else if (node->is<ast::Not>()) {
//		assign(node, mBoolean);
//	} else if (node->is<ast::Length>()) {
//		auto genericTableType = core::wrap(new types::Table(any(), -1));
//		constrain(node, operand, {mString, genericTableType});
//	} else if (node->is<ast::BitwiseNegation>()) {
//		/// @todo Support coercion, as in http://www.lua.org/work/doc/manual.html#3.4.3
//		constrain(node, operand, {mInteger});
//		assign(node, mInteger);
//	}
//}

//void HMLuaSemanticAnalyzer::analyzeBinaryOperator(QSharedPointer<core::ast::Node> const &node)
//{
//	auto left = as<core::ast::BinaryOperator>(node)->leftOperand();
//	auto right = as<core::ast::BinaryOperator>(node)->rightOperand();

//	if (node->is<ast::Addition>() || node->is<ast::Subtraction>() || node->is<ast::Multiplication>()) {
//		constrain(node, left, {mInteger, mFloat});
//		constrain(node, right, {mInteger, mFloat});

//		/// @todo "If both operands are integers, the operation is performed over integers and the result is an integer.
//		///       Otherwise, if both operands are numbers or strings that can be converted to numbers (see §3.4.3), then
//		///       they are converted to floats, the operation is performed following the usual rules for floating-point
//		///       arithmetic (usually the IEEE 754 standard), and the result is a float."
//		///       (http://www.lua.org/work/doc/manual.html#3.4.1)
//		///       Code below is a hack, here we need more complex constraints over type variables.
//		if (typeVariable(left)->isResolved() && typeVariable(left)->finalType() == mInteger
//				&& typeVariable(right)->isResolved() && typeVariable(right)->finalType() == mInteger)
//		{
//			assign(node, mInteger);
//		} else {
//			assign(node, mFloat);
//		}
//	} else if (node->is<ast::Division>() || node->is<ast::Exponentiation>()) {
//		constrain(node, left, {mFloat});
//		constrain(node, right, {mFloat});
//		assign(node, mFloat);
//	} else if (node->is<ast::IntegerDivision>() || node->is<ast::Modulo>()) {
//		constrain(node, left, {mInteger});
//		constrain(node, right, {mInteger});
//		assign(node, mInteger);
//	} else if (node->is<ast::BitwiseAnd>() || node->is<ast::BitwiseXor>() || node->is<ast::BitwiseOr>()
//			|| node->is<ast::BitwiseRightShift>() || node->is<ast::BitwiseLeftShift>())
//	{
//		constrain(node, left, {mInteger});
//		constrain(node, right, {mInteger});
//		assign(node, mInteger);
//	} else if (node->is<ast::Equality>() || node->is<ast::Inequality>()) {
//		assign(node, mBoolean);
//	} else if (node->is<ast::LessThan>() || node->is<ast::LessOrEqual>() || node->is<ast::GreaterThan>()
//			|| node->is<ast::GreaterOrEqual>())
//	{
//		constrain(node, left, {mInteger, mFloat, mString});
//		constrain(node, right, {mInteger, mFloat, mString});
//		assign(node, mBoolean);
//	} else if (node->is<ast::LogicalAnd>() || node->is<ast::LogicalOr>()) {
//		/// @todo Actually, Lua type system allows logical operators to return everything:
//		///       "The conjunction operator 'and' returns its first argument if this value is false or nil; otherwise,
//		///       'and' returns its second argument. The disjunction operator 'or' returns its first argument if this
//		///       value is different from nil and false; otherwise, 'or' returns its second argument.
//		///       (http://www.lua.org/work/doc/manual.html#3.4.5)
//		assign(node, mBoolean);
//	} else if (node->is<ast::Concatenation>()) {
//		assign(node, mString);
//	}
//}

//void HMLuaSemanticAnalyzer::constrainAssignment(QSharedPointer<core::ast::Node> const &operation
//		, QSharedPointer<core::ast::Node> const &lhs, QSharedPointer<core::ast::Node> const &rhs)
//{
//	if (!lhs->is<ast::Identifier>() && !lhs->is<ast::IndexingExpression>()) {
//		reportError(operation, QObject::tr("Incorrect assignment, only variables and tables can be assigned to."));
//		return;
//	}

//	auto lhsType = typeVariable(lhs);
//	auto rhsType = typeVariable(rhs);
//	bool wasCoercion = false;
//	if (!lhsType || !rhsType) {
//		// Most likely error is already reported.
//		return;
//	}

//	lhsType->constrainAssignment(rhsType, generalizationsTable(), &wasCoercion);
//	if (lhsType->isEmpty()) {
//		reportError(operation, QObject::tr("Left and right operand have mismatched types."));
//	} else {
//		if (wasCoercion) {
//			requestRecheck();
//		}
//	}
//}

//void HMLuaSemanticAnalyzer::analyzeFunctionCall(QSharedPointer<core::ast::Node> const &node)
//{
//	auto functionCall = as<ast::FunctionCall>(node);
//	auto function = functionCall->function();
//	if (!function->is<ast::Identifier>()) {
//		reportError(node, QObject::tr("Indirect function calls are not supported"));
//		assign(function, any());
//		assign(node, any());
//		return;
//	}

//	auto name = as<ast::Identifier>(function)->name();
//	if (!mIntrinsicFunctions.contains(name)) {
//		reportError(node, QObject::tr("Unknown function"));
//		assign(function, any());
//		assign(node, any());
//		return;
//	}

//	assign(function, mIntrinsicFunctions.value(name));
//	assign(node, mIntrinsicFunctions.value(name)->returnType());

//	auto formalParameters = mIntrinsicFunctions.value(name)->formalParameters();
//	auto actualParameters = functionCall->arguments();
//	if (formalParameters.size() < actualParameters.size()) {
//		reportError(node, QObject::tr("Too many parameters, %1 expected").arg(formalParameters.size()));
//		return;
//	} else if (formalParameters.size() > actualParameters.size()) {
//		reportError(node, QObject::tr("Not enough parameters, %1 expected").arg(formalParameters.size()));
//		return;
//	} else {
//		for (int i = 0; i < formalParameters.size(); ++i) {
//			constrain(actualParameters[i], actualParameters[i], {formalParameters[i]});
//		}
//	}
//}

//QMap<QString, QSharedPointer<types::TypeExpression>> HMLuaSemanticAnalyzer::variableTypes() const
//{
//	QMap<QString, QSharedPointer<qrtext::core::types::TypeExpression>> result = SemanticAnalyzer::variableTypes();
//	for (QString const &identifier : mIntrinsicFunctions.keys()) {
//		result.remove(identifier);
//	}

//	return result;
//}
