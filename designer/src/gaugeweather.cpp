#pragma execution_character_set("utf-8")

#include "gaugeweather.h"
#include "qsvgrenderer.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qfile.h"
#include "qdebug.h"

GaugeWeather::GaugeWeather(QWidget *parent) : QWidget(parent)
{
    outerMinValue = 0;
    outerMaxValue = 100;
    outerStartAngle = 0;
    outerEndAngle = 0;
    outerValue = 0;
    outerCurrValue = 0;
    outerRingBgColor = QColor(250, 250, 250);
    outerRingColor = QColor(34, 163, 169);

    innerValue = 0;
    innerMinValue = -50;
    innerMaxValue = 50;
    innerStartAngle = 0;
    innerEndAngle = 135;    
    innerCurrValue = 0;
    innerRingBgColor = QColor(250, 250, 250);
    innerRingNegativeColor = QColor(214, 5, 5);
    innerRingPositiveColor = QColor(0, 254, 254);

    innerScaleMajor = 2;
    innerScaleMinor = 0;
    innerScaleColor = QColor(255, 255, 255);
    innerScaleNumColor = QColor(255, 255, 255);

    centerPixMapNegativeColor = QColor(214, 5, 5);
    centerPixMapPositiveColor = QColor(0, 254, 254);

    outerValueTextColor = QColor(34, 163, 169);
    innerNegativeValueTextColor = QColor(214, 5, 5);
    innerPositiveValueTextColor = QColor(0, 254, 254);

    precision = 0;
    outerReverse = false;
    innerReverse = false;
    clockWise = true;

    animation = false;
    animationStep = 2;
    weatherType = SUNNY;
    centerSvgPath = ":/svg/weather-sunny.svg";

    outerTimer = new QTimer(this);
    outerTimer->setInterval(10);
    connect(outerTimer, SIGNAL(timeout()), this, SLOT(updateOuterValue()));

    innerTimer = new QTimer(this);
    innerTimer->setInterval(10);
    connect(innerTimer, SIGNAL(timeout()), this, SLOT(updateInnerValue()));

    setFont(QFont("Arial", 9));
}

GaugeWeather::~GaugeWeather()
{
    if (outerTimer->isActive()) {
        outerTimer->stop();
    }

    if(innerTimer->isActive()) {
        innerTimer->stop();
    }
}

void GaugeWeather::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外环背景
    drawOuterRingBg(&painter);
    //绘制外环进度
    drawOuterRing(&painter);
    //绘制内环背景
    drawInnerRingBg(&painter);
    //绘制内环进度
    drawInnerRing(&painter);
    //绘制内环刻度值
    drawInnerRingScaleNum(&painter);
    //绘制中心图片
    drawCenterPixMap(&painter);
    //绘制数值
    drawValue(&painter);
}

void GaugeWeather::drawOuterRingBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制圆弧方法绘制圆环
    int penWidth = 13;
    QRectF rect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    //可以自行修改画笔的后三个参数,形成各种各样的效果,例如Qt::FlatCap改为Qt::RoundCap可以产生圆角效果
    QPen pen(outerRingBgColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //计算总范围角度
    double angleAll = 360.0 - outerStartAngle - outerEndAngle;

    //绘制总范围角度圆弧
    pen.setColor(outerRingBgColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - outerStartAngle - angleAll) * 16, angleAll * 16);
    painter->restore();
}

