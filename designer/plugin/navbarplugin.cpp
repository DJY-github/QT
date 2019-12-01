#include "../include/navbar.h"
#include "navbarplugin.h"

#include <QtPlugin>

NavBarPlugin::NavBarPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavBarPlugin::createWidget(QWidget *parent)
{
    return new NavBar(parent);
}

QString NavBarPlugin::name() const
{
    return QLatin1String("NavBar");
}

QString NavBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navbar.png"));
}

QString NavBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavBarPlugin::isContainer() const
{
    return false;
}

QString NavBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavBar\" name=\"navBar\">\n</widget>\n");
}

QString NavBarPlugin::includeFile() const
{
    return QLatin1String("navbar.h");
}

