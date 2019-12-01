#include "../include/progressround.h"
#include "progressroundplugin.h"

#include <QtPlugin>

ProgressRoundPlugin::ProgressRoundPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressRoundPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressRoundPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressRoundPlugin::createWidget(QWidget *parent)
{
    return new ProgressRound(parent);
}

QString ProgressRoundPlugin::name() const
{
    return QLatin1String("ProgressRound");
}

QString ProgressRoundPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressRoundPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressround.png"));
}

QString ProgressRoundPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressRoundPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressRoundPlugin::isContainer() const
{
    return false;
}

QString ProgressRoundPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressRound\" name=\"progressRound\">\n</widget>\n");
}

QString ProgressRoundPlugin::includeFile() const
{
    return QLatin1String("progressround.h");
}

