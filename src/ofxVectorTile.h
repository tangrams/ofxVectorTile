//
//  ofxVectorTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "glmTile.h"

class ofxVectorTile : public glmTile {
public:
    
    ofxVectorTile();
    virtual ~ofxVectorTile();
    
    ofMesh getMesh();
    ofMesh getMeshFor(const std::string &_layerName);
    ofMesh getMeshFor(const std::vector< std::string > &_layersNames);
    
    void draw();
};



