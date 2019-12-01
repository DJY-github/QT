#include "../include/tiledbg.h".h"
#include "tiledbgplugin.h"

#include <QtPlugin>

TiledBgPlugin::TiledBgPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TiledBgPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TiledBgPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TiledBgPlugin::createWidget(QWidget *parent)
{
    return new TiledBg(parent);
}

QString TiledBgPlugin::name() const
{
    return QLatin1String("TiledBg");
}

QString TiledBgPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TiledBgPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/tiledbg.png"));
}

QString TiledBgPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TiledBgPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TiledBgPlugin::isContainer() const
{
    return false;
}

QString TiledBgPlugin::domXml() const
{
    return QLatin1String("<widget class=\"TiledBg\" name=\"tiledBg\">\n</widget>\n");
}

QString TiledBgPlugin::includeFile() const
{
    return QLatin1String("tiledbg.h");
}

