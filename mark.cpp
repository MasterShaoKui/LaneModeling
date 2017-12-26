#include "mark.h"
#include <QJsonArray>
#include <QDebug>
#include "constants.h"

Mark::Mark(QJsonObject mark):type(mark.value("type").toString()), isTrustable(false), isVirtual(false)
{
    QJsonArray lines = mark.value("lines").toArray();
    for(int j = 0; j < lines.size(); j++){
        QJsonArray line = lines.at(j).toArray();
        for(int k = 0; k < line.size(); k++){
            QJsonObject point = line.at(k).toObject();
            double x = point.value("x").toDouble();
            double y = point.value("y").toDouble();
            this->line.append(Point(x, y));
        }
    }
    if(line.isEmpty()){
        qDebug() << "发生错误！！！没有获取到各个点的数据！";
    }
    startEndDis = Point::distanceBetweenTwoPoints(line[0], line.last());
    dotProduct = (dotProductCountervail * startEndDis * startEndDis / resolution);
    //qDebug() << "startEndDis: " + QString::number(startEndDis);
    //qDebug() << "成功构造Mark";
    direction = (line.last().y - line[0].y) / (line.last().x - line[0].x);
}

Mark::Mark(QString type):type(type), isVirtual(true),
    startEndDis(0), dotProduct(0), isTrustable(false), direction(0){
    this->line.append(Point());
    this->line.append(Point());
}

QString Mark::toString(){
    qDebug() << "开始转换成字符串！";
    QString result("");
    result += type + "\r\n";
    for(int i = 0; i < line.size(); i++){
        result += "(" + QString::number(line[i].x) + ", " + QString::number(line[i].y) + ")";
        result += ";\n";
    }
    return result;
}

bool Mark::getIsVirtual() const
{
    return isVirtual;
}
