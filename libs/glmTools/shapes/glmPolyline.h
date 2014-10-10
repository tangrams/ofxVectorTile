//
//  glmPolyline.h
//
//  Created by Patricio Gonzalez Vivo on 8/20/14.
//  Inspired by: https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/graphics/ofPolyline.h
//

#pragma once

#include "glmTools.h"
#include "glmRectangle.h"

class glmPolyline {
public:
    
    glmPolyline();
    glmPolyline(const glmPolyline &_poly);
    glmPolyline(const std::vector<glm::vec3> &_points);
    glmPolyline(const glmRectangle &_rect, float _radiants = 0);
    virtual ~glmPolyline();
    
    virtual void add(const glm::vec3 &_point);
    void    add(const std::vector<glm::vec3> &_points);
	void    add(const glm::vec3* verts, int numverts);
    
    virtual glm::vec3 & operator [](const int &_index);
    const glm::vec3 & operator [](const int &_index) const;
    
    virtual glm::vec3   getCentroid();
    virtual const std::vector<glm::vec3> & getVertices() const;
    virtual glm::vec3   getPositionAt(const float &_dist) const;
    virtual glmPolyline get2DConvexHull();
	glmRectangle        getBoundingBox() const;
    
    bool    isInside(float _x, float _y);
    
    virtual int size() const;

    std::vector<glmPolyline> splitAt(float _dist);
    std::vector<glmPolyline> splitAtIntersection(const glmPolyline &_other, float _gap = 1.0);
    
    virtual void    clear();
    virtual void    simplify(float _tolerance=0.3f);
    
    void    draw();

protected:
    std::vector<glm::vec3>  m_points;
    glm::vec3   m_centroid;
    
    bool        m_bChange;
};