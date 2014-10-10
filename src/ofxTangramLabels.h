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
    
    void updateCameraPosition( ofPoint _camPos );
    void updateProjection();
    
    void loadFont(string _font, int _size);
};