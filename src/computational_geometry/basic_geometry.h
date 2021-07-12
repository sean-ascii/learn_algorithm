#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace computational_geometry {
namespace basic_geometry {

constexpr double kPI = 3.14159265358979323846;
constexpr double kEpsilon = 1e-10;
constexpr double kDegToRad = kPI / 180.0;
constexpr double kRadToDeg = 180.0 / kPI;
constexpr double kInf = 1e200;

struct Point {
  Point() : x(0), y(0) {}
  Point(double x_, double y_) : x(x_), y(y_) {}

  double x, y;
};

struct LineSeg {
  LineSeg() {}
  LineSeg(Point s_, Point e_) : s(s_), e(e_) {}

  Point s, e;
};

// ax + by + c = 0
struct Line {
  Line(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
  Line() : a(0), b(0), c(0) {}
  double a, b, c;
};

struct Vector2d {
  Vector2d() : x(0), y(0) {}
  Vector2d(double x_, double y_) : x(x_), y(y_) {}
  double x, y;
};

Vector2d rotate(const Vector2d& v, const double angle);

// p相对于center旋转angle rad
Point rotate(const Point& center, const Point& p, const double angle);

double distance(const Point& p1, const Point& p2);

bool equal(const Point& p1, const Point& p2);

// wraps an angle to [0, 2 * pi)
double wrap_angle(const double angle);
// normalize an angle to [-pi, pi)
double normalize_angle(const double angle);

// vector1: (p1 - p0), vector2: (p2 - p0)
// r = vector1 x vector2
// r > 0: p2 on left of vector1; r = 0: p0 p1 p2 on one line; r < 0: p2 on right of vector1
double cross_multiply(const Point& p0, const Point& p1, const Point& p2);

// r = v1 x v2
double cross_multiply(const Vector2d& v1, const Vector2d& v2);

// vector1: (p1 - p0), vector2: (p2 - p0)
// r = vector1 . vector2
// r > 0: 两向量夹角为锐角; r = 0: 两向量夹角为直角; r < 0: 两向量夹角为钝角
double dot_multiply(const Point& p0, const Point& p1, const Point& p2);

bool on_line_seg(const LineSeg& l, const Point& p);

// 返回点p以o为原点逆时针旋转alpha rad后的位置
Point rotate(const Point& o, const double alpha, const Point& p);


/* 返回顶角在o点，起始边为os，终止边为oe的夹角(单位：弧度)
  角度小于pi，返回正值
  角度大于pi，返回负值
  可以用于求线段之间的夹角
原理：
  r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e))
  r'= multiply(s,e,o)
  r >= 1	angle = 0;
  r <= -1	angle = -PI
  -1<r<1 && r'>0	angle = arccos(r)
  -1<r<1 && r'<=0	angle = -arccos(r)
*/ 
double angle(const Point& p0, const Point& p1, const Point& p2);

/* 判断点与线段的关系,用途很广泛 
本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足 
                AC dot AB 
        r =     --------- 
                 ||AB||^2 
             (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay) 
          = ------------------------------- 
                          L^2 
    r has the following meaning: 
        r=0      P = A 
        r=1      P = B 
        r<0		 P is on the backward extension of AB 
		r>1      P is on the forward extension of AB 
        0<r<1	 P is interior to AB 
*/
double relation(const Point& p, const LineSeg& l);

// 求点C到线段AB所在直线的垂足 P
Point perpendicular(const Point& p, const LineSeg& l);

/* 求点p到线段l的最短距离,并返回线段上距该点最近的点np 
注意：np是线段l上到点p最近的点，不一定是垂足 */
double distance_to_seg(const Point& p, const LineSeg& l, Point *np);

// 求点p到线段l所在直线的距离,请注意本函数与上个函数的区别
double distance_to_line(const Point& p, const LineSeg& l);

// 计算点到折线的最近距离，并返回最近点
double distance_to_polyline(const Point& p, const std::vector<Point>& polyline, Point *np);

// 判断点是否在多边形内，假设多边形点集首尾不重合
// https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
// 该算法不要求多边形的时针序
bool point_in_polygon(const Point& p, const std::vector<Point>& polygon);

/********************************************************************************************
射线法判断点q与多边形polygon的位置关系，要求polygon为简单多边形，顶点逆时针排列
   如果点在多边形内：   返回0
   如果点在多边形边上： 返回1
   如果点在多边形外：	返回2
*********************************************************************************************/
int point_in_polygon_raytrace(const Point& p, const std::vector<Point>& polygon);

bool point_in_convex_polygon(const Point&p, const std::vector<Point>& polygon);

bool circle_in_polygon(const Point& center, const double radius, const std::vector<Point>& polygon);

double segs_angle(const LineSeg& l1, const LineSeg& l2);

// 判断线段l1和l2是否相交（包括端点相交）
bool intersect(const LineSeg& l1, const LineSeg& l2);

// 判断线段l1和l2是否相交（交点不是端点）
bool cross_intersect(const LineSeg& l1, const LineSeg& l2);

// 判断线段l1所在的直线与线段l2相交
bool intersect_line(const LineSeg& l1, const LineSeg& l2);

// 求过两点的直线: ax + by + c = 0 (a >= 0)
Line make_line(const Point& p1, const Point& p2);

// 根据直线的解析方程返回直线的斜率k
double slope(const Line& l);

// 计算直线的倾角[0, pi)
double alpha(const Line& l);

// 判断两条直线是否相交，并且返回交点
bool line_intersect(const Line& l1, const Line& l2, Point* p);

// 判断两个线段是否相交，并返回交点
bool intersect(const LineSeg& l1, const LineSeg& l2, Point* p);

// graham算法，计算凸包，输出为凸包点的合集，按逆时针排列
std::vector<Point> graham_scan(const std::vector<Point>& points);


/******************************\
*               *
* 多边形常用算法模块		  *
*               *
\******************************/

// 如果无特别说明，输入多边形顶点要求按逆时针排列


/*
返回值：输入的多边形是简单多边形，返回true
要 求：输入顶点序列按逆时针排序
说 明：简单多边形定义:
1：循环排序中相邻线段对的交是他们之间共有的单个点
2：不相邻的线段不相交
本程序默认第一个条件已经满足
*/
// 假设多边形点集首尾不重合
bool is_simple(const std::vector<Point>& polygon);

// 按多边形顶点顺序返回对应顶点的凸凹性判断
void check_convex(const std::vector<Point>& polygon, std::vector<bool>* convex_flags);

// 判断多边形的凸凹性
bool is_convex(const std::vector<Point>& polygon);

// 计算多边形面积，逆时针面积为正
double area(const std::vector<Point>& polygon);

// 判断多边形是否为逆时针
bool is_counterclock(const std::vector<Point>& polygon);

/*********************************************************************************************
  判断线段是否在简单多边形内(注意：如果多边形是凸多边形，下面的算法可以化简)
    必要条件一：线段的两个端点都在多边形内;
    必要条件二：线段和多边形的所有边都不内交; 
	用途:
    1. 判断折线是否在简单多边形内
    2. 判断简单多边形是否在另一个简单多边形内
**********************************************************************************************/
bool line_seg_in_polygon(const LineSeg& l, const std::vector<Point>& polygon);

/************************************************
给定一简单多边形，找出一个肯定在该多边形内的点 
定理1	：每个多边形至少有一个凸顶点 
定理2	：顶点数>=4的简单多边形至少有一条对角线 
结论	： x坐标最大，最小的点肯定是凸顶点 
	y坐标最大，最小的点肯定是凸顶点            
************************************************/
Point find_point_in_polygon(const std::vector<Point>& polygon);



/*************************\
*						 *
* 圆的基本运算           *
*					     *
\*************************/
/******************************************************************************
返回值	： 点p在圆内(包括边界)时，返回true
用途	： 因为圆为凸集，所以判断点集，折线，多边形是否在圆内时
	只需要逐一判断点是否在圆内即可。
*******************************************************************************/
bool point_in_circle(const Point& center, const double r, const Point& p);


/******************************************************************************
用 途	：求不共线的三点确定一个圆 
输 入	：三个点p1,p2,p3 
返回值	：如果三点共线，返回false；反之，返回true。圆心由q返回，半径由r返回 
*******************************************************************************/
// https://blog.csdn.net/liyuanbhu/article/details/52891868
bool cocircle(const Point& p1, const Point& p2, const Point& p3, Point* center, double* r);

//两圆关系：
/* 两圆：
相离： return 1；
外切： return 2；
相交： return 3；
内切： return 4；
内含： return 5；
*/
int circle_relation(const Point& center1, const double r1, const Point& center2, const double r2);

} // basic_geometry
} // computational_geometry
} // sakabatou_algorithm
