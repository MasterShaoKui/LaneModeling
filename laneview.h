#ifndef LANEVIEW_H
#define LANEVIEW_H

#include <QWidget>
#include <QPen>
#include <QColor>
#include "lanemodel.h"

namespace Ui {
class LaneView;
}

class LaneView : public QWidget
{
    Q_OBJECT

private:
    Ui::LaneView * ui;
    LaneModel * model;
    bool isShowCarTrace;
    QPen whiteSolid;
    QPen whiteDotted;
    QPen yellowSolid;
    QPen yellowDotted;
    QPen border;
    QPen other;
    QPen unknown;
    QPen carTrace;
    QPen getCorrespondingPen(const QString &) const;
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent * event);

public:
    explicit LaneView(QWidget *parent = 0);
    explicit LaneView(LaneModel * model, QWidget *parent = 0);
    ~LaneView();

public slots:
    void refresh();
    void switchShowCarTrace();

};

#endif // LANEVIEW_H
