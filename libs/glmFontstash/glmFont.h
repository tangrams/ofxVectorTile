//
//  glmFont.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//
#pragma once

#include <vector>
#include <tr1/memory>

#include "glm/glm.hpp"

#include "glmRectangle.h"
#include "glfontstash.h"

class glmFont {
public:
    
    glmFont();
    virtual ~glmFont();
    
    void unload();
    bool loadFont(std::string filename, float fontsize, float depth = 0, bool bUsePolygons = false);
    bool isLoaded();

    glmRectangle getStringBoundingBox(unsigned int id);
    
    void drawString(unsigned int _id, float _alpha);
    void drawString(unsigned int _id, const glm::vec3 &_pos, float _alpha);
    void drawString(unsigned int _id, const glmRectangle &_rect, float _alpha);
    void drawSubString(unsigned int _id, unsigned int _i, bool _offset, float _alpha);
    void drawSubString(unsigned int _id, unsigned int _from, unsigned int _to, float _alpha);
    
    FONScontext* getContext() const;
    FONSeffectType getEffect() const;
    
    float getAscender() const;
    float getDescender() const;
    float getLineH() const;
    
protected:
    bool    m_bLoaded;
    
    FONScontext* m_fs;
    int          m_font;
    FONSeffectType m_effect;
    float m_ascender;
    float m_descender;
    float m_lineh;
};

typedef std::tr1::shared_ptr<glmFont> glmFontRef;