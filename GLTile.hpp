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
#include "GLMacros.h"

using namespace std;
#define defaultTileSize 20
#define defaultTilColor vec4(1,0,0,1)

class GLTile {
public:
    float tileSize;
    vec4 tileColor;
    vector<Vertex> tile;
    GLTopology topology;
    vector<char> vertexIndices;
    struct GLTile* makeTile();
    Vertex firstVertex , secondVertex , thirdVertex , fourthVertex;
    GLTile createTile(float size, vec4 color , GLTopology topology);
    GLTile setTileColor(GLTile tile , vec4 color);
    GLTile setTileOrigin(GLTile tile , vec3 origin);
    Vertex vertexMake(vec3 position, vec4 color);
    
    
   };


#endif /* defined(__Incantor__GLTile__) */
