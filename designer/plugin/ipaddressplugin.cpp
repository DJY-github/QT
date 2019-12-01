#include "../include/ipaddress.h"
#include "ipaddressplugin.h"

#include <QtPlugin>

IPAddressPlugin::IPAddressPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void IPAddressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IPAddressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IPAddressPlugin::createWidget(QWidget *parent)
{
    return new IPAddress(parent);
}

QString IPAddressPlugin::name() const
{
    return QLatin1String("IPAddress");
}

QString IPAddressPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon IPAddressPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/ipaddress.png"));
}

QString IPAddressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IPAddressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool IPAddressPlugin::isContainer() const
{
    return false;
}

QString IPAddressPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IPAddress\" name=\"ipaddress\">\n</widget>\n");
}

QString IPAddressPlugin::includeFile() const
{
    return QLatin1String("ipaddress.h");
}

