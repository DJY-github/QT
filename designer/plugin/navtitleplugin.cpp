#include "../include/navtitle.h"
#include "navtitleplugin.h"

#include <QtPlugin>

NavTitlePlugin::NavTitlePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavTitlePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavTitlePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavTitlePlugin::createWidget(QWidget *parent)
{
    return new NavTitle(parent);
}

QString NavTitlePlugin::name() const
{
    return QLatin1String("NavTitle");
}

QString NavTitlePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavTitlePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navtitle.png"));
}

QString NavTitlePlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavTitlePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavTitlePlugin::isContainer() const
{
    return false;
}

QString NavTitlePlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavTitle\" name=\"navTitle\">\n</widget>\n");
}

QString NavTitlePlugin::includeFile() const
{
    return QLatin1String("navtitle.h");
}

