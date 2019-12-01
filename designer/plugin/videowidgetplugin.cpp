#include "../include/videowidget.h"
#include "videowidgetplugin.h"

#include <QtPlugin>

VideoWidgetPlugin::VideoWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void VideoWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VideoWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VideoWidgetPlugin::createWidget(QWidget *parent)
{
    return new VideoWidget(parent);
}

QString VideoWidgetPlugin::name() const
{
    return QLatin1String("VideoWidget");
}

QString VideoWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon VideoWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/videowidget.png"));
}

QString VideoWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString VideoWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VideoWidgetPlugin::isContainer() const
{
    return false;
}

QString VideoWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VideoWidget\" name=\"videoWidget\">\n</widget>\n");
}

QString VideoWidgetPlugin::includeFile() const
{
    return QLatin1String("videowidget.h");
}

