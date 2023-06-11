//
// Created by 32725 on 2023/6/6.
//
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <Qmessagebox>
#include <QLineEdit>
#include <QPushButton>
#include "Tetris.h"
static QRandomGenerator* generator=QRandomGenerator::global();

bool zTetris::GameOver=false;
zTetris::zTetris(QWidget *parent) : QWidget(parent){
    this->resize((column+5) * (blockSize)+distance, row * (blockSize)+distance);

    //Debug
    if(0){
        auto* editLine=new QLineEdit(this);
        editLine->move((column+1)*blockSize+distance,5*blockSize+distance);
        auto* pushButton=new QPushButton("Change",this);
        pushButton->move((column+1)*blockSize+distance,6*blockSize+distance);
        connect(pushButton,&QPushButton::clicked,[this,pushButton,editLine](){
            int type=0;
            bool isOk=false;
            type=editLine->text().toInt(&isOk);
            if(isOk){
                preViewShape=zShape(zShape::zShapeType(type%7));
            }
        });
    }

    memset(status,empty,sizeof(status));
	painter=new QPainter();
	shape=zShape::GenerateShape();
	static auto* PainterTimer=new QTimer(this);
    preViewShape=zShape::GenerateShape();
    connect(PainterTimer,&QTimer::timeout,[this](){
        if(!zTetris::IsGameOver())
            if(!zTetris::IsGameOver()&&!TryFall()){
                if(shape.pos[rotateBase].y<2){
                    zTetris::SetIsGameOver();
                    QMessageBox::information(nullptr,"Message","GameOver");
                }else{
                    CheckDelete();
                    shape=preViewShape;
                    preViewShape=zShape::GenerateShape();

                }
            }
		update();
	});
	PainterTimer->start(500);
	update();
}

zTetris::~zTetris() {
	delete painter;
}

void zTetris::paintEvent(QPaintEvent *event) {
	painter->begin(this);
	painter->setPen(Qt::red);
	painter->setBrush(Qt::red);
	QWidget::paintEvent(event);
	shape.Draw(painter);
	for (int i = 0; i < column; ++i) {
		for (int j = 0; j < row; ++j) {
			if (status[i][j]) {
				painter->drawRect(i * blockSize+distance, j * blockSize+distance, blockSize-distance, blockSize-distance);
			}
		}
	}
    painter->setPen(Qt::green);
    painter->drawLine(column*(blockSize)+distance,0,column*(blockSize)+distance,height());
    painter->setBrush(Qt::green);
    preViewShape.Draw(painter,column-1,1);
	painter->end();
}



void zTetris::keyPressEvent(QKeyEvent *event) {
	QWidget::keyPressEvent(event);
	switch (event->key()) {
		case Qt::Key_W:
		case Qt::Key_Up:
			shape.Rotate(status);
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			shape.Move(-1, status);
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			shape.Move(1, status);
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			TryFall();
			break;
		case Qt::Key_Space:
			while(TryFall());
			break;
	}
	update();
}

bool zTetris::TryFall() {
	static ivec2 pos[4];
	std::copy(shape.pos,shape.pos+4,pos);
	for(auto & po : pos) {
		po.y++;
		if(po.y>=row||status[po.x][po.y]==full){
			for(auto & p : shape.pos) {
				status[p.x][p.y]=full;
			}
			return false;
		}
	}
	std::copy(pos,pos+4,shape.pos);
	return true;
}

void zTetris::CheckDelete() {
    int top=0;
    for (int i = row-1; i>=top; --i) {
        int nums=0;
        for(int j=0;j<column;++j){
            if(i<=0||status[j][i]==empty){
                break;
            }else if(j==column-1){
                ++nums;
                j=0;
                --i;
            }
        }
        if(nums>0){
            i+=nums;
            for (int j = i; j >=nums+top; --j) {
				for (auto & statu : status) {
                    statu[j]=statu[j-nums];
				}
			}
            top+=nums;
		}
	}
    for(int j=top-1;j>=0;--j){
        for(auto&statu:status){
            statu[j]=empty;
        }
    }

}

zShape zShape::GenerateShape() {
    auto type=static_cast<zShapeType>(generator->bounded(0,6));
	//qDebug()<<test::shapeTypeToString(type);
	return zShape(type);
}

QString test::shapeTypeToString(zShape::zShapeType type){
	switch (type) {
		#define caseType(x) case zShape::zShapeType::e##x: return #x
		caseType(I);
		caseType(O);
		caseType(T);
		caseType(S);
		caseType(Z);
		caseType(J);
		caseType(L);
		#undef caseType
		default:
			throw std::runtime_error("zShapeType error");
	}
}
