#include <QStyleOption>
#include <QPainter>
#include <QLineEdit>
#include <QFile>
#include <QDateTime>
#include "SoftKeyBoard.h"

SoftKeyBoard::SoftKeyBoard(QWidget * parent)
    : QWidget(parent, /*Qt::Tool|*/ Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint),m_lastFocusedWidget_(0)
{
    int num_index=0;
    ui.setupUi(this);
    hide();
    m_bIsUppercase_ = false;
    m_bShiftPressed_ = false;
    m_currentPos_ = 0;
    m_currentPage_ = 0;
    ui.btn_caplock_->setStyleSheet(QString("#btn_caplock_{color: rgb(255,255,255);background-color:rgb(67,63,59);border-radius: 7px;}#btn_caplock_:pressed{background-color: rgb(33,30,27);}"));
    ui.btn_shift_->setStyleSheet(QString("#btn_shift_{color: rgb(255,255,255);background-color:rgb(67,63,59);border-radius: 7px;}#btn_shift_:pressed{background-color: rgb(33,30,27);}"));
    LanguageInit();
    m_btns_[num_index++] = ui.char_a_;
    m_btns_[num_index++] = ui.char_b_;
    m_btns_[num_index++] = ui.char_c_;
    m_btns_[num_index++] = ui.char_d_;
    m_btns_[num_index++] = ui.char_e_;
    m_btns_[num_index++] = ui.char_f_;
    m_btns_[num_index++] = ui.char_g_;
    m_btns_[num_index++] = ui.char_h_;
    m_btns_[num_index++] = ui.char_i_;
    m_btns_[num_index++] = ui.char_j_;
    m_btns_[num_index++] = ui.char_k_;
    m_btns_[num_index++] = ui.char_l_;
    m_btns_[num_index++] = ui.char_m_;
    m_btns_[num_index++] = ui.char_n_;
    m_btns_[num_index++] = ui.char_o_;
    m_btns_[num_index++] = ui.char_p_;
    m_btns_[num_index++] = ui.char_q_;
    m_btns_[num_index++] = ui.char_r_;
    m_btns_[num_index++] = ui.char_s_;
    m_btns_[num_index++] = ui.char_t_;
    m_btns_[num_index++] = ui.char_u_;
    m_btns_[num_index++] = ui.char_v_;
    m_btns_[num_index++] = ui.char_w_;
    m_btns_[num_index++] = ui.char_x_;
    m_btns_[num_index++] = ui.char_y_;
    m_btns_[num_index++] = ui.char_z_;            //字母
    m_btns_[num_index++] = ui.num_0_;
    m_btns_[num_index++] = ui.num_1_;
    m_btns_[num_index++] = ui.num_2_;
    m_btns_[num_index++] = ui.num_3_;
    m_btns_[num_index++] = ui.num_4_;
    m_btns_[num_index++] = ui.num_5_;
    m_btns_[num_index++] = ui.num_6_;
    m_btns_[num_index++] = ui.num_8_;
    m_btns_[num_index++] = ui.num_9_;             //数字
    m_btns_[num_index++] = ui.btn_left_bracket_;  //左括号
    m_btns_[num_index++] = ui.btn_right_bracket_; //右括号
    m_btns_[num_index++] = ui.btn_slash_;         //斜杠
    m_btns_[num_index++] = ui.btn_quota_;         //引号
    m_btns_[num_index++] = ui.btn_semicolon_;     //分号
    m_btns_[num_index++] = ui.btn_backslash_;     //反斜杠
    m_btns_[num_index++] = ui.btn_comma_;         //逗号
    m_btns_[num_index++] = ui.btn_dot_;           //点
    m_btns_[num_index++] = ui.btn_add_;           //加
    m_btns_[num_index++] = ui.btn_dec_;           //减
    m_btns_[num_index++] = ui.num_7_;             //7特殊处理，因为包含&
    m_btns_[num_index++] = ui.btn_up_;//num_index=46
    m_btns_[num_index++] = ui.btn_down_;
    m_btns_[num_index++] = ui.btn_left_;
    m_btns_[num_index++] = ui.btn_right_;         //上下左右
    m_btns_[num_index++] = ui.btn_enter_;         //回车
    m_btns_[num_index++] = ui.btn_backspace_;     //退格
    m_btns_[num_index++] = ui.btn_space_;         //空格
    for(int i = 0;i < num_index;++i)
    {
        m_signalMapper_.setMapping(m_btns_[i],m_btns_[i]);
        connect(m_btns_[i],SIGNAL(clicked()),&m_signalMapper_,SLOT(map()));
    }
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
    connect(&m_signalMapper_, SIGNAL(mapped(QWidget*)),this, SLOT(buttonClicked(QWidget*)));
}

