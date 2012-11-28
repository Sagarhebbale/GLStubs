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

class GLStrip{
    public :
    GLStrip(StripOrientation argOrientation = kStriporientationHorizontal , float width = 10 , GLTopology argStripTopology = kGLTriangleStrip){
        
        orientation = argOrientation;
        width = stripWidth;
        stripTopology = argStripTopology;
    }
    ~GLStrip(){
        free(&tileStrip);
        }
    vector<GLTile> tileStrip;
    vector<char> tileIndicesInStrip;
    static int stripCount;
    float stripWidth;
    float tileSize;
    StripOrientation orientation;
    GLTopology stripTopology;
    GLStrip createTileStrip(float stripWidth, vec2 origin);
    private:
    float numberOfTiles;
    
};

#endif /* defined(__Incantor__GLStrip__) */
