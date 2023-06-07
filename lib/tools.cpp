//
// Created by 32725 on 2023/6/3.
//
#include <QRegularExpression>
#include "tools.h"

//a regular expression to match IP address
QRegularExpression ipReg(R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]\d|\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]\d|\d)$)");

namespace tools {


	bool validIP(const QString &IP){
		return ipReg.match(IP).hasMatch();
	}

	IPPort::IPPort(QWidget *parent) : QWidget(parent) {
		this->resize(200, 60);
		address = new QHostAddress("127.0.0.1");
		ip = new QLineEdit(address->toString(), this);
		ip->resize(150, 20);
		ip->move(50, 0);
		ip->show();
		port = new QLineEdit("11455", this);
		port->resize(150, 20);
		port->move(50, 20);
		port->show();
		IPLabel = new QLabel("IP:", this);
		IPLabel->move(0, 0);
		IPLabel->resize(50, 20);
		IPLabel->show();
		portLabel = new QLabel("Port:", this);
		portLabel->move(0, 20);
		portLabel->resize(50, 20);
		portLabel->show();
		startButton = new QPushButton("Start", this);
		startButton->move(0, 40);
		startButton->resize(100, 20);
		startButton->show();
		connect(ip, &QLineEdit::textChanged, [=]() {
			if (ip->text() == "Any") {
				ip->setStyleSheet("QLineEdit{background-color: white;}");
				*address = QHostAddress::Any;
			}else if (validIP(ip->text())) {
				ip->setStyleSheet("QLineEdit{background-color: white;}");
				*address = QHostAddress(ip->text());
			}else
				ip->setStyleSheet("QLineEdit{background-color: red;}");
		});
		connect(port, &QLineEdit::textChanged, [=]() {
			if(int val=port->text().toInt();val >= 65535 || val <= 0)
				port->setStyleSheet("QLineEdit{background-color: red;}");
			else {
				Port = val;
				port->setStyleSheet("QLineEdit{background-color: white;}");
			}
		});
	}

	IPPort::~IPPort() {
		delete address;
	}

	FileTranslator::FileTranslator(QWidget *parent):QWidget(parent) {

	}

	FileTranslator::~FileTranslator() {

	}
}