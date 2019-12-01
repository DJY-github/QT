#include "../include/progressring.h"
#include "progressringplugin.h"

#include <QtPlugin>

ProgressRingPlugin::ProgressRingPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressRingPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressRingPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressRingPlugin::createWidget(QWidget *parent)
{
    return new ProgressRing(parent);
}

QString ProgressRingPlugin::name() const
{
    return QLatin1String("ProgressRing");
}

QString ProgressRingPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressRingPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressring.png"));
}

QString ProgressRingPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressRingPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressRingPlugin::isContainer() const
{
    return false;
}

QString ProgressRingPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressRing\" name=\"progressRing\">\n</widget>\n");
}

QString ProgressRingPlugin::includeFile() const
{
    return QLatin1String("progressring.h");
}

