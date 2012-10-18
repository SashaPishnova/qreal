#include "waitForColorIntensityBlockGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"
#include "../listsmartline.h"

using namespace robots::generator;

WaitForColorIntensityBlockGenerator::WaitForColorIntensityBlockGenerator()
{
}

QList<SmartLine> WaitForColorIntensityBlockGenerator::convertElementIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		, qReal::Id const elementId, qReal::Id const logicElementId)
{
	QList<SmartLine> result;
	Q_UNUSED(elementId)
	Q_UNUSED(logicElementId)

	nxtGen->errorReporter().addError(QObject::tr("NXTOsek doesn't support color sensor"));
	return result;
}
