#include "beginningOfLoopBlockGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"

using namespace robots::generator;

BeginningOfLoopBlockGenerator::BeginningOfLoopBlockGenerator()
{
}

QList<SmartLine> BeginningOfLoopBlockGenerator::convertElementIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		, qReal::Id const elementId, qReal::Id const logicElementId)
{
	Q_UNUSED(elementId)

	QList<SmartLine> result;
	result << SmartLine("for (int __iter__ = 0; __iter__ < "
			+ nxtGen->api()->stringProperty(logicElementId, "Iterations")
			+ "; __iter__++) {", elementId, SmartLine::increase);
	return result;
}

