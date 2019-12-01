#include "../include/rulerbar.h"
#include "rulerbarplugin.h"

#include <QtPlugin>

RulerBarPlugin::RulerBarPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void RulerBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RulerBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RulerBarPlugin::createWidget(QWidget *parent)
{
    return new RulerBar(parent);
}

QString RulerBarPlugin::name() const
{
    return QLatin1String("RulerBar");
}

QString RulerBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RulerBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/rulerbar.png"));
}

QString RulerBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RulerBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RulerBarPlugin::isContainer() const
{
    return false;
}

QString RulerBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RulerBar\" name=\"rulerBar\">\n</widget>\n");
}

QString RulerBarPlugin::includeFile() const
{
    return QLatin1String("rulerbar.h");
}

