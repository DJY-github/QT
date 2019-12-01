#include "../include/rulerdouble.h"
#include "rulerdoubleplugin.h"

#include <QtPlugin>

RulerDoublePlugin::RulerDoublePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerDoublePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerDoublePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerDoublePlugin::createWidget(QWidget *parent)
{
    return new RulerDouble(parent);
}

QString RulerDoublePlugin::name() const
{
    return QLatin1String("RulerDouble");
}

QString RulerDoublePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerDoublePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerdouble.png"));
}

QString RulerDoublePlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerDoublePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerDoublePlugin::isContainer() const
{
    return false;
}

QString RulerDoublePlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerDouble\" name=\"rulerDouble\">\n</widget>\n");
}

QString RulerDoublePlugin::includeFile() const
{
    return QLatin1String("rulerdouble.h");
}

