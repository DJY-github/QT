#include "../include/colorpanelbar.h"
#include "colorpanelbarplugin.h"

#include <QtPlugin>

ColorPanelBarPlugin::ColorPanelBarPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorPanelBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorPanelBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPanelBarPlugin::createWidget(QWidget *parent)
{
    return new ColorPanelBar(parent);
}

QString ColorPanelBarPlugin::name() const
{
    return QLatin1String("ColorPanelBar");
}

QString ColorPanelBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorPanelBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorpanelbar.png"));
}

QString ColorPanelBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorPanelBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorPanelBarPlugin::isContainer() const
{
    return false;
}

QString ColorPanelBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorPanelBar\" name=\"colorPanelBar\">\n</widget>\n");
}

QString ColorPanelBarPlugin::includeFile() const
{
    return QLatin1String("colorpanelbar.h");
}

