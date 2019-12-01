#include "../include/colorpanelfader.h"
#include "colorpanelfaderplugin.h"

#include <QtPlugin>

ColorPanelFaderPlugin::ColorPanelFaderPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorPanelFaderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorPanelFaderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPanelFaderPlugin::createWidget(QWidget *parent)
{
    return new ColorPanelFader(parent);
}

QString ColorPanelFaderPlugin::name() const
{
    return QLatin1String("ColorPanelFader");
}

QString ColorPanelFaderPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorPanelFaderPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorpanelfader.png"));
}

QString ColorPanelFaderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorPanelFaderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorPanelFaderPlugin::isContainer() const
{
    return false;
}

QString ColorPanelFaderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorPanelFader\" name=\"colorPanelFader\">\n</widget>\n");
}

QString ColorPanelFaderPlugin::includeFile() const
{
    return QLatin1String("colorpanelfader.h");
}

