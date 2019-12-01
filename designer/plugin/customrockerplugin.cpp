#include "../include/customrocker.h"
#include "customrockerplugin.h"

#include <QtPlugin>

CustomRockerPlugin::CustomRockerPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CustomRockerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomRockerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomRockerPlugin::createWidget(QWidget *parent)
{
    return new CustomRocker(parent);
}

QString CustomRockerPlugin::name() const
{
    return QLatin1String("CustomRocker");
}

QString CustomRockerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CustomRockerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/customrocker.png"));
}

QString CustomRockerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomRockerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomRockerPlugin::isContainer() const
{
    return false;
}

QString CustomRockerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomRocker\" name=\"customRocker\">\n</widget>\n");
}

QString CustomRockerPlugin::includeFile() const
{
    return QLatin1String("customrocker.h");
}

