#include "widget.h"
#include <QApplication>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "algorithm.h"
#include "mark.h"
#include <QDebug>
#include <scriptcaller.h>
#include "jigsawlane.h"
#include <QDir>
#include <controller.h>
#include <laneview.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    demoWorkFlow();
    return a.exec();
}

