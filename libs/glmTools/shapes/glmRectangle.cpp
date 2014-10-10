//
//  glmRectangle.cpp
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#include "glmRectangle.h"

glmRectangle::glmRectangle():x(0.0), y(0.0), width(0.0), height(0.0){

}

glmRectangle::glmRectangle(const glm::vec4 &_vec4){
    set(_vec4);
}

glmRectangle::glmRectangle(const glm::ivec4 &_vec4){
    set(_vec4);
}

glmRectangle::glmRectangle(const glmRectangle &_rect, const float &_margin){
    set(_rect.x-_margin, _rect.y-_margin, _rect.width+_margin*2., _rect.height+_margin*2.);
}

glmRectangle::glmRectangle(const float &_x, const float &_y, const float &_width, const float &_height){
    set(_x, _y, _width, _height);
}

glmRectangle::~glmRectangle(){
}

void glmRectangle::set(const glm::vec4 &_vec4){
    set(_vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void glmRectangle::set(const glm::ivec4 &_vec4){
    set(_vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void glmRectangle::set(const float &_x, const float &_y, const float &_width, const float &_height){
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

void glmRectangle::translate(const glm::vec3 &_pos){
    x += _pos.x;
    y += _pos.y;
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getMin() const {
    return glm::vec3(getMinX(),getMinY(),0.);
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getMax() const {
    return glm::vec3(getMaxX(),getMaxY(),0.);
}

//----------------------------------------------------------
float glmRectangle::getMinX() const {
    return MIN(x, x + width);  // - width
}

//----------------------------------------------------------
float glmRectangle::getMaxX() const {
    return MAX(x, x + width);  // - width
}

//----------------------------------------------------------
float glmRectangle::getMinY() const{
    return MIN(y, y + height);  // - height
}

//----------------------------------------------------------
float glmRectangle::getMaxY() const {
    return MAX(y, y + height);  // - height
}

bool glmRectangle::inside(const float &_px, const float &_py) const {
	return inside(glm::vec3(_px,_py,0.));
}

float glmRectangle::getLeft() const {
    return getMinX();
}

//----------------------------------------------------------
float glmRectangle::getRight() const {
    return getMaxX();
}

//----------------------------------------------------------
float glmRectangle::getTop() const {
    return getMinY();
}

//----------------------------------------------------------
float glmRectangle::getBottom() const {
    return getMaxY();
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getTopLeft() const {
    return getMin();
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getTopRight() const {
    return glm::vec3(getRight(),getTop(),0.);
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getBottomLeft() const {
    return glm::vec3(getLeft(),getBottom(),0.);
}

//----------------------------------------------------------
glm::vec3 glmRectangle::getBottomRight() const {
    return getMax();
}

glm::vec3  glmRectangle::getCenter() const {
	return glm::vec3(x + width * 0.5f, y + height * 0.5f, 0.0);
}

//----------------------------------------------------------
bool glmRectangle::inside(const glm::vec3& p) const {
    return p.x > getMinX() && p.y > getMinY() &&
    p.x < getMaxX() && p.y < getMaxY();
}

//----------------------------------------------------------
bool glmRectangle::inside(const glmRectangle& rect) const {
    return inside(rect.getMinX(),rect.getMinY()) &&
            inside(rect.getMaxX(),rect.getMaxY());
}

//----------------------------------------------------------
bool glmRectangle::inside(const glm::vec3& p0, const glm::vec3& p1) const {
    // check to see if a line segment is inside the rectangle
    return inside(p0) && inside(p1);
}

//----------------------------------------------------------
bool glmRectangle::intersects(const glmRectangle& rect) const {
    return (getMinX() < rect.getMaxX() && getMaxX() > rect.getMinX() &&
            getMinY() < rect.getMaxY() && getMaxY() > rect.getMinY());
}

//----------------------------------------------------------
bool glmRectangle::intersects(const glm::vec3& p0, const glm::vec3& p1) const {
    // check for a line intersection
    glm::vec3 p;
    
    glm::vec3 topLeft     = getTopLeft();
    glm::vec3 topRight    = getTopRight();
    glm::vec3 bottomRight = getBottomRight();
    glm::vec3 bottomLeft  = getBottomLeft();
    
    return inside(p0) || // check end inside
    inside(p1) || // check end inside
    lineSegmentIntersection(p0, p1, topLeft,     topRight,    p) || // cross top
    lineSegmentIntersection(p0, p1, topRight,    bottomRight, p) || // cross right
    lineSegmentIntersection(p0, p1, bottomRight, bottomLeft,  p) || // cross bottom
    lineSegmentIntersection(p0, p1, bottomLeft,  topLeft,     p);   // cross left
}

bool glmRectangle::clip( glm::vec3& _p0, glm::vec3& _p1) const {
    
    glm::vec3 topLeft     = getTopLeft();
    glm::vec3 topRight    = getTopRight();
    glm::vec3 bottomRight = getBottomRight();
    glm::vec3 bottomLeft  = getBottomLeft();
    
    if (!inside(_p0)) {
        glm::vec3 r;
        if (lineSegmentIntersection(_p0, _p1, topLeft,     topRight,    r)){
            _p0 = r;
        } else if (lineSegmentIntersection(_p0, _p1, topRight,    bottomRight, r)){
            _p0 = r;
        } else if (lineSegmentIntersection(_p0, _p1, bottomRight, bottomLeft,  r)){
            _p0 = r;
        } else if (lineSegmentIntersection(_p0, _p1, bottomLeft,  topLeft,     r)){
            _p0 = r;
        }
    }
    
    if (!inside(_p1)) {
        glm::vec3 r;
        if (lineSegmentIntersection(_p1, _p0, topLeft,     topRight,    r)){
            _p1 = r;
        } else if (lineSegmentIntersection(_p1, _p0, topRight,    bottomRight, r)){
            _p1 = r;
        } else if (lineSegmentIntersection(_p1, _p0, bottomRight, bottomLeft,  r)){
            _p1 = r;
        } else if (lineSegmentIntersection(_p1, _p0, bottomLeft,  topLeft,     r)){
            _p1 = r;
        }
    }
}

void glmRectangle::growToInclude(const glm::vec3& p){
    float x0 = MIN(getMinX(),p.x);
    float x1 = MAX(getMaxX(),p.x);
    float y0 = MIN(getMinY(),p.y);
    float y1 = MAX(getMaxY(),p.y);
    float w = x1 - x0;
    float h = y1 - y0;
    set(x0,y0,w,h);
}

void glmRectangle::growToInclude(const std::vector<glm::vec3> &_points){
    for(auto &it: _points){
        growToInclude(it);
    }
}

void glmRectangle::drawBorders(){
    glm::vec3 linePoints[5] = {getTopLeft(), getTopRight(), getBottomRight(), getBottomLeft(), getTopLeft()};
    
    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(glm::vec3), &linePoints[0].x);
	glDrawArrays(GL_LINE_STRIP, 0, 5);
}

void glmRectangle::drawCorners(const float &_width){
    glm::vec3 linePoints[16] = {getTopLeft(), getTopLeft(),getTopLeft(), getTopLeft(),
                               getTopRight(), getTopRight(),getTopRight(), getTopRight(),
                               getBottomRight(), getBottomRight(),getBottomRight(), getBottomRight(),
                               getBottomLeft(), getBottomLeft(),getBottomLeft(), getBottomLeft() };
    linePoints[0].x += _width;
    linePoints[3].y += _width;
    
    linePoints[4].x -= _width;
    linePoints[7].y += _width;
    
    linePoints[8].x -= _width;
    linePoints[11].y -= _width;
    
    linePoints[12].x += _width;
    linePoints[15].y -= _width;
    
    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(glm::vec3), &linePoints[0].x);
	glDrawArrays(GL_LINES, 0, 16);
}