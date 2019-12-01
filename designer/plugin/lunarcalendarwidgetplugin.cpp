#include "../include/lunarcalendarwidget.h"
#include "lunarcalendarwidgetplugin.h"

#include <QtPlugin>

LunarCalendarWidgetPlugin::LunarCalendarWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void LunarCalendarWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LunarCalendarWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LunarCalendarWidgetPlugin::createWidget(QWidget *parent)
{
    return new LunarCalendarWidget(parent);
}

QString LunarCalendarWidgetPlugin::name() const
{
    return QLatin1String("LunarCalendarWidget");
}

QString LunarCalendarWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LunarCalendarWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lunarcalendarwidget.png"));
}

QString LunarCalendarWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LunarCalendarWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LunarCalendarWidgetPlugin::isContainer() const
{
    return false;
}

QString LunarCalendarWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LunarCalendarWidget\" name=\"lunarCalendarWidget\">\n</widget>\n");
}

QString LunarCalendarWidgetPlugin::includeFile() const
{
    return QLatin1String("lunarcalendarwidget.h");
}

