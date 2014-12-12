#include "luaHMSemanticAnalyzerTest.h"

#include "qrtext/core/types/any.h"

#include "qrtext/lua/ast/assignment.h"
#include "qrtext/lua/ast/block.h"
#include "qrtext/lua/ast/functionCall.h"
#include "qrtext/lua/ast/indexingExpression.h"
#include "qrtext/lua/ast/unaryMinus.h"

#include "qrtext/lua/types/integer.h"
#include "qrtext/lua/types/float.h"
#include "qrtext/lua/types/string.h"
#include "qrtext/lua/types/table.h"
#include "qrtext/lua/types/boolean.h"
#include "qrtext/lua/types/function.h"
#include "qrtext/lua/types/nil.h"
#include "qrtext/lua/types/number.h"

#include "gtest/gtest.h"

using namespace qrTest;
using namespace qrtext;
using namespace qrtext::lua;
using namespace qrtext::lua::details;
using namespace qrtext::lua::types;

void LuaHMSemanticAnalyzerTest::SetUp()
{
	mAnalyzer.reset(new HMLuaSemanticAnalyzer(mErrors));
	mParser.reset(new LuaParser(mErrors));
	mLexer.reset(new LuaLexer(mErrors));
}

QSharedPointer<qrtext::core::ast::Node> LuaHMSemanticAnalyzerTest::parse(QString const &code)
{
	return mParser->parse(mLexer->tokenize(code), mLexer->userFriendlyTokenNames());
}

TEST_F(LuaHMSemanticAnalyzerTest, integerNumber)
{
	auto tree = parse("239");
	mAnalyzer->analyze(tree);
	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<Integer>());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<Number>());
}

TEST_F(LuaHMSemanticAnalyzerTest, floatNumber)
{
	auto tree = parse("125.25");
	mAnalyzer->analyze(tree);
	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<Float>());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<Number>());
}

TEST_F(LuaHMSemanticAnalyzerTest, string)
{
	auto tree = parse("\"Hello\"");
	mAnalyzer->analyze(tree);
	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<String>());
}

TEST_F(LuaHMSemanticAnalyzerTest, booleanCheck)
{
	auto treeTrue = parse("true");
	auto treeFalse = parse("false");
	mAnalyzer->analyze(treeTrue);
	mAnalyzer->analyze(treeFalse);
	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(treeTrue)->is<Boolean>());
	EXPECT_TRUE(mAnalyzer->type(treeFalse)->is<Boolean>());
}

TEST_F(LuaHMSemanticAnalyzerTest, nil)
{
	auto tree = parse("nil");
	mAnalyzer->analyze(tree);
	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(tree)->is<Nil>());
}

TEST_F(LuaHMSemanticAnalyzerTest, assignment)
{
	auto tree = parse("a = 123");

	auto variable = as<lua::ast::Assignment>(tree)->variable();
	auto value = as<lua::ast::Assignment>(tree)->value();

	mAnalyzer->analyze(tree);

	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(variable)->is<Integer>());
	EXPECT_TRUE(mAnalyzer->type(value)->is<Integer>());
}

TEST_F(LuaHMSemanticAnalyzerTest, unaryOperator)
{
	auto tree = parse("-123");

	mAnalyzer->analyze(tree);

	EXPECT_TRUE(mErrors.empty());
	EXPECT_TRUE(mAnalyzer->type(as<lua::ast::UnaryMinus>(tree))->is<Integer>());
}

TEST_F(LuaHMSemanticAnalyzerTest, addition)
{
	auto tree = parse("5+5");

	mAnalyzer->analyze(tree);

	EXPECT_TRUE(mErrors.empty());
	//EXPECT_TRUE(mAnalyzer->type(as<lua::ast::Addition>(tree))->is<Integer>());
}


