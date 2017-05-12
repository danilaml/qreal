#pragma once

#include <QtCore/QVector>

#include "declSpec.h"

namespace twoDModel {
namespace engine {
class TwoDModelDebuggerControlInterface;
}
}

class QScriptEngine;

namespace trik {

class ROBOTS_TRIK_KIT_INTERPRETER_COMMON_EXPORT TrikQtsDebugger {
public:
	TrikQtsDebugger(twoDModel::engine::TwoDModelDebuggerControlInterface *d);

	void registerNewScriptAgent(QScriptEngine *e);

	void enable(bool isEnabled = true);
	bool isEnabled() const;
	void setBreakpoints(const QVector<int> &bp);

private:
	bool mIsEnabled;
	twoDModel::engine::TwoDModelDebuggerControlInterface *mDebugger;
	QVector<int> mBreakpoints; // replace with some abstraction other breakpoint position.
};

}
