//
//  ofxGlm.h
//
//  A wrapper for OpenFrameworks
//
//  Created by Patricio Gonzalez Vivo on 8/25/14.
//

#pragma once

#include "ofMain.h"

static ofFloatColor toOf(const glm::vec4 &_v){
    return ofFloatColor(_v.x,_v.y,_v.z,_v.w);
}

static ofVec3f toOf(const glm::vec3 &_v){
    return ofVec3f(_v.x,_v.y,_v.z);
}

static ofVec2f toOf(const glm::vec2 &_v){
    return ofVec2f(_v.x,_v.y);
}

static ofIndexType toOf(const uint16_t &_i){
    return ofIndexType(_i);
}

static ofMesh toOf(const glmMesh &_mesh){
    ofMesh mesh;
    
    for (auto &it : _mesh.getColors()) {
        mesh.addColor(toOf(it));
    }
    
    for (auto &it : _mesh.getVertices()) {
        mesh.addVertex(toOf(it));
    }
    
    for (auto &it : _mesh.getNormals()) {
        mesh.addNormal(toOf(it));
    }
    
    for (auto &it : _mesh.getTexCoords()) {
        mesh.addTexCoord(toOf(it));
    }
    
    for (auto &it : _mesh.getIndices()) {
        mesh.addIndex(toOf(it));
    }
    
    mesh.setMode(ofGetOFPrimitiveMode(_mesh.getDrawMode()));
    
    return mesh;
}

static glm::vec4 toGlm(const ofFloatColor &_v){
    return glm::vec4(_v.r,_v.g,_v.b,_v.a);
}

static glm::vec4 toGlm(const ofVec4f &_v){
    return glm::vec4(_v.x,_v.y,_v.z,_v.w);
}

static glm::vec3 toGlm(const ofVec3f &_v){
    return glm::vec3(_v.x,_v.y,_v.z);
}

static glm::vec2 toGlm(const ofVec2f &_v){
    return glm::vec2(_v.x,_v.y);
}

static uint16_t toGlm(const ofIndexType &_i){
    return uint16_t(_i);
}