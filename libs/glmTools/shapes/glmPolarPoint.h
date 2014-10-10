//
//  glmPolarPoint.h
//
//  Created by Patricio Gonzalez Vivo on 9/12/14.
//
//

#pragma once

#include "glm/glm.hpp"

class glmPolarPoint {
public:
    
    glmPolarPoint();
    glmPolarPoint(const float &_angle, const float &_radius, const float &_z = 0.0);
    glmPolarPoint(const glm::vec3 &_org, const glm::vec3 &_dst);
    
    glm::vec3 getXY();
    
    float a,r,z;
};