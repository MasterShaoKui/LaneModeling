#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "laneview.h"
#include <QWidget>
#include <QGridLayout>
#include <QToolButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(LaneView * laneView, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LaneView * laneView;
    QWidget * btnPanel;
    QGridLayout * mainLayout;
    QGridLayout * btnPanelLayout;
    QToolButton * switchShowCarTraceButton;
    QToolButton * refreshButton;
    void setUpButtons();
    void keyPressEvent(QKeyEvent * event);

};

#endif // MAINWINDOW_H
