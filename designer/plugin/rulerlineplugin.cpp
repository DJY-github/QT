#include "../include/rulerline.h"
#include "rulerlineplugin.h"

#include <QtPlugin>

RulerLinePlugin::RulerLinePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerLinePlugin::createWidget(QWidget *parent)
{
    return new RulerLine(parent);
}

QString RulerLinePlugin::name() const
{
    return QLatin1String("RulerLine");
}

QString RulerLinePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerLinePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerline.png"));
}

QString RulerLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerLinePlugin::isContainer() const
{
    return false;
}

QString RulerLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerLine\" name=\"rulerLine\">\n</widget>\n");
}

QString RulerLinePlugin::includeFile() const
{
    return QLatin1String("rulerline.h");
}

