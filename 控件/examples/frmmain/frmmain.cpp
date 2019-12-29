#pragma execution_character_set("utf-8")

#include "frmmain.h"
#include "ui_frmmain.h"

#include "frmgauge.h"
#include "frmprogress.h"
#include "frmnav.h"
#include "frmwave.h"
#include "frmruler.h"
#include "frmslider.h"
#include "frmbar.h"
#include "frmcolor.h"
#include "frmimage.h"
#include "frmpainter.h"
#include "frmother.h"
#include "frmdemo.h"
#include "frmvideo.h"
#include "frmx.h"
#include "frmcommon.h"

#include "gifwidget.h"
#include "screenwidget.h"
#include "colorwidget.h"
#include "maskwidget.h"
#include "trayicon.h"
#include "head.h"

frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->initForm();
    this->addItem();
}

frmMain::~frmMain()
{
    delete ui;
    TrayIcon::Instance()->setVisible(false);
    exit(0);
}

void frmMain::paintEvent(QPaintEvent *)
{
    if (needDraw) {
        QPainter painter(this);
        painter.drawTiledPixmap(rect(), bgPix);
    }
}

void frmMain::initForm()
{
    //是否绘制特殊背景
    needDraw = true;
    //需要绘制的控件的名称集合
    listDraw << "仪表盘控件" << "进度条控件" << "按钮进度条" << "多态进度条" << "播放进度条" << "环形进度条"
             << "汽车仪表盘" << "半圆仪表盘" << "进度仪表盘" << "时钟仪表盘" << "简单仪表盘" << "钟形仪表盘"
             << "指南针仪表盘" << "指南针面板" << "旋转仪表盘" << "飞机仪表盘" << "多彩仪表盘" << "云台仪表盘"
             << "天气仪表盘" << "分贝仪表盘" << "水波进度条" << "高亮按钮" << "旋转圆" << "旋转logo"
             << "魔法小鱼" << "魔法老鼠" << "魔法水滴" << "游动的鱼" << "图片背景日历" << "图片背景时钟"
             << "烤箱旋转按钮" << "自定义多边形" << "自定义摇杆" << "自定义饼状图" << "自定义环形图" << "蚂蚁线" << "描点跟随窗体";

    bgPix = QPixmap(":/image/bg.png");
    connect(ui->navListView, SIGNAL(pressed(QString, QString)), this, SLOT(pressed(QString, QString)));

    //设置文本边距
    ui->navListView->setChildMargin(28);
    ui->navListView->setExpendMode(NavListView::ExpendMode_SingleClick);
    ui->navListView->setSeparateColor(QColor(40, 43, 51));

    //设置子节点颜色
    ui->navListView->setChildBgNormalColor(QColor(40, 43, 51));
    ui->navListView->setChildBgSelectedColor(QColor(20, 20, 20));
    ui->navListView->setChildBgHoverColor(QColor(20, 20, 20));
    ui->navListView->setChildTextNormalColor(QColor(180, 180, 180));
    ui->navListView->setChildTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setChildTextHoverColor(QColor(255, 255, 255));

    //设置父节点颜色
    ui->navListView->setParentBgNormalColor(QColor(57, 61, 73));
    ui->navListView->setParentBgSelectedColor(QColor(78, 83, 102));
    ui->navListView->setParentBgHoverColor(QColor(78, 83, 102));
    ui->navListView->setParentTextNormalColor(QColor(250, 250, 250));
    ui->navListView->setParentTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setParentTextHoverColor(QColor(250, 250, 250));

    listParent << "仪表盘控件" << "进度条控件" << "导航控件" << "波形曲线" << "标尺控件"
               << "滑动条控件" << "柱状条控件" << "颜色控件" << "贴图控件" << "自绘控件"
               << "其他控件" << "内置控件" << "视频监控" << "拓展控件" << "通用类库" << "不可见控件";

    gauge = new frmGauge;
    progress = new frmProgress;
    nav = new frmNav;
    wave = new frmWave;
    ruler = new frmRuler;
    slider = new frmSlider;
    bar = new frmBar;
    color = new frmColor;
    image = new frmImage;
    painter = new frmPainter;
    other = new frmOther;
    demo = new frmDemo;
    video = new frmVideo;
    x = new frmX;
    common = new frmCommon;

    ui->stackedWidget->addWidget(gauge);
    ui->stackedWidget->addWidget(progress);
    ui->stackedWidget->addWidget(nav);
    ui->stackedWidget->addWidget(wave);
    ui->stackedWidget->addWidget(ruler);
    ui->stackedWidget->addWidget(slider);
    ui->stackedWidget->addWidget(bar);
    ui->stackedWidget->addWidget(color);
    ui->stackedWidget->addWidget(image);
    ui->stackedWidget->addWidget(painter);
    ui->stackedWidget->addWidget(other);
    ui->stackedWidget->addWidget(demo);
    ui->stackedWidget->addWidget(video);
    ui->stackedWidget->addWidget(x);
    ui->stackedWidget->addWidget(common);

    //设置遮罩层
    MaskWidget::Instance()->setMainWidget(this);
    MaskWidget::Instance()->setDialogNames(QStringList() << "frmMaskWidget");

    //设置托盘
    TrayIcon::Instance()->setIcon(":/main.ico");
    TrayIcon::Instance()->setToolTip(this->windowTitle());
    TrayIcon::Instance()->setMainWidget(this);
    TrayIcon::Instance()->setVisible(true);
    TrayIcon::Instance()->setVisible(false);

    //居中显示窗体
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}

