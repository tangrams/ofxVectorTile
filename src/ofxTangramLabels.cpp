//
//  ofxTangramLabel.cpp
//  example
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxTangramLabels.h"
#include "glmFont.h"
#include "ofxGlm.h"

ofxTangramLabels::ofxTangramLabels(){
    
}

ofxTangramLabels::~ofxTangramLabels(){
    
}

void ofxTangramLabels::updateCameraPosition( ofPoint _camPos ){
    glmLabelManager::updateCameraPosition( toGlm(_camPos) );
}

void ofxTangramLabels::updateProjection(){
    ofPushMatrix();
//    ofScale(1, -1, 1);
    glmLabelManager::updateProjection();
    ofPopMatrix();
}

void ofxTangramLabels::loadFont(string _font, int _size){
    glmFontRef tmpFont = glmFontRef(new glmFont());
    tmpFont->loadFont(ofToDataPath(_font), _size);
    setFont(tmpFont);
}
