#include "../include/xslider.h"
#include "xsliderplugin.h"

#include <QtPlugin>

XSliderPlugin::XSliderPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XSliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XSliderPlugin::createWidget(QWidget *parent)
{
    return new XSlider(parent);
}

QString XSliderPlugin::name() const
{
    return QLatin1String("XSlider");
}

QString XSliderPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XSliderPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/xslider.png"));
}

QString XSliderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XSliderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XSliderPlugin::isContainer() const
{
    return false;
}

QString XSliderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XSlider\" name=\"xslider\">\n</widget>\n");
}

QString XSliderPlugin::includeFile() const
{
    return QLatin1String("xslider.h");
}

