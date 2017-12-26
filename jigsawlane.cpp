#include "jigsawlane.h"
#include "algorithm.h"
#include "constants.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

JigsawLane::JigsawLane(const QString & filePath) :
    filePath(filePath), isConfident(false), myCurrentLane(-1){
    QJsonObject json = loadJsonFile(filePath);
    _id = json.value("_id").toString();
    QJsonArray marks = json.value("marks").toArray();
    for(int i = 0; i < marks.size(); i++){
        this->marks.append(marks[i].toObject());
    }
    for(int i = 0; i < this->marks.size(); i++){
        //qDebug() << this->marks[i].toString();
    }
}

GuessBean JigsawLane::guess(){
    qDebug() << filePath << "开始进行猜测！";

    //先计算哪些标注线是不必要的
    for(int i = 0; i < marks.length(); i++){
        if(marks[i].dotProduct < maxOmitableLineDotProduct){
            //qDebug() << "因过短，剔除了标注线：" <<"startEndDis: " << marks[i].startEndDis <<"dotProduct: " << marks[i].dotProduct;
            marks[i].isTrustable = false;
        }else{
            marks[i].isTrustable = true;
        }
    }

    QList<double> sortedMarks;

    //对标注线排序
    for (int i = 0; i < marks.length(); i++){
        double currentSmallestX = INFINITY;
        int index = -1;
        for (int j = 0; j < marks.length(); j++){
            if (currentSmallestX > marks[j].line[0].x && sortedMarks.indexOf(j) == -1){
                currentSmallestX = marks[j].line[0].x;
                index = j;
            }
        }
        sortedMarks.append(index);
    }

    //找出X同为图像左边缘，难以区分的结果。
    for(int i = 0; i < sortedMarks.length(); i++){
        if(marks[sortedMarks[i]].line[0].x > (0 + marginShed)){
            if(sortedMarks[i] == 0){//如果第一个标注线就已经不在边缘了
                break;
            }
            for(int k = i-1; k >= 1; k--){
                for(int j = i-1; j >= 1; j--){
                    if((marks[sortedMarks[j-1]].line[0].y - marks[sortedMarks[j]].line[0].y) > marginShed){
                        int temp = sortedMarks[j];
                        sortedMarks[j] = sortedMarks[j-1];
                        sortedMarks[j-1] = temp;
                        qDebug() << "左侧纵轴交换";
                    }
                }
            }
            break;
        }
    }

    //找出X同为图像右边缘，难以区分的结果。
    for(int i = 0; i < sortedMarks.length(); i++){
        if(marks[sortedMarks[i]].line[0].x > (horizontal - marginShed)){//如果已经进入了边缘
            for(int k = i; k < sortedMarks.length(); k++){
                for(int j = i+1; j < sortedMarks.length(); j++){
                    if((marks[sortedMarks[j]].line[0].y - marks[sortedMarks[j-1]].line[0].y) > marginShed){
                        int temp = sortedMarks[j];
                        sortedMarks[j] = sortedMarks[j-1];
                        sortedMarks[j-1] = temp;
                        qDebug() << "右侧纵轴交换";
                    }
                }
            }
            break;
        }
    }

    //如果道路边界右边紧挨着一个实线，那么可以剔除这条实线。
    //这段代码需要改动！！！！！！！！！！！！！！！！
    //!!!!!!!!!!!!!!!!!!!!
    //! 需要加入面积功能后再修改
    for(int i = 0; i < sortedMarks.length()-1; i++){
        if(marks[sortedMarks[i]].type == "道路边界"){
            if(marks[sortedMarks[i+1]].type == "白实线" || marks[sortedMarks[i+1]].type == "黄实线"){
                sortedMarks.removeAt(i+1);
                qDebug() << "移除了一个多余的实线。";
                break;
            }
        }
    }

    //如果道路边界左边紧挨着一个实线，那么可以剔除这条实线。
    //这段代码需要改动！！！！！！！！！！！！！！！！
    //!!!!!!!!!!!!!!!!!!!!
    //! 需要加入面积功能后再修改
    for(int i = sortedMarks.length()-1; i > 0; i--){
        if(marks[sortedMarks[i]].type == "道路边界"){
            if(marks[sortedMarks[i-1]].type == "白实线" || marks[sortedMarks[i-1]].type == "黄实线"){
                sortedMarks.removeAt(i-1);
                qDebug() << "移除了一个多余的实线。";
                break;
            }
        }
    }

    //删去过短的、还不是虚线的点
    for(int i = 0; i < sortedMarks.length()-1; i++){
        if(marks[sortedMarks[i]].type == "白虚线" || marks[sortedMarks[i]].type == "黄虚线"){
            //不考虑虚线的情况
            continue;
        }
        if(marks[sortedMarks[i]].dotProduct < maxOmitableLineDotProduct){
            qDebug() << "移除了一个内积过小的点 dotProduct: " << marks[sortedMarks[i]].dotProduct
                     << "Type" << marks[sortedMarks[i]].type;
            sortedMarks.removeAt(i);
            i--;
        }
    }

    //移除其他类别的标注线
    removeParticularKind("其他", sortedMarks);

    //寻找两个道路边界之间，标注线数量最多的一段作为最后的猜测值。
    cutBorder(sortedMarks);

    //弥补被剪切掉的标注线
    offsetBorder(sortedMarks);

    //打印数据，用于Debug.
    //printLines(sortedMarks);

    //找出我当前所在的是哪条车道
    for(int i = 0; i < sortedMarks.size()-1; i++){
        //如果两条标注线的斜率不相同，则说明从左边->右边，根据仿射变换的原理。
        if(marks[sortedMarks[i]].direction * marks[sortedMarks[i+1]].direction < 0){
            myCurrentLane = i;
            qDebug() << "我所在的车道：" << myCurrentLane;
            break;
        }
    }

    GuessBean bean;
    bean.myCurrentLane = myCurrentLane;
    for(int i = 0; i < sortedMarks.length(); i++){
        bean.marks.append(marks[sortedMarks[i]]);
    }
    bean.picNum = 1;

    return bean;
}

