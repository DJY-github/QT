#include "../include/progresswait.h"
#include "progresswaitplugin.h"

#include <QtPlugin>

ProgressWaitPlugin::ProgressWaitPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressWaitPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressWaitPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressWaitPlugin::createWidget(QWidget *parent)
{
    return new ProgressWait(parent);
}

QString ProgressWaitPlugin::name() const
{
    return QLatin1String("ProgressWait");
}

QString ProgressWaitPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressWaitPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progresswait.png"));
}

QString ProgressWaitPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressWaitPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressWaitPlugin::isContainer() const
{
    return false;
}

QString ProgressWaitPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressWait\" name=\"progressWait\">\n</widget>\n");
}

QString ProgressWaitPlugin::includeFile() const
{
    return QLatin1String("progresswait.h");
}

