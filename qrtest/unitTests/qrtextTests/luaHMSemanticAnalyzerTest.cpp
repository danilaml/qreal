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
	//mAnalyzer.reset(new HMSemanticAnalyzer(mErrors));
	mParser.reset(new LuaParser(mErrors));
	mLexer.reset(new LuaLexer(mErrors));
}

//QSharedPointer<qrtext::core::ast::Node> LuaHMSemanticAnalyzerTest::parse(QString const &code)
//{
//    return mParser->parse(mLexer->tokenize(code), mLexer->userFriendlyTokenNames());
//}

//TEST_F(LuaHMSemanticAnalyzerTest, sanityCheck)
//{
//    auto tree = parse("123");
//    mAnalyzer->analyze(tree);
//    EXPECT_TRUE(mErrors.empty());
//    EXPECT_TRUE(mAnalyzer->type(tree)->is<Integer>());
//    EXPECT_TRUE(mAnalyzer->type(tree)->is<Number>());
//}
