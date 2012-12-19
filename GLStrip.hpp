//
//  GLStrip.h
//  Incantor
//
//  Created by Sagar on 11/27/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef __Incantor__GLStrip__
#define __Incantor__GLStrip__
#include "GLTile.hpp"
#include <iostream>
#include <vector>

typedef enum{
    kStripOrientationVertical = 0,
    kStriporientationHorizontal,
}StripOrientation;

typedef enum{
    kmodeStripCount,
    kmodeStripWidth
}StripDrawMode;

class GLStrip{
    public :
    GLStrip(StripOrientation argOrientation = kStriporientationHorizontal , GLTopology argStripTopology = kGLTriangleStrip){
        orientation = argOrientation;
        stripTopology = argStripTopology;
        }
   
    vector<GLTile> tiles;
    vector<Vertex> vertices;
    vector<char> vertexIndices;
    vector<char> tileIndices;
    vec3 stripOrigin;
    float stripWidth;
    float tileSize;
    int tileCount;
    StripOrientation orientation;
    StripDrawMode drawMode;
    GLTopology stripTopology;
    TileColorMode tileColorMode;
    vec4 tileColor;
    vec4 altTileColor;
    vector<vec4> tileVertexColors;
    bool needsData;
    void setDrawMode(StripDrawMode argDrawMode);
    void setNeedsData(bool argNeedsData);
    void setStripCount(int count);
    void setStripWidth(float width);
    void setTileSize(float size);
    void setStriporigin(vec3 argOrigin);
    void setTileColorMode(TileColorMode argColorMode);
    GLStrip createTileStrip(float stripWidth, vec2 origin);
    private:
    void setStripForStripWidth();
    void setStripForStripCount();
    void setNullTiles();
    void setNullVertices();
    void draw();
    void setVertices();
    void setVertexIndices();
    void fillStripColors();
    void printVertices(vector<Vertex> vert);
    
    
};

#endif /* defined(__Incantor__GLStrip__) */
