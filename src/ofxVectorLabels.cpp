//
//  ofxVectorLabel.cpp
//  example
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxVectorLabels.h"

#include "glmFont.h"
#include "ofxGlm.h"

ofxVectorLabels::ofxVectorLabels(){
    
}

ofxVectorLabels::~ofxVectorLabels(){
    
}

void ofxVectorLabels::setFontColor( const ofFloatColor &_front, const ofFloatColor &_back ){
    m_font->colorFront.r = _front.r;
    m_font->colorFront.g = _front.g;
    m_font->colorFront.b = _front.b;
    
    m_font->colorBack.r = _back.r;
    m_font->colorBack.g = _back.g;
    m_font->colorBack.b = _back.b;
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
