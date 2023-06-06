//
// Created by 32725 on 2023/6/3.
//

#include <QKeyEvent>
#include <QPainter>
#include "Snake.h"

QRandomGenerator *Food::random = new QRandomGenerator(QTime::currentTime().msec());

Snake::Snake(QVector2D headPos, QVector2D direction, int length) : headPos(headPos), direction(direction) {
	QVector2D temp = headPos - direction * (BODY_SIZE * 2 * (length + 1));
	for (int i = 0; i < length; ++i) {
		temp += direction * (BODY_SIZE * 2);
		bodies.enqueue(SnakeBody(temp));
	}
}

void Snake::Walk(Food *food) {
	auto temp = headPos;
	headPos += direction * (BODY_SIZE * 2);
	if (food->isHit(headPos)) {
		food->ChangePos(this);
		bodies.enqueue(SnakeBody(temp));
		emit SizeChanged(GetSize());
	} else {
		bodies.enqueue(SnakeBody(temp));
		bodies.dequeue();
	}
	if(CheckPos(headPos)||headPos.x()<0||headPos.y()<0||headPos.x()>bound.x()||headPos.y()>bound.y())
		GameOver = true;
}

void Snake::Draw(QPainter *painter) {
	painter->setBrush(Qt::blue);
	for (auto &body: bodies) {
		painter->drawRect(body.pos.x() - BODY_SIZE, body.pos.y() - BODY_SIZE, BODY_SIZE * 2, BODY_SIZE * 2);
	}
	painter->setBrush(Qt::darkBlue);
	painter->drawEllipse(headPos.toPointF(), BODY_SIZE, BODY_SIZE);
}

void Snake::ChangeDirection(QKeyEvent *event) {
	using namespace Qt;
	switch (event->key()) {
		case Key_W:
		case Key_Up:
			if (direction == QVector2D{0, 1})
				break;
			direction = {0, -1};
			break;
		case Key_S:
		case Key_Down:
			if (direction == QVector2D{0, -1})
				break;
			direction = {0, 1};
			break;
		case Key_A:
		case Key_Left:
			if (direction == QVector2D{1, 0})
				break;
			direction = {-1, 0};
			break;
		case Key_D:
		case Key_Right:
			if (direction == QVector2D{-1, 0})
				break;
			direction = {1, 0};
			break;
		default:
			break;
	}
}

bool Snake::CheckPos(QVector2D pos) {
	for (auto &body: bodies)
		if (body.isHit(pos))
			return true;
	return false;
}


SnakeBody::SnakeBody(QVector2D pos) : pos(pos) {

}

bool SnakeBody::isHit(QVector2D _pos) {
	return pos.distanceToPoint(_pos) < (BODY_SIZE * 1.5);
}

Food::Food(QVector2D pos) : SnakeBody(pos) {
}

void Food::Draw(QPainter *painter) {
	static unsigned long frame = 0;
	Show = ++frame % 2;
	if (Show) {
		painter->setBrush(Qt::red);
		painter->drawEllipse(pos.toPointF(), BODY_SIZE, BODY_SIZE);
	}
}

bool Food::isHit(QVector2D _pos) {
	return SnakeBody::isHit(_pos);
}

void Food::ChangePos(Snake*snake) {
	do{
		pos = {static_cast<float>(random->bounded(0u + BODY_SIZE, uint(bound.x()) - BODY_SIZE)),
		       static_cast<float>(random->bounded(0u + BODY_SIZE, uint(bound.y()) - BODY_SIZE))};
	}while(snake->CheckPos(pos));
}

void Food::SetBound(QVector2D _bound) {
	bound = _bound;
}
