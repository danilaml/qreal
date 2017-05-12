#pragma once

#include <QtCore/QObject>

#include "twoDModel/twoDModelDeclSpec.h"

namespace twoDModel {
namespace engine {

/// very basic interface for debugging 2d model
class TWO_D_MODEL_EXPORT TwoDModelDebuggerControlInterface : public QObject {
	Q_OBJECT

public:
	virtual ~TwoDModelDebuggerControlInterface() {}

	/// returns whether the model's timeline is paused
	virtual bool isModelPaused() = 0;

public slots:
	/// pauses the 2d model timeline. Useful for implementing breakpoints
	virtual void pauseModel() = 0;

	/// resumes 2d model timeline
	virtual void resumeModel() = 0;

signals:
	/// emitted when the 2D model is paused
	void modelPaused();

	/// emitted when the 2D model is resumed after being paused
	void modelResumed();
};

}
}
