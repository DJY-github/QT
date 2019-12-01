#include "../include/selectwidget.h"
#include "selectwidgetplugin.h"

#include <QtPlugin>

SelectWidgetPlugin::SelectWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void SelectWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SelectWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SelectWidgetPlugin::createWidget(QWidget *parent)
{
    return new SelectWidget(parent);
}

QString SelectWidgetPlugin::name() const
{
    return QLatin1String("SelectWidget");
}

QString SelectWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SelectWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/selectwidget.png"));
}

QString SelectWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SelectWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SelectWidgetPlugin::isContainer() const
{
    return false;
}

QString SelectWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SelectWidget\" name=\"selectWidget\">\n</widget>\n");
}

QString SelectWidgetPlugin::includeFile() const
{
    return QLatin1String("selectwidget.h");
}

