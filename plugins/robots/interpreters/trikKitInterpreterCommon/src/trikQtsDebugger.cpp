#include "trikKitInterpreterCommon/trikQtsDebugger.h"

#include <QtCore/QTimer>
#include <QScriptEngineAgent>
#include <QScriptEngine>
#include "twoDModel/engine/twoDModelDebuggerInterface.h"
#include "trikKitInterpreterCommon/trikQtsAgent.h"

#include <iostream>


trik::TrikQtsDebugger::TrikQtsDebugger(twoDModel::engine::TwoDModelDebuggerControlInterface *d)
	: mIsEnabled(false), mDebugger(d)
{
}

void trik::TrikQtsDebugger::registerNewScriptAgent(QScriptEngine *e)
{
	if (mIsEnabled) {
		TrikQtsAgent *a = new TrikQtsAgent(e, mDebugger);
		a->setBreakpoints(mBreakpoints);
		a->enable(true);
		e->setAgent(a);
	}
}

void trik::TrikQtsDebugger::enable(bool isEnabled)
{
	mIsEnabled = isEnabled;
}

bool trik::TrikQtsDebugger::isEnabled() const
{
	return mIsEnabled;
}

void trik::TrikQtsDebugger::setBreakpoints(const QVector<int> &bp)
{
	mBreakpoints = bp;
}
