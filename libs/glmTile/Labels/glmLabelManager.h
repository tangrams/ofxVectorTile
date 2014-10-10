//
//  glmLabelManager.h
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/4/14.
//
//

#pragma once

#include "glmFont.h"

#include "glmTile.h"
#include "glmFeatureLabelLine.h"
#include "glmFeatureLabelPoint.h"
#include "glmVectorField.h"

class glmLabelManager {
public:
    
    glmLabelManager();
    virtual ~glmLabelManager();
    
    void setFont(glmFont *_font);
    void setFont(glmFontRef &_font);
    
    glmFontRef& getFont();
    
    void addLineLabel( glmFeatureLabelLineRef &_lineLabel );
    void addPointLabel( glmFeatureLabelPointRef &_pointLabel );
    
    bool deleteLabel(const std::string &_idString);
    
    void mergLineLabels( glmFeatureLabelLineRef &_father, glmFeatureLabelLineRef &_child );
    void mergePointLabels( glmFeatureLabelPointRef &_father, glmFeatureLabelPointRef &_child);
    
    void updateFont();
    void updateProjection();
    void updateCameraPosition( const glm::vec3 &_pos );
    void updateOcclusions(float *_depthBuffer, int _width, int _height);
    
    void draw2D();
    void draw3D();

    std::vector<glmFeatureLabelLineRef> lineLabels;
    std::vector<glmFeatureLabelPointRef> pointLabels;
    
    float   minDistance, maxDistance;
    
    bool    bLines;
    bool    bPoints;
    
    bool    bUpdateSegments;
    
    bool    bDebugLines;
    bool    bDebugPoints;
    bool    bDebugGrid;
    bool    bDebugField;
    
private:
    
    glmFontRef  m_font;
    glmVectorField m_field;
    
    glm::ivec4  m_viewport;
    glm::vec3   m_cameraPos;
    
    bool    m_bFontChanged;
    bool    m_bProjectionChanged;
    bool    m_bChange;
};