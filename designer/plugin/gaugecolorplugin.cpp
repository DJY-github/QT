#include "../include/gaugecolor.h"
#include "gaugecolorplugin.h"

#include <QtPlugin>

GaugeColorPlugin::GaugeColorPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeColorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeColorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeColorPlugin::createWidget(QWidget *parent)
{
    return new GaugeColor(parent);
}

QString GaugeColorPlugin::name() const
{
    return QLatin1String("GaugeColor");
}

QString GaugeColorPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeColorPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecolor.png"));
}

QString GaugeColorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeColorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeColorPlugin::isContainer() const
{
    return false;
}

QString GaugeColorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeColor\" name=\"gaugeColor\">\n</widget>\n");
}

QString GaugeColorPlugin::includeFile() const
{
    return QLatin1String("gaugecolor.h");
}

