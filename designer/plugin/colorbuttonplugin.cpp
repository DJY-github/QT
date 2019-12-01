#include "../include/colorbutton.h"
#include "colorbuttonplugin.h"

#include <QtPlugin>

ColorButtonPlugin::ColorButtonPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorButtonPlugin::createWidget(QWidget *parent)
{
    return new ColorButton(parent);
}

QString ColorButtonPlugin::name() const
{
    return QLatin1String("ColorButton");
}

QString ColorButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorbutton.png"));
}

QString ColorButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorButtonPlugin::isContainer() const
{
    return false;
}

QString ColorButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorButton\" name=\"colorButton\">\n</widget>\n");
}

QString ColorButtonPlugin::includeFile() const
{
    return QLatin1String("colorbutton.h");
}

