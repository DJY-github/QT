#include "../include/colorpanelhsb.h"
#include "colorpanelhsbplugin.h"

#include <QtPlugin>

ColorPanelHSBPlugin::ColorPanelHSBPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorPanelHSBPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorPanelHSBPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPanelHSBPlugin::createWidget(QWidget *parent)
{
    return new ColorPanelHSB(parent);
}

QString ColorPanelHSBPlugin::name() const
{
    return QLatin1String("ColorPanelHSB");
}

QString ColorPanelHSBPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorPanelHSBPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorpanelhsb.png"));
}

QString ColorPanelHSBPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorPanelHSBPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorPanelHSBPlugin::isContainer() const
{
    return false;
}

QString ColorPanelHSBPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorPanelHSB\" name=\"colorPanelHSB\">\n</widget>\n");
}

QString ColorPanelHSBPlugin::includeFile() const
{
    return QLatin1String("colorpanelhsb.h");
}

