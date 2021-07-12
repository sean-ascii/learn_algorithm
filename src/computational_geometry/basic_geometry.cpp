#include "computational_geometry/basic_geometry.h"

#include <cmath>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <utility>

namespace sakabatou_algorithm {
namespace computational_geometry {
namespace basic_geometry {

Vector2d rotate(const Vector2d& v, const double angle) {
  return Vector2d{v.x * std::cos(angle) - v.y * std::sin(angle),
                  v.x * std::sin(angle) + v.y * std::cos(angle)};
}

Point rotate(const Point& center, const Point& p, const double angle) {
  Vector2d tmp_v = rotate(Vector2d{p.x - center.x, p.y - center.y}, angle);
  return Point{center.x + tmp_v.x, center.y + tmp_v.y};
}

double distance(const Point& p1, const Point& p2) {
  return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

bool equal(const Point& p1, const Point& p2) {
  return std::abs(p1.x - p2.x) < kEpsilon &&
         std::abs(p1.y - p2.y) < kEpsilon;
}

double wrap_angle(const double angle) {
  double r = std::fmod(angle, 2.0 * kPI);
  return r < 0.0 ? (r + 2.0 * kPI) : r;
}

double normalize_angle(const double angle) {
  double r = std::fmod(angle + kPI, 2.0 * kPI);
  return r < 0.0 ? (r + kPI) : (r - kPI);
}

double cross_multiply(const Point& p0, const Point& p1, const Point& p2) {
  Vector2d v1{p1.x - p0.x, p1.y - p0.y};
  Vector2d v2{p2.x - p0.x, p2.y - p0.y};
  return cross_multiply(v1, v2);
}

double cross_multiply(const Vector2d& v1, const Vector2d& v2) {
  return (v1.x * v2.y - v1.y * v2.x);
}

double dot_multiply(const Point& p0, const Point& p1, const Point& p2) {
  Vector2d v1(p1.x - p0.x, p1.y - p0.y);
  Vector2d v2(p2.x - p0.x, p2.y - p0.y);
  return (v1.x * v2.x + v1.y * v2.y);
}

bool on_line_seg(const LineSeg& l, const Point& p) {
  return cross_multiply(l.s, l.e, p) == 0 && // 共线
         (p.x - l.s.x) * (p.x - l.e.x) <= 0 && // 点p在以线段l为对角线的矩形内
         (p.y - l.s.y) * (p.y - l.e.y) <= 0;
}

Point rotate(const Point& o, const double alpha, const Point& p) {
  Vector2d v(p.x - o.x, p.y - o.y);
  Vector2d new_v;
  new_v.x = v.x * std::cos(alpha) - v.y * std::sin(alpha);
  new_v.y = v.x * std::sin(alpha) + v.y * std::cos(alpha);
  return Point(o.x + new_v.x, o.y + new_v.y);
}

double angle(const Point& p0, const Point& p1, const Point& p2){
  Vector2d v1(p1.x - p0.x, p1.y - p0.y);
  Vector2d v2(p2.x - p0.x, p2.y - p0.y);
  double cos_theta = dot_multiply(p0, p1, p2) / (distance(p0, p1) * distance(p0, p2));
  if (cos_theta >= 1.0) return 0;
  if (cos_theta <= -1.0) return -kPI;
  if (cross_multiply(p0, p1, p2) > 0.0)
    return std::acos(cos_theta);
  else
    return -std::cos(cos_theta);
}

double relation(const Point& p, const LineSeg& l) {
  return dot_multiply(l.s, l.e, p) / (distance(l.s, l.e) * distance(l.s, l.e));
}

Point perpendicular(const Point& p, const LineSeg& l) {
  double r = relation(p, l);
  Point result;
  result.x = l.s.x + r * (l.e.x - l.s.x);
  result.y = l.s.y + r * (l.e.y - l.s.y);
  return result;
}

double distance_to_seg(const Point& p, const LineSeg& l, Point *np) {
  double r = relation(p, l);
  if (r < 0) {
    *np = l.s;
    return distance(p, l.s);
  } else if (r > 1) {
    *np = l.e;
    return distance(p, l.e);
  } else {
    *np = perpendicular(p, l);
    return distance(p, *np);
  }
}

double distance_to_line(const Point& p, const LineSeg& l) {
  return std::abs(cross_multiply(l.s, l.e, p) / distance(l.s, l.e));
}

double distance_to_polyline(const Point& p, const std::vector<Point>& polyline, Point *np) {
  double min_d = std::numeric_limits<double>::max();
  for (int i = 0; i < polyline.size() - 1; i++) {
    LineSeg seg(polyline[i], polyline[i + 1]);
    Point tmp_np;
    double distance = distance_to_seg(p, seg, &tmp_np);
    if (distance < min_d) {
      *np = tmp_np;
      min_d  = distance;
    }
  }
  return min_d;
}

bool point_in_polygon(const Point& p, const std::vector<Point>& polygon) {
  bool in = false;
  std::int32_t i, j, size = polygon.size();
  for (i = 0, j = size - 1; i < size; j = i++) {
    if ((polygon.at(i).y > p.y) != (polygon.at(j).y > p.y)
        && p.x < (polygon.at(j).x - polygon.at(i).x) * (p.y - polygon.at(i).y) /
                 (polygon.at(j).y - polygon.at(i).y) + polygon.at(i).x) {
      in = !in;
    }
  }
  return in;
}

int point_in_polygon_raytrace(const Point& p, const std::vector<Point>& polygon) {
  LineSeg raytrace(p, p);
  raytrace.e.x = -kInf;
  int n = polygon.size();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    LineSeg seg(polygon[i], polygon[(i + 1) % n]);
    if (on_line_seg(seg, p))
      return 1;
    if (std::abs(seg.s.y - seg.e.y) < kEpsilon) { // 忽略水平边
      continue;
    }
    if (on_line_seg(raytrace, seg.s) && seg.s.y > seg.e.y) {
      cnt++;
    } else if (on_line_seg(raytrace, seg.e) && seg.e.y > seg.s.y) {
      cnt++;
    } else if (intersect(raytrace, seg)) {
      cnt++;
    }
  }
  if (cnt % 2 == 1) {
    return 0;
  } else {
    return 2;
  }
}

bool point_in_convex_polygon(const Point&p, const std::vector<Point>& polygon) {
  // 先找到一个肯定在多边形内的点，如几何中心
  Point center;
  int n = polygon.size();
  for (const auto& p : polygon) {
    center.x += p.x;
    center.y += p.y;
  }
  center.x /= n;
  center.y /= n;

  // 判断center和p是否可能在某个线段两边
  for (int i = 0; i < n; i++) {
    if (cross_multiply(polygon[i], polygon[(i + 1) % n], p) *
        cross_multiply(polygon[i], polygon[(i + 1) % n], center) < 0) {
      return false;
    }
  }
  return true;
}

bool circle_in_polygon(
    const Point& center, const double radius, const std::vector<Point>& polygon) {
  bool center_in_polygon = point_in_polygon(center, polygon);
  if (!center_in_polygon) return false;

  Point dummy_p;
  double distance = distance_to_polyline(center, polygon, &dummy_p);
  return distance < radius;
}

double segs_angle(const LineSeg& l1, const LineSeg& l2) {
  Point p0, p1, p2;
  p0.x = p0.y = 0;
  p1.x = l1.e.x - l1.s.x;
  p1.y = l1.e.y - l1.s.y;
  p2.x = l2.e.x - l2.s.x;
  p2.y = l2.e.y - l2.s.y;
  return angle(p0, p1, p2);
}

bool intersect(const LineSeg& l1, const LineSeg& l2) {
  return std::max(l1.s.x, l1.e.x) >= std::min(l2.s.x, l2.e.x) &&  // 排斥实验
         std::max(l2.s.x, l2.e.x) >= std::min(l1.s.x, l1.e.x) &&
         std::max(l1.s.y, l1.e.y) >= std::min(l2.s.y, l2.e.y) &&
         std::max(l2.s.y, l2.e.y) >= std::min(l1.s.y, l1.e.y) &&
         cross_multiply(l2.s, l2.e, l1.s) * cross_multiply(l2.s, l2.e, l1.e) <= 0 && // 跨立实验
         cross_multiply(l1.s, l1.e, l2.s) * cross_multiply(l1.s, l1.e, l2.e) <= 0;
}

bool cross_intersect(const LineSeg& l1, const LineSeg& l2) {
  return intersect(l1, l2) &&
         !on_line_seg(l1, l2.s) &&
         !on_line_seg(l1, l2.e) &&
         !on_line_seg(l2, l1.s) &&
         !on_line_seg(l2, l1.e);
}

bool intersect_line(const LineSeg& l1, const LineSeg& l2) {
  return cross_multiply(l1.s, l1.e, l2.s) * cross_multiply(l1.s, l1.e, l2.e) <= 0;
}

Line make_line(const Point& p1, const Point& p2) {
  Line l;
  int sign = 1;
  l.a = p2.y - p1.y;
  if (l.a < 0) {
    sign = -1;
    l.a *= sign;
  }
  l.b = sign * (p1.x - p2.x);
  l.c = sign * (p1.y * p2.x - p2.y * p1.x);
  return l;
}

double slope(const Line& l) {
  if (std::abs(l.a) < 1e-20)
    return 0.0;
  else if (std::abs(l.b) < 1e-20)
    return kInf;
  else
    return -l.a / l.b;
}

double alpha(const Line& l) {
  if (std::abs(l.a) < kEpsilon) {
    return 0.0;
  }
  if (std::abs(l.b) < kEpsilon) {
    return kPI / 2.0;
  }
  double k = slope(l);
  if (k > 0) {
    return std::atan(k);
  } else {
    return std::atan(k) + kPI;
  }
}

bool line_intersect(const Line& l1, const Line& l2, Point* p) {
  double d = l1.a * l2.b - l2.a * l1.b;
  if (std::abs(d) < kEpsilon)
    return false;
  p->x = (l2.c * l1.b - l1.c * l2.b) / d;
  p->y = (l2.a * l1.c - l1.a * l2.c) / d;
  return true;
}

bool intersect(const LineSeg& l1, const LineSeg& l2, Point* p) {
  if (!intersect(l1, l2)) return false;

  Line line1 = make_line(l1.s, l1.e);
  Line line2 = make_line(l2.s, l2.e);
  if (line_intersect(line1, line2, p)) {
    return true;
  } else {
    return false;
  }
}

bool is_simple(const std::vector<Point>& polygon) {
  int size = polygon.size();
  for (int i = 0; i < size; i++) {
    LineSeg l1, l2;
    l1.s = polygon[i];
    l1.e = polygon[(i + 1) % size];
    int cnt = size - 3;
    while (cnt) {
      l2.s = polygon[(i + 2) % size];
      l2.e = polygon[(i + 3) % size];
      if (intersect(l1, l2)) {
        break;
      }
      cnt--;
    }
    if (cnt)
      return false;
  }
  return true;
}

void check_convex(const std::vector<Point>& polygon, std::vector<bool>* convex_flags) {
  int n = polygon.size();
  convex_flags->resize(n, true);
  for (int i = 0; i < n; i++) {
    if (cross_multiply(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]) > 0) {
      convex_flags->at((i + 1) % n) = true;
    } else {
      convex_flags->at((i + 1) % n) = false;
    }
  }
}

bool is_convex(const std::vector<Point>& polygon) {
  std::vector<bool> flags(polygon.size());
  check_convex(polygon, &flags);
  for (const auto f : flags) {
    if (!f) return false;
  }
  return true;
}

double area(const std::vector<Point>& polygon) {
  if (polygon.size() < 3) return 0;
  int n = polygon.size();
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += cross_multiply(Vector2d{polygon[i].x, polygon[i].y},
                          Vector2d{polygon[(i + 1) % n].x, polygon[(i + 1) % n].y});
  }
  return sum / 2.0;
}

bool is_counterclock(const std::vector<Point>& polygon) {
  return area(polygon) > 0;
}

bool line_seg_in_polygon(const LineSeg& l, const std::vector<Point>& polygon) {
  // TODO: 允许线段顶点在多边形上，下面point_in_polgon需要替换
  if (!point_in_polygon(l.s, polygon) || !point_in_polygon(l.e, polygon)) {
    return false;
  }

  std::vector<Point> on_seg_points;
  int n = polygon.size();
  for (int i = 0; i < n; i++) {
    LineSeg seg;
    seg.s = polygon[i];
    seg.e = polygon[(i + 1) % n];
    if (on_line_seg(seg, l.s)) {
      on_seg_points.push_back(l.s);
    } else if (on_line_seg(seg, l.e)) {
      on_seg_points.push_back(l.e);
    } else {
      if (on_line_seg(l, seg.s)) {
        on_seg_points.push_back(seg.s);
      } else if (on_line_seg(l, seg.e)) {
        on_seg_points.push_back(seg.e);
      } else {
        if (intersect(l, seg)) { //此时只可能是内交
          return false;
        }
      }
    }
  }

  std::sort(on_seg_points.begin(), on_seg_points.end(), [](const auto& p1, const auto& p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
  });
  for (int i = 0; i < on_seg_points.size() - 1; i++) {
    Point center((on_seg_points[i].x + on_seg_points[i + 1].x) / 2.0,
                 (on_seg_points[i].y + on_seg_points[i + 1].y) / 2.0);
    if (!point_in_polygon(center, polygon)) {
      return false;
    }
  }
  return true;
}

Point find_point_in_polygon(const std::vector<Point>& polygon) {
  // 寻找一个凸顶点v
  int n = polygon.size();
  int lowest_index = 0;
  double lowest_y = polygon.front().x;
  for (int i = 1; i < n; i++) {
    if (polygon[i].y < lowest_y) {
      lowest_index = i;
      lowest_y = polygon[i].y;
    }
  }
  // 以该凸顶点为中间点构造三角形
  std::vector<Point> triangle;
  triangle.push_back(polygon[(lowest_index - 1 + n) % n]);
  triangle.push_back(polygon[lowest_index]);
  triangle.push_back(polygon[(lowest_index + 1) % n]);
  // 寻找在三角形内且离顶点v最近的顶点q
  double nearest_d = std::numeric_limits<double>::max();
  int nearest_index = -1;
  for (int i = 0; i < n; i++) {
    if (i == lowest_index ||
        i == (lowest_index - 1 + n) % n ||
        i == (lowest_index + 1) % n) {
      continue;
    }
    if (!point_in_convex_polygon(polygon[i], triangle)) {
      continue;
    }
    double d = distance(polygon[lowest_index], polygon[i]);
    if (d < nearest_d) {
      nearest_d = d;
      nearest_index = i;
    }
  }
  Point r;
  if (nearest_index == -1) { // 没有找到三角形内部的点，返回v对边中点
    r.x = (triangle.front().x + triangle.back().x) / 2.0;
    r.y = (triangle.front().y + triangle.back().y) / 2.0;
  } else {
    r.x = (polygon[lowest_index].x + polygon[nearest_index].x) / 2.0;
    r.y = (polygon[lowest_index].y + polygon[nearest_index].y) / 2.0;
  }
  return r;
}

bool point_in_circle(const Point& center, const double r, const Point& p) {
  return distance(center, p) < r;
}

bool cocircle(const Point& p1, const Point& p2, const Point& p3, Point* center, double* r) {
  double x1 = p1.x, x2 = p2.x, x3 = p3.x;
  double y1 = p1.y, y2 = p2.y, y3 = p3.y;
  double a = x1 - x2;
  double b = y1 - y2;
  double c = x1 - x3;
  double d = y1 - y3;
  double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
  double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
  double det = b * c - a * d;
  if (std::abs(det) < kEpsilon) {
    return false;
  }

  center->x = -(d * e - b * f) / det;
  center->y = -(a * f - c * e) / det;
  *r = distance(*center, p1);
  return true;
}

int circle_relation(const Point& center1, const double r1, const Point& center2, const double r2) {
  double d = std::hypot(center1.x - center2.x, center1.y - center2.y);

  if (std::abs(d - r1 - r2) < kEpsilon) {
    return 2;
  }
  if (std::abs(d - std::abs(r1 - r2)) < kEpsilon) {
    return 4;
  }
  if (d < std::abs(r1 - r2)) {
    return 5;
  }
  if (d > r1 + r2) {
    return 1;
  }
  if (d > std::abs(r1 - r2) && d < r1 + r2) {
    return 3;
  }
  return 0; // error!
}

std::vector<Point> graham_scan(const std::vector<Point>& points) {
  int n = points.size();
  if (n <= 3) return points;
  std::vector<Point> result = points;
  // 找到y坐标最小的点，如果有多个相通的y，取x坐标最小的点
  int min_index = 0;
  for (int i = 1; i < n; i++) {
    if (result[i].y < result[min_index].y ||
        (result[i].y == result[min_index].y && result[i].x < result[min_index].x)) {
      min_index = i;
    }
  }
  // 将y最小的点放到第0个位置
  if (min_index != 0) {
    std::swap(result[0], result[min_index]);
  }
  // 对0以外的顶点，使用相对于0点的极角进行从小到大排序（通过叉乘计算），极角相通按照离0点由近及远排序
  std::sort(result.begin() + 1, result.end(), [&](const Point& lhs, const Point& rhs) {
    double cm = cross_multiply(result[0], lhs, rhs);
    return cm > 0 || (cm == 0 && distance(result[0], lhs) <= distance(result[0], rhs));
  });

  // 由stack中的栈顶前一个元素、栈顶、points待检测点构成的折线，如果不拐向左边，则执行出栈操作
  int top = 2;
  for (int i = 3; i < n; i++) {
    while (cross_multiply(result[top - 1], result[top], result[i]) <= 0) {
      top--;
    }
    if (top + 1 != i) {
      result[++top] = result[i];
    }
  }
  result.resize(top + 1);
  return result;
}

} // basic_geometry
} // computational_geometry
} // sakabatou_algorithm
