//
//  glmFont.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFont.h"
glmFont::glmFont(): m_bLoaded(false), m_font(NULL), colorBack(0.,0.,0.), colorFront(1.,1.,1.) {
}

glmFont::~glmFont(){
//    unload();
}

void glmFont::unload(){
    if (m_font != NULL) {
        delete m_font;
        m_font = NULL;
    }
    
    m_bLoaded = false;
}

bool glmFont::loadFont(std::string _filename, float _fontsize, float _depth, bool _bUsePolygons){
    if (m_bLoaded) {
        unload();
    }
    
    _fontsize *= 2;
    
    if (_depth != 0) {
        m_font = new FTExtrudeFont(_filename.c_str());
        m_font->Depth(_depth);
    } else if (_bUsePolygons) {
        m_font = new FTPolygonFont(_filename.c_str());
    } else {
        m_font = new FTTextureFont(_filename.c_str());
    }
    
    m_outlineFont = new FTOutlineFont(_filename.c_str());
    
    m_font->CharMap(ft_encoding_unicode);
    m_outlineFont->CharMap(ft_encoding_unicode);
    m_outlineFont->Outset(1);
    
    if(m_font->Error()){
        std::cout << "Error loading font " << _filename << std::endl;
        delete m_font;
		return false;
    }
    
    if(!m_font->FaceSize(_fontsize)){
        std::cout << "Failed to set font size" << std::endl;
        delete m_font;
		return false;
    }
    
    if(!m_outlineFont->FaceSize(_fontsize)){
        std::cout << "Failed to set outline font size" << std::endl;
        delete m_outlineFont;
		return false;
    }
    
    m_bLoaded = true;
    return true;
}

float glmFont::getSpaceSize(){
	return stringWidth(" ");
}

float glmFont::stringWidth(const std::string &_c){
    if (_c.compare(" ") == 0) {
        // FTGL won't measure a space width properly, so we
        // have to use this hack to get that value.
        return (stringWidth("A A") - stringWidth("AA"));
    } else {
        glmRectangle rect = getStringBoundingBox(_c);
        return rect.width;
    }
}

float glmFont::stringHeight(const std::string &_c) {
    glmRectangle rect = getStringBoundingBox(_c);
    return rect.height;
}

bool glmFont::isLoaded(){
    return m_bLoaded;
}

void glmFont::setSize(int size){
    if(m_bLoaded){
	    m_font->FaceSize(size);
    }
}

int glmFont::getSize(){
	return m_font->FaceSize();
}


float glmFont::getLineHeight() const{
    if (m_bLoaded) {
        return m_font->LineHeight();
    }
    return 0;
}

float glmFont::getAscender() const{
    if (m_bLoaded) {
        return m_font->Ascender();
    }
    return 0;
}

float glmFont::getDescender() const{
    if (m_bLoaded) {
        return m_font->Descender();
    }
    return 0;
}

float glmFont::getXHeight() const{
    if (m_bLoaded) {
        return m_font->LineHeight() - m_font->Ascender() - m_font->Descender();
    }
    return 0;
}

glmRectangle glmFont::getStringBoundingBox(const std::string &_s){
    if(m_bLoaded){
    	FTBBox bbox = m_font->BBox(_s.c_str(), -1, FTPoint());
	    return glmRectangle(bbox.Lower().Xf(), bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return glmRectangle();
}

glmRectangle glmFont::getStringBoundingBox(const std::wstring &_s){
    if(m_bLoaded){
    	FTBBox bbox = m_font->BBox((wchar_t*)_s.c_str(), -1, FTPoint());
	    return glmRectangle(bbox.Lower().Xf(), bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return glmRectangle();
}

void glmFont::drawString(const std::string &_s, float _alpha){
    
    glLineWidth(2);
    glColor4f(colorBack.r,colorBack.g,colorBack.b, _alpha);
    m_outlineFont->Render(_s.c_str(), -1, FTPoint());
    glColor4f(colorFront.r,colorFront.g,colorFront.b, _alpha);
    m_font->Render(_s.c_str(), -1, FTPoint());
    glLineWidth(1);
    
}

void glmFont::drawString(const std::string &_s, const glm::vec3 &_pos, float _alpha){
    glPushMatrix();
    glTranslatef(_pos.x,_pos.y,_pos.z);
    glScalef(1,-1,1);
    
    drawString(_s, _alpha);
    
    glPopMatrix();
}

void glmFont::drawString(const std::string &_s, const glmRectangle &_rect, float _alpha){
    glPushMatrix();
    glm::vec3 p = _rect.getBottomLeft();
    glTranslatef(p.x,p.y,p.z);
    glScalef(1,-1,1);
    
    drawString(_s, _alpha);
    
    glPopMatrix();
}