void frmMain::addItem()
{
    //listItem格式: 标题|父节点标题(父节点为空)|是否展开|提示信息|图标值
    listItem.clear();
    listGauge.clear();
    listProgress.clear();
    listNav.clear();
    listWave.clear();
    listRuler.clear();
    listSlider.clear();
    listBar.clear();
    listColor.clear();
    listImage.clear();
    listPainter.clear();
    listOther.clear();
    listDemo.clear();
    listVideo.clear();
    listX.clear();
    listCommon.clear();
    listHide.clear();

    addGauge();
    addProgress();
    addNav();
    addWave();
    addRuler();
    addSlider();
    addBar();
    addColor();
    addImage();
    addPainter();
    addOther();
    addDemo();
    addVideo();
    addX();
    addCommon();
    addHide();

    QString item = listItem.join(",");
    ui->navListView->setItems(item);
    //qDebug() << item;

    //统计控件个数,animationbutton2+bottomwidget+lunarcalendaritem+tumblerdate+tumblertime未单独列出
    int count = 5;
    count += listGauge.count();
    count += listProgress.count();
    count += listNav.count();
    count += listWave.count();
    count += listRuler.count();
    count += listSlider.count();
    count += listBar.count();
    count += listColor.count();
    count += listImage.count();
    count += listPainter.count();
    count += listOther.count();
    count += listDemo.count();
    count += listVideo.count();
    count += listX.count();
    count += listCommon.count();
    count += listHide.count();

    this->setWindowTitle(QString("Qt自定义控件大全(QQ:517216493) 共 %1 个控件").arg(count));
    ui->navListView->setCurrentRow(0);
}

void frmMain::addItem(const QString &parentName, const QStringList &childNames)
{
    int count = childNames.count();
    listItem.append(QString("%1||1|%2|").arg(parentName).arg(count));
    for (int i = 0; i < count; i++) {
        listItem.append(QString("%1. %2|%3|1||0xf0da").arg(i + 1, 2, 10, QChar('0')).arg(childNames.at(i)).arg(parentName));
    }
}

