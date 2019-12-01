#pragma execution_character_set("utf-8")

#include "navlistview.h"
#include "qfontdatabase.h"
#include "qpainter.h"
#include "qdebug.h"

NavDelegate::NavDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    nav = (NavListView *)parent;

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome")) {
        int fontId = fontDb.addApplicationFont(":/image/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome")) {
        iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }
}

NavDelegate::~NavDelegate()
{

}

QSize NavDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    NavModel::TreeNode *node = (NavModel::TreeNode *)index.data(Qt::UserRole).toULongLong();

    //设置最小的宽高
    bool parent = (node->level == 1);
    QSize size(50, parent ? nav->getParentHeight() : nav->getChildHeight());
    return size;
}

void NavDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    NavModel::TreeNode *node = (NavModel::TreeNode *)index.data(Qt::UserRole).toULongLong();

    //定义变量存储区域
    QRect optionRect = option.rect;
    int x = optionRect.x();
    int y = optionRect.y();
    int width = optionRect.width();
    int height = optionRect.height();

    int fontSize = nav->getParentFontSize();

    //父节点和子节点颜色分开设置
    bool parent = (node->level == 1);

    //根据不同的状态设置不同的颜色 bgColor-主背景色 textColor-主文字颜色 tipBgColor-提示信息背景颜色 tipTextColor-提示信息文字颜色
    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (option.state & QStyle::State_Selected) {
        bgColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
        textColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
        tipBgColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
        tipTextColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
        iconColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
    } else if (option.state & QStyle::State_MouseOver) {
        bgColor = parent ? nav->getParentBgHoverColor() : nav->getChildBgHoverColor();
        textColor = parent ? nav->getParentTextHoverColor() : nav->getChildTextHoverColor();
        tipBgColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
        tipTextColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
        iconColor = parent ? nav->getParentTextHoverColor() : nav->getChildTextHoverColor();
    } else {
        bgColor = parent ? nav->getParentBgNormalColor() : nav->getChildBgNormalColor();
        textColor = parent ? nav->getParentTextNormalColor() : nav->getChildTextNormalColor();
        tipBgColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
        tipTextColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
        iconColor = parent ? nav->getParentTextNormalColor() : nav->getChildTextNormalColor();
    }

    //绘制背景
    painter->fillRect(optionRect, bgColor);

    //绘制线条,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int lineWidth = nav->getLineWidth();
    if (!parent && nav->getLineVisible() && lineWidth > 0) {
        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver)) {
            //设置偏移量,不然上下部分会有点偏移
            float offset = (float)lineWidth / 2;

            //计算上下两个坐标点
            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!nav->getLineLeft()) {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            //设置线条颜色和宽度
            painter->setPen(QPen(nav->getLineColor(), lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    //绘制三角形,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int triangleWidth = nav->getTriangleWidth();
    if (!parent && nav->getTriangleVisible() && triangleWidth > 0) {
        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver)) {
            QFont font = iconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(nav->getTriangleColor());

            //采用图形字体中的三角形绘制
            if (nav->getTriangleLeft()) {
                painter->drawText(optionRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
            } else {
                painter->drawText(optionRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
            }
        }
    }

    //绘制行分隔符
    if (nav->getSeparateVisible()) {
        if (node->level == 1 || (node->level == 2 && node->last)) {
            painter->setPen(QPen(nav->getSeparateColor(), nav->getSeparateHeight()));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    //绘制文字,如果文字为空则不绘制
    QString text = node->text;
    if (!text.isEmpty()) {
        //文字离左边的距离+字体大小
        int margin = nav->getParentMargin();
        if (node->level == 2) {
            margin = nav->getChildMargin();
            fontSize = nav->getChildFontSize();
        }

        //计算文字区域
        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font;
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    //绘制提示信息,如果不需要显示提示信息或者提示信息为空则不绘制
    QString tip = node->tip;
    if (nav->getTipVisible() && !tip.isEmpty()) {
        //如果是数字则将超过999的数字显示成 999+
        //如果显示的提示信息长度过长则将多余显示成省略号 .
        if (tip.toInt() > 0) {
            tip = tip.toInt() > 999 ? "999+" : tip;
        } else if (tip.length() > 2) {
            tip = tip.left(2) + " .";
        }

        //计算绘制区域,半径取高度的四分之一
        int radius = height / 4;
        QRect tipRect = optionRect;
        tipRect.setHeight(radius * 2);
        tipRect.moveCenter(optionRect.center());
        tipRect.setLeft(optionRect.right() - nav->getTipWidth() - 5);
        tipRect.setRight(optionRect.right() - 5);

        //设置字体大小
        QFont font;
        font.setPixelSize(fontSize - 2);
        painter->setFont(font);

        //绘制提示文字的背景
        painter->setPen(Qt::NoPen);
        painter->setBrush(tipBgColor);
        painter->drawRoundedRect(tipRect, radius, radius);

        //绘制提示文字
        painter->setPen(tipTextColor);
        painter->setBrush(Qt::NoBrush);
        painter->drawText(tipRect, Qt::AlignCenter, tip);
    }

    //计算绘制图标区域
    QRect iconRect = optionRect;
    iconRect.setLeft(parent ? nav->getParentIconMargin() : nav->getChildIconMargin());

    //设置图形字体和画笔颜色
    QFont font = iconFont;
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(textColor);

    //绘制左侧图标,有图标则绘制图标,没有的话父窗体取 + -
    if (!node->icon.isNull()) {
        painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, node->icon);
    } else if (parent) {
        if (node->expand) {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf067));
        } else {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf068));
        }
    }

    //绘制父节点右侧图标
    iconRect.setRight(optionRect.width() - 10);
    if (!(nav->getTipVisible() && !node->tip.isEmpty()) && nav->getRightIconVisible() && parent) {
        if (node->expand) {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf054));
        } else {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf078));
        }
    }
}


