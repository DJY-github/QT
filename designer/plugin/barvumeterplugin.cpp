#include "../include/barvumeter.h"
#include "barvumeterplugin.h"

#include <QtPlugin>

BarVUMeterPlugin::BarVUMeterPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void BarVUMeterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BarVUMeterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BarVUMeterPlugin::createWidget(QWidget *parent)
{
    return new BarVUMeter(parent);
}

QString BarVUMeterPlugin::name() const
{
    return QLatin1String("BarVUMeter");
}

QString BarVUMeterPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon BarVUMeterPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/barvumeter.png"));
}

QString BarVUMeterPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BarVUMeterPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BarVUMeterPlugin::isContainer() const
{
    return false;
}

QString BarVUMeterPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BarVUMeter\" name=\"barVUMeter\">\n</widget>\n");
}

QString BarVUMeterPlugin::includeFile() const
{
    return QLatin1String("barvumeter.h");
}

