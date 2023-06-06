//
// Created by 32725 on 2023/6/5.
//
#include <QApplication>
#include "zVideoWidget.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Player w{};
	w.show();
	return QApplication::exec();
}