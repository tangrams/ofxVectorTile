//
//  glmFeatureLabelLine.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFeatureLabelLine.h"

glmFeatureLabelLine::glmFeatureLabelLine(){
}

glmFeatureLabelLine::glmFeatureLabelLine(const std::string &_text){
    setText(_text);
}

glmFeatureLabelLine::~glmFeatureLabelLine(){
    
}

void glmFeatureLabelLine::seedAnchorsEvery(glmAnchorLine &_anchorLine, float _minDistance, float _maxDistance){
    
    //  Update Fonts/Text cached values if something change
    //
    if(m_bChanged){
        updateCached();
    }
    
    float segmentLength = _anchorLine.getLength();
    
    //  How many times?
    int nTimes = segmentLength/(m_label.width+_maxDistance);
    
    //  At what distance between each other?
    float margin = (segmentLength-m_label.width*(float)nTimes)/((float)nTimes+1.0);
    
    //  Center the Labels
    float seed = margin;
    
    //  Add anchor points for seeds every _distance
    for (int i = 0; i < nTimes; i++) {
        _anchorLine.marks.push_back(AnchorMark(seed/_anchorLine.getLength()));
        seed += m_label.width+margin;
    }
}

void glmFeatureLabelLine::seedAnchorOnSegmentsAt(glmAnchorLine &_anchorLine, float _minDistance, float _maxDistance){
    
    //  Update Fonts/Text cached values if something change
    //
    if(m_bChanged){
        updateCached();
    }
    
    float lastSeed = 0.0;
    for (int i = 0; i < _anchorLine.size()-1; i++) {
        float offset = _anchorLine.getDistances()[i];
        
        float segmentLength = _anchorLine.getDistances()[i+1]-_anchorLine.getDistances()[i];//_anchorLine.getPolars()[i].r;
        
        //  Fits?
        //
        if( segmentLength >= (m_label.width+_maxDistance) ){

            //  How many times?
            int nTimes = segmentLength/(m_label.width+_maxDistance);
            
            //  At what distance between each other?
            float margin = (segmentLength-m_label.width*(float)nTimes)/((float)nTimes+1.0);
            
            //  Add anchors points for seeds
            float seed = margin;
            for (int i = 0; i < nTimes; i++) {
                float potentialSeed = offset + seed ;
                if( potentialSeed-lastSeed > _minDistance ){
                    lastSeed = potentialSeed;
                    _anchorLine.marks.push_back(AnchorMark(lastSeed/_anchorLine.getLength()));
                    seed += m_label.width+margin;
                }
            }
            
        } else if ( segmentLength >= m_label.width+_minDistance){
            
            //  Only one time
            //
            float margin = (segmentLength-m_label.width)*0.5;
            float potentialSeed = offset + margin ;
            if( potentialSeed-lastSeed > _minDistance){
                lastSeed = potentialSeed;
                _anchorLine.marks.push_back(AnchorMark(lastSeed/_anchorLine.getLength()));
            }
        }
    }
}

void glmFeatureLabelLine::updateCached(){
    if(m_font!=NULL&&m_text!="NONE"){
        
        m_lettersWidth.clear();
        m_wordsWidth.clear();
        
        std::string word = "";
        float wordWidth = 0.0f;
        
        for(int i = 0; i < m_text.size(); i++){
            float letterWidth = m_font->stringWidth( std::string(1,m_text[i]) );
            
            if( m_text[i] == ' '){
                m_lettersWidth.push_back(letterWidth);
                m_wordsWidth.push_back(wordWidth);
                wordWidth = 0.;
                word = "";
            } else {
                m_lettersWidth.push_back(letterWidth);
                wordWidth += letterWidth;
                word += &m_text[i];
            }
        }
        
        m_label = m_font->getStringBoundingBox(m_text);
        m_bChanged = false;
    } else {
        bVisible = false;
    }
}


void glmFeatureLabelLine::draw2D(){
    if(m_font!=NULL&&m_text!="NONE"&&bVisible){
        
        //  Global m_alpha
        //
        if(m_cameraPos!=0 && bVisible){
            float angle = glm::dot(glm::normalize( *m_cameraPos - shapes[0].getCentroid()),glm::vec3(0.,0.,1.));
            m_alpha = lerpValue(m_alpha,powf( CLAMP(angle,0.01,1.0), 0.6 ),0.1);
        } else {
            m_alpha = lerpValue(m_alpha,0.0, 0.1);
        }
        
        if(m_alpha > 0.1){
            for (auto &it: m_anchorLines) {
                drawTextOn(it);
            }
        }
        
    }
}

void glmFeatureLabelLine::drawDebug(){
    glColor4f(m_font->colorFront.x,m_font->colorFront.y,m_font->colorFront.z,m_alpha);
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);
    for (auto &it: m_anchorLines) {
        it.draw();
    }
    glDisable(GL_LINE_STIPPLE);
    
    for (auto &it: m_anchorLines) {
        for (int i = 0; i < it.size(); i++) {
            if(i == 0 ){
                glLineWidth(2);
                drawCross(it[i],5);
            } else {
                glLineWidth(1);
                drawCross(it[i]);
                
                //  Print distances
                //
//                glPushMatrix();
//                glTranslated(it[i].x, it[i].y, it[i].z);
//                glScalef(0.75,-0.75,1);
//                glRotated(it.getPolars()[i-1].a*RAD_TO_DEG, 0, 0, -1);
//                glTranslated(5.,3.,0.);
//                m_font->drawString( toString( (int)it.getDistances()[i]), m_alpha );
//                glPopMatrix();
            }
        }
    }
}

