#ifndef MARK_H
#define MARK_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <math.h>

class Point{
public:
    double x;
    double y;
    Point():x(0),y(0){}
    Point(int x, int y):x(x),y(y){}
    double static distanceBetweenTwoPoints(Point pointA, Point pointB){
        double xdiff = pointB.x - pointA.x;// 计算两个点的横坐标之差
        double ydiff = pointB.y - pointA.y;// 计算两个点的纵坐标之差
        return sqrt(xdiff * xdiff + ydiff * ydiff);
    }
};

class Mark
{
private:
    bool isVirtual;//这个标注是不是真实存在的
public:
    QList<Point> line;
    QString type;
    double startEndDis;//这个标注前后端点的距离
    double dotProduct;//这跟标注的内积
    bool isTrustable;//这根标注是否可信
    double direction;//方向，即斜率
    Mark(QJsonObject json);
    Mark(QString type);
    Mark &operator=(const Mark &rhs){
        // 首先检测等号右边的是否就是左边的对象本，若是本对象本身,则直接返回
        if ( this == &rhs ){
            return *this;
        }
        // 复制等号右边的成员到左边的对象中
        this->line = rhs.line;
        this->type = rhs.type;
        this->startEndDis = rhs.startEndDis;
        this->dotProduct = rhs.dotProduct;
        this->isTrustable = rhs.isTrustable;
        this->direction = rhs.direction;
        this->isVirtual = rhs.isVirtual;
        return *this;
    }
    QString toString();
    bool getIsVirtual() const;
};

#endif // MARK_H
