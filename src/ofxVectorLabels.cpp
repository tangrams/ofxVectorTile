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
    // TODO : fix color
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
