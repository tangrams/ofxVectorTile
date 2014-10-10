//
//  glmVectorField.h
//
//  Created by Patricio Gonzalez Vivo on 9/25/14.
//
//

#pragma once

#include "glmTools.h"

class glmVectorField {
public:
    glmVectorField();
    virtual ~glmVectorField();
    
    bool    set( int _width, int _height, int _res );
    
    glm::vec3 &	getForceAt(const glm::vec3 &_pos);
    
    void    addRepelForce(const glm::vec3 &_pos, float _radius, float _strength);
    void    addRepelBorders(float _strength);
    
    void    drawGrid();
    void    drawForces();

private:
    void    deallocate();
    
    glm::vec3 **m_forces;
    int         m_width, m_height;
    int         m_cols, m_rows;
    int         m_resolution;
};