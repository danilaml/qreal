/* Copyright 2016 Yurii Litvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include "utils/utilsDeclSpec.h"

class QState;
class QFileInfo;

namespace utils {
namespace robotCommunication {

class TcpRobotCommunicator;
class Protocol;

class ROBOTS_UTILS_EXPORT RunProgramProtocol : public QObject
{
	Q_OBJECT

public:
	explicit RunProgramProtocol(TcpRobotCommunicator &communicator);
	~RunProgramProtocol() override;

	void run(const QFileInfo &fileToRun);

signals:
	void success();
	void error();
	void timeout();

private:
	QScopedPointer<Protocol> mProtocol;

	/// Does not have direct ownership (will be disposed by mProtocol).
	QState *mWaitingForUploadingComplete = nullptr;

	/// Does not have direct ownership (will be disposed by mProtocol).
	QState *mWaitingForRunComplete = nullptr;
};

}
}