void SoftKeyBoard::LanguageInit()
{
    if(m_bIsUppercase_)
        on_btn_caplock__clicked();
    resize(1188, 420);
}



bool SoftKeyBoard::event(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::WindowActivate:
        if (m_lastFocusedWidget_)
            m_lastFocusedWidget_->activateWindow();
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void SoftKeyBoard::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus))
        m_lastFocusedWidget_ = newFocus;
}

void SoftKeyBoard::buttonClicked(QWidget *w)
{
    if(!w)
        return;
    QString text;
    int key = -1;

    if(GetBtnText(w,text,0,26) && text.size() > 0)//英文 字母
        key = m_bShiftPressed_ ? (text[0] >= 'A' && text[0] <= 'Z' ? text[0].toLower().unicode() : text[0].toUpper().unicode()) : text[0].unicode();//按下shift
    else if(m_bShiftPressed_ && GetBtnText(w,text,26,20) && text.size() > 0)
        key = text[0].unicode();
    else if(!m_bShiftPressed_ && GetBtnText(w,text,26,19) && text.size() > 0)
        key = text[2].unicode();
    else if(!m_bShiftPressed_ && GetBtnText(w,text,45,1) && text.size() > 0)
        key = text[3].unicode();
    else if(w == m_btns_[46])
        key = Qt::Key_Up;
    else if(w == m_btns_[47])
        key = Qt::Key_Down;
    else if(w == m_btns_[48])
        key = Qt::Key_Left;
    else if(w == m_btns_[49])
        key = Qt::Key_Right;
    else if(w == m_btns_[50])
        key = Qt::Key_Enter;
    else if(w == m_btns_[51])
        key = Qt::Key_Backspace;
    else if(w == m_btns_[52])
        key = Qt::Key_Space;
    qDebug()<<__PRETTY_FUNCTION__<<text<<key;
    emit characterGenerated(key);


}

void SoftKeyBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_ptPress_ = event->globalPos();        //记录按下位置
        m_bLeftBtnPress_ = true;
    }
    event->ignore();
}

void SoftKeyBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftBtnPress_)                        //移动窗口
    {
        move(pos() + event->globalPos() - m_ptPress_);
        m_ptPress_ = event->globalPos();
    }
    event->ignore();
}

void SoftKeyBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        m_bLeftBtnPress_ = false;
    event->ignore();
}

void SoftKeyBoard::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SoftKeyBoard::on_btn_caplock__clicked()
{
    m_bIsUppercase_ = !m_bIsUppercase_;
    ui.btn_caplock_->setStyleSheet(QString("#btn_caplock_{color: rgb(255,255,255);background-color:") + (m_bIsUppercase_ ? "rgb(127,122,117)" : "rgb(67,63,59)") + ";border-radius: 7px;}#btn_caplock_:pressed{background-color: rgb(33,30,27);}");
    for(int i = 0;i < 26;++i)
        m_btns_[i]->setText(QString(m_bIsUppercase_ ? 'A' + i : 'a' + i ));
}

void SoftKeyBoard::on_btn_shift__clicked()
{
    m_bShiftPressed_ = !m_bShiftPressed_;
    ui.btn_shift_->setStyleSheet(QString("#btn_shift_{color: rgb(255,255,255);background-color:") + (m_bShiftPressed_ ? "rgb(127,122,117)" : "rgb(67,63,59)") + ";border-radius: 7px;}#btn_shift_:pressed{background-color: rgb(33,30,27);}");
}

bool SoftKeyBoard::InitChinese()
{
    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QFile file(":/FontLibrary.txt");
    int i = 0;
    if(file.open(QIODevice::ReadOnly))
    {
        QString str;
        QString key;
        while (true)
        {
            str = file.readLine();
            if(str.size() < 4)
                break;
            key = str.mid(2,str.size() - 4);
            m_map_[key].push_back(str.left(1));
            ++i;
        }
        file.close();
        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")<<i;
        //for(std::map<QString,std::vector<QString> >::iterator it = m_map_.begin();it != m_map_.end();++it)
        //{
        //    qDebug()<<it->first;
        //    int c = 0;
        //    for(size_t i = 0;i < it->second.size();++i,++c)
        //    {
        //        qDebug()<<it->second[i];
        //    }
        //    qDebug()<<c;
        //}
        //qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        return true;
    }
    return false;
}

bool SoftKeyBoard::GetBtnText(QWidget *widget, QString &text, int start, int count)
{
    text = "";
    for(int i = start;i < start + count;++i)
    {
        if(widget == m_btns_[i])
        {
            text = m_btns_[i]->text();
            return true;
        }
    }
    return true;
}


