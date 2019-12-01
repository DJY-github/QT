#include "../include/rulerslider.h"
#include "rulersliderplugin.h"

#include <QtPlugin>

RulerSliderPlugin::RulerSliderPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerSliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerSliderPlugin::createWidget(QWidget *parent)
{
    return new RulerSlider(parent);
}

QString RulerSliderPlugin::name() const
{
    return QLatin1String("RulerSlider");
}

QString RulerSliderPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerSliderPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerslider.png"));
}

QString RulerSliderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerSliderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerSliderPlugin::isContainer() const
{
    return false;
}

QString RulerSliderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerSlider\" name=\"rulerSlider\">\n</widget>\n");
}

QString RulerSliderPlugin::includeFile() const
{
    return QLatin1String("rulerslider.h");
}

