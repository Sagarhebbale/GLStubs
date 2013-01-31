//
//  GLTile.h
//  Incantor
//
//  Created by Sagar on 11/14/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef __Incantor__GLTile__
#define __Incantor__GLTile__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <iostream>
#include "Vector.hpp"
#include "GLMath.hpp"
#include <vector>
#include "GLMacros.hpp"

using namespace std;
#define defaultTileSize 20
#define defaultTilColor vec4(1,0,0,1)
#define tileVertexCount 4;


class GLTile {
public:
    //tile properties
    vec3 origin;
    float tileWidth;
    float tileHeight;
    vector<Vertex> vertices;
    vector<Vertex> absVertices;
    GLTopology topology;   //indicates the openGLTopology to draw the tile in
    vector<char> vertexIndices;
   //indicates the mode of coloring of vertices
    bool needsVertexData;  
    Vertex firstVertex , secondVertex , thirdVertex , fourthVertex;
    struct GLTile* makeTile();
    GLTile createPlainTile(float size, vec4 color , GLTopology argTopology);
    void setOrigin(vec3 origin);
    void setNeedsVertexData(bool needsData);
    void createTile(float tileWidth, float tileHeight , vec4 color , GLTopology argTopology);
    void enableDataSource(bool isDataSource);
    ~GLTile();
private:
    void setVerticesForWidthAndHeight(float width , float height , vec4 color);
    void setNullVertices();
    void reloadVertexData();
    Vertex vertexMake(vec3 position, vec4 color);
    void setAbsVertices();
    
    
};


#endif /* defined(__Incantor__GLTile__) */
