#include "../include/gaugepercent.h"
#include "gaugepercentplugin.h"

#include <QtPlugin>

GaugePercentPlugin::GaugePercentPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugePercentPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugePercentPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugePercentPlugin::createWidget(QWidget *parent)
{
    return new GaugePercent(parent);
}

QString GaugePercentPlugin::name() const
{
    return QLatin1String("GaugePercent");
}

QString GaugePercentPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugePercentPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugepercent.png"));
}

QString GaugePercentPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugePercentPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugePercentPlugin::isContainer() const
{
    return false;
}

QString GaugePercentPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugePercent\" name=\"gaugePercent\">\n</widget>\n");
}

QString GaugePercentPlugin::includeFile() const
{
    return QLatin1String("gaugepercent.h");
}

