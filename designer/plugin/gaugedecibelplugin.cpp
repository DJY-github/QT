#include "../include/gaugedecibel.h"
#include "gaugedecibelplugin.h"

#include <QtPlugin>

GaugeDecibelPlugin::GaugeDecibelPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeDecibelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeDecibelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeDecibelPlugin::createWidget(QWidget *parent)
{
    return new GaugeDecibel(parent);
}

QString GaugeDecibelPlugin::name() const
{
    return QLatin1String("GaugeDecibel");
}

QString GaugeDecibelPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeDecibelPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugedecibel.png"));
}

QString GaugeDecibelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeDecibelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeDecibelPlugin::isContainer() const
{
    return false;
}

QString GaugeDecibelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeDecibel\" name=\"gaugeDecibel\">\n</widget>\n");
}

QString GaugeDecibelPlugin::includeFile() const
{
    return QLatin1String("gaugedecibel.h");
}

