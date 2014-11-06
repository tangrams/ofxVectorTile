//
//  ofxVectorLabel.h
//  example
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "glmLabelManager.h"

#include "glmFont.h"
#include "ofxGlm.h"

class ofxVectorLabels: public glmLabelManager {
public:
    
    ofxVectorLabels();
    virtual ~ofxVectorLabels();
    
    void setFontColor( const ofFloatColor &_front, const ofFloatColor &_back );
    void loadFont( const string &_font, int _size);
    
    void updateCameraPosition( const ofPoint &_camPos );
    void updateProjection();
};