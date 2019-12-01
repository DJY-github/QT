#include "../include/rulerprogress.h"
#include "rulerprogressplugin.h"

#include <QtPlugin>

RulerProgressPlugin::RulerProgressPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerProgressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerProgressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerProgressPlugin::createWidget(QWidget *parent)
{
    return new RulerProgress(parent);
}

QString RulerProgressPlugin::name() const
{
    return QLatin1String("RulerProgress");
}

QString RulerProgressPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerProgressPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerprogress.png"));
}

QString RulerProgressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerProgressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerProgressPlugin::isContainer() const
{
    return false;
}

QString RulerProgressPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerProgress\" name=\"rulerProgress\">\n</widget>\n");
}

QString RulerProgressPlugin::includeFile() const
{
    return QLatin1String("rulerprogress.h");
}

