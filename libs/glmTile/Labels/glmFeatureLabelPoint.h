//
//  glmFeatureLabelPoint.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#pragma once

#include "glmFeatureLabel.h"

class glmFeatureLabelPoint : public glmFeatureLabel{
public:
    
    glmFeatureLabelPoint();
    glmFeatureLabelPoint(const std::string &_text);
    virtual ~glmFeatureLabelPoint();
    
    void    setPosition(const glm::vec3 &_pos);
    void    setLabelAngle(const double &_radiant);
    void    setLabelMargin(const float &_margin);
    
    glm::vec3 getScreenPosition() const;
    
    glmRectangle getLabel( const float &_marign ) const;
    glm::vec3    getAnchorPoint() const;
    
    bool    isOver(const glmFeatureLabelPoint *_other, float _margin);
    bool    isInside(const glm::vec3 &_point);
    
    void    update();
    void    draw2D();
    void    draw3D();

    void    drawDebug();
    
    glm::vec3   m_offset;
    glm::vec3   m_centroid;
    glm::vec3   m_anchorPoint;
    glm::vec3   m_projectedCentroid;
    
protected:
    void    updateCached();
    
    glmMesh m_line;
    
    double  m_angle;
    float   m_margin;
};

typedef std::tr1::shared_ptr<glmFeatureLabelPoint> glmFeatureLabelPointRef;