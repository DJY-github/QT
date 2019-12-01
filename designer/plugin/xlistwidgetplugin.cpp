#include "../include/xlistwidget.h"
#include "xlistwidgetplugin.h"

#include <QtPlugin>

XListWidgetPlugin::XListWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XListWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XListWidgetPlugin::createWidget(QWidget *parent)
{
    return new XListWidget(parent);
}

QString XListWidgetPlugin::name() const
{
    return QLatin1String("XListWidget");
}

QString XListWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XListWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/xlistwidget.png"));
}

QString XListWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XListWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XListWidgetPlugin::isContainer() const
{
    return false;
}

QString XListWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XListWidget\" name=\"xlistWidget\">\n</widget>\n");
}

QString XListWidgetPlugin::includeFile() const
{
    return QLatin1String("xlistwidget.h");
}

