//
//  ofxVectorTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxVectorTile.h"

#include "ofxGlm.h"

ofxVectorTile::ofxVectorTile(){
    
}

ofxVectorTile::~ofxVectorTile(){
    
}

ofMesh ofxVectorTile::getMesh(){
    return toOf(glmTile::getMesh());
}

ofMesh ofxVectorTile::getMeshFor(const std::string &_layerName){
    return toOf(glmTile::getMeshFor(_layerName));
}

ofMesh ofxVectorTile::getMeshFor(const std::vector< std::string > &_layersNames){
    return toOf(glmTile::getMeshFor(_layersNames));
}

void ofxVectorTile::draw(){
    for (auto &layer : byLayers ){
        for( auto &feature : layer.second ){
            feature->draw();
        }
    }
}