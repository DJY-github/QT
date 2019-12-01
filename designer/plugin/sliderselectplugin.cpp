#include "../include/sliderselect.h"
#include "sliderselectplugin.h"

#include <QtPlugin>

SliderSelectPlugin::SliderSelectPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void SliderSelectPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderSelectPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderSelectPlugin::createWidget(QWidget *parent)
{
    return new SliderSelect(parent);
}

QString SliderSelectPlugin::name() const
{
    return QLatin1String("SliderSelect");
}

QString SliderSelectPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SliderSelectPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/sliderselect.png"));
}

QString SliderSelectPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderSelectPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderSelectPlugin::isContainer() const
{
    return false;
}

QString SliderSelectPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SliderSelect\" name=\"sliderSelect\">\n</widget>\n");
}

QString SliderSelectPlugin::includeFile() const
{
    return QLatin1String("sliderselect.h");
}

