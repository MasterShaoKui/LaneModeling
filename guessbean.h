#ifndef GUESSBEAN_H
#define GUESSBEAN_H
#include <QList>
#include "mark.h"

class GuessBean{
public:
    QList<Mark> marks;
    int myCurrentLane;
    int picNum;
    bool operator == (const GuessBean& b)//重载 ==
    {
        if(this->marks.length() != b.marks.length()){//如果两个mark的长度不相同
            return false;
        }
        for(int i = 0; i < b.marks.length(); i++){
            if(this->marks[i].type != b.marks[i].type){//暂时只看类型
                return false;
            }
        }
        //如果能直行到这里，说明marks都是相同的
        bool finalResult = this->myCurrentLane == b.myCurrentLane;
        return finalResult;
    }
};

#endif // GUESSBEAN_H
