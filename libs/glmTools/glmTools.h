//
//  Header.h
//
//  Created by Patricio Gonzalez Vivo on 8/25/14.
//
//

#pragma once

#include <vector>
#include <iostream>
#include <sstream>

#include <OpenGL/gl.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#ifndef PI
#define PI       3.14159265358979323846
#endif

#ifndef TWO_PI
#define TWO_PI   6.28318530717958647693
#endif

#ifndef M_TWO_PI
#define M_TWO_PI   6.28318530717958647693
#endif

#ifndef FOUR_PI
#define FOUR_PI 12.56637061435917295385
#endif

#ifndef HALF_PI
#define HALF_PI  1.57079632679489661923
#endif

#ifndef QUARTER_PI
#define QUARTER_PI 0.785398163
#endif

#ifndef R_EARTH
#define R_EARTH 6378137
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD (PI/180.0)
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG (180.0/PI)
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef CLAMP
#define CLAMP(val,min,max) ((val) < (min) ? (min) : ((val > max) ? (max) : (val)))
#endif

#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif

const glm::vec3 UP_NORMAL = glm::vec3(0.0f, 0.0f, 1.0f);

double y2lat(double y);
double x2lon(double x);
double lat2y(double lat);
double lon2x(double lon);

void wrapRad(double &_angle);
float mapValue(const float &_value, const float &_inputMin, const float &_inputMax, const float &_outputMin, const float &_outputMax, bool clamp = false);
float lerpValue(const float &_start, const float &_stop, const float &_amt);

std::string toString(const int &_float);
std::string toString(const float &_float);
std::string toString(const double &_float);

void stringPurifier ( std::string& s );

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec);

inline std::istream& operator>>(std::istream& is, glm::vec3& vec);

glm::vec3 getCentroid(std::vector<glm::vec3> &_pts);

void drawArrow(const glm::vec3 &_pos, const float &_angle, const float &_width = 6.0);
void drawCross(const glm::vec3 &_pos, const float &_width = 3.5);

void drawLine(const glm::vec3 &_a, const glm::vec3 &_b);

void drawStippleLine(const glm::vec3 &_a, const glm::vec3 &_b, const GLushort &_pattern = 0x00FF);

bool lineSegmentIntersection(const glm::vec3 &_line1Start, const glm::vec3 &_line1End,
                             const glm::vec3 &_line2Start, const glm::vec3 &_line2End,
                             glm::vec3 &_intersection );

// isLeft(): test if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2 on the line
//            <0 for P2 right of the line
//    See: Algorithm 1 on Area of Triangles http://geomalgorithms.com/a10-_hull-1.html
//
inline double isLeft( const glm::vec3 &_P0, const glm::vec3 &_P1, const glm::vec3 &_P2 ){
    return (_P1.x - _P0.x)*(_P2.y - _P0.y) - (_P2.x - _P0.x)*(_P1.y - _P0.y);
}
