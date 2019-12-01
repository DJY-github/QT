#include "../include/magicfish.h"
#include "magicfishplugin.h"

#include <QtPlugin>

MagicFishPlugin::MagicFishPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void MagicFishPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MagicFishPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MagicFishPlugin::createWidget(QWidget *parent)
{
    return new MagicFish(parent);
}

QString MagicFishPlugin::name() const
{
    return QLatin1String("MagicFish");
}

QString MagicFishPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon MagicFishPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/magicfish.png"));
}

QString MagicFishPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MagicFishPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MagicFishPlugin::isContainer() const
{
    return false;
}

QString MagicFishPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MagicFish\" name=\"magicFish\">\n</widget>\n");
}

QString MagicFishPlugin::includeFile() const
{
    return QLatin1String("magicfish.h");
}

