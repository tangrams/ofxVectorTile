//
//  ofxTangramBuilder.h
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTangramTile.h"
#include "glmGeometryBuilder.h"

class ofxTangramBuilder : public glmGeometryBuilder {
public:
    
    ofxTangramBuilder();
    virtual ~ofxTangramBuilder();
    
    ofxTangramTile getFromWeb(int _tileX, int _tileY, int _zoom);
    
    ofPoint getOffset();
    
    
private:
    
    bool    bFirst;
};