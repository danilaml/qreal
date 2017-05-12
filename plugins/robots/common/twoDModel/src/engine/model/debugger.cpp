#include "twoDModel/engine/model/debugger.h"
#include "twoDModel/engine/model/timeline.h"

twoDModel::model::Debugger::Debugger(twoDModel::model::Timeline &timeline) : mTimeline(timeline)
{
}

void twoDModel::model::Debugger::pauseModel()
{
	mTimeline.pause();
	emit modelPaused();
}

void twoDModel::model::Debugger::resumeModel()
{
	mTimeline.resume();
	emit modelResumed();
}

bool twoDModel::model::Debugger::isModelPaused()
{
	return mTimeline.isPaused();
}
