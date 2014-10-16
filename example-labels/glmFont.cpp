//
//  glmFont.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFont.h"

#define GLFONTSTASH_IMPLEMENTATION
#include "glfontstash.h"

glmFont::glmFont(): m_bLoaded(false) {
    m_fs = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT);
}

glmFont::~glmFont(){
    unload();
}

void glmFont::unload(){
    m_bLoaded = false;
    
    glfonsDelete(m_fs);
}

bool glmFont::loadFont(std::string _filename, float _fontsize, float _depth, bool _bUsePolygons){
    _fontsize *= 2;

    std::string resourcePath = "../Resources/" + _filename;
    
    m_fontNormal = fonsAddFont(m_fs, "sans", resourcePath.c_str());
    if(m_fontNormal == FONS_INVALID) {
        printf("Could not add font normal.\n");
    }
    
    fonsSetSize(m_fs, _fontsize);
    fonsSetFont(m_fs, m_fontNormal);
    
    m_bLoaded = true;
    
    return true;
}

bool glmFont::isLoaded(){
    return m_bLoaded;
}

glmRectangle glmFont::getStringBoundingBox(unsigned int id) {
    if(m_bLoaded){
        glm::vec4 bbox;
        glfonsGetBBox(m_fs, id, &bbox[0], &bbox[1], &bbox[2], &bbox[3]);
        return glmRectangle(bbox);
    }
    return glmRectangle();
}

void glmFont::drawString(unsigned int _id, float _alpha) {
    glfonsSetColor(m_fs, 255, 255, 255, _alpha * 255);
    glfonsScale(m_fs, 1, -1);
    glfonsDrawText(m_fs, _id);
}

void glmFont::drawString(unsigned int _id, const glm::vec3 &_pos, float _alpha) {
    glfonsPushMatrix(m_fs);
    
    glfonsTranslate(m_fs, _pos.x, _pos.y);
    
    glfonsSetColor(m_fs, 255, 255, 255, _alpha * 255);
    glfonsDrawText(m_fs, _id);
    
    glfonsPopMatrix(m_fs);
}

void glmFont::drawString(unsigned int _id, const glmRectangle &_rect, float _alpha) {
    glm::vec3 p = _rect.getBottomLeft();
    glfonsPushMatrix(m_fs);
    
    glfonsTranslate(m_fs, p.x, p.y);
    
    glfonsSetColor(m_fs, 255, 255, 255, _alpha * 255);
    glfonsDrawText(m_fs, _id);
    
    glfonsPopMatrix(m_fs);
}

void glmFont::drawSubString(unsigned int _id, unsigned int _i, bool _offset, float _alpha) {
    if(!_offset) {
        // fix subuffer drawing by offseting by the position of the glyph
        // because the buffer contains the whole string
        float xglyphOffset = glfonsGetGlyphOffset(m_fs, _id, _i);
        glfonsTranslate(m_fs, -xglyphOffset, 0.0);
    }
    drawSubString(_id, _i, _i, _alpha);
}

void glmFont::drawSubString(unsigned int _id, unsigned int _from, unsigned int _to, float _alpha) {
    glfonsScale(m_fs, 1, -1);
    glfonsDrawText(m_fs, _id, _from, _to);
}

FONScontext* glmFont::getContext() const {
    return m_fs;
}