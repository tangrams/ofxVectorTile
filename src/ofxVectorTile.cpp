//
//  ofxVectorTile.cpp
//  example
//
//  Created by Patricio Gonzalez Vivo on 11/10/14.
//
//

#include "ofxVectorTile.h"

#include "ofxGlm.h"
#include "ofxGlmTools.h"

ofxVectorTile::ofxVectorTile(){
    
}

ofxVectorTile::~ofxVectorTile(){
    
}

ofxVectorTile& ofxVectorTile::operator = (const glmTile &_tile){
    byLayers.clear();
    labeledFeatures.clear();
    labeledLines.clear();
    labeledPoints.clear();
    
    byLayers = _tile.byLayers;
    labeledFeatures = _tile.labeledFeatures;
    labeledLines = _tile.labeledLines;
    labeledPoints = _tile.labeledPoints;
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