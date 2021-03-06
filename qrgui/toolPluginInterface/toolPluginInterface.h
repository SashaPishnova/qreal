#pragma once

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QList>

#include "../../qrrepo/repoControlInterface.h"
#include "../dialogs/preferencesPages/page.h"

#include "customizer.h"
#include "pluginConfigurator.h"
#include "actionInfo.h"

namespace qReal {

class ToolPluginInterface
{
public:
	virtual Customizer* customizationInterface()
	{
		return NULL;
	}

	virtual void updateSettings()
	{
	}

	virtual QList<ActionInfo> actions()
	{
		return QList<ActionInfo>();
	}

	virtual void init(PluginConfigurator const &configurator)
	{
		Q_UNUSED(configurator);
	}

	virtual QPair<QString, PreferencesPage *> preferencesPage()
	{
		return QPair<QString, PreferencesPage *>(QString(), NULL);
	}

	// TODO: Properly rename it or remove at all.
	virtual void closeNeededWidget()
	{
	}
};

}

Q_DECLARE_INTERFACE(qReal::ToolPluginInterface, "ru.tepkom.QReal.ToolPluginInterface/0.1")
