//
//  ofxTangramTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxTangramTile.h"

#include "ofxGlm.h"

ofxTangramTile::ofxTangramTile(){
    
}

ofxTangramTile::~ofxTangramTile(){
    
}

ofMesh ofxTangramTile::getMesh(){
    return toOf(glmTile::getMesh());
}

ofMesh ofxTangramTile::getMeshFor(const std::string &_layerName){
    return toOf(glmTile::getMeshFor(_layerName));
}

ofMesh ofxTangramTile::getMeshFor(const std::vector< std::string > &_layersNames){
    return toOf(glmTile::getMeshFor(_layersNames));
}

void ofxTangramTile::draw(){
    for (auto &layer : byLayers ){
        for( auto &feature : layer.second ){
            feature->draw();
        }
    }
}