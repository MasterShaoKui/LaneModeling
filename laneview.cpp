#include "laneview.h"
#include "ui_laneview.h"
#include "constants.h"
#include "guessbean.h"
#include "mark.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

LaneView::LaneView(QWidget * parent) :
    QWidget(parent),ui(new Ui::LaneView)
{
    ui->setupUi(this);
}

LaneView::LaneView(LaneModel * model, QWidget * parent) :
    QWidget(parent), model(model), isShowCarTrace(true),
    ui(new Ui::LaneView)
{
    whiteSolid.setStyle(Qt::SolidLine);
    whiteSolid.setColor(QColor(Qt::lightGray));//	#778899
    whiteSolid.setWidth(penLineWidth);
    whiteDotted.setStyle(Qt::DotLine);
    whiteDotted.setColor(QColor(0,255,0));
    whiteDotted.setWidth(penLineWidth);
    yellowSolid.setStyle(Qt::SolidLine);
    yellowSolid.setColor(QColor(Qt::darkYellow));
    yellowSolid.setWidth(penLineWidth);
    yellowDotted.setStyle(Qt::DotLine);
    yellowDotted.setColor(QColor(255, 153, 0));
    yellowDotted.setWidth(penLineWidth);
    border.setStyle(Qt::SolidLine);
    border.setColor(QColor(153,0,255));
    border.setWidth(penLineWidth);
    other.setStyle(Qt::SolidLine);
    other.setColor(QColor(0,0,255));
    other.setWidth(penLineWidth);
    unknown.setStyle(Qt::SolidLine);
    unknown.setColor(QColor(16,16,16));//黑色
    unknown.setWidth(penLineWidth);
    carTrace.setStyle(Qt::SolidLine);
    carTrace.setWidth(penLineWidth);
    carTrace.setColor(QColor(255,0,0));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
}

LaneView::~LaneView()
{
    delete model;
    delete ui;
}

void LaneView::paintEvent(QPaintEvent * event){
    if(model->getJigsaws().isEmpty()){
        return;
    }
    int startX = 30;//画笔起始点的X坐标
    int startY = 60;//画笔起始点的Y坐标
    int carPosX = startX;//汽车的坐标
    int carPosY = (height() - 100) / (model->getJigsaws()[0].marks.size() - 1);;//汽车的坐标
    QPainter painter(this);
    const double step = (width() - 50) / model->getTotalPicNum();//一个“图片”有多“长”
    //const double laneWidth = (height() - 30) / (model->getMaxLaneNum() - 1);//一条车道有多宽
    for(int i = 0; i < model->getJigsaws().length(); i++){
        GuessBean currentPart = model->getJigsaws()[i];
        double lineLength = step * currentPart.picNum;//有多少张图片就画多长的道路线
        double lineWidth = (height() - 100) / (model->getJigsaws()[i].marks.size() - 1);
        for(int j = 0; j < currentPart.marks.size(); j++){
            painter.setPen(getCorrespondingPen(currentPart.marks[j].type));
            painter.drawLine(startX, startY + j*lineWidth, startX + lineLength, startY + j*lineWidth);
        }
        //计算下一画线起始点
        startX = startX + lineLength;
        if(!isShowCarTrace){
            continue;
        }
        //开始描绘汽车轨迹
        if(currentPart.myCurrentLane >= 0 && currentPart.myCurrentLane < currentPart.marks.length()){
            painter.setPen(carTrace);
            //找到车当前的位置
            int carCurrentPosY = startY + (lineWidth / 2) + currentPart.myCurrentLane * lineWidth;
            //转换车道
            //painter.drawLine(carPosX, carPosY, carPosX, carCurrentPosY);
            //水平移动
            painter.drawLine(carPosX, carCurrentPosY, carPosX + lineLength, carCurrentPosY);
            carPosX += lineLength;
            carPosY = carCurrentPosY;
        }
    }
}

QPen LaneView::getCorrespondingPen(const QString & type) const{
    if(type == white_solid){
        return whiteSolid;
    }else if(type == white_dotted){
        return whiteDotted;
    }else if(type == yellow_solid){
        return yellowSolid;
    }else if(type == yellow_dotted){
        return yellowDotted;
    }else if(type == lane_border){
        return border;
    }else if(type == theOther){
        return other;
    }else{
        return unknown;
    }
}

void LaneView::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        this->close();
        break;
    default:
        break;
    }
}

void LaneView::switchShowCarTrace(){
    isShowCarTrace = !isShowCarTrace;
    this->repaint();
}

void LaneView::refresh(){
    this->update();
}
