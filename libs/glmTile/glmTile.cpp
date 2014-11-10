//
//  glmTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#include "glmTile.h"

glmTile::glmTile():tileX(-1), tileY(-1), zoom(-1){
}

glmTile::~glmTile(){
    byLayers.clear();
    labeledFeatures.clear();
    labeledLines.clear();
    labeledPoints.clear();
}

glmMesh glmTile::getMeshFor(const std::string &_layerName){
    glmMesh mesh;
    for (auto &it : byLayers[_layerName]){
        mesh.add( *it );
    }
    return mesh;
}

glmMesh glmTile::getMeshFor(const std::vector< std::string > &_layersNames){
    glmMesh mesh;
    for (auto &it : _layersNames ) {
        mesh.add(getMeshFor(it));
    }
    return mesh;
}

glmMesh glmTile::getMesh(){
    glmMesh mesh;
    for (auto &it : byLayers ){
        mesh.add( getMeshFor(it.first) );
    }
    return mesh;
}