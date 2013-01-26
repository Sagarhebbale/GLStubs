//
//  GLMacros.h
//  Incantor
//
//  Created by Sagar on 11/26/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef Incantor_GLMacros_h
#define Incantor_GLMacros_h
#define NULL_VERTEX vertexMake(vec3(0,0,0) , vec4(0,0,0,0));
#define SCREEN_LEFTBOUNDS -4.2
#define SCREEN_RIGHTBOUNDS 4.2
#define SCREEN_TOPBOUNDS 6.25
#define SCREEN_BOTTOMBOUNDS -6.25

#define MAP_REQUEST_BASE_URL @"http://a.tiles.mapbox.com/v3/sagar.map-fmc0olbz/"


typedef enum{
    kGLTriangleStrip = 0,
    kGLTrianles,
    KGLTriangleFan,
    
}GLTopology;

typedef struct {
    double latitude;
    double longitude;
    float zoomLevel;
    
} MapTileParams;



#endif
