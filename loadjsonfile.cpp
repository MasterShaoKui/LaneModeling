#include "algorithm.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

QJsonObject loadJsonFile(const QString & filePath){
    QString val;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    return d.object();
}
