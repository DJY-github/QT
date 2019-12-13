/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyBoard
{
public:
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *prevBt;
    QPushButton *nextBt;
    QPushButton *delBt;
    QPushButton *zh_1_Bt;
    QPushButton *zh_2_Bt;
    QPushButton *zh_3_Bt;
    QPushButton *zh_4_Bt;
    QPushButton *zh_5_Bt;
    QPushButton *zh_6_Bt;
    QPushButton *zh_7_Bt;
    QPushButton *zh_8_Bt;
    QPushButton *zh_9_Bt;
    QPushButton *zh_10_Bt;
    QPushButton *q_Bt;
    QPushButton *w_Bt;
    QPushButton *e_Bt;
    QPushButton *r_Bt;
    QPushButton *t_Bt;
    QPushButton *y_Bt;
    QPushButton *u_Bt;
    QPushButton *i_Bt;
    QPushButton *o_Bt;
    QPushButton *p_Bt;
    QPushButton *caps_Bt;
    QPushButton *a_Bt;
    QPushButton *s_Bt;
    QPushButton *d_Bt;
    QPushButton *f_Bt;
    QPushButton *g_Bt;
    QPushButton *h_Bt;
    QPushButton *j_Bt;
    QPushButton *k_Bt;
    QPushButton *l_Bt;
    QPushButton *zh_us_Bt;
    QPushButton *z_Bt;
    QPushButton *x_Bt;
    QPushButton *c_Bt;
    QPushButton *v_Bt;
    QPushButton *b_Bt;
    QPushButton *n_Bt;
    QPushButton *m_Bt;
    QPushButton *spaceBt;
    QLabel *showLb;
    QLabel *langLb;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QPushButton *num_2_Bt;
    QPushButton *num_1_Bt;
    QPushButton *num_9_Bt;
    QPushButton *num_3_Bt;
    QPushButton *num_6_Bt;
    QPushButton *num_5_Bt;
    QPushButton *num_8_Bt;
    QPushButton *num_7_Bt;
    QPushButton *num_0_Bt;
    QPushButton *num_4_Bt;
    QPushButton *closeBt;

    void setupUi(QDialog *KeyBoard)
    {
        if (KeyBoard->objectName().isEmpty())
            KeyBoard->setObjectName(QStringLiteral("KeyBoard"));
        KeyBoard->setEnabled(true);
        KeyBoard->resize(600, 200);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KeyBoard->sizePolicy().hasHeightForWidth());
        KeyBoard->setSizePolicy(sizePolicy);
        KeyBoard->setMinimumSize(QSize(600, 200));
        KeyBoard->setMaximumSize(QSize(600, 200));
        KeyBoard->setStyleSheet(QStringLiteral(""));
        line = new QFrame(KeyBoard);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(465, 6, 1, 189));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(1, 189));
        line->setMaximumSize(QSize(1, 182));
        line->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 0);"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(KeyBoard);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(5, 4, 590, 1));
        line_2->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 0);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(KeyBoard);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(5, 195, 590, 1));
        line_3->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 0);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(KeyBoard);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(594, 5, 1, 191));
        line_4->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 0);"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(KeyBoard);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(5, 5, 1, 190));
        line_5->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 0);"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(KeyBoard);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 451, 181));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        prevBt = new QPushButton(layoutWidget);
        prevBt->setObjectName(QStringLiteral("prevBt"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(prevBt->sizePolicy().hasHeightForWidth());
        prevBt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(prevBt, 0, 7, 1, 1);

        nextBt = new QPushButton(layoutWidget);
        nextBt->setObjectName(QStringLiteral("nextBt"));
        sizePolicy2.setHeightForWidth(nextBt->sizePolicy().hasHeightForWidth());
        nextBt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(nextBt, 0, 8, 1, 1);

        delBt = new QPushButton(layoutWidget);
        delBt->setObjectName(QStringLiteral("delBt"));
        sizePolicy2.setHeightForWidth(delBt->sizePolicy().hasHeightForWidth());
        delBt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(delBt, 0, 9, 1, 1);

        zh_1_Bt = new QPushButton(layoutWidget);
        zh_1_Bt->setObjectName(QStringLiteral("zh_1_Bt"));
        sizePolicy2.setHeightForWidth(zh_1_Bt->sizePolicy().hasHeightForWidth());
        zh_1_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_1_Bt, 1, 0, 1, 1);

        zh_2_Bt = new QPushButton(layoutWidget);
        zh_2_Bt->setObjectName(QStringLiteral("zh_2_Bt"));
        sizePolicy2.setHeightForWidth(zh_2_Bt->sizePolicy().hasHeightForWidth());
        zh_2_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_2_Bt, 1, 1, 1, 1);

        zh_3_Bt = new QPushButton(layoutWidget);
        zh_3_Bt->setObjectName(QStringLiteral("zh_3_Bt"));
        sizePolicy2.setHeightForWidth(zh_3_Bt->sizePolicy().hasHeightForWidth());
        zh_3_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_3_Bt, 1, 2, 1, 1);

        zh_4_Bt = new QPushButton(layoutWidget);
        zh_4_Bt->setObjectName(QStringLiteral("zh_4_Bt"));
        sizePolicy2.setHeightForWidth(zh_4_Bt->sizePolicy().hasHeightForWidth());
        zh_4_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_4_Bt, 1, 3, 1, 1);

        zh_5_Bt = new QPushButton(layoutWidget);
        zh_5_Bt->setObjectName(QStringLiteral("zh_5_Bt"));
        sizePolicy2.setHeightForWidth(zh_5_Bt->sizePolicy().hasHeightForWidth());
        zh_5_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_5_Bt, 1, 4, 1, 1);

        zh_6_Bt = new QPushButton(layoutWidget);
        zh_6_Bt->setObjectName(QStringLiteral("zh_6_Bt"));
        sizePolicy2.setHeightForWidth(zh_6_Bt->sizePolicy().hasHeightForWidth());
        zh_6_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_6_Bt, 1, 5, 1, 1);

        zh_7_Bt = new QPushButton(layoutWidget);
        zh_7_Bt->setObjectName(QStringLiteral("zh_7_Bt"));
        sizePolicy2.setHeightForWidth(zh_7_Bt->sizePolicy().hasHeightForWidth());
        zh_7_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_7_Bt, 1, 6, 1, 1);

        zh_8_Bt = new QPushButton(layoutWidget);
        zh_8_Bt->setObjectName(QStringLiteral("zh_8_Bt"));
        sizePolicy2.setHeightForWidth(zh_8_Bt->sizePolicy().hasHeightForWidth());
        zh_8_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_8_Bt, 1, 7, 1, 1);

        zh_9_Bt = new QPushButton(layoutWidget);
        zh_9_Bt->setObjectName(QStringLiteral("zh_9_Bt"));
        sizePolicy2.setHeightForWidth(zh_9_Bt->sizePolicy().hasHeightForWidth());
        zh_9_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_9_Bt, 1, 8, 1, 1);

        zh_10_Bt = new QPushButton(layoutWidget);
        zh_10_Bt->setObjectName(QStringLiteral("zh_10_Bt"));
        sizePolicy2.setHeightForWidth(zh_10_Bt->sizePolicy().hasHeightForWidth());
        zh_10_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_10_Bt, 1, 9, 1, 1);

        q_Bt = new QPushButton(layoutWidget);
        q_Bt->setObjectName(QStringLiteral("q_Bt"));
        sizePolicy2.setHeightForWidth(q_Bt->sizePolicy().hasHeightForWidth());
        q_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(q_Bt, 2, 0, 1, 1);

        w_Bt = new QPushButton(layoutWidget);
        w_Bt->setObjectName(QStringLiteral("w_Bt"));
        sizePolicy2.setHeightForWidth(w_Bt->sizePolicy().hasHeightForWidth());
        w_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(w_Bt, 2, 1, 1, 1);

        e_Bt = new QPushButton(layoutWidget);
        e_Bt->setObjectName(QStringLiteral("e_Bt"));
        sizePolicy2.setHeightForWidth(e_Bt->sizePolicy().hasHeightForWidth());
        e_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(e_Bt, 2, 2, 1, 1);

        r_Bt = new QPushButton(layoutWidget);
        r_Bt->setObjectName(QStringLiteral("r_Bt"));
        sizePolicy2.setHeightForWidth(r_Bt->sizePolicy().hasHeightForWidth());
        r_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(r_Bt, 2, 3, 1, 1);

        t_Bt = new QPushButton(layoutWidget);
        t_Bt->setObjectName(QStringLiteral("t_Bt"));
        sizePolicy2.setHeightForWidth(t_Bt->sizePolicy().hasHeightForWidth());
        t_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(t_Bt, 2, 4, 1, 1);

        y_Bt = new QPushButton(layoutWidget);
        y_Bt->setObjectName(QStringLiteral("y_Bt"));
        sizePolicy2.setHeightForWidth(y_Bt->sizePolicy().hasHeightForWidth());
        y_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(y_Bt, 2, 5, 1, 1);

        u_Bt = new QPushButton(layoutWidget);
        u_Bt->setObjectName(QStringLiteral("u_Bt"));
        sizePolicy2.setHeightForWidth(u_Bt->sizePolicy().hasHeightForWidth());
        u_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(u_Bt, 2, 6, 1, 1);

        i_Bt = new QPushButton(layoutWidget);
        i_Bt->setObjectName(QStringLiteral("i_Bt"));
        sizePolicy2.setHeightForWidth(i_Bt->sizePolicy().hasHeightForWidth());
        i_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(i_Bt, 2, 7, 1, 1);

        o_Bt = new QPushButton(layoutWidget);
        o_Bt->setObjectName(QStringLiteral("o_Bt"));
        sizePolicy2.setHeightForWidth(o_Bt->sizePolicy().hasHeightForWidth());
        o_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(o_Bt, 2, 8, 1, 1);

        p_Bt = new QPushButton(layoutWidget);
        p_Bt->setObjectName(QStringLiteral("p_Bt"));
        sizePolicy2.setHeightForWidth(p_Bt->sizePolicy().hasHeightForWidth());
        p_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(p_Bt, 2, 9, 1, 1);

        caps_Bt = new QPushButton(layoutWidget);
        caps_Bt->setObjectName(QStringLiteral("caps_Bt"));
        sizePolicy2.setHeightForWidth(caps_Bt->sizePolicy().hasHeightForWidth());
        caps_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(caps_Bt, 3, 0, 1, 1);

        a_Bt = new QPushButton(layoutWidget);
        a_Bt->setObjectName(QStringLiteral("a_Bt"));
        sizePolicy2.setHeightForWidth(a_Bt->sizePolicy().hasHeightForWidth());
        a_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(a_Bt, 3, 1, 1, 1);

        s_Bt = new QPushButton(layoutWidget);
        s_Bt->setObjectName(QStringLiteral("s_Bt"));
        sizePolicy2.setHeightForWidth(s_Bt->sizePolicy().hasHeightForWidth());
        s_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(s_Bt, 3, 2, 1, 1);

        d_Bt = new QPushButton(layoutWidget);
        d_Bt->setObjectName(QStringLiteral("d_Bt"));
        sizePolicy2.setHeightForWidth(d_Bt->sizePolicy().hasHeightForWidth());
        d_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(d_Bt, 3, 3, 1, 1);

        f_Bt = new QPushButton(layoutWidget);
        f_Bt->setObjectName(QStringLiteral("f_Bt"));
        sizePolicy2.setHeightForWidth(f_Bt->sizePolicy().hasHeightForWidth());
        f_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(f_Bt, 3, 4, 1, 1);

        g_Bt = new QPushButton(layoutWidget);
        g_Bt->setObjectName(QStringLiteral("g_Bt"));
        sizePolicy2.setHeightForWidth(g_Bt->sizePolicy().hasHeightForWidth());
        g_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(g_Bt, 3, 5, 1, 1);

        h_Bt = new QPushButton(layoutWidget);
        h_Bt->setObjectName(QStringLiteral("h_Bt"));
        sizePolicy2.setHeightForWidth(h_Bt->sizePolicy().hasHeightForWidth());
        h_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(h_Bt, 3, 6, 1, 1);

        j_Bt = new QPushButton(layoutWidget);
        j_Bt->setObjectName(QStringLiteral("j_Bt"));
        sizePolicy2.setHeightForWidth(j_Bt->sizePolicy().hasHeightForWidth());
        j_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(j_Bt, 3, 7, 1, 1);

        k_Bt = new QPushButton(layoutWidget);
        k_Bt->setObjectName(QStringLiteral("k_Bt"));
        sizePolicy2.setHeightForWidth(k_Bt->sizePolicy().hasHeightForWidth());
        k_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(k_Bt, 3, 8, 1, 1);

        l_Bt = new QPushButton(layoutWidget);
        l_Bt->setObjectName(QStringLiteral("l_Bt"));
        sizePolicy2.setHeightForWidth(l_Bt->sizePolicy().hasHeightForWidth());
        l_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(l_Bt, 3, 9, 1, 1);

        zh_us_Bt = new QPushButton(layoutWidget);
        zh_us_Bt->setObjectName(QStringLiteral("zh_us_Bt"));
        sizePolicy2.setHeightForWidth(zh_us_Bt->sizePolicy().hasHeightForWidth());
        zh_us_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(zh_us_Bt, 4, 0, 1, 1);

        z_Bt = new QPushButton(layoutWidget);
        z_Bt->setObjectName(QStringLiteral("z_Bt"));
        sizePolicy2.setHeightForWidth(z_Bt->sizePolicy().hasHeightForWidth());
        z_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(z_Bt, 4, 1, 1, 1);

        x_Bt = new QPushButton(layoutWidget);
        x_Bt->setObjectName(QStringLiteral("x_Bt"));
        sizePolicy2.setHeightForWidth(x_Bt->sizePolicy().hasHeightForWidth());
        x_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(x_Bt, 4, 2, 1, 1);

        c_Bt = new QPushButton(layoutWidget);
        c_Bt->setObjectName(QStringLiteral("c_Bt"));
        sizePolicy2.setHeightForWidth(c_Bt->sizePolicy().hasHeightForWidth());
        c_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(c_Bt, 4, 3, 1, 1);

        v_Bt = new QPushButton(layoutWidget);
        v_Bt->setObjectName(QStringLiteral("v_Bt"));
        sizePolicy2.setHeightForWidth(v_Bt->sizePolicy().hasHeightForWidth());
        v_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(v_Bt, 4, 4, 1, 1);

        b_Bt = new QPushButton(layoutWidget);
        b_Bt->setObjectName(QStringLiteral("b_Bt"));
        sizePolicy2.setHeightForWidth(b_Bt->sizePolicy().hasHeightForWidth());
        b_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(b_Bt, 4, 5, 1, 1);

        n_Bt = new QPushButton(layoutWidget);
        n_Bt->setObjectName(QStringLiteral("n_Bt"));
        sizePolicy2.setHeightForWidth(n_Bt->sizePolicy().hasHeightForWidth());
        n_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(n_Bt, 4, 6, 1, 1);

        m_Bt = new QPushButton(layoutWidget);
        m_Bt->setObjectName(QStringLiteral("m_Bt"));
        sizePolicy2.setHeightForWidth(m_Bt->sizePolicy().hasHeightForWidth());
        m_Bt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(m_Bt, 4, 7, 1, 1);

        spaceBt = new QPushButton(layoutWidget);
        spaceBt->setObjectName(QStringLiteral("spaceBt"));
        sizePolicy2.setHeightForWidth(spaceBt->sizePolicy().hasHeightForWidth());
        spaceBt->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(spaceBt, 4, 8, 1, 2);

        showLb = new QLabel(layoutWidget);
        showLb->setObjectName(QStringLiteral("showLb"));
        showLb->setStyleSheet(QStringLiteral(""));
        showLb->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(showLb, 0, 2, 1, 5);

        langLb = new QLabel(layoutWidget);
        langLb->setObjectName(QStringLiteral("langLb"));
        langLb->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(langLb, 0, 0, 1, 2);

        layoutWidget1 = new QWidget(KeyBoard);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(470, 10, 121, 181));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        num_2_Bt = new QPushButton(layoutWidget1);
        num_2_Bt->setObjectName(QStringLiteral("num_2_Bt"));
        sizePolicy2.setHeightForWidth(num_2_Bt->sizePolicy().hasHeightForWidth());
        num_2_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_2_Bt, 3, 1, 1, 1);

        num_1_Bt = new QPushButton(layoutWidget1);
        num_1_Bt->setObjectName(QStringLiteral("num_1_Bt"));
        sizePolicy2.setHeightForWidth(num_1_Bt->sizePolicy().hasHeightForWidth());
        num_1_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_1_Bt, 3, 0, 1, 1);

        num_9_Bt = new QPushButton(layoutWidget1);
        num_9_Bt->setObjectName(QStringLiteral("num_9_Bt"));
        sizePolicy2.setHeightForWidth(num_9_Bt->sizePolicy().hasHeightForWidth());
        num_9_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_9_Bt, 1, 2, 1, 1);

        num_3_Bt = new QPushButton(layoutWidget1);
        num_3_Bt->setObjectName(QStringLiteral("num_3_Bt"));
        sizePolicy2.setHeightForWidth(num_3_Bt->sizePolicy().hasHeightForWidth());
        num_3_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_3_Bt, 3, 2, 1, 1);

        num_6_Bt = new QPushButton(layoutWidget1);
        num_6_Bt->setObjectName(QStringLiteral("num_6_Bt"));
        sizePolicy2.setHeightForWidth(num_6_Bt->sizePolicy().hasHeightForWidth());
        num_6_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_6_Bt, 2, 2, 1, 1);

        num_5_Bt = new QPushButton(layoutWidget1);
        num_5_Bt->setObjectName(QStringLiteral("num_5_Bt"));
        sizePolicy2.setHeightForWidth(num_5_Bt->sizePolicy().hasHeightForWidth());
        num_5_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_5_Bt, 2, 1, 1, 1);

        num_8_Bt = new QPushButton(layoutWidget1);
        num_8_Bt->setObjectName(QStringLiteral("num_8_Bt"));
        sizePolicy2.setHeightForWidth(num_8_Bt->sizePolicy().hasHeightForWidth());
        num_8_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_8_Bt, 1, 1, 1, 1);

        num_7_Bt = new QPushButton(layoutWidget1);
        num_7_Bt->setObjectName(QStringLiteral("num_7_Bt"));
        sizePolicy2.setHeightForWidth(num_7_Bt->sizePolicy().hasHeightForWidth());
        num_7_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_7_Bt, 1, 0, 1, 1);

        num_0_Bt = new QPushButton(layoutWidget1);
        num_0_Bt->setObjectName(QStringLiteral("num_0_Bt"));
        sizePolicy2.setHeightForWidth(num_0_Bt->sizePolicy().hasHeightForWidth());
        num_0_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_0_Bt, 0, 0, 1, 1);

        num_4_Bt = new QPushButton(layoutWidget1);
        num_4_Bt->setObjectName(QStringLiteral("num_4_Bt"));
        sizePolicy2.setHeightForWidth(num_4_Bt->sizePolicy().hasHeightForWidth());
        num_4_Bt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(num_4_Bt, 2, 0, 1, 1);

        closeBt = new QPushButton(layoutWidget1);
        closeBt->setObjectName(QStringLiteral("closeBt"));
        sizePolicy2.setHeightForWidth(closeBt->sizePolicy().hasHeightForWidth());
        closeBt->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(closeBt, 0, 2, 1, 1);


        retranslateUi(KeyBoard);

        QMetaObject::connectSlotsByName(KeyBoard);
    } // setupUi

    void retranslateUi(QDialog *KeyBoard)
    {
        KeyBoard->setWindowTitle(QApplication::translate("KeyBoard", "Dialog", Q_NULLPTR));
        prevBt->setText(QApplication::translate("KeyBoard", "<", Q_NULLPTR));
        nextBt->setText(QApplication::translate("KeyBoard", ">", Q_NULLPTR));
        delBt->setText(QApplication::translate("KeyBoard", "Del", Q_NULLPTR));
        zh_1_Bt->setText(QString());
        zh_2_Bt->setText(QString());
        zh_3_Bt->setText(QString());
        zh_4_Bt->setText(QString());
        zh_5_Bt->setText(QString());
        zh_6_Bt->setText(QString());
        zh_7_Bt->setText(QString());
        zh_8_Bt->setText(QString());
        zh_9_Bt->setText(QString());
        zh_10_Bt->setText(QString());
        q_Bt->setText(QApplication::translate("KeyBoard", "q", Q_NULLPTR));
        w_Bt->setText(QApplication::translate("KeyBoard", "w", Q_NULLPTR));
        e_Bt->setText(QApplication::translate("KeyBoard", "e", Q_NULLPTR));
        r_Bt->setText(QApplication::translate("KeyBoard", "r", Q_NULLPTR));
        t_Bt->setText(QApplication::translate("KeyBoard", "t", Q_NULLPTR));
        y_Bt->setText(QApplication::translate("KeyBoard", "y", Q_NULLPTR));
        u_Bt->setText(QApplication::translate("KeyBoard", "u", Q_NULLPTR));
        i_Bt->setText(QApplication::translate("KeyBoard", "i", Q_NULLPTR));
        o_Bt->setText(QApplication::translate("KeyBoard", "o", Q_NULLPTR));
        p_Bt->setText(QApplication::translate("KeyBoard", "p", Q_NULLPTR));
        caps_Bt->setText(QApplication::translate("KeyBoard", "Caps", Q_NULLPTR));
        a_Bt->setText(QApplication::translate("KeyBoard", "a", Q_NULLPTR));
        s_Bt->setText(QApplication::translate("KeyBoard", "s", Q_NULLPTR));
        d_Bt->setText(QApplication::translate("KeyBoard", "d", Q_NULLPTR));
        f_Bt->setText(QApplication::translate("KeyBoard", "f", Q_NULLPTR));
        g_Bt->setText(QApplication::translate("KeyBoard", "g", Q_NULLPTR));
        h_Bt->setText(QApplication::translate("KeyBoard", "h", Q_NULLPTR));
        j_Bt->setText(QApplication::translate("KeyBoard", "j", Q_NULLPTR));
        k_Bt->setText(QApplication::translate("KeyBoard", "k", Q_NULLPTR));
        l_Bt->setText(QApplication::translate("KeyBoard", "l", Q_NULLPTR));
        zh_us_Bt->setText(QApplication::translate("KeyBoard", "\344\270\255/\350\213\261", Q_NULLPTR));
        z_Bt->setText(QApplication::translate("KeyBoard", "z", Q_NULLPTR));
        x_Bt->setText(QApplication::translate("KeyBoard", "x", Q_NULLPTR));
        c_Bt->setText(QApplication::translate("KeyBoard", "c", Q_NULLPTR));
        v_Bt->setText(QApplication::translate("KeyBoard", "v", Q_NULLPTR));
        b_Bt->setText(QApplication::translate("KeyBoard", "b", Q_NULLPTR));
        n_Bt->setText(QApplication::translate("KeyBoard", "n", Q_NULLPTR));
        m_Bt->setText(QApplication::translate("KeyBoard", "m", Q_NULLPTR));
        spaceBt->setText(QApplication::translate("KeyBoard", "space", Q_NULLPTR));
        showLb->setText(QString());
        langLb->setText(QApplication::translate("KeyBoard", "\350\213\261\346\226\207", Q_NULLPTR));
        num_2_Bt->setText(QApplication::translate("KeyBoard", "2", Q_NULLPTR));
        num_1_Bt->setText(QApplication::translate("KeyBoard", "1", Q_NULLPTR));
        num_9_Bt->setText(QApplication::translate("KeyBoard", "9", Q_NULLPTR));
        num_3_Bt->setText(QApplication::translate("KeyBoard", "3", Q_NULLPTR));
        num_6_Bt->setText(QApplication::translate("KeyBoard", "6", Q_NULLPTR));
        num_5_Bt->setText(QApplication::translate("KeyBoard", "5", Q_NULLPTR));
        num_8_Bt->setText(QApplication::translate("KeyBoard", "8", Q_NULLPTR));
        num_7_Bt->setText(QApplication::translate("KeyBoard", "7", Q_NULLPTR));
        num_0_Bt->setText(QApplication::translate("KeyBoard", "0", Q_NULLPTR));
        num_4_Bt->setText(QApplication::translate("KeyBoard", "4", Q_NULLPTR));
        closeBt->setText(QApplication::translate("KeyBoard", "\357\271\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class KeyBoard: public Ui_KeyBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
