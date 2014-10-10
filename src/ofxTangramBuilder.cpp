//
//  ofxTangramBuilder.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxTangramBuilder.h"

#include "ofxGlm.h"

ofxTangramBuilder::ofxTangramBuilder():bFirst(true){

}

ofxTangramBuilder::~ofxTangramBuilder(){
    
}

ofPoint ofxTangramBuilder::getOffset(){
    return toOf(m_geometryOffset);
}

ofxTangramTile ofxTangramBuilder::getFromWeb(int _tileX, int _tileY, int _zoom){
    if(bFirst){
        glmGeometryBuilder::setOffset(_tileX,_tileY,_zoom);
        bFirst = false;
    }
    
    ofxTangramTile tile;
    glmGeometryBuilder::load(_tileX,_tileY,_zoom,tile);
    
    return tile;
}