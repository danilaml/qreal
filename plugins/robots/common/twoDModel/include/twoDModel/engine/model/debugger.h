#pragma once

#include "twoDModel/engine/twoDModelDebuggerInterface.h"

namespace twoDModel {
namespace model {

class Timeline;

class Debugger : public engine::TwoDModelDebuggerControlInterface {
public:
	Debugger(Timeline &timeline);

	virtual void pauseModel() override;
	virtual void resumeModel() override;
	virtual bool isModelPaused() override;
private:
	Timeline &mTimeline;
};

}
}
