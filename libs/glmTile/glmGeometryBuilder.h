//
//  glmGeometryBuilder.h
//
//  Created by Patricio Gonzalez Vivo on 9/4/14.
//
//

#pragma once

#include "json/json.h"
#include "glmTools.h"

#include "glmTile.h"
#include "glmLabelManager.h"

#include <memory>

class glmGeometryBuilder {
public:
    
    glmGeometryBuilder();
    virtual ~glmGeometryBuilder();
    
    static glmGeometryBuilder* GetInstance() {
        static glmGeometryBuilder *instance = new glmGeometryBuilder();
        return instance;
    }
    
    //  Setting up
    //
    void setOffset(glm::vec3 _center);
    void setOffset(int _tileX, int _tileY, int _zoom);
    void setLabelManager(glmLabelManager *_lm);

    //  Loading the data
    //
    void load(int _tileX, int _tileY, int _zoom, glmTile &_tile);
    void load(Json::Value &_jsonRoot, glmTile &_tile);
    glmTile getFromFile(std::string _fileName);
    glmTile getFromWeb(int _tileX, int _tileY, int _zoom);
    
    glm::vec3 getOffset();
    
    void mergeFeature(const glmFeatureRef &_father, const glmFeatureRef &_child);
    void deleteFeature( glmTile &_tile, const std::string &_idString );
    
    std::map< std::string, glm::vec4 > LayerColorPalette;
    
    float lineWidth;
    
private:
    
    void buildLayer(Json::Value &_jsonRoot, const std::string &_layerName, glmTile &_tile, float _minHeight = 0.);
    
    //  Mesh constructors
    //
    void lineJson2Polyline(Json::Value &_lineJson, glmPolyline &_poly, float _minHeight = 0.);
    void pointJson2Mesh(Json::Value &_lineJson, glmMesh &_mesh, float _radius, int _sides = 6, float _minHeight = 0.);
    void polygonJson2Mesh(Json::Value &_polygonJson, glmMesh &_mesh, float _minHeight, float _height);
    
    glm::vec3 m_geometryOffset;
    
    glmLabelManager *labelManager;
};