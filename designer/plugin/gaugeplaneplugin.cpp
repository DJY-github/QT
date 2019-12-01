#include "../include/gaugeplane.h"
#include "gaugeplaneplugin.h"

#include <QtPlugin>

GaugePlanePlugin::GaugePlanePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugePlanePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugePlanePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugePlanePlugin::createWidget(QWidget *parent)
{
    return new GaugePlane(parent);
}

QString GaugePlanePlugin::name() const
{
    return QLatin1String("GaugePlane");
}

QString GaugePlanePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugePlanePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeplane.png"));
}

QString GaugePlanePlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugePlanePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugePlanePlugin::isContainer() const
{
    return false;
}

QString GaugePlanePlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugePlane\" name=\"gaugePlane\">\n</widget>\n");
}

QString GaugePlanePlugin::includeFile() const
{
    return QLatin1String("gaugeplane.h");
}