void glmFeatureLabelLine::drawTextOn( glmAnchorLine &_anchorLine){
    if(_anchorLine.bLetterByLetter){
        drawLetterByLetter(_anchorLine);
    } else {
        drawAllTextAtOnce(_anchorLine);
    }
}

void glmFeatureLabelLine::drawAllTextAtOnce( glmAnchorLine &_anchorLine){
    for (auto &mark : _anchorLine.marks){
        glm::ivec4 viewport;
        glGetIntegerv(GL_VIEWPORT, &viewport[0]);
        glmRectangle screen = glmRectangle(viewport);
        
        //  Orientation
        //
        float angle = PI;
        glm::vec3 diff = _anchorLine[0]-_anchorLine[_anchorLine.size()-1];
        angle = atan2f(-diff.y, diff.x);
        float offset = mark.m_pct*_anchorLine.getLength();
        glm::vec3 src = _anchorLine.getPositionAt(offset);
        
        if(bVisible){
            mark.m_alpha = lerpValue(mark.m_alpha,m_alpha,0.1);
        } else {
            mark.m_alpha = lerpValue(mark.m_alpha,0.0,0.1);
        }
        
        if(screen.inside(src)){
            double rot = _anchorLine.getAngleAt(offset);
            
            glmRectangle boundingBox = glmPolyline(m_label,angle).getBoundingBox();
            boundingBox.translate( _anchorLine.getPositionAt( offset + m_label.width*0.5) );
            
            // Draw boundign box for debug
            //
//            boundingBox.drawCorners();
            
            bool bOver = false;
            
            for (int i = 0; i < pointLabels->size(); i++ ){
                if(pointLabels->at(i)->bVisible){
                    if( boundingBox.intersects(pointLabels->at(i)->getLabel(0) ) ){
                        bOver = true;
                        break;
                    }
                }
            }
            
            if(!bOver){
                
                glPushMatrix();
                glTranslated(src.x, src.y, src.z);
                
                glScalef(1,-1,1);
                glRotated(rot*RAD_TO_DEG, 0, 0, -1);
                
                if(angle < PI*0.5 && angle > -PI*0.5){
                    glScaled(-1, -1, 1);
                    glTranslated(-m_label.width, 0, 0);
                }
                
                glTranslatef(0., -m_label.height*0.5,0.);
                m_font->drawString( m_text, mark.m_alpha );
                glPopMatrix();
            }
        }
        
    }
}

void glmFeatureLabelLine::drawLetterByLetter(glmAnchorLine &_anchorLine){
    for (auto &mark : _anchorLine.marks){
        glm::ivec4 viewport;
        glGetIntegerv(GL_VIEWPORT, &viewport[0]);
        glmRectangle screen = glmRectangle(viewport);
        
        //  Orientation
        //
        float angle = PI;
        glm::vec3 diff = _anchorLine[0]-_anchorLine[_anchorLine.size()-1];
        angle = atan2f(-diff.y, diff.x);
        float offset = mark.m_pct*_anchorLine.getLength();
        
        if(bVisible){
            mark.m_alpha = lerpValue(mark.m_alpha,m_alpha,0.1);
        } else {
            mark.m_alpha = lerpValue(mark.m_alpha,0.0,0.1);
        }
        
        if(angle < PI*0.5 && angle > -PI*0.5){
            for (int i = m_text.length()-1; i >=0 ; i--) {
                
                glm::vec3 src = _anchorLine.getPositionAt(offset);
                
                if(screen.inside(src)){
                    double rot = _anchorLine.getAngleAt(offset);
                    
                    glPushMatrix();
                    glTranslated(src.x, src.y, src.z);
                    
                    glScalef(1,-1,1);
                    glRotated(rot*RAD_TO_DEG, 0, 0, -1);
                    
                    glScaled(-1, -1, 1);
                    glTranslated(-m_lettersWidth[i], 0, 0);
                    
                    glTranslatef(0., -m_label.height*0.5,0.);
                    m_font->drawString( std::string(1,m_text[i]), mark.m_alpha );
                    glPopMatrix();
                    offset += m_lettersWidth[i];
                } else {
                    break;
                }

            }
        } else {
            
            for (int i = 0; i < m_text.length(); i++) {
                glm::vec3 src = _anchorLine.getPositionAt(offset);
                if(screen.inside(src)){
                    double rot = _anchorLine.getAngleAt(offset);
                    
                    glPushMatrix();
                    glTranslated(src.x, src.y, src.z);
                    
                    glScalef(1,-1,1);
                    glRotated(rot*RAD_TO_DEG, 0, 0, -1);
                    
                    glTranslatef(0., -m_label.height*0.5,0.);
                    m_font->drawString( std::string(1,m_text[i]), mark.m_alpha );
                    
                    glPopMatrix();
                    offset += m_lettersWidth[i];
                } else {
                    break;
                }
            }
        }
    }
}