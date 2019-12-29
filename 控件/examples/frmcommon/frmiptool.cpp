#include "frmiptool.h"
#include "ui_frmiptool.h"
#include "head.h"

frmIPTool::frmIPTool(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmIPTool)
{
	ui->setupUi(this);
}

frmIPTool::~frmIPTool()
{
	delete ui;
}

//判断IP地址及端口是否在线
bool frmIPTool::ipLive(QString ip, int port)
{
	QTcpSocket tcpClient;
	tcpClient.abort();
	tcpClient.connectToHost(ip, port);
	//100毫秒没有连接上则判断不在线
	return tcpClient.waitForConnected(100);
}

//获取网页所有源代码
QString frmIPTool::getHtml(QString url)
{
	QNetworkAccessManager *manager = new QNetworkAccessManager();
	QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
	QByteArray responseData;
	QEventLoop eventLoop;
	QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	responseData = reply->readAll();
	return QString(responseData);
}

//获取本机公网IP地址
QString frmIPTool::getNetIP(QString webCode)
{
	QString web = webCode.replace(" ", "");
	web = web.replace("\r", "");
	web = web.replace("\n", "");
	QStringList list = web.split("<br/>");
	QString tar = list[3];
	QStringList ip = tar.split("=");
	return ip[1];
}

//获取本机IP
QString frmIPTool::getLocalIP()
{
	QString ip;
	QString local = QHostInfo::localHostName();
	QHostInfo host = QHostInfo::fromName(local);
	QList<QHostAddress> address = host.addresses();

	foreach (QHostAddress add, address) {
		ip = add.toString();
		if (isIP(ip)) {
			break;
		}
	}

	return ip;
}

//判断是否是IP地址
bool frmIPTool::isIP(QString ip)
{
	QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	return RegExp.exactMatch(ip);
}

//判断是否通外网
bool frmIPTool::isWebOk()
{
	//能接通百度IP说明可以通外网
	return ipLive("115.239.211.112", 80);
}

void frmIPTool::on_btnGetLocalIP_clicked()
{
	ui->txtLocalIP->clear();
	ui->txtLocalIP->setText(getLocalIP());
}

void frmIPTool::on_btnGetWebIP_clicked()
{
	ui->txtWebIP->clear();

	if (!ipLive("115.239.211.112", 80)) {
		ui->txtWebIP->setText("net error");
		return;
	}

	ui->txtWebIP->setText(getNetIP(getHtml("http://whois.pconline.com.cn/")));
}

void frmIPTool::on_btnWebOk_clicked()
{
	ui->txtWebOk->clear();
	ui->txtWebOk->setText(isWebOk() ? "true" : "false");
}

void frmIPTool::on_btnUrlIP_clicked()
{
	ui->txtIP->clear();

	if (!ipLive("115.239.211.112", 80)) {
		ui->txtIP->setText("net error");
		return;
	}

	QString url = ui->txtUrl->text();
	QHostInfo host = QHostInfo::fromName(url);
	ui->txtIP->setText(host.addresses().at(0).toString());
}