void JigsawLane::cutBorder(QList<double> &sortedMarks){
    //看看有多少个道路边界
    int roadBoarderCount = 0;
    for(int i = 0; i < sortedMarks.length(); i++){
        if(marks[sortedMarks[i]].type == "道路边界"){
            roadBoarderCount++;
        }
    }
    qDebug() << "道路边界数：" << roadBoarderCount;
    if(roadBoarderCount == 0){
        return;
    }
    //获得初期道路边界的分割值
    int counter = -1;
    int startIndex = -1;
    int endIndex = -1;
    int nextStartIndex = -1;
    for(int i = 0; i < sortedMarks.length(); i++){
        if(marks[sortedMarks[i]].type == "道路边界"){
            counter = i;
            startIndex = -1;
            endIndex = i;
            nextStartIndex = i + 1;
            break;
        }
    }
    //有几个道路边界就要遍历几次
    for(int k = 0; k < roadBoarderCount; k++){
        int tempCounter = -1;
        for(int i = nextStartIndex; i < sortedMarks.length(); i++){
            if(marks[sortedMarks[i]].type == "道路边界"){
                tempCounter = (i - nextStartIndex) - 1;
                if(tempCounter >= counter){
                    startIndex = nextStartIndex - 1;
                    endIndex = i;
                }
                nextStartIndex = i + 1;
                break;
            }
            //如果发现已经是最后一部分了
            if(i == (sortedMarks.length()-1)){
                tempCounter = (i - nextStartIndex) - 1;
                if(tempCounter >= counter){
                    startIndex = nextStartIndex - 1;
                    endIndex = i;
                }
                nextStartIndex = i + 1;
            }
        }
    }
    if(startIndex == -1){
        startIndex = 0;
    }
    if(endIndex == -1){
        endIndex = sortedMarks.length() - 1;
    }
    sortedMarks = sortedMarks.mid(startIndex, endIndex - startIndex + 1);
}

void JigsawLane::offsetBorder(QList<double> &sortedMarks){
    if(marks[sortedMarks[0]].type == white_dotted || marks[sortedMarks[0]].type == yellow_dotted){
        marks.append(Mark(lane_border));
        sortedMarks.prepend(marks.length() - 1);
    }
    if(marks[sortedMarks.last()].type == white_dotted || marks[sortedMarks.last()].type == yellow_dotted){
        marks.append(Mark(lane_border));
        sortedMarks.append(marks.length() - 1);
    }
}

void JigsawLane::printLines(QList<double> &sortedMarks){
    //输出所有Lines，用于debug
    qDebug() << "排序结果为：\n";
    for(int i = 0; i < sortedMarks.length(); i++){
        qDebug() << "标注线 " << sortedMarks[i] << "---" <<
                    "x: " << marks[sortedMarks[i]].line[0].x <<
                    "y: " << marks[sortedMarks[i]].line[0].y <<
                    "Type: " << marks[sortedMarks[i]].type;
    }
}

void JigsawLane::removeParticularKind(QString kind, QList<double> &sortedMarks){
    for(int i = 0; i < sortedMarks.size(); i++){
        if(marks[sortedMarks[i]].type == kind){
            sortedMarks.removeAt(i);
            i--;
        }
    }
}

void JigsawLane::changeParticualrKind(QString from, QString to, QList<double> &sortedMarks){
    for(int i = 0; i < sortedMarks.size(); i++){
        if(marks[sortedMarks[i]].type == from){
            marks[sortedMarks[i]].type = to;
        }
    }
}


