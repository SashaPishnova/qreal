#include "initialBlockGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"

using namespace robots::generator;

InitialBlockGenerator::InitialBlockGenerator()
{
}

QList<SmartLine> InitialBlockGenerator::convertElementIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		, qReal::Id const elementId, qReal::Id const logicElementId)
{
	QList<SmartLine> result;
	QList<SmartLine> initCode;
	QList<SmartLine> terminateCode;
	int const numberOfPorts = 4;
	for (int i = 1; i <= numberOfPorts; i++) {
		QString const curPort = "port_" + QString::number(i);
		QByteArray portValue = nxtGen->api()->stringProperty(logicElementId, curPort).toUtf8();

		switch (i) {
		case 1:
			nxtGen->portValue1() = portValue;
			break;
		case 2:
			nxtGen->portValue2() = portValue;
			break;
		case 3:
			nxtGen->portValue3() = portValue;
			break;
		case 4:
			nxtGen->portValue4() = portValue;
			break;
		}

		if (portValue == "Ультразвуковой сенсор") {
			initCode.append(SmartLine("ecrobot_init_sonar_sensor(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
			terminateCode.append(SmartLine("ecrobot_term_sonar_sensor(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
		} else if ((portValue == "Сенсор цвета (все цвета)")
			|| (portValue == "Сенсор цвета (красный)")
			|| (portValue == "Сенсор цвета (зеленый)")
			|| (portValue == "Сенсор цвета (синий)")
			|| (portValue == "Сенсор цвета (пассивный)")) {
			nxtGen->errorReporter().addError(QObject::tr("NXTOsek doesn't support color sensor"));
			return initCode;
		} else if (portValue == "Сенсор света") {
			initCode.append(SmartLine("ecrobot_set_light_sensor_active(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
			terminateCode.append(SmartLine("ecrobot_set_light_sensor_inactive(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
		}
	}
	nxtGen->initCode().append(initCode);
	nxtGen->terminateCode().append(terminateCode);

	return result;
}
