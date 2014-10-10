//
//  ofxVectorBuilder.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxVectorBuilder.h"

#include "ofxGlm.h"

ofxVectorBuilder::ofxVectorBuilder():bFirst(true){

}

ofxVectorBuilder::~ofxVectorBuilder(){
    
}

ofPoint ofxVectorBuilder::getOffset(){
    return toOf(m_geometryOffset);
}

ofxVectorTile ofxVectorBuilder::getFromWeb(int _tileX, int _tileY, int _zoom){
    if(bFirst){
        glmGeometryBuilder::setOffset(_tileX,_tileY,_zoom);
        bFirst = false;
    }
    
    ofxVectorTile tile;
    glmGeometryBuilder::load(_tileX,_tileY,_zoom,tile);
    
    return tile;
}