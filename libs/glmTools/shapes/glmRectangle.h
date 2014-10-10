//
//  glmRectangle.h
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//  Inspired by https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/types/ofRectangle.h
//

#pragma once

#include "glmTools.h"

class glmRectangle {
public:
    
    glmRectangle();
    glmRectangle(const glm::vec4 &_vec4);
    glmRectangle(const glm::ivec4 &_viewPort);
    glmRectangle(const glmRectangle &_rectangel, const float &_margin = 0.0);
    glmRectangle(const float &_x, const float &_y, const float &_width, const float &_height);
    virtual ~glmRectangle();
    
    void    set(const glm::vec4 &_vec4);
    void    set(const glm::ivec4 &_viewPort);
    void    set(const float &_x, const float &_y, const float &_width, const float &_height);
    
    void    translate(const glm::vec3 &_pos);
    
    void    growToInclude(const glm::vec3& _point);
    void    growToInclude(const std::vector<glm::vec3> &_points);
    
    bool    inside(const float &_px, const float &_py) const;
    bool    inside(const glm::vec3& _p) const;
    bool    inside(const glmRectangle& _rect) const;
    bool    inside(const glm::vec3& p0, const glm::vec3& p1) const;
    
    bool    intersects(const glmRectangle& _rect) const;
    bool    intersects(const glm::vec3& _p0, const glm::vec3& _p1) const;
    bool    clip( glm::vec3& _p0, glm::vec3& _p1) const;
    
    float   getMinX() const;
    float   getMaxX() const;
    float   getMinY() const;
    float   getMaxY() const;
    
    float   getLeft()   const;
    float   getRight()  const;
    float   getTop()    const;
    float   getBottom() const;
    
    glm::vec3   getMin() const;
    glm::vec3   getMax() const;
    
    glm::vec3   getCenter() const;
    glm::vec3   getTopLeft() const;
    glm::vec3   getTopRight() const;
    glm::vec3   getBottomLeft() const;
    glm::vec3   getBottomRight() const;
    
    void    drawBorders();
    void    drawCorners(const float &_width = 4.);
    
    float   x,y,width,height;
};