void GaugeWeather::drawOuterRing(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制圆弧方法绘制圆环
    int penWidth = 13;
    QRectF rect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    //可以自行修改画笔的后三个参数,形成各种各样的效果,例如Qt::FlatCap改为Qt::RoundCap可以产生圆角效果
    QPen pen(outerRingColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - outerStartAngle - outerEndAngle;
    double angleCurrent = angleAll * ((outerCurrValue - outerMinValue) / (outerMaxValue - outerMinValue));

    //绘制当前值饼圆
    painter->setPen(pen);
    painter->drawArc(rect, (270 - outerStartAngle - angleCurrent) * 16, angleCurrent * 16);
    painter->restore();
}

void GaugeWeather::drawInnerRingBg(QPainter *painter)
{
    int radius = 77;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    double penWidth = 13;
    QPen pen(innerRingBgColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);
    painter->setPen(pen);

    double angleAll = 360.0 - innerStartAngle - innerEndAngle;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //零值以上背景
    painter->drawArc(rect, (270 - innerStartAngle -  angleAll) * 16 , angleAll * 16);
    //零值以下背景
    //painter->drawArc(rect,(270 -innerStartAngle -  null2MinAngle) * 16 ,null2MinAngle * 16);

    painter->restore();
}

void GaugeWeather::drawInnerRing(QPainter *painter)
{
    int radius = 77;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    int penWidth = 13.5;
    QPen pen(innerRingPositiveColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    double angleAll = 360.0 - innerStartAngle - innerEndAngle;
    double null2MinAngle = angleAll * (( 0 - innerMinValue) / (innerMaxValue - innerMinValue));  //零点所占的角度
    double nullUpAllAngle = angleAll - null2MinAngle;   //正基本角度
    double currAngle;
    if(innerCurrValue >= 0) {
        //正角度
        pen.setColor(innerRingNegativeColor);
        currAngle = nullUpAllAngle * (innerCurrValue / innerMaxValue)  * -1;
    } else {
        //负角度
        pen.setColor(innerRingPositiveColor);
        currAngle = null2MinAngle * (innerCurrValue / innerMinValue);
    }

    painter->setPen(pen);

    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, (270 - innerStartAngle -  null2MinAngle) * 16 , currAngle * 16);

    painter->restore();

}

void GaugeWeather::drawInnerRingScale(QPainter *painter)
{
    int radius = 76;
    painter->save();
    painter->setPen(innerScaleColor);

    painter->rotate(innerStartAngle);
    int steps = (innerScaleMajor * innerScaleMinor);
    double angleStep = (360.0 - innerStartAngle - innerEndAngle) / steps;
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % innerScaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 12, 0, radius);
        } else {
            pen.setWidthF(1.0);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeWeather::drawInnerRingScaleNum(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(innerScaleNumColor);

    double startRad = (360 - innerStartAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - innerStartAngle - innerEndAngle) * (M_PI / 180) / innerScaleMajor;

    for (int i = 0; i <= innerScaleMajor; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        double value = 1.0 * i * ((innerMaxValue - innerMinValue) / innerScaleMajor) + innerMinValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeWeather::drawCenterPixMap(QPainter *painter)
{
    painter->save();
    int width_svg = 50;
    int height_svg = 50;

    QFile file(centerSvgPath);
    file.open(QIODevice::ReadOnly);
    QByteArray baData = file.readAll();
    QDomDocument doc;
    doc.setContent(baData);
    file.close();

    //正负角度切换不同颜色
    if(innerCurrValue >= 0) {
        setColor(doc.documentElement(), "path", "fill", rgb2HexStr(centerPixMapNegativeColor));
    } else {
        setColor(doc.documentElement(), "path", "fill", rgb2HexStr(centerPixMapPositiveColor));
    }

    QSvgRenderer m_svgRender(doc.toByteArray());
    m_svgRender.render(painter , QRectF(-width_svg, -height_svg / 2, width_svg , height_svg));
    painter->restore();
}

void GaugeWeather::drawValue(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    painter->setPen(outerValueTextColor);

    QFontMetrics fm = painter->fontMetrics();
    QString outerStrValue = QString("h: %1%").arg(QString::number(outerCurrValue, 'f', 0));
    QRectF titleRect(5, 0, fm.width(outerStrValue), fm.height());
    painter->drawText(titleRect, Qt::AlignHCenter | Qt::AlignTop, outerStrValue);
    if(innerCurrValue >= 0 ) {
        painter->setPen(innerNegativeValueTextColor);
    } else {
        painter->setPen(innerPositiveValueTextColor);
    }

    QString innerDir = innerCurrValue >= 0 ? "+" : "-";
    QString innerStrValue = QString("t: %1%2℃").arg(innerDir).arg(QString::number(abs(innerCurrValue), 'f', 0));
    QRectF innerTitleRect(5, 0, fm.width(innerStrValue), -fm.height());
    painter->drawText(innerTitleRect, Qt::AlignHCenter | Qt::AlignVCenter, innerStrValue);

    painter->restore();
}

QString GaugeWeather::rgb2HexStr(const QColor &color)
{
    QString redStr = QString("%1").arg(color.red(), 2, 16, QChar('0'));
    QString greenStr = QString("%1").arg(color.green(), 2, 16, QChar('0'));
    QString blueStr = QString("%1").arg(color.blue(), 2, 16, QChar('0'));
    QString key = "#" + redStr + greenStr + blueStr;
    return key;
}

void GaugeWeather::setColor(QDomElement elem, QString strtagname, QString strattr, QString strattrval)
{
    if (elem.tagName().compare(strtagname) == 0) {
        elem.setAttribute(strattr, strattrval);
    }

    for (int i = 0; i < elem.childNodes().count(); i++) {
        if (!elem.childNodes().at(i).isElement()) {
            continue;
        }

        setColor(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
    }
}

double GaugeWeather::getOuterValue() const
{
    return this->outerValue;
}

double GaugeWeather::getOuterMinValue() const
{
    return this->outerMinValue;
}

double GaugeWeather::getOuterMaxValue() const
{
    return this->outerMaxValue;
}

int GaugeWeather::getOuterStartAngle() const
{
    return this->outerStartAngle;
}

int GaugeWeather::getOuterEndAngle() const
{
    return this->outerEndAngle;
}

QColor GaugeWeather::getOuterRingBgColor() const
{
    return this->outerRingBgColor;
}

QColor GaugeWeather::getOuterRingColor() const
{
    return this->outerRingColor;
}

QColor GaugeWeather::getOuterValueTextColor() const
{
    return this->outerValueTextColor;
}

double GaugeWeather::getInnerMinValue() const
{
    return this->innerMinValue;
}

double GaugeWeather::getInnerMaxValue() const
{
    return this->innerMaxValue;
}

double GaugeWeather::getInnerValue() const
{
    return this->innerValue;
}

int GaugeWeather::getInnerStartAngle() const
{
    return this->innerStartAngle;
}

int GaugeWeather::getInnerEndAngle() const
{
    return this->innerEndAngle;
}

QColor GaugeWeather::getInnerRingBgColor() const
{
    return this->innerRingBgColor;
}

QColor GaugeWeather::getInnerNegativeColor() const
{
    return this->innerRingNegativeColor;
}

QColor GaugeWeather::getInnerPositiveColor() const
{
    return this->innerRingPositiveColor;
}

int GaugeWeather::getInnerScaleMajor() const
{
    return this->innerScaleMajor;
}

int GaugeWeather::getInnerScaleMinor() const
{
    return this->innerScaleMinor;
}

QColor GaugeWeather::getInnerScaleColor() const
{
    return this->innerScaleColor;
}

QColor GaugeWeather::getInnerScaleNumColor() const
{
    return this->innerScaleNumColor;
}

QColor GaugeWeather::getInnerNegativeValueTextColor() const
{
    return this->innerNegativeValueTextColor;
}

QColor GaugeWeather::getInnerPositiveValueTextColor() const
{
    return this->innerPositiveValueTextColor;
}

QColor GaugeWeather::getCenterPixMapNegativeColor() const
{
    return this->centerPixMapNegativeColor;
}

QColor GaugeWeather::getCenterPixMapPositiveColor() const
{
    return this->centerPixMapPositiveColor;
}

bool GaugeWeather::getAnimation() const
{
    return this->animation;
}

double GaugeWeather::getAnimationStep() const
{
    return this->animationStep;
}

GaugeWeather::WeatherType GaugeWeather::getWeatherType()  const
{
    return this->weatherType;
}

QSize GaugeWeather::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeWeather::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeWeather::setOuterRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->outerMinValue = minValue;
    this->outerMaxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (outerValue < minValue || outerValue > maxValue) {
        setOuterValue(outerValue);
    }

    this->update();
}

void GaugeWeather::setOuterMinValue(double value)
{
    setOuterRange(value, outerMaxValue);
}

void GaugeWeather::setOuterMaxValue(double value)
{
    setOuterRange(outerMinValue, value);
}

void GaugeWeather::setOuterValue(double value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < outerMinValue || value > outerMaxValue || value == this->outerValue) {
        return;
    }

    if (value > this->outerValue) {
        outerReverse = false;
    } else if (value < this->outerValue) {
        outerReverse = true;
    }

    this->outerValue = value;
    emit valueChanged(value);

    if (!animation) {
        outerCurrValue = this->outerValue;
        this->update();
    } else {
        outerTimer->start();
    }
}

void GaugeWeather::setOuterStartAngle(int startAngle)
{
    if (this->outerStartAngle != startAngle) {
        this->outerStartAngle = startAngle;
        this->update();
    }
}

void GaugeWeather::setOuterEndAngle(int endAngle)
{
    if (this->outerEndAngle != endAngle) {
        this->outerEndAngle = endAngle;
        this->update();
    }
}

void GaugeWeather::setOuterRingBgColor(const QColor &color)
{
    if (this->outerRingBgColor != color) {
        this->outerRingBgColor = color;
        this->update();
    }
}

void GaugeWeather::setOuterRingColor(const QColor &color)
{
    if (this->outerRingColor != color) {
        this->outerRingColor = color;
        this->update();
    }
}

void GaugeWeather::setOuterValueTextColor(const QColor &color)
{
    if (this->outerValueTextColor != color) {
        this->outerValueTextColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->innerMinValue = minValue;
    this->innerMaxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (innerValue < minValue || innerValue > maxValue) {
        setInnerValue(innerValue);
    }

    this->update();
}

void GaugeWeather::setInnerMinValue(double value)
{
    setInnerRange(value, innerMaxValue);
}

void GaugeWeather::setInnerMaxValue(double value)
{
    setInnerRange(innerMinValue, value);
}

void GaugeWeather::setInnerValue(double value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < innerMinValue || value > innerMaxValue || value == this->innerValue) {
        return;
    }

    if(this->innerValue >= 0) {
        clockWise = true;
        if(value < this->innerValue) {
            //如果要设置的值小于已有的值，需要回滚
            innerReverse = true;
        } else {
            innerReverse = false;
        }
    } else {
        clockWise = false;
        if(value > this->innerValue) {
            //如果要设置的值大于已有的值，需要回滚
            innerReverse = true;
        } else {
            innerReverse = false;
        }
    }

    this->innerValue = value;
    emit valueChanged(value);

    if (!animation) {
        innerCurrValue = this->innerValue;
        this->update();
    } else {
        innerTimer->start();
    }
}

void GaugeWeather::setInnerStartAngle(int startAngle)
{
    if (this->innerStartAngle != startAngle) {
        this->innerStartAngle = startAngle;
        this->update();
    }
}

void GaugeWeather::setInnerEndAngle(int endAngle)
{
    if (this->innerEndAngle != endAngle) {
        this->innerEndAngle = endAngle;
        this->update();
    }
}

void GaugeWeather::setInnerRingBgColor(const QColor &color)
{
    if (this->innerRingBgColor != color) {
        this->innerRingBgColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerNegativeColor(const QColor &color)
{
    if (this->innerRingNegativeColor != color) {
        this->innerRingNegativeColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerPositiveColor(const QColor &color)
{
    if (this->innerRingPositiveColor != color) {
        this->innerRingPositiveColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerScaleMajor(int value)
{
    if (this->innerScaleMajor != value) {
        this->innerScaleMajor = value;
        this->update();
    }
}

void GaugeWeather::setInnerScaleMinor(int value)
{
    if (this->innerScaleMinor != value) {
        this->innerScaleMinor = value;
        this->update();
    }
}

void GaugeWeather::setInnerScaleColor(const QColor &color)
{
    if (this->innerScaleColor != color) {
        this->innerScaleColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerScaleNumColor(const QColor &color)
{
    if (this->innerScaleNumColor != color) {
        this->innerScaleNumColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerNegativeValueTextColor(const QColor &color)
{
    if (this->innerNegativeValueTextColor != color) {
        this->innerNegativeValueTextColor = color;
        this->update();
    }
}

void GaugeWeather::setInnerPositiveValueTextColor(const QColor &color)
{
    if (this->innerPositiveValueTextColor != color) {
        this->innerPositiveValueTextColor = color;
        this->update();
    }
}

void GaugeWeather::setCenterPixMapNegativeColor(const QColor &color)
{
    if (this->centerPixMapNegativeColor != color) {
        this->centerPixMapNegativeColor = color;
        this->update();
    }
}

void GaugeWeather::setCenterPixMapPositiveColor(const QColor &color)
{
    if (this->centerPixMapPositiveColor != color) {
        this->centerPixMapPositiveColor = color;
        this->update();
    }
}

void GaugeWeather::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void GaugeWeather::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void GaugeWeather::setWeatherType(GaugeWeather::WeatherType &type)
{
    if(this->weatherType != type) {
        this->weatherType = type;

        switch (type) {
        case SUNNY:
            centerSvgPath = ":/svg/weather-sunny.svg";
            break;
        case RAINY:
            centerSvgPath = ":/svg/weather-rainy.svg";
            break;
        case SNOWY:
            centerSvgPath = ":/svg/weather-snowy.svg";
            break;
        case CLOUDY:
            centerSvgPath = ":/svg/weather-cloudy.svg";
            break;
        case WINDY:
            centerSvgPath = ":/svg/weather-windy.svg";
            break;
        case SNOWY_RAINY:
            centerSvgPath = ":/svg/weather-snowy-rainy.svg";
            break;
        case HAIL:
            centerSvgPath = ":/svg/weather-hail.svg";
            break;
        case LIGHTNING:
            centerSvgPath = ":/svg/weather-lightning.svg";
            break;
        case FOG:
            centerSvgPath = ":/svg/weather-fog.svg";
            break;
        case PARTLYCLOUDY:
            centerSvgPath = ":/svg/weather-partlycloudy.svg";
            break;
        default:
            centerSvgPath = ":/svg/weather-sunny.svg";
            break;
        }

        this->update();
    }
}

void GaugeWeather::updateOuterValue()
{
    if (!outerReverse) {
        if (outerCurrValue >= outerValue) {
            outerCurrValue = outerValue;
            outerTimer->stop();
        } else {
            outerCurrValue += animationStep;
        }
    } else {
        if (outerCurrValue <= outerValue) {
            outerCurrValue = outerValue;
            outerTimer->stop();
        } else {
            outerCurrValue -= animationStep;
        }
    }

    this->update();
}

void GaugeWeather::updateInnerValue()
{
    //currValue变成Value的过程
    if(clockWise) {
        //针对value大于零时，当currValue 小于 Value，需要回滚，否则前滚，
        if (!innerReverse) {
            if (innerCurrValue >= innerValue) {
                innerCurrValue = innerValue;
                innerTimer->stop();
            } else {
                innerCurrValue += animationStep;
            }
        } else {
            if (innerCurrValue <= innerValue) {
                innerCurrValue = innerValue;
                innerTimer->stop();
            } else {
                innerCurrValue -= animationStep;
            }
        }

    } else {
        //针对value大于零时，当currValue 大于 Value，需要回滚，否则前滚，
        if (!innerReverse) {
            if (innerCurrValue <= innerValue) {
                innerCurrValue = innerValue;
                innerTimer->stop();
            } else {
                innerCurrValue -= animationStep;
            }
        } else {
            if (innerCurrValue >= innerValue) {
                innerCurrValue = innerValue;
                innerTimer->stop();
            } else {
                innerCurrValue += animationStep;
            }
        }
    }

    this->update();
}
