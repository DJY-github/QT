#include "../include/tumblerdatetime.h"
#include "tumblerdatetimeplugin.h"

#include <QtPlugin>

TumblerDateTimePlugin::TumblerDateTimePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TumblerDateTimePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TumblerDateTimePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TumblerDateTimePlugin::createWidget(QWidget *parent)
{
    return new TumblerDateTime(parent);
}

QString TumblerDateTimePlugin::name() const
{
    return QLatin1String("TumblerDateTime");
}

QString TumblerDateTimePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TumblerDateTimePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/tumblerdatetime.png"));
}

QString TumblerDateTimePlugin::toolTip() const
{
    return QLatin1String("");
}

QString TumblerDateTimePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TumblerDateTimePlugin::isContainer() const
{
    return false;
}

QString TumblerDateTimePlugin::domXml() const
{
    return QLatin1String("<widget class=\"TumblerDateTime\" name=\"tumblerDateTime\">\n</widget>\n");
}

QString TumblerDateTimePlugin::includeFile() const
{
    return QLatin1String("tumblerdatetime.h");
}

