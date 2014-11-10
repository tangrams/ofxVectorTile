//
//  ofxVectorBuilder.cpp
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#include "ofxVectorBuilder.h"

#include "ofxGlm.h"
#include "ofxGlmTools.h"

ofxVectorBuilder::ofxVectorBuilder(){

}

ofxVectorBuilder::~ofxVectorBuilder(){
    
}

ofPoint ofxVectorBuilder::getOffset(){
    return toOf(glmGeometryBuilder::getOffset());
}

ofPoint ofxVectorBuilder::getPointAt(double _lat, double _lon, double _alt){
    return toOf(glmGeometryBuilder::getPointAt(_lat, _lon, _alt));
}

ofMesh ofxVectorBuilder::getMesh(int _tileX, int _tileY, int _zoom){
    return toOf( getFromWeb(_tileX, _tileY, _zoom).getMesh() );
}

ofMesh ofxVectorBuilder::getMesh(double _lat, double _lon, int _zoom){
    return toOf( getFromWeb(_lat,_lon,_zoom).getMesh() );
}
