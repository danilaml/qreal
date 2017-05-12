#include "trikKitInterpreterCommon/trikQtsAgent.h"

#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QEventLoop>
#include "twoDModel/engine/twoDModelDebuggerInterface.h"

trik::TrikQtsAgent::TrikQtsAgent(QScriptEngine *e, twoDModel::engine::TwoDModelDebuggerControlInterface *d)
	: QScriptEngineAgent(e), mIsEnabled(false), mDebugger(d)
{
}

void trik::TrikQtsAgent::enable(bool isEnabled)
{
	mIsEnabled = isEnabled;
}

bool trik::TrikQtsAgent::isEnabled() const
{
	return mIsEnabled;
}

void trik::TrikQtsAgent::setBreakpoints(const QVector<int> &bp)
{
	mBreakpoints = bp;
}

void trik::TrikQtsAgent::scriptLoad(qint64 id, const QString &program, const QString &fileName, int baseLineNumber)
{
	QStringList lines = program.split('\n');
	mScripts[id] = lines;
	mBaseLineNumber[id] = baseLineNumber;
}

void trik::TrikQtsAgent::positionChange(qint64 scriptId, int lineNumber, int columnNumber)
{
	if (mIsEnabled && mBreakpoints.contains(lineNumber - mBaseLineNumber[scriptId])) {
		QEventLoop loop;
		QObject::connect(mDebugger
				, &twoDModel::engine::TwoDModelDebuggerControlInterface::modelResumed
				, &loop
				, &QEventLoop::quit);
		//QScopedPointer<utils::AbstractTimer> t(mTwoDRobotModel->timeline().produceTimer());
		//t->moveToThread(QThread::currentThread());
		//t->setRepeatable(true);
		//connect(t.data(), SIGNAL(timeout()), &loop, SLOT(quit()), Qt::DirectConnection);
		//t->start(milliseconds);
//		if (!mIsWaitingEnabled)
//			return; // to be safe;
		QTimer::singleShot(0, mDebugger, &twoDModel::engine::TwoDModelDebuggerControlInterface::pauseModel);
		loop.exec();
	}
}
