//
//  ofxVectorLabel.cpp
//  example
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxVectorLabels.h"

#include "ofxGlm.h"

#include "glmFont.h"

ofxVectorLabels::ofxVectorLabels(){
    
}

ofxVectorLabels::~ofxVectorLabels(){
    
}

void ofxVectorLabels::setFontColor( const ofFloatColor &_front, const ofFloatColor &_back ){
    m_font->outlineColor = glm::vec3(_back.r, _back.g, _back.b);
    m_font->fontColor = glm::vec3(_front.r, _front.g, _front.b);
}

void ofxVectorLabels::updateCameraPosition( const ofPoint &_camPos ){
    glmLabelManager::updateCameraPosition( toGlm(_camPos) );
}

void ofxVectorLabels::updateProjection(){
    ofPushMatrix();
//    ofScale(1, -1, 1);
    glmLabelManager::updateProjection();
    ofPopMatrix();
}

void ofxVectorLabels::loadFont(const string &_font, int _size){
    glmFontRef tmpFont = glmFontRef(new glmFont());
    tmpFont->loadFont(ofToDataPath(_font), _size);
    setFont(tmpFont);
}
