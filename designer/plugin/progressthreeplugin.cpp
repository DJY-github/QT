#include "../include/progressthree.h"
#include "progressthreeplugin.h"

#include <QtPlugin>

ProgressThreePlugin::ProgressThreePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressThreePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressThreePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressThreePlugin::createWidget(QWidget *parent)
{
    return new ProgressThree(parent);
}

QString ProgressThreePlugin::name() const
{
    return QLatin1String("ProgressThree");
}

QString ProgressThreePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressThreePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressthree.png"));
}

QString ProgressThreePlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressThreePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressThreePlugin::isContainer() const
{
    return false;
}

QString ProgressThreePlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressThree\" name=\"progressThree\">\n</widget>\n");
}

QString ProgressThreePlugin::includeFile() const
{
    return QLatin1String("progressthree.h");
}

