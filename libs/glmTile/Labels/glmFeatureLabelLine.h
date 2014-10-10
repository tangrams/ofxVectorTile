//
//  glmFeatureLabelLine.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#pragma once

#include "glmFeatureLabel.h"

#include "glmPolyline.h"
#include "glmAnchorLine.h"

#include "glmFeatureLabelPoint.h"

class glmFeatureLabelLine : public glmFeatureLabel{
public:
    
    glmFeatureLabelLine();
    glmFeatureLabelLine(const std::string &_text);
    virtual ~glmFeatureLabelLine();
    
    void    update();
    void    seedAnchorsEvery(glmAnchorLine &_anchorLine, float _minDistance, float _maxDistance);
    void    seedAnchorOnSegmentsAt(glmAnchorLine &_anchorLine, float _minDistance, float _maxDistance);
    
    void    draw2D();
    void    drawTextOn(glmAnchorLine &_anchorLine);
    void    drawDebug();

    std::vector<glmFeatureLabelPointRef> *pointLabels;
    
protected:
    void    updateCached();

    void    drawAllTextAtOnce( glmAnchorLine &_anchorLine);
    void    drawLetterByLetter( glmAnchorLine &_anchorLine);
    
    //  Text cached data
    std::vector<float> m_wordsWidth;
    std::vector<float> m_lettersWidth;
};

typedef std::tr1::shared_ptr<glmFeatureLabelLine> glmFeatureLabelLineRef;