//
//  glmFastPolyline.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#pragma once

#include "glmTools.h"
#include "glmPolyline.h"
#include "glmPolarPoint.h"

class glmFastPolyline : public glmPolyline {
public:
    
    glmFastPolyline();
    glmFastPolyline(const glmPolyline &_poly);
    glmFastPolyline(const std::vector<glm::vec3> &_points);
    virtual ~glmFastPolyline();
    
    virtual void add(const glm::vec3 &_point);
    virtual void clear();
    
    virtual float       getLength(const int &_index = -1) const;
    virtual glm::vec3   getPositionAt(const float &_dist) const;
    virtual float       getAngleAt(const float &_dist) const;
    virtual float       getFractAt(const float &_dist, const float &_offset=1.) const;
    
    const std::vector<float> & getDistances() const;
    const std::vector<glmPolarPoint> & getPolars() const;
    
    virtual void    simplify(float _tol);
    virtual void    updateCache();
    virtual void    drawNormals();
    
protected:
    std::vector<glmPolarPoint>  m_polars;
    std::vector<float>          m_distances;
};