//
// Created by 32725 on 2023/6/3.
//
#include <QTimer>
#include "zWidget.h"

zWidget::zWidget(QWidget *parent) : QWidget(parent) {
	this->resize(500, 500);
	sizeLabel = new QLabel("10",this);
	sizeLabel->resize(20, 20);
	sizeLabel->move(0, 0);
	sizeLabel->show();
	snake = new Snake({static_cast<float>(width() / 2), static_cast<float>(height() / 2)}, {1, 0}, 10);
	snake->SetBound({static_cast<float>(width()), static_cast<float>(height())});
	food = new Food(QVector2D{static_cast<float>(width() / 2), static_cast<float>(height() / 2)}-QVector2D{100, 100});
	food->SetBound({static_cast<float>(width()), static_cast<float>(height())});
	food->ChangePos(snake);
	auto timer = new QTimer(this);
	connect(snake, &Snake::SizeChanged,this, [&](int size){
		sizeLabel->setText(QString::number(size));
	});
	connect(timer, &QTimer::timeout, this, [=] {
		if(!snake->isGameOver())
			snake->Walk(food);
		update();
	});
	timer->start(500);
	painter = new QPainter();
}

zWidget::~zWidget() {
	delete snake;
	delete painter;
	delete food;
}

void zWidget::paintEvent(QPaintEvent *event) {
	QWidget::paintEvent(event);
	painter->begin(this);
	snake->Draw(painter);
	food->Draw(painter);
	painter->end();
}

void zWidget::keyPressEvent(QKeyEvent *event) {
	QWidget::keyPressEvent(event);
	snake->ChangeDirection(event);
}

void zWidget::resizeEvent(QResizeEvent *event) {
	QWidget::resizeEvent(event);
	snake->SetBound({static_cast<float>(width()), static_cast<float>(height())});
	food->SetBound({static_cast<float>(width()), static_cast<float>(height())});
}
