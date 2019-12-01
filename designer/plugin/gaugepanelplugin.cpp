#include "../include/gaugepanel.h"
#include "gaugepanelplugin.h"

#include <QtPlugin>

GaugePanelPlugin::GaugePanelPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugePanelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugePanelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugePanelPlugin::createWidget(QWidget *parent)
{
    return new GaugePanel(parent);
}

QString GaugePanelPlugin::name() const
{
    return QLatin1String("GaugePanel");
}

QString GaugePanelPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugePanelPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugepanel.png"));
}

QString GaugePanelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugePanelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugePanelPlugin::isContainer() const
{
    return false;
}

QString GaugePanelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugePanel\" name=\"gaugePanel\">\n</widget>\n");
}

QString GaugePanelPlugin::includeFile() const
{
    return QLatin1String("gaugepanel.h");
}

