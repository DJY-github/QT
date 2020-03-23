/***************************************************************************
 *   Copyright (C) 2008 by Giovanni Romano                                 *
 *   Giovanni.Romano.76@gmail.com                                          *
 *                                                                         *
 *   This program may be distributed under the terms of the Q Public       *
 *   License as defined by Trolltech AS of Norway and appearing in the     *
 *   file LICENSE.QPL included in the packaging of this file.              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 ***************************************************************************/


#include "QKeyPushButton.h"
#include "widgetKeyBoard.h"
#include <QKeyEvent>
#include <QCoreApplication>


QKeyPushButton::QKeyPushButton(QWidget *parent) : QPushButton(parent), m_parent(parent)
{
	this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON));
	connect(this, SIGNAL(pressedKey(bool)), SLOT(getKeyPress(bool)));
        if ((static_cast<widgetKeyBoard *> (parent))->isEmbeddedKeyboard() == true)
            this->style_embedded = QString(EMBEDDED_KEYBOARD);
}

void QKeyPushButton::getKeyPress(bool capsStatus)
{
	int 		keyCode = 0;
	QKeyEvent	*key = NULL;
	QString		text = this->text();
	//
	// per tutti i car speciali tranne il CAPS (RETURN, ALT, SHIFT, ecc...) inoltra al componente widgetKeyBoard:
        if (NO_SPECIAL_KEY(text) == false && (IS_BACK(text) == true || IS_BACK_EMB(text) == true || IS_TAB(text) == true || IS_RETURN(text) == true || IS_CTRL_LEFT(text) == true ||
                        IS_ALT(text) == true || IS_CANC(text) == true || IS_CUT_LEFT(text) == true || IS_PASSWORD(text) || IS_PASSWORD_EMB(text) || IS_PASTE(text) || IS_COPY(text)))
		key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
	else { // trattasi di caratteri stampabili
        keyCode = text.toUtf8()[0]; // prende il valore numerico (sempre maiuscolo)
        if (capsStatus == false) { // se deve prendere minuscolo, controlla se il carattere è alfabetico
            if (keyCode >= tr("A")[0] && keyCode <= tr("Z")[0]) {
                keyCode += 32; // carattere piccolo
                text = (char ) keyCode; // carattere piccolo
            }
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
		}
		else
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::ShiftModifier, text);
	}
    ((widgetKeyBoard *) this->m_parent)->receiptChildKey(key, NULL);
	QCoreApplication::processEvents();
}


void QKeyPushButton::mousePressEvent(QMouseEvent * /*event */)
{
    static bool 	m_capsActive = true;
    widgetKeyBoard  *tmpKeyBoard = (widgetKeyBoard *) this->m_parent;
    static int      yMarginKeyboard = tmpKeyBoard->rect().y();
	QString		text = this->text();
    short           adjustZoomedKey = HEIGHT_ZOOM_KEY;
    QString         defaultStyleButton = QString(DEFAULT_STYLE_BUTTON);
    QString         changedColorButton = QString(CHANGED_BACKGROUND_BUTTON);
	//
	// se si tratta del maiuscolo:
    if (IS_CAPS(text) == true) {
        if (m_capsActive == false)
			m_capsActive = true;
		else {
            changedColorButton = QString(DEFAULT_BACKGROUND_BUTTON);
			m_capsActive = false;
		}
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
	}
    else if (tmpKeyBoard->isEnabledSwitchingEcho() == true && (IS_PASSWORD(text) == true || IS_PASSWORD_EMB(text) == true))
        tmpKeyBoard->switchKeyEchoMode(tmpKeyBoard->currentTextBox());
	else {
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
		emit pressedKey(m_capsActive);
	}
    this->m_oldYKey = 0;
    if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() && NO_SPECIAL_KEY(text) && text.trimmed().length() != 0) {
        tmpKeyBoard->setCursor(Qt::BlankCursor);
        if (this->y() - adjustZoomedKey - KEY_HEIGHT_EMBEDDED < yMarginKeyboard)
            this->m_oldYKey = this->y();
        else
            adjustZoomedKey = -HEIGHT_ZOOM_KEY;
        this->setGeometry(this->x() - 10, this->y() + adjustZoomedKey - KEY_HEIGHT_EMBEDDED, KEY_WIDTH_EMBEDDED + WIDTH_ZOOM_KEY, KEY_HEIGHT_EMBEDDED + HEIGHT_ZOOM_KEY);
        this->setStyleSheet(changedColorButton + defaultStyleButton);
        QCoreApplication::processEvents();
    }
}

void QKeyPushButton::mouseReleaseEvent(QMouseEvent * /* event */)
{
    widgetKeyBoard  *tmpKeyBoard = (widgetKeyBoard *) this->m_parent;
    bool            pressedEcho = IS_PASSWORD(this->text()) == true || IS_PASSWORD_EMB(this->text()) == true;

    if (IS_CAPS(this->text()) == false && pressedEcho == false) {
        if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() && NO_SPECIAL_KEY(this->text())  && this->text().trimmed().length() != 0) {
            tmpKeyBoard->setCursor(Qt::ArrowCursor);
            if (this->m_oldYKey != 0)
                this->setGeometry(this->x() + 10, this->m_oldYKey, KEY_WIDTH_EMBEDDED, KEY_HEIGHT_EMBEDDED);
            else
                this->setGeometry(this->x() + 10, this->y() + HEIGHT_ZOOM_KEY + KEY_HEIGHT_EMBEDDED, KEY_WIDTH_EMBEDDED, KEY_HEIGHT_EMBEDDED);
            this->m_oldYKey = 0;
            QCoreApplication::processEvents();
        }        
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
    }
    else if (pressedEcho == true && tmpKeyBoard->isEnabledSwitchingEcho() == false && tmpKeyBoard->currentTextBox()->echoMode() == QLineEdit::Normal)
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
    tmpKeyBoard->soundClick();
}
