#include "../include/customgraphics.h"
#include "customgraphicsplugin.h"

#include <QtPlugin>

CustomGraphicsPlugin::CustomGraphicsPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CustomGraphicsPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomGraphicsPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomGraphicsPlugin::createWidget(QWidget *parent)
{
    return new CustomGraphics(parent);
}

QString CustomGraphicsPlugin::name() const
{
    return QLatin1String("CustomGraphics");
}

QString CustomGraphicsPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CustomGraphicsPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/customgraphics.png"));
}

QString CustomGraphicsPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomGraphicsPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomGraphicsPlugin::isContainer() const
{
    return false;
}

QString CustomGraphicsPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomGraphics\" name=\"customGraphics\">\n</widget>\n");
}

QString CustomGraphicsPlugin::includeFile() const
{
    return QLatin1String("customgraphics.h");
}

