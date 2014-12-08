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

//TEST_F(LuaHMSemanticAnalyzerTest, booleanCheck)
//{
//	auto tree = parse("1 == 1");
//	mAnalyzer->analyze(tree);
//	EXPECT_TRUE(mErrors.empty());
//	EXPECT_TRUE(mAnalyzer->type(tree)->is<Boolean>());
//}

//TEST_F(LuaHMSemanticAnalyzerTest, assignment)
//{
//	auto tree = parse("a = 123");

//	auto variable = as<lua::ast::Assignment>(tree)->variable();
//	auto value = as<lua::ast::Assignment>(tree)->value();

//	mAnalyzer->analyze(tree);

//	EXPECT_TRUE(mErrors.empty());
//	EXPECT_TRUE(mAnalyzer->type(variable)->is<types::Integer>());
//	EXPECT_TRUE(mAnalyzer->type(value)->is<types::Integer>());
//}


