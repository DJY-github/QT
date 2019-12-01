#include "../include/customring.h"
#include "customringplugin.h"

#include <QtPlugin>

CustomRingPlugin::CustomRingPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CustomRingPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomRingPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomRingPlugin::createWidget(QWidget *parent)
{
    return new CustomRing(parent);
}

QString CustomRingPlugin::name() const
{
    return QLatin1String("CustomRing");
}

QString CustomRingPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CustomRingPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/customring.png"));
}

QString CustomRingPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomRingPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomRingPlugin::isContainer() const
{
    return false;
}

QString CustomRingPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomRing\" name=\"customRing\">\n</widget>\n");
}

QString CustomRingPlugin::includeFile() const
{
    return QLatin1String("customring.h");
}

