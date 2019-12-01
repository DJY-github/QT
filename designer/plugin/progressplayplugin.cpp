#include "../include/progressplay.h"
#include "progressplayplugin.h"

#include <QtPlugin>

ProgressPlayPlugin::ProgressPlayPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressPlayPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressPlayPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressPlayPlugin::createWidget(QWidget *parent)
{
    return new ProgressPlay(parent);
}

QString ProgressPlayPlugin::name() const
{
    return QLatin1String("ProgressPlay");
}

QString ProgressPlayPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressPlayPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressplay.png"));
}

QString ProgressPlayPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressPlayPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressPlayPlugin::isContainer() const
{
    return false;
}

QString ProgressPlayPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressPlay\" name=\"progressPlay\">\n</widget>\n");
}

QString ProgressPlayPlugin::includeFile() const
{
    return QLatin1String("progressplay.h");
}

