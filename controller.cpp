#include "controller.h"
#include "constants.h"
#include "jigsawlane.h"
#include "lanemodel.h"
#include "laneview.h"
#include "mainwindow.h"
#include <QDir>
#include <QList>
#include <QDebug>

Controller::Controller()
{

}

int demoWorkFlow(){
    QDir dir(jsonDirPath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();

    QList<JigsawLane> jigsaws;//获取全部拼图

    //初始化所有拼图
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        qDebug() << fileInfo.fileName();
        jigsaws.append(jsonDirPath + "\\" + fileInfo.fileName());
    }

    QList<GuessBean> beans;

    //每个拼图做出猜测
    for(int i = 0; i < jigsaws.size(); ++i){
        beans.append(jigsaws[i].guess());
    }

    LaneModel * model = new LaneModel(beans);

    LaneView * laneView = new LaneView(model);
    //laneView->show();

    MainWindow * mainWindow = new MainWindow(laneView);
    mainWindow->show();
}
