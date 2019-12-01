#include "../include/telwidget.h"
#include "telwidgetplugin.h"

#include <QtPlugin>

TelWidgetPlugin::TelWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TelWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TelWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TelWidgetPlugin::createWidget(QWidget *parent)
{
    return new TelWidget(parent);
}

QString TelWidgetPlugin::name() const
{
    return QLatin1String("TelWidget");
}

QString TelWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TelWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/telwidget.png"));
}

QString TelWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TelWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TelWidgetPlugin::isContainer() const
{
    return false;
}

QString TelWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"TelWidget\" name=\"telWidget\">\n</widget>\n");
}

QString TelWidgetPlugin::includeFile() const
{
    return QLatin1String("telwidget.h");
}

