//
//  glmMesh.h
//
//  Created by Patricio Gonzalez Vivo on 8/22/14.
//  Inspired by: https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/3d/ofMesh.h
//

#pragma once

#include "glmTools.h"
#include "glmPolyline.h"

class glmMesh {
public:
    
    glmMesh();
    glmMesh(const glmMesh &_mother);
    glmMesh(const glmPolyline &_poly);
    glmMesh(const std::vector<glmPolyline> &_polylines);
    glmMesh(const glmPolyline &_line, float _lineWidth);
    
    virtual ~glmMesh();
    
    void    setDrawMode(GLenum _drawMode);
    
    void    setColor(const glm::vec4 &_color);
    void    addColor(const glm::vec4 &_color);
    void    addColors(const std::vector<glm::vec4> &_colors);
    
    void    addVertex(const glm::vec3 &_point);
    void    addVertices(const std::vector<glm::vec3>& _verts);
    void    addVertices(const glm::vec3* _verts, int _amt);
    
    void    addNormal(const glm::vec3 &_normal);
    void    addNormals(const std::vector<glm::vec3> &_normals );
    
    void    addTexCoord(const glm::vec2 &_uv);
    void    addTexCoords(const std::vector<glm::vec2> &_uvs);
    
    void    addIndex(uint16_t _i);
    void    addIndices(const std::vector<uint16_t>& _inds);
    void    addIndices(const uint16_t* _inds, int _amt);
    
    void    addTriangle(uint16_t index1, uint16_t index2, uint16_t index3);
    
    void    add(const glmMesh &_mesh);
    void    add(const glmPolyline &_polyline);                      // Close Shape
    void    add(const std::vector<glmPolyline> &_polylines );       // Close Shape with holes
    void    add(const glmPolyline &_polyline, float _lineWidth);    // Lines
    
    GLenum  getDrawMode() const;
    
    const std::vector<glm::vec4> & getColors() const;
    const std::vector<glm::vec3> & getVertices() const;
    const std::vector<glm::vec3> & getNormals() const;
    const std::vector<glm::vec2> & getTexCoords() const;
    const std::vector<uint16_t>  & getIndices() const;
    
    void    save(std::string _path, bool useBinary = false) const;
    void    clear();
    void    draw();
    
private:
    std::vector<glm::vec4>  m_colors;
    std::vector<glm::vec3>  m_vertices;
    std::vector<glm::vec3>  m_normals;
    std::vector<glm::vec2>  m_texCoords;
    std::vector<uint16_t>   m_indices;
    
    GLenum  m_drawMode;
};