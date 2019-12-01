#include "../include/lunarcalendaritem.h"
#include "lunarcalendaritemplugin.h"

#include <QtPlugin>

LunarCalendarItemPlugin::LunarCalendarItemPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void LunarCalendarItemPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LunarCalendarItemPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LunarCalendarItemPlugin::createWidget(QWidget *parent)
{
    return new LunarCalendarItem(parent);
}

QString LunarCalendarItemPlugin::name() const
{
    return QLatin1String("LunarCalendarItem");
}

QString LunarCalendarItemPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LunarCalendarItemPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lunarcalendaritem.png"));
}

QString LunarCalendarItemPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LunarCalendarItemPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LunarCalendarItemPlugin::isContainer() const
{
    return false;
}

QString LunarCalendarItemPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LunarCalendarItem\" name=\"lunarCalendarItem\">\n</widget>\n");
}

QString LunarCalendarItemPlugin::includeFile() const
{
    return QLatin1String("lunarcalendaritem.h");
}

