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

typedef enum{
    kTileColorModePlain,
    kTileColorModeMixed,
}TileColorMode;

class GLTile {
public:
    //tile properties
    vec3 origin;
    float tileSize;
    vector<Vertex> vertices;
    GLTopology topology;   //indicates the openGLTopology to draw the tile in
    vector<char> vertexIndices;
    TileColorMode colorMode;   //indicates the mode of coloring of vertices
    bool needsVertexData;  
    Vertex firstVertex , secondVertex , thirdVertex , fourthVertex;
    struct GLTile* makeTile();
    void setColorMode(TileColorMode argMode);
    GLTile createPlainTile(float size, vec4 color , GLTopology argTopology);
    GLTile createTileWithMixedColor(float tileSize, vector<vec4> vertexColors, GLTopology topology);
    void setOrigin(vec3 origin);
    void setNeedsVertexData(bool needsData);
    

    ~GLTile();
private:
    void setVertices(float size , vector<vec4> colors);
    void setNullVertices();
    void reloadVertexData();
    Vertex vertexMake(vec3 position, vec4 color);
    
    
};


#endif /* defined(__Incantor__GLTile__) */
