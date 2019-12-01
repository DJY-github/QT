#include "../include/xprogressbar.h"
#include "xprogressbarplugin.h"

#include <QtPlugin>

XProgressBarPlugin::XProgressBarPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XProgressBarPlugin::createWidget(QWidget *parent)
{
    return new XProgressBar(parent);
}

QString XProgressBarPlugin::name() const
{
    return QLatin1String("XProgressBar");
}

QString XProgressBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XProgressBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/xprogressbar.png"));
}

QString XProgressBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XProgressBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XProgressBarPlugin::isContainer() const
{
    return false;
}

QString XProgressBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XProgressBar\" name=\"xProgressBar\">\n</widget>\n");
}

QString XProgressBarPlugin::includeFile() const
{
    return QLatin1String("xprogressbar.h");
}

