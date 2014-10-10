//
//  ofxTangramLabel.h
//  example
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofMain.h"
#include "glmLabelManager.h"

class ofxTangramLabels: public glmLabelManager {
public:
    
    ofxTangramLabels();
    virtual ~ofxTangramLabels();
    
    void setFontColor( const ofFloatColor &_front, const ofFloatColor &_back );
    void loadFont( const string &_font, int _size);
    
    void updateCameraPosition( const ofPoint &_camPos );
    void updateProjection();
    
    
};