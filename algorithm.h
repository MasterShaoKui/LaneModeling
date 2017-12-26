#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QString>
#include <QJsonObject>

class Algorithm
{
public:
    Algorithm();
};

QJsonObject loadJsonFile(const QString & filePath);

#endif // ALGORITHM_H
