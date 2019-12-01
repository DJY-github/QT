#include "../include/progressbutton.h"
#include "progressbuttonplugin.h"

#include <QtPlugin>

ProgressButtonPlugin::ProgressButtonPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressButtonPlugin::createWidget(QWidget *parent)
{
    return new ProgressButton(parent);
}

QString ProgressButtonPlugin::name() const
{
    return QLatin1String("ProgressButton");
}

QString ProgressButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressbutton.png"));
}

QString ProgressButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressButtonPlugin::isContainer() const
{
    return false;
}

QString ProgressButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressButton\" name=\"progressButton\">\n</widget>\n");
}

QString ProgressButtonPlugin::includeFile() const
{
    return QLatin1String("progressbutton.h");
}

