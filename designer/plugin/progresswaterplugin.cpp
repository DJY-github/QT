#include "../include/progresswater.h"
#include "progresswaterplugin.h"

#include <QtPlugin>

ProgressWaterPlugin::ProgressWaterPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressWaterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressWaterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressWaterPlugin::createWidget(QWidget *parent)
{
    return new ProgressWater(parent);
}

QString ProgressWaterPlugin::name() const
{
    return QLatin1String("ProgressWater");
}

QString ProgressWaterPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressWaterPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progresswater.png"));
}

QString ProgressWaterPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressWaterPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressWaterPlugin::isContainer() const
{
    return false;
}

QString ProgressWaterPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressWater\" name=\"progressWater\">\n</widget>\n");
}

QString ProgressWaterPlugin::includeFile() const
{
    return QLatin1String("progresswater.h");
}

