#pragma once

#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QPluginLoader>

#include "../toolPluginInterface/toolPluginInterface.h"
#include "../toolPluginInterface/customizer.h"
#include "../toolPluginInterface/pluginConfigurator.h"
#include "../dialogs/preferencesPages/page.h"

namespace qReal {

class ToolPluginManager
{
public:
	explicit ToolPluginManager(QObject *parent = NULL);
	virtual ~ToolPluginManager();

	void init(PluginConfigurator const &configurator);
	void updateSettings();
	QList<ActionInfo> actions() const;
	QList<QPair<QString, PreferencesPage *> > preferencesPages() const;

	/// Returns GUI customizer object. In each QReal's instance there should be only one plugin with
	/// valid customizationInterface(): robots plugin for QReal:Robots, ubiq plugin for QReal:Ubiq etc.
	/// If there're more than one plugin of that kind, it is not specified which one will be used.
	Customizer const *customizer() const;

private:
	QDir mPluginsDir;

	QList<ToolPluginInterface *> mPlugins;
	QList<QPluginLoader *> mLoaders;

	/// An object and that is used to customize GUI with values from plugins
	Customizer const mCustomizer;  // Has ownership
};

}
