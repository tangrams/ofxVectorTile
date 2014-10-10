//
//  glmFastPolyline.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFastPolyline.h"

glmFastPolyline::glmFastPolyline(){
};

glmFastPolyline::glmFastPolyline(const glmPolyline &_poly){
    for (int i = 0; i < _poly.size(); i++) {
        add(_poly[i]);
    }
}

glmFastPolyline::glmFastPolyline(const std::vector<glm::vec3> &_points){
    for (auto &it : _points) {
        add(it);
    }
}

glmFastPolyline::~glmFastPolyline(){
};

void glmFastPolyline::clear(){
    glmPolyline::clear();
    m_polars.clear();
    m_distances.clear();
}

void glmFastPolyline::add( const glm::vec3 & _point ){
    
    //  Cache distances and angles between points together with total distance to fast use
    //
    if(size()>0){
        m_polars.push_back( glmPolarPoint(m_points[m_points.size()-1],_point) );
        m_distances.push_back( m_distances[m_distances.size()-1] + m_polars[m_polars.size()-1].r );
    } else {
        m_distances.push_back(0.0);
    }
    
    //  Add point in a regular way
    //
    glmPolyline::add(_point);
}

const std::vector<glmPolarPoint> & glmFastPolyline::getPolars() const{
    return m_polars;
}

const std::vector<float> & glmFastPolyline::getDistances() const{
    return m_distances;
}

float glmFastPolyline::getAngleAt(const float &_dist) const{
    
    if(m_polars.size() == 0 || m_distances.size() == 0){
        return -1;
    } else if(_dist <= 0){
        return m_polars[0].a;
    } else if (_dist >= getLength()){
        return m_polars[m_polars.size()-1].a;
    }
    
    for (int i = 1; i < m_distances.size(); i++) {
        if(_dist<=m_distances[i]){
            return m_polars[i-1].a;
        }
    }
    
    for (int i = 1; i < m_distances.size(); i++) {
        if(_dist<=m_distances[i]){
            return m_polars[i-1].a;
        }
    }
    
    return 0;
}

glm::vec3 glmFastPolyline::getPositionAt(const float &_dist) const{

    if(_dist <= 0){
        return m_points[0];
    } else if (_dist >= getLength()){
        return m_points[size()-1];
    }
    
    // We improve it with @sevko. Check for JS implementation at https://github.com/pelias/line-interpolate-points
    //
    
    //  Linear Search
    for (int i = 0; i < m_distances.size()-1; i++) {
        if(_dist<m_distances[i+1]){
            float pct = (_dist-m_distances[i])/m_polars[i].r;
            return m_points[i] + (m_points[i+1]-m_points[i])*pct;
        }
    }
    
    //  For distances out of range
    return m_points[size()-1];
}

float glmFastPolyline::getFractAt(const float &_dist, const float &_offset) const{
    float a = getAngleAt(_dist-_offset);
    float b = getAngleAt(_dist+_offset);
    
    float diff= (a - b);
    if (diff < -PI) diff += PI*2.;
    if (diff > PI) diff -= PI*2.;
    
    return abs(diff)/PI;
}

void glmFastPolyline::updateCache(){
    
    //  TODO: only update the once that change
    //
    m_polars.clear();
    m_distances.clear();
    
    float total = 0;
    for (int i = 1; i < size(); i++) {
        glmPolarPoint p = glmPolarPoint(m_points[i-1],m_points[i]);
        m_polars.push_back(p);
        m_distances.push_back( total );
        total += p.r;
    }
    m_distances.push_back( total );
}

float glmFastPolyline::getLength(const int &_index) const {
    
    if(_index >= size() || size() == 0){
        return -1;
    } else if(_index == -1){
        return m_distances[size()-1];
    } else if ( _index < 0){
        return 0;
    } else {
        return m_distances[_index];
    }
}

void glmFastPolyline::simplify(float _tol){
    glmPolyline::simplify(_tol);
    updateCache();
}

void glmFastPolyline::drawNormals(){
    for (int i = 0; i < size()-1; i++) {
        drawLine(m_points[i], m_points[i] + glmPolarPoint(m_polars[i].a-HALF_PI,m_polars[i].r).getXY());
    }
}