//
//  ofxVectorBuilder.h
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"

#include "ofxGlmTools.h"

#include "glmGeometryBuilder.h"

class ofxVectorBuilder : public glmGeometryBuilder {
public:
    
    ofxVectorBuilder();
    virtual ~ofxVectorBuilder();
    
    ofPoint getOffset();
    ofPoint getPointAt(double _lat, double _lon, double _alt = 0);
    
    ofMesh getMesh(int _tileX, int _tileY, int _zoom);
    ofMesh getMesh(double _lat, double _lon, int _zoom);
    
private:
};