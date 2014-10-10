//
//  ofxVectorBuilder.h
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxVectorTile.h"
#include "glmGeometryBuilder.h"

class ofxVectorBuilder : public glmGeometryBuilder {
public:
    
    ofxVectorBuilder();
    virtual ~ofxVectorBuilder();
    
    ofxVectorTile getFromWeb(int _tileX, int _tileY, int _zoom);
    
    ofPoint getOffset();
    
    
private:
    
    bool    bFirst;
};