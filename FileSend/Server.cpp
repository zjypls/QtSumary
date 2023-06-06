//
// Created by 32725 on 2023/6/3.
//
#include <memory>
#include <QMessageBox>
#include <QFileDialog>
#include "Server.h"


zServer::zServer(QWidget *parent): QWidget(parent) {
	this->setWindowTitle("Server");
	sendButton=new QPushButton(this);
	sendButton->setText("Send");
	sendButton->resize(100,30);
	sendButton->move(50,60);
	server=new QTcpServer(this);
	ip=new tools::IPPort(this);
	ip->RegisterForStart([=](){
		if(server->isListening()){
			server->close();
			ip->getButton()->setText("Listen");
		}else{
			if(server->listen(ip->getIP(),ip->getPort())){
				ip->getButton()->setText("Close");
			}else{
				QMessageBox::critical(this,"Error","Listen failed!");
			}
		}
	});
	connect(server,&QTcpServer::newConnection,[&]{
		delete send;
		if(sendThread&&sendThread->isRunning()) {
			sendThread->quit();
			sendThread->wait();
		}
		delete sendThread;
		sendThread=new QThread();
		send=new ServerSend(server->nextPendingConnection());
		send->moveToThread(sendThread);
		sendThread->start();
	});
	connect(sendButton,&QPushButton::clicked,[&]{
		QString path=QFileDialog::getOpenFileName(this,"Select a file to send");
		if(path.isEmpty())return;
		send->Send(path);
	});
}

zServer::~zServer() {
	delete send;
	if(sendThread){
		sendThread->quit();
		sendThread->wait();
	}
	delete sendThread;
}
