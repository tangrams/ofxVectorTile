//
//  ofxTangramTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofxGlm.h"
#include "glmTile.h"

#include "ofxTangramBuilder.h"

class ofxTangramTile : public glmTile {
public:
    
    ofMesh getMesh();
    ofMesh getMeshFor(const std::string &_layerName);
    ofMesh getMeshFor(const std::vector< std::string > &_layersNames);
    
    void draw();
};



