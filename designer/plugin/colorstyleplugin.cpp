#include "../include/colorstyle.h"
#include "colorstyleplugin.h"

#include <QtPlugin>

ColorStylePlugin::ColorStylePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ColorStylePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorStylePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorStylePlugin::createWidget(QWidget *parent)
{
    return new ColorStyle(parent);
}

QString ColorStylePlugin::name() const
{
    return QLatin1String("ColorStyle");
}

QString ColorStylePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorStylePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorstyle.png"));
}

QString ColorStylePlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorStylePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorStylePlugin::isContainer() const
{
    return false;
}

QString ColorStylePlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorStyle\" name=\"colorStyle\">\n</widget>\n");
}

QString ColorStylePlugin::includeFile() const
{
    return QLatin1String("colorstyle.h");
}

