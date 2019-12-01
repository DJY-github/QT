#include "../include/wavechart.h"
#include "wavechartplugin.h"

#include <QtPlugin>

WaveChartPlugin::WaveChartPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void WaveChartPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveChartPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveChartPlugin::createWidget(QWidget *parent)
{
    return new WaveChart(parent);
}

QString WaveChartPlugin::name() const
{
    return QLatin1String("WaveChart");
}

QString WaveChartPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveChartPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/wavechart.png"));
}

QString WaveChartPlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveChartPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveChartPlugin::isContainer() const
{
    return false;
}

QString WaveChartPlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveChart\" name=\"waveChart\">\n</widget>\n");
}

QString WaveChartPlugin::includeFile() const
{
    return QLatin1String("wavechart.h");
}

