//
//  glmParticle.h
//
//  Created by Patricio Gonzalez Vivo on 9/25/14.
//
//

#pragma once

#include "glmTools.h"

class glmParticle {
public:
    
    glmParticle();
    virtual ~glmParticle();
    
    void    addForce(const glm::vec3 &_force);
    
    void    update();
    void    drawDebug();
    
    glm::vec3   m_pos;
    glm::vec3   m_vel;
    glm::vec3   m_acc;
    
    float       m_dump;
    float       m_mass;
};