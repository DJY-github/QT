#include "../include/buttongroup.h"
#include "buttongroupplugin.h"

#include <QtPlugin>

ButtonGroupPlugin::ButtonGroupPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ButtonGroupPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ButtonGroupPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ButtonGroupPlugin::createWidget(QWidget *parent)
{
    return new ButtonGroup(parent);
}

QString ButtonGroupPlugin::name() const
{
    return QLatin1String("ButtonGroup");
}

QString ButtonGroupPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ButtonGroupPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/buttongroup.png"));
}

QString ButtonGroupPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ButtonGroupPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ButtonGroupPlugin::isContainer() const
{
    return false;
}

QString ButtonGroupPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ButtonGroup\" name=\"buttonGroup\">\n</widget>\n");
}

QString ButtonGroupPlugin::includeFile() const
{
    return QLatin1String("buttongroup.h");
}

