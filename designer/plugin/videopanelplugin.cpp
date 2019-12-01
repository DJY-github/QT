#include "../include/videopanel.h"
#include "videopanelplugin.h"

#include <QtPlugin>

VideoPanelPlugin::VideoPanelPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void VideoPanelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VideoPanelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VideoPanelPlugin::createWidget(QWidget *parent)
{
    return new VideoPanel(parent);
}

QString VideoPanelPlugin::name() const
{
    return QLatin1String("VideoPanel");
}

QString VideoPanelPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon VideoPanelPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/videopanel.png"));
}

QString VideoPanelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString VideoPanelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VideoPanelPlugin::isContainer() const
{
    return false;
}

QString VideoPanelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VideoPanel\" name=\"videoPanel\">\n</widget>\n");
}

QString VideoPanelPlugin::includeFile() const
{
    return QLatin1String("videopanel.h");
}

