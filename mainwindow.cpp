#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QGridLayout>

MainWindow::MainWindow(LaneView *laneView, QWidget *parent) :
    QWidget(parent), laneView(laneView), btnPanel(new QWidget()),
    mainLayout(new QGridLayout()), btnPanelLayout(new QGridLayout),
    switchShowCarTraceButton(new QToolButton()),
    refreshButton(new QToolButton),
    ui(new Ui::MainWindow)
{
    this->setLayout(mainLayout);
    btnPanel->setLayout(btnPanelLayout);

    mainLayout->addWidget(btnPanel, 0, 0, 1, 1);
    mainLayout->addWidget(laneView, 0, 1, 1, 5);

    //初始化全部按钮
    setUpButtons();

    this->setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpButtons(){
    //设置 显示/不显示行车轨迹 按钮
    btnPanelLayout->addWidget(switchShowCarTraceButton);
    switchShowCarTraceButton->setText("显示/不显示 行车轨迹");
    switchShowCarTraceButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(switchShowCarTraceButton, SIGNAL(clicked()),laneView, SLOT(switchShowCarTrace()));
    //设置 刷新 按钮
    btnPanelLayout->addWidget(refreshButton);
    refreshButton->setText("刷新");
    refreshButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(refreshButton, SIGNAL(clicked()), laneView, SLOT(refresh()));
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        this->close();
        break;
    default:
        break;
    }
}
