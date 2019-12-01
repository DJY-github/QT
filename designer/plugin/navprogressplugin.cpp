#include "../include/navprogress.h"
#include "navprogressplugin.h"

#include <QtPlugin>

NavProgressPlugin::NavProgressPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavProgressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavProgressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavProgressPlugin::createWidget(QWidget *parent)
{
    return new NavProgress(parent);
}

QString NavProgressPlugin::name() const
{
    return QLatin1String("NavProgress");
}

QString NavProgressPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavProgressPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navprogress.png"));
}

QString NavProgressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavProgressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavProgressPlugin::isContainer() const
{
    return false;
}

QString NavProgressPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavProgress\" name=\"navProgress\">\n</widget>\n");
}

QString NavProgressPlugin::includeFile() const
{
    return QLatin1String("navprogress.h");
}

