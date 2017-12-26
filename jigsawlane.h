#ifndef JIGSAWLANE_H
#define JIGSAWLANE_H
#include <QString>
#include <QList>
#include "mark.h"
#include "guessbean.h"

class JigsawLane
{
private:
    const QString filePath;
    QString _id;
    QList<Mark> marks;

    int myCurrentLane;//我当前所在的车道
    QList<Mark> guessedMark;//我认为当前车道，从左到右，有这些标注线
    bool isConfident;//我有没有自信做出这个假设
    void cutBorder(QList<double> & sortedMarks);
    void offsetBorder(QList<double> & sortedMarks);
    void printLines(QList<double> & sortedMarks);
    void removeParticularKind(QString kind, QList<double> & sortedMarks);//将某中特定类别的道路线移除
    void changeParticualrKind(QString from, QString to, QList<double> & sortedMarks);

public:
    JigsawLane(const QString &filePath);
    JigsawLane &operator =(const JigsawLane & rhs){
        // 首先检测等号右边的是否就是左边的对象本，若是本对象本身,则直接返回
        if ( this == &rhs )
        {
            return *this;
        }

        // 复制等号右边的成员到左边的对象中
        this->_id = rhs._id;
        this->marks = rhs.marks;
        this->myCurrentLane = rhs.myCurrentLane;
        return *this;
    }
    GuessBean guess();
};

#endif // JIGSAWLANE_H
