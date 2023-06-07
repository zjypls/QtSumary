//
// Created by 32725 on 2023/6/6.
//
#include <QPainter>
#include "Tetris.h"

zTetris::zTetris(QWidget *parent) : QWidget(parent){
	this->resize(column * blockSize, row * blockSize);
	std::memset(status, true, sizeof(status));
	painter=new QPainter();
	update();
}

zTetris::~zTetris() {
	delete painter;
}

void zTetris::paintEvent(QPaintEvent *event) {
	painter->begin(this);
	painter->setPen(Qt::red);
	QWidget::paintEvent(event);
	for (int i = 0; i < column; ++i) {
		for (int j = 0; j < row; ++j) {
			if (status[i][j]) {
				painter->drawRect(i * blockSize+distance, j * blockSize+distance, blockSize-distance, blockSize-distance);
			}
		}
	}
	painter->end();
}

void zTetris::keyPressEvent(QKeyEvent *event) {
	QWidget::keyPressEvent(event);
}
