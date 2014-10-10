//
//  glmTile.h
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#pragma once

#include <map>

#include "glmFeature.h"
#include "glmFeatureLabel.h"
#include "glmFeatureLabelLine.h"
#include "glmFeatureLabelPoint.h"

class glmTile {
public:
    
    glmTile();
    virtual ~glmTile();
    
    bool    load(int _tileX, int _tileY, int _zoom);
    
    glmMesh getMesh();
    glmMesh getMeshFor(const std::string &_layerName);
    glmMesh getMeshFor(const std::vector< std::string > &_layersNames);
    
    std::map< std::string, std::vector<glmFeatureRef> > byLayers;

    std::vector<glmFeatureLabelRef> labeledFeatures;
    std::vector<glmFeatureLabelLineRef> labeledLines;   // Usualy Roads
    std::vector<glmFeatureLabelPointRef> labeledPoints;
    
    int     tileX, tileY, zoom;
};