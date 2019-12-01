#include "../include/gaugecompasspan.h"
#include "gaugecompasspanplugin.h"

#include <QtPlugin>

GaugeCompassPanPlugin::GaugeCompassPanPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeCompassPanPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCompassPanPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCompassPanPlugin::createWidget(QWidget *parent)
{
    return new GaugeCompassPan(parent);
}

QString GaugeCompassPanPlugin::name() const
{
    return QLatin1String("GaugeCompassPan");
}

QString GaugeCompassPanPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCompassPanPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecompasspan.png"));
}

QString GaugeCompassPanPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCompassPanPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCompassPanPlugin::isContainer() const
{
    return false;
}

QString GaugeCompassPanPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCompassPan\" name=\"gaugeCompassPan\">\n</widget>\n");
}

QString GaugeCompassPanPlugin::includeFile() const
{
    return QLatin1String("gaugecompasspan.h");
}

