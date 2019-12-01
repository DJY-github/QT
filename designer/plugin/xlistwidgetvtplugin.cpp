#include "../include/xlistwidgetvt.h"
#include "xlistwidgetvtplugin.h"

#include <QtPlugin>

XListWidgetVTPlugin::XListWidgetVTPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XListWidgetVTPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XListWidgetVTPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XListWidgetVTPlugin::createWidget(QWidget *parent)
{
    return new XListWidgetVT(parent);
}

QString XListWidgetVTPlugin::name() const
{
    return QLatin1String("XListWidgetVT");
}

QString XListWidgetVTPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XListWidgetVTPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/xlistwidgetvt.png"));
}

QString XListWidgetVTPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XListWidgetVTPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XListWidgetVTPlugin::isContainer() const
{
    return false;
}

QString XListWidgetVTPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XListWidgetVT\" name=\"xlistWidgetVT\">\n</widget>\n");
}

QString XListWidgetVTPlugin::includeFile() const
{
    return QLatin1String("xlistwidgetvt.h");
}

