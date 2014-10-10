//
//  glmMesh.cpp
//
//  Created by Patricio Gonzalez Vivo on 8/22/14.
//
//

#include "glmMesh.h"

#include <fstream>
#include <iostream>

#include "tesselator.h"

glmMesh::glmMesh():m_drawMode(GL_TRIANGLES){
    
}

glmMesh::glmMesh(const glmMesh &_mother):m_drawMode(_mother.getDrawMode()){
    add(_mother);
}

glmMesh::glmMesh(const glmPolyline &_poly):m_drawMode(GL_TRIANGLES){
    add(_poly);
}

glmMesh::glmMesh(const std::vector<glmPolyline> &_polylines):m_drawMode(GL_TRIANGLES){
    add(_polylines);
}

glmMesh::glmMesh(const glmPolyline &_line, float _lineWidth):m_drawMode(GL_TRIANGLES){
    add(_line,_lineWidth);
}

glmMesh::~glmMesh(){
    
}

void glmMesh::setDrawMode(GLenum _drawMode){
    m_drawMode = _drawMode;
}

void glmMesh::setColor(const glm::vec4 &_color){
    m_colors.clear();
    for (int i = 0; i < m_vertices.size(); i++) {
        m_colors.push_back(_color);
    }
}

void glmMesh::addColor(const glm::vec4 &_color){
    m_colors.push_back(_color);
}

void glmMesh::addColors(const std::vector<glm::vec4> &_colors){
    m_colors.insert(m_colors.end(), _colors.begin(), _colors.end());
}

void glmMesh::addVertex(const glm::vec3 &_point){
   m_vertices.push_back(_point);
}

void glmMesh::addVertices(const std::vector<glm::vec3>& _verts){
   m_vertices.insert(m_vertices.end(),_verts.begin(),_verts.end());
}

void glmMesh::addVertices(const glm::vec3* verts, int amt){
   m_vertices.insert(m_vertices.end(),verts,verts+amt);
}

void glmMesh::addNormal(const glm::vec3 &_normal){
    m_normals.push_back(_normal);
}

void glmMesh::addNormals(const std::vector<glm::vec3> &_normals ){
    m_normals.insert(m_normals.end(), _normals.begin(), _normals.end());
}

void glmMesh::addTexCoord(const glm::vec2 &_uv){
    m_texCoords.push_back(_uv);
}

void glmMesh::addTexCoords(const std::vector<glm::vec2> &_uvs){
    m_texCoords.insert(m_texCoords.end(), _uvs.begin(), _uvs.end());
}

void glmMesh::addIndex(uint16_t _i){
    m_indices.push_back(_i);
}

void glmMesh::addIndices(const std::vector<uint16_t>& inds){
	m_indices.insert(m_indices.end(),inds.begin(),inds.end());
}

void glmMesh::addIndices(const uint16_t* inds, int amt){
	m_indices.insert(m_indices.end(),inds,inds+amt);
}

void glmMesh::addTriangle(uint16_t index1, uint16_t index2, uint16_t index3){
    addIndex(index1);
    addIndex(index2);
    addIndex(index3);
}

void glmMesh::add(const glmMesh &_mesh){
    
    if(_mesh.getDrawMode() != m_drawMode){
        std::cout << "INCOMPATIBLE DRAW MODES" << std::endl;
        return;
    }
    
    uint16_t indexOffset = (uint16_t)getVertices().size();
    
    addColors(_mesh.getColors());
    addVertices(_mesh.getVertices());
    addNormals(_mesh.getNormals());
    addTexCoords(_mesh.getTexCoords());
    
    for (int i = 0; i < _mesh.getIndices().size(); i++) {
        addIndex(indexOffset+_mesh.getIndices()[i]);
    }
}

