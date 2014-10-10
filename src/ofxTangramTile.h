//
//  ofxTangramTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "glmTile.h"

class ofxTangramTile : public glmTile {
public:
    
    ofxTangramTile();
    virtual ~ofxTangramTile();
    
    ofMesh getMesh();
    ofMesh getMeshFor(const std::string &_layerName);
    ofMesh getMeshFor(const std::vector< std::string > &_layersNames);
    
    void draw();
};



