//
//  GLPlane.h
//  Incantor
//
//  Created by Sagar on 11/28/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef __Incantor__GLPlane__
#define __Incantor__GLPlane__
#include "GLStrip.hpp"
#include <iostream>
#include <vector>

class GLPlane{
    public:
    GLPlane(float argWidth =0.0 , float argHeight =0.0)
    {
        planeHeight = argHeight;
        planeWidth = argWidth;
       }
    ~GLPlane(){
        free(&plane);
    }
    float planeWidth;
    float planeHeight;
    float tileSize;
    vector<GLStrip> plane;
    vector<char> stripIndices;
    GLPlane createPlaneAt(float argTileSize , vec2 origin);
};

#endif /* defined(__Incantor__GLPlane__) */
