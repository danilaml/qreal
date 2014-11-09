#include "qrtext/src/hm/HMSemanticAnalyzer.h"

using namespace qrtext;
using namespace qrtext::core;

HMSemanticAnalyzer::HMSemanticAnalyzer(QSharedPointer<GeneralizationsTableInterface> const &generalizationsTable
                                       , QList<Error> &errors)
    : SemanticAnalyzer(generalizationsTable, errors)
{
}
