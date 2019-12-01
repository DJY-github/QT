#include "../include/gaugemini.h"
#include "gaugeminiplugin.h"

#include <QtPlugin>

GaugeMiniPlugin::GaugeMiniPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeMiniPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeMiniPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeMiniPlugin::createWidget(QWidget *parent)
{
    return new GaugeMini(parent);
}

QString GaugeMiniPlugin::name() const
{
    return QLatin1String("GaugeMini");
}

QString GaugeMiniPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeMiniPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugemini.png"));
}

QString GaugeMiniPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeMiniPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeMiniPlugin::isContainer() const
{
    return false;
}

QString GaugeMiniPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeMini\" name=\"gaugeMini\">\n</widget>\n");
}

QString GaugeMiniPlugin::includeFile() const
{
    return QLatin1String("gaugemini.h");
}

