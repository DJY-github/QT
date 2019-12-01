#include "../include/adswidget2.h"
#include "adswidget2plugin.h"

#include <QtPlugin>

AdsWidget2Plugin::AdsWidget2Plugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void AdsWidget2Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AdsWidget2Plugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AdsWidget2Plugin::createWidget(QWidget *parent)
{
    return new AdsWidget2(parent);
}

QString AdsWidget2Plugin::name() const
{
    return QLatin1String("AdsWidget2");
}

QString AdsWidget2Plugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon AdsWidget2Plugin::icon() const
{
    return QIcon(QLatin1String(":/ico/adswidget2.png"));
}

QString AdsWidget2Plugin::toolTip() const
{
    return QLatin1String("");
}

QString AdsWidget2Plugin::whatsThis() const
{
    return QLatin1String("");
}

bool AdsWidget2Plugin::isContainer() const
{
    return false;
}

QString AdsWidget2Plugin::domXml() const
{
    return QLatin1String("<widget class=\"AdsWidget2\" name=\"adsWidget2\">\n</widget>\n");
}

QString AdsWidget2Plugin::includeFile() const
{
    return QLatin1String("adswidget2.h");
}

