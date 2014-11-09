#pragma once

#include "qrtext/core/semantics/semanticAnalyzer.h"

#include "qrtext/declSpec.h"

namespace qrtext {
using namespace core;

class QRTEXT_EXPORT HMSemanticAnalyzer : public core::SemanticAnalyzer
{
public:
	HMSemanticAnalyzer(QSharedPointer<GeneralizationsTableInterface> const &generalizationsTable
	                   , QList<Error> &errors);
};

}