void frmMain::addGauge()
{
    listGauge << "汽车仪表盘" << "圆弧仪表盘" << "百分比仪表盘" << "半圆仪表盘" << "进度仪表盘"
              << "范围仪表盘" << "速度仪表盘" << "时钟仪表盘" << "网络仪表盘" << "简单仪表盘"
              << "时速仪表盘" << "指南针仪表盘" << "指南针面板" << "旋转仪表盘" << "迷你仪表盘"
              << "圆环仪表盘" << "飞机仪表盘" << "LPM仪表盘" << "多彩仪表盘" << "云台仪表盘"
              << "天气仪表盘" << "分贝仪表盘" << "面板仪表盘";
    addItem("仪表盘控件", listGauge);
}

void frmMain::addProgress()
{
    listProgress << "水波进度条" << "百分比进度条" << "圆环进度条" << "等待进度条" << "多彩进度条"
                 << "按钮进度条" << "多态进度条" << "播放进度条" << "环形进度条";
    addItem("进度条控件", listProgress);
}

void frmMain::addNav()
{
    listNav << "导航按钮" << "导航标签" << "导航进度条" << "树状导航栏" << "树状导航窗体"
            << "滑动导航栏" << "滑动导航窗体" << "导航按钮组" << "导航标题栏";
    addItem("导航控件", listNav);
}

void frmMain::addWave()
{
    listWave << "直方动态图" << "直方对称图" << "直方波形图" << "波浪曲线" << "简单曲线图"
             << "声音波形图";
    addItem("波形曲线", listWave);
}

void frmMain::addRuler()
{
    listRuler << "柱状标尺" << "线性标尺" << "滑动标尺" << "双向刻度尺" << "温度计标尺"
              << "半圆仪标尺" << "进度标尺";
    addItem("标尺控件", listRuler);
}

void frmMain::addSlider()
{
    listSlider << "范围选择条" << "范围滑动条" << "滑动提示条";
    addItem("滑动条控件", listSlider);
}

void frmMain::addBar()
{
    listBar << "柱状音量条" << "左右声道音量条";
    addItem("柱状条控件", listBar);
}

void frmMain::addColor()
{
    listColor << "颜色面板集合" << "颜色按钮面板" << "颜色滑块面板" << "颜色选取面板" << "颜色多态按钮"
              << "颜色下拉框" << "样式面板集合";
    addItem("颜色控件", listColor);
}

void frmMain::addImage()
{
    listImage << "广告轮播" << "图片轮播" << "动画图片按钮" << "设备防区" << "图片切换动画" << "图片开关"
              << "图片浏览" << "图片背景日历" << "图片背景电池" << "图片背景时钟" << "图片指示灯";
    addItem("贴图控件", listImage);
}

void frmMain::addPainter()
{
    listPainter << "自绘电池" << "高亮按钮" << "发光按钮" << "魔法小鱼" << "魔法老鼠" << "魔法水滴"
                << "游动的鱼" << "旋转圆" << "多彩旋转" << "旋转logo" << "开关按钮" << "烤箱旋转按钮"
                << "滑动选择器" << "滑动日期面板" << "自定义农历组件" << "自定义农历面板" << "平铺背景控件"
                << "手机通讯录" << "自定义多边形" << "自定义摇杆" << "自定义饼状图" << "自定义环形图";
    addItem("自绘控件", listPainter);
}

void frmMain::addOther()
{
    listOther << "移动控件" << "面板元素" << "面板窗体" << "LCD时间" << "LCD数码管"
              << "LED数码管" << "LED文字" << "磁盘容量统计" << "CPU内存" << "文字滚动"
              << "验证码" << "图标编辑器" << "IP地址输入框" << "自定义下拉框" << "蚂蚁线"
              << "描点跟随窗体" << "流式动态布局";
    addItem("其他控件", listOther);
}

void frmMain::addDemo()
{
    listDemo << "企鹅矢量图" << "颜色拾取" << "矢量颜色" << "放大镜" << "矢量线条";
    addItem("内置控件", listDemo);
}

void frmMain::addVideo()
{
    listVideo << "视频监控画面" << "视频回放控件" << "视频窗体控件";
    addItem("视频监控", listVideo);
}

