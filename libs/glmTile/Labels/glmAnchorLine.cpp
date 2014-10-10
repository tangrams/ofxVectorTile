//
//  glmAnchorLine.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/26/14.
//
//

#include "glmAnchorLine.h"

glmAnchorLine::glmAnchorLine():originalCentroid(0.0,0.0,0.0),bLetterByLetter(false){
};

void glmAnchorLine::clear(){
    glmFastPolyline::clear();
    marks.clear();
}