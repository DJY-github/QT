#include "../include/rulertemp.h"
#include "rulertempplugin.h"

#include <QtPlugin>

RulerTempPlugin::RulerTempPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerTempPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerTempPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerTempPlugin::createWidget(QWidget *parent)
{
    return new RulerTemp(parent);
}

QString RulerTempPlugin::name() const
{
    return QLatin1String("RulerTemp");
}

QString RulerTempPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerTempPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulertemp.png"));
}

QString RulerTempPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerTempPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerTempPlugin::isContainer() const
{
    return false;
}

QString RulerTempPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerTemp\" name=\"rulerTemp\">\n</widget>\n");
}

QString RulerTempPlugin::includeFile() const
{
    return QLatin1String("rulertemp.h");
}

