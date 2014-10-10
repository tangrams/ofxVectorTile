//
//  glmParticle.cpp
//
//  Created by Patricio Gonzalez Vivo on 9/25/14.
//
//

#include "glmParticle.h"

glmParticle::glmParticle():m_pos(0.,0.,0.),m_vel(0.,0.,0.),m_acc(0.,0.,0.),m_mass(1.0),m_dump(0.98){
    
}

glmParticle::~glmParticle(){
    
}

void glmParticle::addForce(const glm::vec3 &_force){
    m_acc += (_force / m_mass);
}

void glmParticle::update(){
    m_vel += m_acc;
    m_pos += m_vel;
    m_vel *= m_dump;
    m_acc *= 0.0;
}

void glmParticle::drawDebug(){
    drawCross(m_pos);
}