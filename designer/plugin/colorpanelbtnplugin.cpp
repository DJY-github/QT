#include "../include/colorpanelbtn.h"
#include "colorpanelbtnplugin.h"

#include <QtPlugin>

ColorPanelBtnPlugin::ColorPanelBtnPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorPanelBtnPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorPanelBtnPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPanelBtnPlugin::createWidget(QWidget *parent)
{
    return new ColorPanelBtn(parent);
}

QString ColorPanelBtnPlugin::name() const
{
    return QLatin1String("ColorPanelBtn");
}

QString ColorPanelBtnPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorPanelBtnPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorpanelbtn.png"));
}

QString ColorPanelBtnPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorPanelBtnPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorPanelBtnPlugin::isContainer() const
{
    return false;
}

QString ColorPanelBtnPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorPanelBtn\" name=\"colorPanelBtn\">\n</widget>\n");
}

QString ColorPanelBtnPlugin::includeFile() const
{
    return QLatin1String("colorpanelbtn.h");
}

