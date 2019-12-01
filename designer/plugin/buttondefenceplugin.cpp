#include "../include/buttondefence.h"
#include "buttondefenceplugin.h"

#include <QtPlugin>

ButtonDefencePlugin::ButtonDefencePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ButtonDefencePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ButtonDefencePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ButtonDefencePlugin::createWidget(QWidget *parent)
{
    return new ButtonDefence(parent);
}

QString ButtonDefencePlugin::name() const
{
    return QLatin1String("ButtonDefence");
}

QString ButtonDefencePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ButtonDefencePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/buttondefence.png"));
}

QString ButtonDefencePlugin::toolTip() const
{
    return QLatin1String("");
}

QString ButtonDefencePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ButtonDefencePlugin::isContainer() const
{
    return false;
}

QString ButtonDefencePlugin::domXml() const
{
    return QLatin1String("<widget class=\"ButtonDefence\" name=\"buttonDefence\">\n</widget>\n");
}

QString ButtonDefencePlugin::includeFile() const
{
    return QLatin1String("buttondefence.h");
}

