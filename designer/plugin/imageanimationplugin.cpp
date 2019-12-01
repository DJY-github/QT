#include "../include/imageanimation.h"
#include "imageanimationplugin.h"

#include <QtPlugin>

ImageAnimationPlugin::ImageAnimationPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ImageAnimationPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImageAnimationPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImageAnimationPlugin::createWidget(QWidget *parent)
{
    return new ImageAnimation(parent);
}

QString ImageAnimationPlugin::name() const
{
    return QLatin1String("ImageAnimation");
}

QString ImageAnimationPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImageAnimationPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imageanimation.png"));
}

QString ImageAnimationPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImageAnimationPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImageAnimationPlugin::isContainer() const
{
    return false;
}

QString ImageAnimationPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImageAnimation\" name=\"imageAnimation\">\n</widget>\n");
}

QString ImageAnimationPlugin::includeFile() const
{
    return QLatin1String("imageanimation.h");
}

