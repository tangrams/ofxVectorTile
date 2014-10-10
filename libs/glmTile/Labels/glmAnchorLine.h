//
//  glmAnchorLine.h
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/26/14.
//
//

#pragma once

#include "glmFastPolyline.h"

struct AnchorMark {
    AnchorMark():m_pct(0),m_alpha(0.0){};
    AnchorMark(float _pct):m_pct(_pct),m_alpha(1.0){};
    
    float m_pct;
    float m_alpha;
};

class glmAnchorLine : public glmFastPolyline {
public:
    
    glmAnchorLine();
    
    void    clear();
    
    std::vector<AnchorMark> marks;
    glm::vec3   originalCentroid;
    bool        bLetterByLetter;
};