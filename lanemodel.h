#ifndef LANEMODEL_H
#define LANEMODEL_H

#include <QList>
#include <jigsawlane.h>

class LaneModel
{
private:
    QList<GuessBean> jigsaws;
    const int originTotalPicNum;
    void mergeGuesses();

public:
    LaneModel(QList<GuessBean> jigsaws);
    QList<GuessBean> getJigsaws() const;
    void printJigsaws();
    int getTotalPicNum() const;
    int getMaxLaneNum() const;//获得道路线最多的一条道路的道路线数。
    void absoluteMerge();
    int getOriginTotalPicNum() const;
};

#endif // LANEMODEL_H
