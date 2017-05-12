#pragma once

#include <QScriptEngineAgent>
#include <QtCore/QVector>
#include <QtCore/QMap>

#include "declSpec.h"

namespace twoDModel {
namespace engine {
class TwoDModelDebuggerControlInterface;
}
}

namespace trik {

class ROBOTS_TRIK_KIT_INTERPRETER_COMMON_EXPORT TrikQtsAgent : public QScriptEngineAgent {
public:
	TrikQtsAgent(QScriptEngine *e, twoDModel::engine::TwoDModelDebuggerControlInterface *d);

	void enable(bool isEnabled = true);
	bool isEnabled() const;
	void setBreakpoints(const QVector<int> &bp);

	virtual void scriptLoad(qint64 id, const QString &program, const QString &fileName, int baseLineNumber) override;
	virtual void positionChange(qint64 scriptId, int lineNumber, int columnNumber) override;

private:
	bool mIsEnabled;
	twoDModel::engine::TwoDModelDebuggerControlInterface *mDebugger; // doesn't have ownership
	QVector<int> mBreakpoints; // replace with some abstraction other breakpoint position.
	QMap<int, QStringList> mScripts;
	QMap<int, int> mBaseLineNumber;
};

}
