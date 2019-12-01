#include "../include/rulerscale.h"
#include "rulerscaleplugin.h"

#include <QtPlugin>

RulerScalePlugin::RulerScalePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerScalePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerScalePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerScalePlugin::createWidget(QWidget *parent)
{
    return new RulerScale(parent);
}

QString RulerScalePlugin::name() const
{
    return QLatin1String("RulerScale");
}

QString RulerScalePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerScalePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerscale.png"));
}

QString RulerScalePlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerScalePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerScalePlugin::isContainer() const
{
    return false;
}

QString RulerScalePlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerScale\" name=\"rulerScale\">\n</widget>\n");
}

QString RulerScalePlugin::includeFile() const
{
    return QLatin1String("rulerscale.h");
}

