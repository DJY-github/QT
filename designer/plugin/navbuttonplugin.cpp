#include "../include/navbutton.h"
#include "navbuttonplugin.h"

#include <QtPlugin>

NavButtonPlugin::NavButtonPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavButtonPlugin::createWidget(QWidget *parent)
{
    return new NavButton(parent);
}

QString NavButtonPlugin::name() const
{
    return QLatin1String("NavButton");
}

QString NavButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navbutton.png"));
}

QString NavButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavButtonPlugin::isContainer() const
{
    return false;
}

QString NavButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavButton\" name=\"navButton\">\n</widget>\n");
}

QString NavButtonPlugin::includeFile() const
{
    return QLatin1String("navbutton.h");
}

