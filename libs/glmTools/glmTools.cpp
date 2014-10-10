//
//  glmTools.cpp
//
//  Created by Patricio Gonzalez Vivo on 9/4/14.
//
//

#include "glmTools.h"

double y2lat(double y) { return glm::degrees(2. * atan(exp(glm::radians(y))) - PI / 2); }
double x2lon(double x) { return glm::degrees(x / R_EARTH); }
double lat2y(double lat) { return R_EARTH * log(tan(PI / 4 + glm::radians(lat) / 2)); }
double lon2x(double lon) { return glm::radians(lon) * R_EARTH; }

float mapValue(const float &value, const float &inputMin, const float &inputMax, const float &outputMin, const float &outputMax, bool clamp ) {
	if (fabs(inputMin - inputMax) < FLT_EPSILON){
		return outputMin;
	} else {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
        
		if( clamp ){
			if(outputMax < outputMin){
				if( outVal < outputMax )outVal = outputMax;
				else if( outVal > outputMin )outVal = outputMin;
			}else{
				if( outVal > outputMax )outVal = outputMax;
				else if( outVal < outputMin )outVal = outputMin;
			}
		}
		return outVal;
	}
}

float lerpValue(const float &_start, const float &_stop, float const &_amt) {
    if(_start!=_stop){
        return _start + (_stop-_start) * _amt;
    } else {
        return _stop;
    }
}

void wrapRad(double &_angle){
    if (_angle < -PI) _angle += PI*2.;
    if (_angle > PI) _angle -= PI*2.;
}

std::string toString(const int &_int){
    std::ostringstream strStream;
    strStream<<_int;
    return strStream.str();
}

std::string toString(const float &_float){
    std::ostringstream strStream;
    strStream<<_float;
    return strStream.str();
}

std::string toString(const double &_double){
    std::ostringstream strStream;
    strStream<<_double;
    return strStream.str();
}

std::string toString(const char &_char){
    std::stringstream strStream;
    strStream<<_char;
    return strStream.str();
}

void stringPurifier ( std::string& s ){
    for ( std::string::iterator it = s.begin(), itEnd = s.end(); it!=itEnd; ++it){
        if ( static_cast<unsigned int>(*it) < 32 || static_cast<unsigned int>(*it) > 127 ){
            (*it) = ' ';
        }
    }
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
	os << vec.x << ", " << vec.y << ", " << vec.z;
	return os;
}

inline std::istream& operator>>(std::istream& is, glm::vec3& vec) {
	is >> vec.x;
	is.ignore(2);
	is >> vec.y;
	is.ignore(2);
	is >> vec.z;
	return is;
}

glm::vec3 getCentroid(std::vector<glm::vec3> &_pts){
    glm::vec3 centroid;
    for (int i = 0; i < _pts.size(); i++) {
        centroid += _pts[i] / (float)_pts.size();
    }
    return centroid;
}

void drawArrow(const glm::vec3 &_pos, const float &_angle, const float &_width ){
    glm::ivec3 linePoints[4] = {    glm::ivec3(_pos.x,_pos.y,_pos.z),
                                    glm::ivec3(_pos.x,_pos.y,_pos.z),
                                    glm::ivec3(_pos.x,_pos.y,_pos.z),
                                    glm::ivec3(_pos.x,_pos.y,_pos.z)};
    linePoints[0].x += (int)_width*cos(_angle+QUARTER_PI*3.);
    linePoints[0].y += (int)_width*sin(_angle+QUARTER_PI*3.);
    
    linePoints[3].x += (int)_width*cos(_angle-QUARTER_PI*3.);
    linePoints[3].y += (int)_width*sin(_angle-QUARTER_PI*3.);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, sizeof(glm::ivec3), &linePoints[0].x);
    glDrawArrays(GL_LINES, 0, 4);
}

void drawCross(const glm::vec3 &_pos, const float &_width ){
    glm::ivec3 linePoints[4] = {    glm::ivec3(_pos.x,_pos.y,_pos.z),
        glm::ivec3(_pos.x,_pos.y,_pos.z),
        glm::ivec3(_pos.x,_pos.y,_pos.z),
        glm::ivec3(_pos.x,_pos.y,_pos.z) };
    linePoints[0].x -= _width;
    linePoints[1].x += _width;
    linePoints[2].y -= _width;
    linePoints[3].y += _width;
    
    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, sizeof(glm::ivec3), &linePoints[0].x);
	glDrawArrays(GL_LINES, 0, 4);
}

void drawLine(const glm::vec3 &_a, const glm::vec3 &_b){
    glm::ivec3 linePoints[2];
    linePoints[0] = glm::ivec3(_a.x,_a.y,_a.z);
    linePoints[1] = glm::ivec3(_b.x,_b.y,_b.z);;
    
    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, sizeof(glm::ivec3), &linePoints[0].x);
	glDrawArrays(GL_LINES, 0, 2);
};

void drawStippleLine(const glm::vec3 &_a, const glm::vec3 &_b, const GLushort &_pattern ){
    glm::vec3 linePoints[2];
    linePoints[0] = _a;
    linePoints[1] = _b;
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, _pattern);
    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(glm::vec3), &linePoints[0].x);
	glDrawArrays(GL_LINES, 0, 2);
    glDisable(GL_LINE_STIPPLE);
};

bool lineSegmentIntersection(const glm::vec3 &_line1Start, const glm::vec3 &_line1End,
                             const glm::vec3 &_line2Start, const glm::vec3 &_line2End,
                             glm::vec3 &_intersection ){
	glm::vec3 diffLA, diffLB;
	double compareA, compareB;
	diffLA = _line1End - _line1Start;
	diffLB = _line2End - _line2Start;
	compareA = diffLA.x*_line1Start.y - diffLA.y*_line1Start.x;
	compareB = diffLB.x*_line2Start.y - diffLB.y*_line2Start.x;
	if (
		(
         ( ( diffLA.x*_line2Start.y - diffLA.y*_line2Start.x ) < compareA ) ^
         ( ( diffLA.x*_line2End.y - diffLA.y*_line2End.x ) < compareA )
         )
		&&
		(
         ( ( diffLB.x*_line1Start.y - diffLB.y*_line1Start.x ) < compareB ) ^
         ( ( diffLB.x*_line1End.y - diffLB.y*_line1End.x) < compareB )
         )
        )
	{
		double lDetDivInv = 1 / ((diffLA.x*diffLB.y) - (diffLA.y*diffLB.x));
		_intersection.x =  -((diffLA.x*compareB) - (compareA*diffLB.x)) * lDetDivInv ;
		_intersection.y =  -((diffLA.y*compareB) - (compareA*diffLB.y)) * lDetDivInv ;
        
		return true;
	}
    
	return false;
};