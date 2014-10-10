//
//  glmVectorField.cpp
//
//  Created by Patricio Gonzalez Vivo on 9/25/14.
//
//

#include "glmVectorField.h"

glmVectorField::glmVectorField():m_forces(NULL),m_width(0), m_height(0), m_cols(0), m_rows(0), m_resolution(10){
    
}

glmVectorField::~glmVectorField(){
    deallocate();
}

void glmVectorField::deallocate(){
    
    if(m_forces != NULL){
        for(int i = 0; i < m_rows; i++){
            delete [] m_forces[i];
        }
        
        delete [] m_forces;  //delete the array of pointers
        m_forces = NULL;
    }
}

bool glmVectorField::set( int _width, int _height, int _res ){
    
    if(m_width != _width || m_height != _height || m_resolution != _res){

        deallocate();
        
        m_width = _width;
        m_height = _height;
        m_resolution = _res;
        
        m_cols = m_width / m_resolution + 1;
        m_rows = m_height / m_resolution + 1;
        
        //  Allocation
        //
        m_forces = new glm::vec3*[m_cols];
        for(int i = 0; i < m_cols; i++){
            m_forces[i] = new glm::vec3[m_rows];
        }
        
        // Initialization
        //
        for(int j = 0; j < m_cols; j++){
            for(int i = 0; i < m_rows; i++){
                m_forces[j][i] = glm::vec3(0.,0.,0.);
            }
        }
        
        return true;
    } else {
        return false;
    }
}

glm::vec3 &	glmVectorField::getForceAt(const glm::vec3 &_pos){
    
    if(m_width > 0 && m_height > 0 ){
        float pctX = _pos.x / m_width;
        float pctY = _pos.y / m_height;
        
        int cols = m_width / m_resolution;
        int rows = m_height / m_resolution;
        
        int xVal = CLAMP(pctX*m_cols, 0, m_cols-1);
        int yVal = CLAMP(pctY*m_rows, 0, m_rows-1);
        
        return m_forces[xVal][yVal];
    } else {
        glm::vec3 none = glm::vec3(0.,0.,0.);
        return none;
    }
}

void glmVectorField::addRepelForce(const glm::vec3 &_pos, float _radius, float _strength) {
    
    float pctX = _pos.x / m_width;
    float pctY = _pos.y / m_height;
    
    int cols = m_width / m_resolution;
    int rows = m_height / m_resolution;
    
    int xVal = pctX * cols;
    int yVal = pctY * rows;
    
    for( int x = 0; x < m_cols; x++){
        for( int y = 0; y < m_rows; y++){
            glm::vec3 np = glm::vec3( x*m_resolution, y*m_resolution, 0.0 );
            
            if( glm::distance(_pos, np) < _radius ){
                float pct = 1 - ( glm::distance(_pos, np) / _radius);
                glm::vec3 dir = glm::normalize(np - _pos);
                m_forces[x][y] += dir * _strength * pct;
            }
        }
    }
}

void glmVectorField::addRepelBorders(float _strength){
    
    glm::vec3 toCenter = glm::vec3(m_width*0.5,m_height*0.5,0.);
    for (int x = 0; x < m_cols; x++) {
        int y = 0;
        glm::vec3 np = glm::vec3( x*m_resolution, y*m_resolution, 0.0 );
        m_forces[x][y] += glm::normalize(toCenter - np )*_strength;
        
        y = m_rows-1;
        np = glm::vec3( x*m_resolution, y*m_resolution, 0.0 );
        m_forces[x][y] += glm::normalize(toCenter - np )*_strength;
    }
    
    for (int y = 0; y < m_rows; y++) {
        int x = 0;
        glm::vec3 np = glm::vec3( x*m_resolution, y*m_resolution, 0.0 );
        m_forces[x][y] += glm::normalize(toCenter - np )*_strength;
        
        x = m_cols-1;
        np = glm::vec3( x*m_resolution, y*m_resolution, 0.0 );
        m_forces[x][y] += glm::normalize(toCenter - np )*_strength;
    }
}

void glmVectorField::drawGrid(){
    for( int x = 0; x < m_cols; x++){
        for( int y = 0; y < m_rows; y++){
            drawCross( glm::vec3( x*m_resolution, y*m_resolution, 0.0), 5 );
        }
    }
}

void glmVectorField::drawForces(){
    for( int x = 0; x < m_cols; x++){
        for( int y = 0; y < m_rows; y++){
            glm::vec3 pos = glm::vec3( x*m_resolution, y*m_resolution, 0.0);
            pos += glm::vec3(m_resolution*0.5,m_resolution*0.5,0.);
            drawLine(pos, pos+m_forces[x][y]);
            float angle = atan2f(m_forces[x][y].y, m_forces[x][y].x);
            drawArrow(pos+m_forces[x][y], angle,5);
        }
    }
}