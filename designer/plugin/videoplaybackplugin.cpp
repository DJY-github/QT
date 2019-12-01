#include "../include/videoplayback.h"
#include "videoplaybackplugin.h"

#include <QtPlugin>

VideoPlaybackPlugin::VideoPlaybackPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void VideoPlaybackPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VideoPlaybackPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VideoPlaybackPlugin::createWidget(QWidget *parent)
{
    return new VideoPlayback(parent);
}

QString VideoPlaybackPlugin::name() const
{
    return QLatin1String("VideoPlayback");
}

QString VideoPlaybackPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon VideoPlaybackPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/videoplayback.png"));
}

QString VideoPlaybackPlugin::toolTip() const
{
    return QLatin1String("");
}

QString VideoPlaybackPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VideoPlaybackPlugin::isContainer() const
{
    return false;
}

QString VideoPlaybackPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VideoPlayback\" name=\"videoPlayback\">\n</widget>\n");
}

QString VideoPlaybackPlugin::includeFile() const
{
    return QLatin1String("videoplayback.h");
}

