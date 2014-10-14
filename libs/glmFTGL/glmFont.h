//
//  glmFont.h
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//
#pragma once

#include <vector>
#include <tr1/memory>

#include "ftgl.h"
#include "glm/glm.hpp"

#include "glmRectangle.h"
#include "glfontstash.h"

#define GLFONTSTASH

class glmFont {
public:
    
    glmFont();
    virtual ~glmFont();
    
    void unload();
    bool loadFont(std::string filename, float fontsize, float depth = 0, bool bUsePolygons = false);
    bool isLoaded();
    
    void setSize(int size);
    int getSize();
    
    float getLineHeight() const;
    float getAscender() const;
    float getDescender() const;
    float getXHeight() const;
    
    glmRectangle getStringBoundingBox(const std::wstring &_s);
    glmRectangle getStringBoundingBox(const std::string &_s);
    float stringHeight(const std::string &_c);
    float stringWidth(const std::string &_c);
    float getSpaceSize();
    
    void drawString(const std::string &_s, float _alpha );
    void drawString(const std::string &_s, const glm::vec3 &_pos, float _alpha );
    void drawString(const std::string &_s, const glmRectangle &_rect, float _alpha);

#ifdef GLFONTSTASH
    void drawString(const std::string &_s, unsigned int _id, float _alpha);
    void drawString(const std::string &_s, unsigned int _id, const glm::vec3 &_pos, float _alpha);
    void drawString(const std::string &_s, unsigned int _id, const glmRectangle &_rect, float _alpha);
    
    FONScontext* getContext() const;
#endif
    
    glm::vec3   colorBack;
    glm::vec3   colorFront;
    
protected:
    FTFont* m_font;
    FTFont* m_outlineFont;
    bool    m_bLoaded;
    
#ifdef GLFONTSTASH
    FONScontext* m_fs;
    int          m_fontNormal;
#endif
};

typedef std::tr1::shared_ptr<glmFont> glmFontRef;