#include "../include/slidertip.h"
#include "slidertipplugin.h"

#include <QtPlugin>

SliderTipPlugin::SliderTipPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void SliderTipPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderTipPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderTipPlugin::createWidget(QWidget *parent)
{
    return new SliderTip(parent);
}

QString SliderTipPlugin::name() const
{
    return QLatin1String("SliderTip");
}

QString SliderTipPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SliderTipPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/slidertip.png"));
}

QString SliderTipPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderTipPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderTipPlugin::isContainer() const
{
    return false;
}

QString SliderTipPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SliderTip\" name=\"sliderTip\">\n</widget>\n");
}

QString SliderTipPlugin::includeFile() const
{
    return QLatin1String("slidertip.h");
}

