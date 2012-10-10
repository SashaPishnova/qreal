#include "endOfLoopBlockGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"

using namespace robots::generator;

EndOfLoopBlockGenerator::EndOfLoopBlockGenerator()
{
}

QList<SmartLine> EndOfLoopBlockGenerator::convertElementIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		, qReal::Id const elementId, qReal::Id const logicElementId)
{
	Q_UNUSED(nxtGen)
	Q_UNUSED(logicElementId)

	QList<SmartLine> result;
	result.append(SmartLine("}",elementId));
	return result;
}