NavModel::NavModel(QObject *parent)	: QAbstractListModel(parent)
{

}

NavModel::~NavModel()
{
    for (QList<TreeNode *>::iterator it = treeNode.begin(); it != treeNode.end();) {
        for (QList<TreeNode *>::iterator child = (*it)->children.begin(); child != (*it)->children.end();) {
            delete(*child);
            child = (*it)->children.erase(child);
        }

        delete(*it);
        it = treeNode.erase(it);
    }
}

int NavModel::rowCount(const QModelIndex &parent) const
{
    return listNode.size();
}

QVariant NavModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= listNode.size() || index.row() < 0) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return listNode.at(index.row()).text;
    } else if (role == Qt::UserRole) {
        return (quint64)(listNode.at(index.row()).treeNode);
    }

    return QVariant();
}


void NavModel::setItems(const QStringList &items)
{
    int count = items.count();
    if (count == 0) {
        return;
    }

    bool ok;
    treeNode.clear();
    listNode.clear();

    //listItem格式: 标题|父节点标题(父节点为空)|是否展开|提示信息|左侧图标
    for (int i = 0; i < count; i++) {
        QString item = items.at(i);
        QStringList list = item.split("|");
        if (list.count() < 5) {
            continue;
        }

        //逐个取出字符串数据
        QString text = list.at(0);
        QString parentText = list.at(1);
        QString expand = list.at(2);
        QString tip = list.at(3);
        QString icon = list.at(4);

        //将父节点即父节点标题为空的元素加载完毕
        if (parentText.isEmpty()) {
            TreeNode *node = new TreeNode;

            //设置父节点的level为1,是否要打开子节点从参数取
            node->level = 1;
            node->expand = expand.toInt();
            node->last = false;

            if (!icon.isEmpty()) {
                node->icon = QChar(icon.toInt(&ok, 16));
            }

            node->text = text;
            node->tip = tip;
            node->parentText = parentText;

            //查找该父节点是否有对应子节点,有则加载
            for (int j = 0; j < count; j++) {
                QString childItem = items.at(j);
                QStringList childList = childItem.split("|");
                if (childList.count() < 5) {
                    continue;
                }

                QString childText = childList.at(0);
                QString childParentText = childList.at(1);
                QString childTip = childList.at(3);
                QString childIcon = childList.at(4);

                //传过来的图标字符串可能以0x打头,要去掉
                childIcon = childIcon.replace("0x", "");

                //如果当前子节点的父节点名称是上一个节点的名称则归属于该节点
                if (childParentText == text) {
                    TreeNode *childNode = new TreeNode;

                    //设置子节点的level为2,是否要打开子节点设置false,可自行更改从参数取,如果有三级节点的话
                    childNode->level = 2;
                    childNode->expand = false;
                    childNode->last = (j == count - 1);

                    if (!childIcon.isEmpty()) {
                        childNode->icon = QChar(childIcon.toInt(&ok, 16));
                    }

                    childNode->text = childText;
                    childNode->tip = childTip;
                    childNode->parentText = childParentText;
                    node->children.push_back(childNode);
                }
            }

            treeNode.push_back(node);
        }
    }

    refreshList();
    beginResetModel();
    endResetModel();
}

