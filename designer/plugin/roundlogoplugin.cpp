#include "../include/roundlogo.h"
#include "roundlogoplugin.h"

#include <QtPlugin>

RoundLogoPlugin::RoundLogoPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RoundLogoPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RoundLogoPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RoundLogoPlugin::createWidget(QWidget *parent)
{
    return new RoundLogo(parent);
}

QString RoundLogoPlugin::name() const
{
    return QLatin1String("RoundLogo");
}

QString RoundLogoPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RoundLogoPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/roundlogo.png"));
}

QString RoundLogoPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RoundLogoPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RoundLogoPlugin::isContainer() const
{
    return false;
}

QString RoundLogoPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RoundLogo\" name=\"roundLogo\">\n</widget>\n");
}

QString RoundLogoPlugin::includeFile() const
{
    return QLatin1String("roundlogo.h");
}

