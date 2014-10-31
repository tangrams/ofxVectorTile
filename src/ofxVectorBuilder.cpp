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
    return toOf(glmGeometryBuilder::getOffset());
}

ofPoint ofxVectorBuilder::getPointAt(double _lat, double _lon, double _alt){
    return toOf(glmGeometryBuilder::getPointAt(_lat, _lon, _alt));
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

ofxVectorTile ofxVectorBuilder::getFromWeb(double _lat, double _lon, int _zoom){

    int tileX = long2tilex(_lon, _zoom);
    int tileY = lat2tiley(_lat, _zoom);
    
    if(bFirst){
        glmGeometryBuilder::setOffset(tileX,tileY,_zoom);
        bFirst = false;
    }
    
    ofxVectorTile tile;
    glmGeometryBuilder::load(tileX,tileY,_zoom,tile);
    
    return tile;
}