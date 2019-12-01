#include "../include/gaugelpm.h"
#include "gaugelpmplugin.h"

#include <QtPlugin>

GaugeLpmPlugin::GaugeLpmPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeLpmPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeLpmPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeLpmPlugin::createWidget(QWidget *parent)
{
    return new GaugeLpm(parent);
}

QString GaugeLpmPlugin::name() const
{
    return QLatin1String("GaugeLpm");
}

QString GaugeLpmPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeLpmPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugelpm.png"));
}

QString GaugeLpmPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeLpmPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeLpmPlugin::isContainer() const
{
    return false;
}

QString GaugeLpmPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeLpm\" name=\"gaugeLpm\">\n</widget>\n");
}

QString GaugeLpmPlugin::includeFile() const
{
    return QLatin1String("gaugelpm.h");
}

