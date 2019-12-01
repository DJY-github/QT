#include "../include/antline.h"
#include "antlineplugin.h"

#include <QtPlugin>

AntLinePlugin::AntLinePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void AntLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AntLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AntLinePlugin::createWidget(QWidget *parent)
{
    return new AntLine(parent);
}

QString AntLinePlugin::name() const
{
    return QLatin1String("AntLine");
}

QString AntLinePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon AntLinePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/antline.png"));
}

QString AntLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString AntLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool AntLinePlugin::isContainer() const
{
    return false;
}

QString AntLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"AntLine\" name=\"antLine\">\n</widget>\n");
}

QString AntLinePlugin::includeFile() const
{
    return QLatin1String("antline.h");
}