void glmMesh::add(const glmPolyline &_polyline){
    TESStesselator *m_tess = tessNewTess(NULL);
    
    uint16_t indexOffset = (uint16_t)m_vertices.size();
    glmRectangle bBox = _polyline.getBoundingBox();
    
    for (int i = 0; i < _polyline.size(); i++) {
        // Add contour to tesselator
        tessAddContour(m_tess, 3, &_polyline.getVertices()[0].x, sizeof(glm::vec3), _polyline.size());
    }
    
    if(m_drawMode == GL_TRIANGLES){
        // Tessellate polygon into triangles
        tessTesselate(m_tess, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 3, NULL);
        
        // Extract triangle elements from tessellator
        
        const int numIndices = tessGetElementCount(m_tess);
        const TESSindex* indices = tessGetElements(m_tess);
        
        for (int i = 0; i < numIndices; i++) {
            const TESSindex* poly = &indices[i*3];
            for (int j = 0; j < 3; j++) {
                addIndex(poly[j] + indexOffset);
            }
        }
        
        const int numVertices = tessGetVertexCount(m_tess);
        const float* vertices = tessGetVertices(m_tess);
        for (int i = 0; i < numVertices; i++) {
            
            addTexCoord(glm::vec2(mapValue(vertices[3*i],bBox.getMinX(),bBox.getMaxX(),0.,1.),
                                  mapValue(vertices[3*i+1],bBox.getMinY(),bBox.getMaxY(),0.,1.)));
            addNormal(UP_NORMAL);
            addVertex(glm::vec3(vertices[3*i], vertices[3*i + 1], vertices[3*i + 2]));
        }
        
    } else if(m_drawMode == GL_TRIANGLE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_LINES){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }  else if(m_drawMode == GL_LINE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_POINTS){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else {
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }
    
    tessDeleteTess(m_tess);
}

void glmMesh::add(const std::vector<glmPolyline> &_polylines){
    TESStesselator  *m_tess = tessNewTess(NULL);            // Tesselator instance
    uint16_t indexOffset = (uint16_t)m_vertices.size();    // track indices
    
    glmRectangle bBox;  // this will calculate the total bounding box to compute a UV for top the top view
    
    //  Go through the Json polygons making walls and adding it to the tessalator
    //
    for (int i = 0; i < _polylines.size(); i++) {
        
        //  Grow  bounding box
        //
        bBox.growToInclude(_polylines[i].getVertices());
        //  Add to tesselator
        tessAddContour(m_tess, 3, &_polylines[i].getVertices()[0].x, sizeof(glm::vec3), _polylines[i].size());
    }
    
    if(m_drawMode == GL_TRIANGLES){
        // Tessellate polygon into triangles
        tessTesselate(m_tess, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 3, NULL);
        
        // Extract triangle elements from tessellator
        const int numIndices = tessGetElementCount(m_tess);
        const TESSindex* indices = tessGetElements(m_tess);
        for (int i = 0; i < numIndices; i++) {
            const TESSindex* poly = &indices[i*3];
            for (int j = 0; j < 3; j++) {
                addIndex(poly[j] + indexOffset);
            }
        }
        
        //  Add vertexes from tessellator
        //
        const int numVertices = tessGetVertexCount(m_tess);
        const float* vertices = tessGetVertices(m_tess);
        for (int i = 0; i < numVertices; i++) {
            addTexCoord(glm::vec2(mapValue(vertices[3*i],bBox.getMinX(),bBox.getMaxX(),0.,1.),
                                  mapValue(vertices[3*i+1],bBox.getMinY(),bBox.getMaxY(),0.,1.)));
            addNormal(UP_NORMAL);
            addVertex(glm::vec3(vertices[3*i], vertices[3*i + 1], vertices[3*i + 2]));
        }
    } else if(m_drawMode == GL_TRIANGLE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_LINES){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }  else if(m_drawMode == GL_LINE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_POINTS){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else {
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }
    
    tessDeleteTess(m_tess);
}


//  http://artgrammer.blogspot.co.uk/2011/07/drawing-polylines-by-tessellation.html
//  https://www.mapbox.com/blog/drawing-antialiased-lines/
//
void glmMesh::add(const glmPolyline &_polyline, float _lineWidth){
    uint16_t indexOffset = (uint16_t)m_vertices.size();
    
    glm::vec3 normi;             // Right normal to segment between previous and current m_points
    glm::vec3 normip1;           // Right normal to segment between current and next m_points
    glm::vec3 rightNorm;         // Right "normal" at current point, scaled for miter joint
    
    glm::vec3 im1;                   // Previous point coordinates
    glm::vec3 i0 = _polyline[0];    // Current point coordinates
    glm::vec3 ip1 = _polyline[1];   // Next point coordinates
    
    normip1.x = ip1.y - i0.y;
    normip1.y = i0.x - ip1.x;
    normip1.z = 0.;
    
    normip1 = glm::normalize(normip1);
    
    rightNorm = glm::vec3(normip1.x*_lineWidth,normip1.y*_lineWidth,normip1.z*_lineWidth);
    
    addVertex(i0 + rightNorm);
    addNormal(UP_NORMAL);
    addTexCoord(glm::vec2(1.0,0.0));
    
    addVertex(i0 - rightNorm);
    addNormal(UP_NORMAL);
    addTexCoord(glm::vec2(0.0,0.0));
    
    // Loop over intermediate m_points in the polyline
    //
    for (int i = 1; i < _polyline.size() - 1; i++) {
        im1 = i0;
        i0 = ip1;
        ip1 = _polyline[i+1];
        
        normi = normip1;
        normip1.x = ip1.y - i0.y;
        normip1.y = i0.x - ip1.x;
        normip1.z = 0.0f;
        normip1 = glm::normalize(normip1);
        
        rightNorm = normi + normip1;
        float scale = sqrtf(2. / (1. + glm::dot(normi,normip1) )) * _lineWidth / 2.;
        rightNorm *= scale;
        
        addVertex(i0+rightNorm);
        addNormal(UP_NORMAL);
        addTexCoord(glm::vec2(1.0,(float)i/(float)_polyline.size()));
        
        addVertex(i0-rightNorm);
        addNormal(UP_NORMAL);
        addTexCoord(glm::vec2(0.0,(float)i/(float)_polyline.size()));
        
    }
    
    normip1 *= _lineWidth;
    
    addVertex(ip1 + normip1);
    addNormal(UP_NORMAL);
    addTexCoord(glm::vec2(1.0,1.0));
    
    addVertex(ip1 - normip1);
    addNormal(UP_NORMAL);
    addTexCoord(glm::vec2(0.0,1.0));
    
    if (m_drawMode == GL_TRIANGLES){
        for (int i = 0; i < _polyline.size() - 1; i++) {
            addIndex(indexOffset + 2*i+3);
            addIndex(indexOffset + 2*i+2);
            addIndex(indexOffset + 2*i);
            
            addIndex(indexOffset + 2*i);
            addIndex(indexOffset + 2*i+1);
            addIndex(indexOffset + 2*i+3);
        }
    } else if(m_drawMode == GL_TRIANGLE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_LINES){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }  else if(m_drawMode == GL_LINE_STRIP){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else if(m_drawMode == GL_POINTS){
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    } else {
        //  TODO
        //
        std::cout << "ERROR: glmMesh only add GL_TRIANGLES for NOW !!" << std::endl;
    }
}

GLenum glmMesh::getDrawMode() const{
    return m_drawMode;
}

const std::vector<glm::vec4> & glmMesh::getColors() const{
    return m_colors;
}

const std::vector<glm::vec3> & glmMesh::getVertices() const{
	return m_vertices;
}

const std::vector<glm::vec3> & glmMesh::getNormals() const{
    return m_normals;
}

const std::vector<glm::vec2> & glmMesh::getTexCoords() const{
    return m_texCoords;
}

const std::vector<glm::uint16_t> & glmMesh::getIndices() const{
    return m_indices;
}

void glmMesh::clear(){
    if(!m_vertices.empty()){
		m_vertices.clear();
	}
	if(!m_colors.empty()){
		m_colors.clear();
	}
	if(!m_normals.empty()){
		m_normals.clear();
	}
    if(!m_indices.empty()){
		m_indices.clear();
	}

}

void glmMesh::draw(){
    if(m_vertices.size()){
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), &m_vertices[0].x);
	}
	if(m_normals.size()){
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(glm::vec3), &m_normals[0].x);
	}
	if(m_colors.size()){
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT, sizeof(glm::vec4), &m_colors[0].x);
	}
    if(m_texCoords.size()){
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec2), &m_texCoords[0].x);
	}

    if(m_indices.size()){
        glDrawElements(m_drawMode, m_indices.size(),GL_UNSIGNED_SHORT,&m_indices[0]);
    }else{
        glDrawArrays(m_drawMode, 0, m_vertices.size());
    }
    
    if(m_texCoords.size()){
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	if(m_colors.size()){
		glDisableClientState(GL_COLOR_ARRAY);
	}
	if(m_normals.size()){
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void glmMesh::save(std::string _path, bool _useBinary ) const{
    
    std::ios_base::openmode binary_mode = _useBinary ? std::ios::binary : (std::ios_base::openmode)0;
    std::fstream os(_path.c_str(), std::ios::out | binary_mode);
    
	os << "ply" << std::endl;
	if(_useBinary) {
		os << "format binary_little_endian 1.0" << std::endl;
	} else {
		os << "format ascii 1.0" << std::endl;
	}
    
	if(m_vertices.size()){
		os << "element vertex " << m_vertices.size() << std::endl;
		os << "property float x" << std::endl;
		os << "property float y" << std::endl;
		os << "property float z" << std::endl;
		if(m_colors.size()){
			os << "property uchar red" << std::endl;
			os << "property uchar green" << std::endl;
			os << "property uchar blue" << std::endl;
			os << "property uchar alpha" << std::endl;
		}
		if(m_texCoords.size()){
			os << "property float u" << std::endl;
			os << "property float v" << std::endl;
		}
		if(m_normals.size()){
			os << "property float nx" << std::endl;
			os << "property float ny" << std::endl;
			os << "property float nz" << std::endl;
		}
	}
    
	unsigned char faceSize = 3;
	if(m_indices.size()){
		os << "element face " << m_indices.size() / faceSize << std::endl;
		os << "property list uchar int vertex_indices" << std::endl;
	} else if(m_drawMode == GL_TRIANGLES) {
		os << "element face " << m_indices.size() / faceSize << std::endl;
		os << "property list uchar int vertex_indices" << std::endl;
	}
    
	os << "end_header" << std::endl;
    
	for(int i = 0; i < m_vertices.size(); i++){
		if(_useBinary) {
			os.write((char*) &m_vertices[i], sizeof(glm::vec3));
		} else {
			os << m_vertices[i].x << " " << m_vertices[i].y << " " << m_vertices[i].z;
		}
		if(m_colors.size()){
			// VCG lib / MeshLab don't support float colors, so we have to cast
            glm::vec4 c = m_colors[i] * glm::vec4(255,255,255,255);
            glm::ivec4 cur = glm::ivec4(c.r,c.g,c.b,c.a);
			if(_useBinary) {
				os.write((char*) &cur, sizeof(glm::ivec4));
			} else {
				os << " " << (int) cur.r << " " << (int) cur.g << " " << (int) cur.b << " " << (int) cur.a;
			}
		}
		if(m_texCoords.size()){
			if(_useBinary) {
				os.write((char*) &m_texCoords[i], sizeof(glm::vec2));
			} else {
				os << " " << m_texCoords[i].x << " " << m_texCoords[i].y;
			}
		}
		if(m_normals.size()){
            glm::vec3 norm = glm::normalize(m_normals[i]);
			if(_useBinary) {
				os.write((char*) &norm, sizeof(glm::vec3));
			} else {
				os << " " << norm.x << " " << norm.y << " " << norm.z;
			}
		}
		if(!_useBinary) {
			os << std::endl;
		}
	}
    
	if(m_indices.size()) {
		for(int i = 0; i < m_indices.size(); i += faceSize) {
			if(_useBinary) {
				os.write((char*) &faceSize, sizeof(unsigned char));
				for(int j = 0; j < faceSize; j++) {
					int curIndex = m_indices[i + j];
					os.write((char*) &curIndex, sizeof(int));
				}
			} else {
				os << (int) faceSize << " " << m_indices[i] << " " << m_indices[i+1] << " " << m_indices[i+2] << std::endl;
			}
		}
	} else if(m_drawMode == GL_TRIANGLES) {
		for(int i = 0; i < m_vertices.size(); i += faceSize) {
			int indices[] = {i, i + 1, i + 2};
			if(_useBinary) {
				os.write((char*) &faceSize, sizeof(unsigned char));
				for(int j = 0; j < faceSize; j++) {
					os.write((char*) &indices[j], sizeof(int));
				}
			} else {
				os << (int) faceSize << " " << indices[0] << " " << indices[1] << " " << indices[2] << std::endl;
			}
		}
	}
    
    os.close();
}