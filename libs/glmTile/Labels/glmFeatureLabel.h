//
//  glmFeatureLabel.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#pragma once

#include "glmGL.h"
#include "glmGeom.h"
#include "glmString.h"

#include "glmFeature.h"
#include "glmFont.h"
#include "glmAnchorLine.h"
#include "glmRectangle.h"

class glmFeatureLabel : public glmFeature{
public:
    
    glmFeatureLabel();
    glmFeatureLabel(const std::string &_text);
    virtual ~glmFeatureLabel();
    
    void    setFont(glmFontRef &_fontRef);
    void    setCameraPos(glm::vec3 *_camPos);
    void    setText(const std::string &_text);
    
    std::string     getText();
    virtual void    draw2D() = 0;
    
    std::vector<glmAnchorLine> m_anchorLines;   // Use to mount the text
    glmRectangle    m_label;                    // Containg the text information
    
    bool    bVisible;
    
    unsigned int getId() const;
    
protected:
    virtual void updateCached() = 0;

    std::string m_text;
    glmFontRef  m_font;
    
    glm::vec3   *m_cameraPos;
    
    float       m_alpha;
    bool        m_bChanged;
    
    fsuint      m_fsid;
};

typedef std::tr1::shared_ptr<glmFeatureLabel> glmFeatureLabelRef;