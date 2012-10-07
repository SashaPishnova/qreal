#include "enginesGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"
#include "../listsmartline.h"

using namespace robots::generator;

EnginesGenerator::EnginesGenerator(QString const &engineType): mEngineType(engineType)
{
}

void EnginesGenerator::addInitAndTerminateCode(NxtOSEKRobotGenerator *nxtGen  // duplicated code - not true
		, qReal::Id const elementId, QString const &enginePort)
{
	QString const initTerminateVelocity = "0";
	QString const initBrakeMode = "1";
	QString const terminateBrakeMode = "0";
	QString const initCodeEngines = "nxt_motor_set_speed("
			+ enginePort + ", "
			+ initTerminateVelocity + ", "
			+ initBrakeMode + ");";
	QString const terminateCodeEngines = "nxt_motor_set_speed("
			+ enginePort + ", "
			+ initTerminateVelocity + ", "
			+ terminateBrakeMode + ");";
	if (!ListSmartLine::isContains(nxtGen->initCode(), initCodeEngines)) {
		nxtGen->initCode().append(SmartLine(initCodeEngines, elementId));
		nxtGen->terminateCode().append(SmartLine(terminateCodeEngines, elementId));
	}
}

QList<SmartLine> EnginesGenerator::convertElementIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		 , qReal::Id const elementId, qReal::Id const logicElementId)
{
	QList<SmartLine> result;
	QString const ports = nxtGen->api()->stringProperty(logicElementId, "Ports");
	QString const power = nxtGen->api()->stringProperty(logicElementId, "Power");
	QString brakeMode = nxtGen->api()->stringProperty(logicElementId, "BrakeMode");
	if (brakeMode.compare("скользить")) {
		brakeMode = "0";
	} else {
		brakeMode = "1";
	}

	QString signRotate = "";
	if (mEngineType == "EnginesBackward") {
		signRotate = "-";
	}

	foreach (QString const &enginePort, portsToEngineNames(ports)) {
		result.append(SmartLine("nxt_motor_set_speed(" + enginePort + ", "
				+ signRotate + power + ", "
				+ brakeMode + ");", elementId));
		addInitAndTerminateCode(nxtGen, elementId, enginePort);
	}

	QString const tachoLimit = nxtGen->api()->stringProperty(logicElementId, "TachoLimit");
	if (tachoLimit > 0) {
		int numberOfPortsUsed = 0;
		QString tachoLimitResult = "";
		foreach (QString const &enginePort, portsToEngineNames(ports)) {
			numberOfPortsUsed++;
			if (numberOfPortsUsed > 1) {
				tachoLimitResult.append(" && ");
			}
			tachoLimitResult.append("(nxt_motor_get_count(" + enginePort + ") < "
					+ tachoLimit + ")");
		}
		if (numberOfPortsUsed > 1) {
			tachoLimitResult.append(")");
			tachoLimitResult.prepend("(");
		}
		if (numberOfPortsUsed > 0) {
			tachoLimitResult.prepend("while ");
			result.append(SmartLine(tachoLimitResult, elementId));
			result.append(SmartLine("{", elementId));
			result.append(SmartLine("}", elementId));
		}
	}

	return result;
}
