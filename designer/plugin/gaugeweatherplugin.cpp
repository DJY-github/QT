#include "../include/gaugeweather.h"
#include "gaugeweatherplugin.h"

#include <QtPlugin>

GaugeWeatherPlugin::GaugeWeatherPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeWeatherPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeWeatherPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeWeatherPlugin::createWidget(QWidget *parent)
{
    return new GaugeWeather(parent);
}

QString GaugeWeatherPlugin::name() const
{
    return QLatin1String("GaugeWeather");
}

QString GaugeWeatherPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeWeatherPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeweather.png"));
}

QString GaugeWeatherPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeWeatherPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeWeatherPlugin::isContainer() const
{
    return false;
}

QString GaugeWeatherPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeWeather\" name=\"gaugeWeather\">\n</widget>\n");
}

QString GaugeWeatherPlugin::includeFile() const
{
    return QLatin1String("gaugeweather.h");
}

