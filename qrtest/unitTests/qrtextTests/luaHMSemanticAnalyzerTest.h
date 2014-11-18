#pragma once

#include <QtCore/QScopedPointer>

#include <gtest/gtest.h>

#include "qrtext/src/hm/HMSemanticAnalyzer.h"
#include "qrtext/src/lua/luaParser.h"
#include "qrtext/src/lua/luaLexer.h"

namespace qrTest {

class LuaHMSemanticAnalyzerTest : public testing::Test
{
protected:
    void SetUp() override;

    QSharedPointer<qrtext::core::ast::Node> parse(QString const &code);

    QScopedPointer<qrtext::HMSemanticAnalyzer> mAnalyzer;
    QScopedPointer<qrtext::lua::details::LuaParser> mParser;
    QScopedPointer<qrtext::lua::details::LuaLexer> mLexer;
    QList<qrtext::core::Error> mErrors;
};

}
