//
// Created by 32725 on 2023/6/3.
//
#include <QPushButton>
#include <QBuffer>
#include <QThread>
#include <QTimer>
#include "Client.h"

zClient::zClient(QWidget *parent):QWidget(parent) {
	this->setWindowTitle("Client");
	ipPort = new tools::IPPort(this);
	clientSend = new ClientSend();
	recThread = new QThread();
	clientSend->moveToThread(recThread);
	recThread->start();
	ipPort->RegisterForStart([=]{
		if (clientSend->Connected()) {
			clientSend->DisConnect();
			ipPort->getButton()->setText("Connect");
		} else {
			clientSend->Connect(ipPort->getIP(), ipPort->getPort());
			ipPort->getButton()->setText("Disconnect");
		}
	});
}

zClient::~zClient() {
	if (recThread) {
		recThread->quit();
		recThread->wait();
	}
	delete clientSend;
	delete recThread;
}
