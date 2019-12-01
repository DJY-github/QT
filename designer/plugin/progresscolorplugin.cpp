#include "../include/progresscolor.h"
#include "progresscolorplugin.h"

#include <QtPlugin>

ProgressColorPlugin::ProgressColorPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressColorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressColorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressColorPlugin::createWidget(QWidget *parent)
{
    return new ProgressColor(parent);
}

QString ProgressColorPlugin::name() const
{
    return QLatin1String("ProgressColor");
}

QString ProgressColorPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressColorPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progresscolor.png"));
}

QString ProgressColorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressColorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressColorPlugin::isContainer() const
{
    return false;
}

QString ProgressColorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressColor\" name=\"progressColor\">\n</widget>\n");
}

QString ProgressColorPlugin::includeFile() const
{
    return QLatin1String("progresscolor.h");
}

