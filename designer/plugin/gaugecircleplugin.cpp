#include "../include/gaugecircle.h"
#include "gaugecircleplugin.h"

#include <QtPlugin>

GaugeCirclePlugin::GaugeCirclePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeCirclePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCirclePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCirclePlugin::createWidget(QWidget *parent)
{
    return new GaugeCircle(parent);
}

QString GaugeCirclePlugin::name() const
{
    return QLatin1String("GaugeCircle");
}

QString GaugeCirclePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCirclePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecircle.png"));
}

QString GaugeCirclePlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCirclePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCirclePlugin::isContainer() const
{
    return false;
}

QString GaugeCirclePlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCircle\" name=\"gaugeCircle\">\n</widget>\n");
}

QString GaugeCirclePlugin::includeFile() const
{
    return QLatin1String("gaugecircle.h");
}

