#include "../include/panelitem.h"
#include "panelitemplugin.h"

#include <QtPlugin>

PanelItemPlugin::PanelItemPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void PanelItemPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PanelItemPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PanelItemPlugin::createWidget(QWidget *parent)
{
    return new PanelItem(parent);
}

QString PanelItemPlugin::name() const
{
    return QLatin1String("PanelItem");
}

QString PanelItemPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon PanelItemPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/panelitem.png"));
}

QString PanelItemPlugin::toolTip() const
{
    return QLatin1String("");
}

QString PanelItemPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool PanelItemPlugin::isContainer() const
{
    return true;
}

QString PanelItemPlugin::domXml() const
{
    return QLatin1String("<widget class=\"PanelItem\" name=\"panelItem\">\n</widget>\n");
}

QString PanelItemPlugin::includeFile() const
{
    return QLatin1String("panelitem.h");
}

