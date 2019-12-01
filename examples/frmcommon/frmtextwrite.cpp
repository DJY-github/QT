#include "frmtextwrite.h"
#include "ui_frmtextwrite.h"
#include "head.h"

frmTextWrite::frmTextWrite(QWidget *parent) : QWidget(parent), ui(new Ui::frmTextWrite)
{
	ui->setupUi(this);
	this->initForm();
}

frmTextWrite::~frmTextWrite()
{
	delete ui;
}

void frmTextWrite::initForm()
{
    QFont font("Microsoft Yahei", 15);
	ui->txt1->setFont(font);
	ui->txt2->setFont(font);

    QFile file(":/image/test.txt");
	file.open(QFile::ReadOnly | QFile::Text);
	content = file.readAll();
	len = content.length();
	ui->txt1->setText(content);
	connect(ui->txt2, SIGNAL(textChanged()), this, SLOT(changeText()));
}

void frmTextWrite::changeText()
{
	QStringList html;
	//头部固定格式
	html.append("<html><head/><body style=\"font-family:'微软雅黑';font-size:15pt;font-weight:400;font-style:normal;\"><p>");

	QString str = ui->txt2->toPlainText();
	int strLen = str.length();

	for (int i = 0; i < len; i++) {
		if (i < strLen) {
            if (content.at(i) == str.at(i)) {
				//已输入正确字符
                html.append(QString("<span style=\"background-color:rgb(171,171,171);\">%1</span>").arg(content.at(i)));
			} else {
				//已输入错误字符
                html.append(QString("<span style=\"background-color:rgb(255,0,0);\">%1</span>").arg(content.at(i)));
			}
		} else {
			//未输入字符
			html.append(QString("<span style=\"background-color:rgba(0,0,0,0);\">%1</span>").arg(content.mid(strLen, len - 1)));
			break;
		}
	}

	//尾部固定结束格式
	html.append("</p></body></html>");
	ui->txt1->setHtml(html.join(""));
}
