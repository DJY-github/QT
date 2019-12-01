#include "../include/custompie.h"
#include "custompieplugin.h"

#include <QtPlugin>

CustomPiePlugin::CustomPiePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CustomPiePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomPiePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomPiePlugin::createWidget(QWidget *parent)
{
    return new CustomPie(parent);
}

QString CustomPiePlugin::name() const
{
    return QLatin1String("CustomPie");
}

QString CustomPiePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CustomPiePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/custompie.png"));
}

QString CustomPiePlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomPiePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomPiePlugin::isContainer() const
{
    return false;
}

QString CustomPiePlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomPie\" name=\"customPie\">\n</widget>\n");
}

QString CustomPiePlugin::includeFile() const
{
    return QLatin1String("custompie.h");
}

