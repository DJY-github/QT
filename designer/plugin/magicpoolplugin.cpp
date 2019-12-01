#include "../include/magicpool.h".h"
#include "magicpoolplugin.h"

#include <QtPlugin>

MagicPoolPlugin::MagicPoolPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void MagicPoolPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MagicPoolPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MagicPoolPlugin::createWidget(QWidget *parent)
{
    return new MagicPool(parent);
}

QString MagicPoolPlugin::name() const
{
    return QLatin1String("MagicPool");
}

QString MagicPoolPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon MagicPoolPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/magicpool.png"));
}

QString MagicPoolPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MagicPoolPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MagicPoolPlugin::isContainer() const
{
    return false;
}

QString MagicPoolPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MagicPool\" name=\"magicPool\">\n</widget>\n");
}

QString MagicPoolPlugin::includeFile() const
{
    return QLatin1String("magicpool.h");
}

