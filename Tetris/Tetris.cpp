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
#include <QTime>
#include "Tetris.h"
static QRandomGenerator* generator=QRandomGenerator::global();

bool zTetris::GameOver=false;
zTetris::zTetris(QWidget *parent) : QWidget(parent){
    this->resize((Colums+5) * (BlockSize)+Distance, Rows * (BlockSize)+Distance);

    //Debug
    if(0){
        auto* editLine=new QLineEdit(this);
        editLine->move((Colums+1)*BlockSize+Distance,5*BlockSize+Distance);
        auto* pushButton=new QPushButton("Change",this);
        pushButton->move((Colums+1)*BlockSize+Distance,6*BlockSize+Distance);
        connect(pushButton,&QPushButton::clicked,[this,pushButton,editLine](){
            int type=0;
            bool isOk=false;
            type=editLine->text().toInt(&isOk);
            if(isOk){
                preViewShape=zShape(zShape::zShapeType(type%7));
            }
        });
    }

    memset(Board,Empty,sizeof(Board));
	painter=new QPainter();
	shape=zShape::GenerateShape();
	static auto* PainterTimer=new QTimer(this);
    preViewShape=zShape::GenerateShape();
    connect(PainterTimer,&QTimer::timeout,[this](){
        if(!zTetris::IsGameOver())
            if(!zTetris::IsGameOver()&&!TryFall()){
                if(shape.pos[RotateBaseIndex].y<2){
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
    for (int i = 0; i < Colums; ++i) {
        for (int j = 0; j < Rows; ++j) {
            if (Board[j][i]) {
                painter->drawRect(i * BlockSize+Distance, j * BlockSize+Distance, BlockSize-Distance, BlockSize-Distance);
			}
		}
	}
    painter->setPen(Qt::green);
    painter->drawLine(Colums*(BlockSize)+Distance,0,Colums*(BlockSize)+Distance,height());
    painter->setBrush(Qt::green);
    preViewShape.Draw(painter,Colums-1,1);
	painter->end();
}



void zTetris::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
        shape.Rotate(Board);
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            shape.Move(-1, Board);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            shape.Move(1, Board);
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
            if(po.y>=Rows||Board[po.y][po.x]==Full){
            for(auto & p : shape.pos) {
                Board[p.y][p.x]=Full;
            }
            return false;
        }
    }
	std::copy(pos,pos+4,shape.pos);
	return true;
}

void zTetris::CheckDelete() {
    int deleteCount=0;
    unsigned int states=0;
    for (int i=0;i<Rows;++i) {
        bool IsFull=true;
        for(auto&block:Board[i]){
            if(block==Empty){
                IsFull=false;
                break;
            }
        }
        if(IsFull){
            std::memset(Board[i],0,sizeof(Board[i]));
            ++deleteCount;
            states|=(1u<<i);
        }
    }
    int ptr1=-1,ptr2=-1;
    for(int i=Rows-1;i>=0;--i){
        if((1u<<i)&states){
            ptr1=i;
            ptr2=i-1;
            break;
        }
    }
    for(;ptr2>=deleteCount;--ptr2){
        if((!((1<<ptr2)&states))){
            std::swap_ranges(Board[ptr1],Board[ptr1]+Colums,Board[ptr2]);
            --ptr1;
        }
    }
    std::memset(Board,0,sizeof(short)*deleteCount*Colums);

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
