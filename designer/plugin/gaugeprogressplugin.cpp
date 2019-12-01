#include "../include/gaugeprogress.h"
#include "gaugeprogressplugin.h"

#include <QtPlugin>

GaugeProgressPlugin::GaugeProgressPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeProgressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeProgressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeProgressPlugin::createWidget(QWidget *parent)
{
    return new GaugeProgress(parent);
}

QString GaugeProgressPlugin::name() const
{
    return QLatin1String("GaugeProgress");
}

QString GaugeProgressPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeProgressPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeprogress.png"));
}

QString GaugeProgressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeProgressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeProgressPlugin::isContainer() const
{
    return false;
}

QString GaugeProgressPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeProgress\" name=\"gaugeProgress\">\n</widget>\n");
}

QString GaugeProgressPlugin::includeFile() const
{
    return QLatin1String("gaugeprogress.h");
}