void frmMain::addX()
{
    listX << "显示值滑动条" << "高级列表面板" << "视频源面板" << "视频终端面板" << "自定义进度条";
    addItem("拓展控件", listX);
}

void frmMain::addCommon()
{
    listCommon << "FlatUI" << "汉字转拼音" << "简繁转换" << "Ntp校时" << "日志输出" << "运行时间"
               << "IP地址工具" << "去除PNG警告" << "打字对照板" << "代码行数统计";
    addItem("通用类库", listCommon);
}

void frmMain::addHide()
{
    listHide << "GIF录屏" << "屏幕截图" << "颜色拾取器" << "遮罩层" << "托盘图标" << "关于Qt";
    addItem("不可见控件", listHide);
}

void frmMain::pressed(const QString &childText, const QString &parentText)
{
    //如果带了 . 表示序号,要删除再比较
    QString text = childText;
    if (text.contains(".")) {
        text = text.mid(text.indexOf(".") + 2, text.length());
    }

    if (listDraw.contains(text)) {
        needDraw = true;
        this->update();
    } else {
        needDraw = false;
        this->update();
    }

    if (parentText.isEmpty()) {
        ui->stackedWidget->setCurrentIndex(listParent.indexOf(text));
    } else {
        //如果当前窗体的主窗体不在当前则切换过去
        int index = listParent.indexOf(parentText);
        if (ui->stackedWidget->currentIndex() != index) {
            ui->stackedWidget->setCurrentIndex(index);
        }

        if (parentText == "仪表盘控件") {
            gauge->setIndex(listGauge.indexOf(text));
        } else if (parentText == "进度条控件") {
            progress->setIndex(listProgress.indexOf(text));
        } else if (parentText == "导航控件") {
            nav->setIndex(listNav.indexOf(text));
        } else if (parentText == "波形曲线") {
            wave->setIndex(listWave.indexOf(text));
        } else if (parentText == "标尺控件") {
            ruler->setIndex(listRuler.indexOf(text));
        } else if (parentText == "滑动条控件") {
            slider->setIndex(listSlider.indexOf(text));
        } else if (parentText == "柱状条控件") {
            bar->setIndex(listBar.indexOf(text));
        } else if (parentText == "颜色控件") {
            color->setIndex(listColor.indexOf(text));
        } else if (parentText == "贴图控件") {
            image->setIndex(listImage.indexOf(text));
        } else if (parentText == "自绘控件") {
            painter->setIndex(listPainter.indexOf(text));
        } else if (parentText == "其他控件") {
            other->setIndex(listOther.indexOf(text));
        } else if (parentText == "内置控件") {
            demo->setIndex(listDemo.indexOf(text));
        } else if (parentText == "视频监控") {
            video->setIndex(listVideo.indexOf(text));
        } else if (parentText == "拓展控件") {
            x->setIndex(listX.indexOf(text));
        } else if (parentText == "通用类库") {
            common->setIndex(listCommon.indexOf(text));
        } else if (parentText == "不可见控件") {
            if (text == "GIF录屏") {
                GifWidget::Instance()->show();
            } else if (text == "屏幕截图") {
                ScreenWidget::Instance()->showFullScreen();
            } else if (text == "颜色拾取器") {
                ColorWidget::Instance()->show();
            } else if (text == "遮罩层") {
                QDialog d;
                d.setObjectName("frmMaskWidget");
                d.setWindowTitle("遮罩层弹出窗体");
                d.resize(400, 300);
                d.exec();
            } else if (text == "托盘图标") {
                if (TrayIcon::Instance()->getVisible()) {
                    TrayIcon::Instance()->setVisible(false);
                } else {
                    TrayIcon::Instance()->setVisible(true);
                    TrayIcon::Instance()->showMessage(this->windowTitle(), "已经最小化到托盘,双击打开!");
                }
            } else if (text == "关于Qt") {
                qApp->aboutQt();
            }
        }
    }
}

