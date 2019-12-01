#include "../include/lcddatetime.h"
#include "lcddatetimeplugin.h"

#include <QtPlugin>

LcdDateTimePlugin::LcdDateTimePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void LcdDateTimePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LcdDateTimePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LcdDateTimePlugin::createWidget(QWidget *parent)
{
    return new LcdDateTime(parent);
}

QString LcdDateTimePlugin::name() const
{
    return QLatin1String("LcdDateTime");
}

QString LcdDateTimePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LcdDateTimePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lcddatetime.png"));
}

QString LcdDateTimePlugin::toolTip() const
{
    return QLatin1String("");
}

QString LcdDateTimePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LcdDateTimePlugin::isContainer() const
{
    return false;
}

QString LcdDateTimePlugin::domXml() const
{
    return QLatin1String("<widget class=\"LcdDateTime\" name=\"lcdDateTime\">\n</widget>\n");
}

QString LcdDateTimePlugin::includeFile() const
{
    return QLatin1String("lcddatetime.h");
}

