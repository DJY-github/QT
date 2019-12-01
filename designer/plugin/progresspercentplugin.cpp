#include "../include/progresspercent.h"
#include "progresspercentplugin.h"

#include <QtPlugin>

ProgressPercentPlugin::ProgressPercentPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressPercentPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressPercentPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressPercentPlugin::createWidget(QWidget *parent)
{
    return new ProgressPercent(parent);
}

QString ProgressPercentPlugin::name() const
{
    return QLatin1String("ProgressPercent");
}

QString ProgressPercentPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressPercentPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progresspercent.png"));
}

QString ProgressPercentPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressPercentPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressPercentPlugin::isContainer() const
{
    return false;
}

QString ProgressPercentPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressPercent\" name=\"progressPercent\">\n</widget>\n");
}

QString ProgressPercentPlugin::includeFile() const
{
    return QLatin1String("progresspercent.h");
}

