#include "../include/magicmouse.h"
#include "magicmouseplugin.h"

#include <QtPlugin>

MagicMousePlugin::MagicMousePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void MagicMousePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MagicMousePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MagicMousePlugin::createWidget(QWidget *parent)
{
    return new MagicMouse(parent);
}

QString MagicMousePlugin::name() const
{
    return QLatin1String("MagicMouse");
}

QString MagicMousePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon MagicMousePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/magicmouse.png"));
}

QString MagicMousePlugin::toolTip() const
{
    return QLatin1String("");
}

QString MagicMousePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MagicMousePlugin::isContainer() const
{
    return false;
}

QString MagicMousePlugin::domXml() const
{
    return QLatin1String("<widget class=\"MagicMouse\" name=\"magicMouse\">\n</widget>\n");
}

QString MagicMousePlugin::includeFile() const
{
    return QLatin1String("magicmouse.h");
}

