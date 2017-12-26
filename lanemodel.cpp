#include "lanemodel.h"
#include <QDebug>

LaneModel::LaneModel(QList<GuessBean> jigsaws) : jigsaws(jigsaws), originTotalPicNum(jigsaws.length())
{
    //将各个假设合并，多个假设可能指的是同一个道路的不同断点。
    mergeGuesses();
    printJigsaws();
}

int LaneModel::getTotalPicNum() const{
    int totalPicNum = 0;
    for(int i = 0; i < jigsaws.size(); i++){
        totalPicNum += jigsaws[i].picNum;
    }
    return totalPicNum;
}

int LaneModel::getOriginTotalPicNum() const
{
    return originTotalPicNum;
}

void LaneModel::mergeGuesses(){
    //进行合并
    //首先合并完全一样的
    absoluteMerge();

    //获得最大的道路线个数
    int maxLaneNum = getMaxLaneNum();
    QList<int> laneNumCounter;
    QList<int> deleteList_usingLaneNum;
    //设置每种道路线数量的图片数为0
    for(int i = 0; i <= maxLaneNum; i++){
        laneNumCounter.append(0);
    }
    for(int i = 0; i < jigsaws.length(); i++){
        laneNumCounter[jigsaws[i].marks.size()] += jigsaws[i].picNum;
    }
    for(int i = 0; i < laneNumCounter.length(); i++){
        if(laneNumCounter[i] < originTotalPicNum * 0.5){
            deleteList_usingLaneNum.append(i);
        }
        qDebug() << i <<laneNumCounter[i];
    }
    //删去标注线数量不合理的图片
    for(int k = 0; k < deleteList_usingLaneNum.length(); k++){
        int laneNumDelete = deleteList_usingLaneNum[k];
        for(int i = 0; i < jigsaws.length(); i++){
            if(jigsaws[i].marks.length() == laneNumDelete && jigsaws[i].picNum < 3){
                jigsaws.removeAt(i);
                i--;
            }
        }
    }
    absoluteMerge();
}

void LaneModel::absoluteMerge(){
    for(int i = 0; i < jigsaws.length() - 1; i++){
        if(jigsaws[i] == jigsaws[i+1]){
            jigsaws[i].picNum++;
            jigsaws.removeAt(i+1);
            i--;
        }
    }
}

QList<GuessBean> LaneModel::getJigsaws() const{
    return jigsaws;
}

void LaneModel::printJigsaws(){
    for(int i = 0; i < this->jigsaws.length(); i++){
        qDebug() << "-----------No. " << i+1 << "----------------------------------------------------";
        qDebug() << "PicNum" << this->jigsaws[i].picNum;
        qDebug() << "myCurrentLane" << this->jigsaws[i].myCurrentLane;
        qDebug() << "laneNum" << this->jigsaws[i].marks.length();
        for(int j = 0; j < this->jigsaws[i].marks.length(); j++){
            qDebug() << "Type: " << this->jigsaws[i].marks[j].type;
        }
        qDebug() << "-----------No. " << i+1 << "----------------------------------------------------";
    }
}

int LaneModel::getMaxLaneNum() const{
    int max = -1;
    for(int i = 0; i < this->jigsaws.length(); i++){
        if(max < jigsaws[i].marks.length()){
            max = jigsaws[i].marks.length();
        }
    }
    return max;
}
