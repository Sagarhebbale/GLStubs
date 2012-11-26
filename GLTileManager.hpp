//
//  GLTileManager.h
//  Incantor
//
//  Created by Sagar on 11/8/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef __Incantor__GLTileManager__
#define __Incantor__GLTileManager__

#include <iostream>
#include "Vector.hpp"
#include "GLTile.hpp"



using namespace std;


class GLTileManager{
    public :
        struct GLTileManager* createTileManager();
        void initialize(float argtileSize);
        vector<GLTile> createTileStrip(float stripWidth, vec2 origin);
        vector<vector<GLTile>> createPlane(vec2 origin, float width , float height);
        int tileCount;
    private :
       float tileSize;
       Vertex vertexMake(vec3 position, vec4 color);
    
};

#endif /* defined(__Incantor__GLTileManager__) */