void NavModel::expand(const QModelIndex &index)
{
    TreeNode *node = listNode.at(index.row()).treeNode;
    if (node->children.size() == 0) {
        return;
    }

    node->expand = !node->expand;
    refreshList();

    if (!node->expand) {
        beginInsertRows(QModelIndex(), index.row() + 1, index.row() + node->children.size());
        endInsertRows();
    } else {
        beginRemoveRows(QModelIndex(), index.row() + 1, index.row() + 1);
        endRemoveRows();
    }
}

void NavModel::refreshList()
{
    listNode.clear();
    for (QList<TreeNode *>::iterator it = treeNode.begin(); it != treeNode.end(); ++it) {
        ListNode node;
        node.text = (*it)->text;
        node.treeNode = *it;

        listNode.push_back(node);
        if ((*it)->expand) {
            continue;
        }

        for (QList<TreeNode *>::iterator child = (*it)->children.begin(); child != (*it)->children.end(); ++child) {
            ListNode node;
            node.text = (*child)->text;
            node.treeNode = *child;
            node.treeNode->last = false;
            listNode.push_back(node);
        }

        if (!listNode.empty()) {
            listNode.back().treeNode->last = true;
        }
    }
}


NavListView::NavListView(QWidget *parent) : QListView(parent)
{
    rightIconVisible = true;
    tipVisible = true;
    tipWidth = 40;

    separateVisible = true;
    separateHeight = 1;
    separateColor = QColor(40, 43, 51);

    lineLeft = true;
    lineVisible = true;
    lineWidth = 6;
    lineColor = QColor(0, 187, 158);

    triangleLeft = false;
    triangleVisible = true;
    triangleWidth = 6;
    triangleColor = QColor(250, 250, 250);

    parentIconMargin = 10;
    parentMargin = 30;
    parentFontSize = 12;
    parentHeight = 35;
    parentBgNormalColor = QColor(57, 61, 73);
    parentBgSelectedColor = QColor(78, 83, 102);
    parentBgHoverColor = QColor(78, 83, 102);
    parentTextNormalColor = QColor(250, 250, 250);
    parentTextSelectedColor = QColor(250, 250, 250);
    parentTextHoverColor = QColor(250, 250, 250);

    childIconMargin = 15;
    childMargin = 35;
    childFontSize = 12;
    childHeight = 30;
    childBgNormalColor = QColor(40, 43, 51);
    childBgSelectedColor = QColor(20, 20, 20);
    childBgHoverColor = QColor(20, 20, 20);
    childTextNormalColor = QColor(180, 180, 180);
    childTextSelectedColor = QColor(250, 250, 250);
    childTextHoverColor = QColor(255, 255, 255);

    expendMode = ExpendMode_SingleClick;

    this->setMouseTracking(true);
    model = new NavModel(this);
    delegate = new NavDelegate(this);
    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(pressed(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
}

NavListView::~NavListView()
{
    delete model;
    delete delegate;
}

void NavListView::pressed(const QModelIndex &data)
{
    NavModel::TreeNode *node = (NavModel::TreeNode *)data.data(Qt::UserRole).toULongLong();

    QString text = node->text;
    QString parentText = node->parentText;
    int parentIndex = parentItem.indexOf(parentText);

    //默认没有子节点则父节点为子节点
    int index = parentItem.indexOf(text);
    if (parentIndex >= 0) {
        index = childItem.at(parentIndex).indexOf(text);
    }

    //找出子节点在子节点队列中的索引
    int childIndex = -1;
    for (int i = 0; i < childItem.count(); i++) {
        QStringList item = childItem.at(i);
        bool ok = false;
        foreach (QString str, item) {
            childIndex++;

            //找到了对应子节点
            if (str == text) {
                ok = true;
                break;
            }
        }

        if (ok) {
            break;
        }
    }

    //如果当前节点是父节点则将子节点索引置为-1
    if (parentIndex == -1) {
        childIndex = -1;
    }

    //当前节点名称+父节点名称
    emit pressed(text, parentText);

    //当前节点索引+父节点索引
    emit pressed(index, parentIndex);

    //整个子节点中对应的索引
    emit pressed(childIndex);

    //qDebug() << text << parentText << index << parentIndex << childIndex;
}

void NavListView::setData(const QStringList &listItems)
{
    model->setItems(listItems);
    this->setModel(model);
    this->setItemDelegate(delegate);
}

QString NavListView::getItems() const
{
    return this->items;
}

bool NavListView::getRightIconVisible() const
{
    return this->rightIconVisible;
}

bool NavListView::getTipVisible() const
{
    return this->tipVisible;
}

int NavListView::getTipWidth() const
{
    return this->tipWidth;
}

bool NavListView::getSeparateVisible() const
{
    return this->separateVisible;
}

int NavListView::getSeparateHeight() const
{
    return this->separateHeight;
}

QColor NavListView::getSeparateColor() const
{
    return this->separateColor;
}

bool NavListView::getLineLeft() const
{
    return this->lineLeft;
}

bool NavListView::getLineVisible() const
{
    return this->lineVisible;
}

int NavListView::getLineWidth() const
{
    return this->lineWidth;
}

QColor NavListView::getLineColor() const
{
    return this->lineColor;
}

bool NavListView::getTriangleLeft() const
{
    return this->triangleLeft;
}

bool NavListView::getTriangleVisible() const
{
    return this->triangleVisible;
}

int NavListView::getTriangleWidth() const
{
    return this->triangleWidth;
}

QColor NavListView::getTriangleColor() const
{
    return this->triangleColor;
}

int NavListView::getParentIconMargin() const
{
    return this->parentIconMargin;
}

int NavListView::getParentMargin() const
{
    return this->parentMargin;
}

int NavListView::getParentFontSize() const
{
    return this->parentFontSize;
}

int NavListView::getParentHeight() const
{
    return this->parentHeight;
}

QColor NavListView::getParentBgNormalColor() const
{
    return this->parentBgNormalColor;
}

QColor NavListView::getParentBgSelectedColor() const
{
    return this->parentBgSelectedColor;
}

QColor NavListView::getParentBgHoverColor() const
{
    return this->parentBgHoverColor;
}

QColor NavListView::getParentTextNormalColor() const
{
    return this->parentTextNormalColor;
}

QColor NavListView::getParentTextSelectedColor() const
{
    return this->parentTextSelectedColor;
}

QColor NavListView::getParentTextHoverColor() const
{
    return this->parentTextHoverColor;
}

int NavListView::getChildIconMargin() const
{
    return this->childIconMargin;
}

int NavListView::getChildMargin() const
{
    return this->childMargin;
}

int NavListView::getChildFontSize() const
{
    return this->childFontSize;
}

int NavListView::getChildHeight() const
{
    return this->childHeight;
}

QColor NavListView::getChildBgNormalColor() const
{
    return this->childBgNormalColor;
}

QColor NavListView::getChildBgSelectedColor() const
{
    return this->childBgSelectedColor;
}

QColor NavListView::getChildBgHoverColor() const
{
    return this->childBgHoverColor;
}

QColor NavListView::getChildTextNormalColor() const
{
    return this->childTextNormalColor;
}

QColor NavListView::getChildTextSelectedColor() const
{
    return this->childTextSelectedColor;
}

QColor NavListView::getChildTextHoverColor() const
{
    return this->childTextHoverColor;
}

NavListView::ExpendMode NavListView::getExpendMode() const
{
    return this->expendMode;
}

QSize NavListView::sizeHint() const
{
    return QSize(200, 300);
}

QSize NavListView::minimumSizeHint() const
{
    return QSize(20, 20);
}

void NavListView::setItems(const QString &items)
{
    if (this->items != items) {
        this->items = items;
        QStringList item = items.split(",");
        setData(item);

        //将对应的父节点子节点转换为数组,以便用户按下鼠标时候判断
        parentItem.clear();
        childItem.clear();
        int count = item.count();

        for (int i = 0; i < count; i++) {
            QStringList list = item.at(i).split("|");
            if (list.count() < 5) {
                continue;
            }

            //父节点名称为空则说明是父节点
            QString text = list.at(0);
            QString parentText = list.at(1);
            if (parentText.isEmpty()) {
                //找出该父节点下的所有子节点
                QStringList childs;
                for (int j = 0; j < count; j++) {
                    QStringList childList = item.at(j).split("|");
                    if (childList.count() < 5) {
                        continue;
                    }

                    QString childText = childList.at(0);
                    QString childParentText = childList.at(1);

                    //如果父节点的名称和上一个子节点的名称一致则说明当前节点为其子节点
                    if (childParentText == text) {
                        childs << childText;
                    }
                }

                parentItem << text;
                childItem << childs;
            }
        }

        //qDebug() << parentItem << childItem;
    }
}

void NavListView::setCurrentRow(int row)
{
    this->setCurrentIndex(model->index(row, 0));
}

void NavListView::setRightIconVisible(bool rightIconVisible)
{
    this->rightIconVisible = rightIconVisible;
}

void NavListView::setTipVisible(bool tipVisible)
{
    this->tipVisible = tipVisible;
}

void NavListView::setTipWidth(int tipWidth)
{
    this->tipWidth = tipWidth;
}

void NavListView::setSeparateVisible(bool separateVisible)
{
    this->separateVisible = separateVisible;
}

void NavListView::setSeparateHeight(int separateHeight)
{
    this->separateHeight = separateHeight;
}

void NavListView::setSeparateColor(const QColor &separateColor)
{
    this->separateColor = separateColor;
}

void NavListView::setLineLeft(bool lineLeft)
{
    this->lineLeft = lineLeft;
}

void NavListView::setLineVisible(bool lineVisible)
{
    this->lineVisible = lineVisible;
}

void NavListView::setLineWidth(int lineWidth)
{
    this->lineWidth = lineWidth;
}

void NavListView::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;
}

void NavListView::setTriangleLeft(bool triangleLeft)
{
    this->triangleLeft = triangleLeft;
}

void NavListView::setTriangleVisible(bool triangleVisible)
{
    this->triangleVisible = triangleVisible;
}

void NavListView::setTriangleWidth(int triangleWidth)
{
    this->triangleWidth = triangleWidth;
}

void NavListView::setTriangleColor(const QColor &triangleColor)
{
    this->triangleColor = triangleColor;
}

void NavListView::setParentIconMargin(int parentIconMargin)
{
    this->parentIconMargin = parentIconMargin;
}

void NavListView::setParentMargin(int parentMargin)
{
    this->parentMargin = parentMargin;
}

void NavListView::setParentFontSize(int parentFontSize)
{
    this->parentFontSize = parentFontSize;
}

void NavListView::setParentHeight(int parentHeight)
{
    this->parentHeight = parentHeight;
}

void NavListView::setParentBgNormalColor(const QColor &parentBgNormalColor)
{
    this->parentBgNormalColor = parentBgNormalColor;
}

void NavListView::setParentBgSelectedColor(const QColor &parentBgSelectedColor)
{
    this->parentBgSelectedColor = parentBgSelectedColor;
}

void NavListView::setParentBgHoverColor(const QColor &parentBgHoverColor)
{
    this->parentBgHoverColor = parentBgHoverColor;
}

void NavListView::setParentTextNormalColor(const QColor &parentTextNormalColor)
{
    this->parentTextNormalColor = parentTextNormalColor;
}

void NavListView::setParentTextSelectedColor(const QColor &parentTextSelectedColor)
{
    this->parentTextSelectedColor = parentTextSelectedColor;
}

void NavListView::setParentTextHoverColor(const QColor &parentTextHoverColor)
{
    this->parentTextHoverColor = parentTextHoverColor;
}

void NavListView::setChildIconMargin(int childIconMargin)
{
    this->childIconMargin = childIconMargin;
}

void NavListView::setChildMargin(int childMargin)
{
    this->childMargin = childMargin;
}

void NavListView::setChildFontSize(int childFontSize)
{
    this->childFontSize = childFontSize;
}

void NavListView::setChildHeight(int childHeight)
{
    this->childHeight = childHeight;
}

void NavListView::setChildBgNormalColor(const QColor &childBgNormalColor)
{
    this->childBgNormalColor = childBgNormalColor;
}

void NavListView::setChildBgSelectedColor(const QColor &childBgSelectedColor)
{
    this->childBgSelectedColor = childBgSelectedColor;
}

void NavListView::setChildBgHoverColor(const QColor &childBgHoverColor)
{
    this->childBgHoverColor = childBgHoverColor;
}

void NavListView::setChildTextNormalColor(const QColor &childTextNormalColor)
{
    this->childTextNormalColor = childTextNormalColor;
}

void NavListView::setChildTextSelectedColor(const QColor &childTextSelectedColor)
{
    this->childTextSelectedColor = childTextSelectedColor;
}

void NavListView::setChildTextHoverColor(const QColor &childTextHoverColor)
{
    this->childTextHoverColor = childTextHoverColor;
}

void NavListView::setExpendMode(const NavListView::ExpendMode &expendMode)
{
    if(this->expendMode != expendMode) {
        this->expendMode = expendMode;
        if(expendMode == ExpendMode_SingleClick) {
            disconnect(this, SIGNAL(doubleClicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
            connect(this, SIGNAL(clicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
        } else if(expendMode == ExpendMode_DoubleClick) {
            disconnect(this, SIGNAL(clicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
            connect(this, SIGNAL(doubleClicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
        } else if(expendMode == ExpendMode_NoClick) {
            disconnect(this, SIGNAL(clicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
            disconnect(this, SIGNAL(doubleClicked(QModelIndex)), model, SLOT(expand(QModelIndex)));
        }
    }
}
