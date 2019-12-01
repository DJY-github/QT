#include "../include/wavedata.h"
#include "wavedataplugin.h"

#include <QtPlugin>

WaveDataPlugin::WaveDataPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void WaveDataPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveDataPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveDataPlugin::createWidget(QWidget *parent)
{
    return new WaveData(parent);
}

QString WaveDataPlugin::name() const
{
    return QLatin1String("WaveData");
}

QString WaveDataPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveDataPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/wavedata.png"));
}

QString WaveDataPlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveDataPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveDataPlugin::isContainer() const
{
    return false;
}

QString WaveDataPlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveData\" name=\"waveData\">\n</widget>\n");
}

QString WaveDataPlugin::includeFile() const
{
    return QLatin1String("wavedata.h");
}

