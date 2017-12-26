#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QPen>
#include <QColor>

const static QString jsonDirPath = "C:\\Users\\ezios\\Desktop\\gps\\MarksOf173_v2";

/**
 * 积分精度，即要把函数图像分成多少份。
 * @type {number}
 */
const static int calculusAccuracy = 10000;

/**
 * 判断失真的分水岭，如果像素个数少于该值，则视为可以忽略。
 * @type {number}
 */
const static int distortionShed = 30;

/**
 * 判断端点偏移的分水岭，即起点最多可以偏离多少。
 * @type {number}
 */
const static int maxForgive = 5;

/**
 * 单位面积补偿，用于防止计算后的单位面积过小，使其相对变的可读。
 * @type {number}
 */
const static int unitAreaCountervail = 10000 * 10000;

/**
 * 单位长度补偿，用于防止计算后的单位长度过小，使其相对变的可读。
 * @type {number}
 */
const static int unitDisCountervail = 1000 * 1000;

/**
 * 内积补偿
 * @type {number}
 */
const static int dotProductCountervail = 100 * 10;

const static double resolution = 1920 * 1088;
const static double horizontal = 1920;
const static double vertical = 1088;

/**
 * 起点和终点的单位偏差
 * @type {number}
 */
const static int maxNormDistanceDIff = 64;

/**
 * 最大可以忽略的标注线内积大小
 * @type {number}
 */
const static int maxOmitableLineDotProduct = 50;

/**
 * 处于多少像素以内，算作边缘
 * @brief marginShed
 */
const static int marginShed = 20;

const static QString white_solid = "白实线";
const static QString white_dotted = "白虚线";
const static QString yellow_solid = "黄实线";
const static QString yellow_dotted = "黄虚线";
const static QString lane_border = "道路边界";
const static QString theOther = "其他";

const static int penLineWidth = 12;


#endif // CONSTANTS_H
