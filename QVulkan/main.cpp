//
// Created by 32725 on 2023/6/5.
//
#include <QApplication>
#include "zVulkanWidget.h"
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	zVulkanWidget w{};
	w.show();
	return QApplication::exec();
}