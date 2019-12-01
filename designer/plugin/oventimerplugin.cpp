#include "../include/oventimer.h"
#include "oventimerplugin.h"

#include <QtPlugin>

OvenTimerPlugin::OvenTimerPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void OvenTimerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OvenTimerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OvenTimerPlugin::createWidget(QWidget *parent)
{
    return new OvenTimer(parent);
}

QString OvenTimerPlugin::name() const
{
    return QLatin1String("OvenTimer");
}

QString OvenTimerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon OvenTimerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/oventimer.png"));
}

QString OvenTimerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OvenTimerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OvenTimerPlugin::isContainer() const
{
    return false;
}

QString OvenTimerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OvenTimer\" name=\"ovenTimer\">\n</widget>\n");
}

QString OvenTimerPlugin::includeFile() const
{
    return QLatin1String("oventimer.h");
}

