#include "../include/gaugecloud.h"
#include "gaugecloudplugin.h"

#include <QtPlugin>

GaugeCloudPlugin::GaugeCloudPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeCloudPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCloudPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCloudPlugin::createWidget(QWidget *parent)
{
    return new GaugeCloud(parent);
}

QString GaugeCloudPlugin::name() const
{
    return QLatin1String("GaugeCloud");
}

QString GaugeCloudPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCloudPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecloud.png"));
}

QString GaugeCloudPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCloudPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCloudPlugin::isContainer() const
{
    return false;
}

QString GaugeCloudPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCloud\" name=\"gaugeCloud\">\n</widget>\n");
}

QString GaugeCloudPlugin::includeFile() const
{
    return QLatin1String("gaugecloud.h");
}

