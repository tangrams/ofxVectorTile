//
//  glmFeatureLabelPoint.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFeatureLabelPoint.h"

glmFeatureLabelPoint::glmFeatureLabelPoint():m_centroid(0.0,0.0,0.0), m_offset(0.0,0.0,0.0), m_anchorPoint(0.0,0.0,0.0), m_margin(8.0), m_angle(HALF_PI) {
};

glmFeatureLabelPoint::glmFeatureLabelPoint(const std::string &_text):m_centroid(0.0,0.0,0.0), m_offset(0.0,0.0,0.0), m_anchorPoint(0.0,0.0,0.0), m_margin(8.0), m_angle(HALF_PI){
    setText(_text);
}

glmFeatureLabelPoint::~glmFeatureLabelPoint(){

};

void glmFeatureLabelPoint::setPosition(const glm::vec3 &_pos){
    m_centroid = _pos;
    m_bChanged = true;
}

void glmFeatureLabelPoint::setLabelAngle(const double &_radiant){
    m_angle = _radiant;
    m_bChanged = true;
}

void glmFeatureLabelPoint::setLabelMargin(const float &_margin){
    m_margin = _margin;
    m_bChanged = true;
}

glm::vec3 glmFeatureLabelPoint::getScreenPosition() const{
    return m_anchorPoint;
}

glmRectangle glmFeatureLabelPoint::getLabel(const float &_marign) const{
    if (_marign == 0.0) {
        return m_label;
    } else {
        return glmRectangle(m_label, _marign);
    }
}

glm::vec3 glmFeatureLabelPoint::getAnchorPoint() const{
    return m_anchorPoint;
}

bool glmFeatureLabelPoint::isOver(const glmFeatureLabelPoint *_other, float _margin){
    if(m_bChanged){
        updateCached();
    }
    return m_label.intersects(_other->getLabel(_margin)) || isInside(_other->getAnchorPoint());
}

bool glmFeatureLabelPoint::isInside(const glm::vec3 &_point){
    if(m_bChanged){
        updateCached();
    }
    return m_label.inside(_point);
}

void glmFeatureLabelPoint::updateCached(){
    if(m_font!=NULL&&m_text!="NONE"){
        m_label = m_font->getStringBoundingBox(m_text);
        m_bChanged = false;
    }
}

void glmFeatureLabelPoint::update(){
    
    if(m_font!=NULL&&m_text!="NONE"){
        glm::ivec4 viewport;
        glm::mat4x4 mvmatrix, projmatrix;
        glGetIntegerv(GL_VIEWPORT, &viewport[0]);
        glGetFloatv(GL_MODELVIEW_MATRIX, &mvmatrix[0][0]);
        glGetFloatv(GL_PROJECTION_MATRIX, &projmatrix[0][0]);
        
        if(m_bChanged){
            updateCached();
        }
        
        m_label.x = m_anchorPoint.x + m_margin * cos(m_angle);
        m_label.y = m_anchorPoint.y + m_margin * sin(-m_angle);
        
        if (m_angle <= QUARTER_PI && m_angle >= -QUARTER_PI){
            //  EAST
            //
            m_label.x += 0.0;
            m_label.y += mapValue(m_angle,
                                  QUARTER_PI,     -QUARTER_PI,
                                  -m_label.height,  0);
            
        } else if (m_angle >= QUARTER_PI && m_angle <= QUARTER_PI*3.){
            //  NORTH
            //
            m_label.x += mapValue(m_angle,
                                  QUARTER_PI*3.,  QUARTER_PI,
                                  -m_label.width,   0);
            m_label.y += -m_label.height;
        } else if (m_angle <= -QUARTER_PI && m_angle >= -QUARTER_PI*3.){
            //  SOUTH
            //
            m_label.x += mapValue(m_angle,
                                  -QUARTER_PI*3., -QUARTER_PI,
                                  -m_label.width,   0);
            m_label.y += 0.0;
        } else if (m_angle > QUARTER_PI*3. || m_angle < -QUARTER_PI*3. ){
            //  WEST
            //
            m_label.x -= m_label.width;
            
            if(m_angle > 0){
                m_label.y += mapValue(m_angle,
                                      QUARTER_PI*3., PI,
                                      -m_label.height, -m_label.height*0.5);
            } else {
                m_label.y += mapValue(m_angle,
                                      -PI, -QUARTER_PI*3.,
                                      -m_label.height*0.5,0.0);
            }
        }
        
        bVisible = m_anchorPoint.z >= 0.0 && m_anchorPoint.z <= 1.0;
    } else {
        bVisible = false;
    }
};

void glmFeatureLabelPoint::draw2D(){
    
    //  2D ancher line
    //
//    float angle = 0;
//    float length = 0;
//    
//    if(m_cameraPos!=0 ){
//        glm::vec3 dist = *m_cameraPos - m_centroid;
//        length = glm::distance(*m_cameraPos, m_centroid)*0.2;
//        angle = (1.-glm::dot( glm::normalize( dist ), glm::vec3(0.,0.,1.)));
//    }
//    
//    m_offset.z = lerpValue(m_offset.z,angle*length,0.1);
    
    if(m_font != NULL){
        if(m_bChanged){
            updateCached();
        }
        
        if (bVisible) {
            m_alpha = lerpValue(m_alpha, powf(m_anchorPoint.z,5), 0.1);
        } else {
            m_alpha = lerpValue(m_alpha,0.,0.1);
        }
        
        if(m_alpha > 0.0 && m_projectedCentroid.z > 0 && m_anchorPoint.z > 0){
            glColor4f(m_font->colorFront.x,m_font->colorFront.y,m_font->colorFront.z,m_alpha);
//            drawStippleLine(m_projectedCentroid, m_anchorPoint, 0x1111);
            m_font->drawString(m_text, m_label, m_alpha);
        }
    }
}

void glmFeatureLabelPoint::draw3D(){
    float angle = 0;
    float length = 0;
    
    if(m_cameraPos!=0 ){
        glm::vec3 dist = *m_cameraPos - m_centroid;
        length = glm::distance(*m_cameraPos, m_centroid)*0.2;
        angle = (1.-glm::dot( glm::normalize( dist ), glm::vec3(0.,0.,1.)));
    }
    
    m_offset.z = lerpValue(m_offset.z,angle*length,0.1);
    
    if(m_alpha > 0.1){
        
        m_line.clear();
        m_line.setDrawMode(GL_LINES);
        m_line.addVertex(m_centroid);
        m_line.addVertex(m_centroid+m_offset);
        
        glColor4f(1., 1., 1., m_alpha);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x1111);
        m_line.draw();
        glDisable(GL_LINE_STIPPLE);
        
        glColor4f(1., 1., 1., 1.);
    }
}

void glmFeatureLabelPoint::drawDebug(){
    
    glColor4f(m_font->colorFront.r, m_font->colorFront.g, m_font->colorFront.g, m_alpha);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);
    for (auto &it: m_anchorLines) {
        it.draw();
    }
    glDisable(GL_LINE_STIPPLE);
    drawCross(m_anchorPoint,3.0);
    
    if(!bVisible){
//        glColor4f(m_font->colorFront.r, m_font->colorFront.g, m_font->colorFront.g,0.2);
//        m_label.drawCorners();
    } else {
        glColor4f(m_font->colorFront.r, m_font->colorFront.g, m_font->colorFront.g,1.);
        getLabel(25).drawCorners();
    }
}

