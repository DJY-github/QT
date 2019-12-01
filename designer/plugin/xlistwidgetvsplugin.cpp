#include "../include/xlistwidgetvs.h"
#include "xlistwidgetvsplugin.h"

#include <QtPlugin>

XListWidgetVSPlugin::XListWidgetVSPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XListWidgetVSPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XListWidgetVSPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XListWidgetVSPlugin::createWidget(QWidget *parent)
{
    return new XListWidgetVS(parent);
}

QString XListWidgetVSPlugin::name() const
{
    return QLatin1String("XListWidgetVS");
}

QString XListWidgetVSPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XListWidgetVSPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/xlistwidgetvs.png"));
}

QString XListWidgetVSPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XListWidgetVSPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XListWidgetVSPlugin::isContainer() const
{
    return false;
}

QString XListWidgetVSPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XListWidgetVS\" name=\"xlistWidgetVS\">\n</widget>\n");
}

QString XListWidgetVSPlugin::includeFile() const
{
    return QLatin1String("xlistwidgetvs.h");
}

