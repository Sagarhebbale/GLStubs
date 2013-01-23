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

#define MAP_REQUEST_BASE_URL http://a.tiles.mapbox.com/v3/sagar.map-fmc0olbz/


typedef enum{
    kGLTriangleStrip = 0,
    kGLTrianles,
    KGLTriangleFan,
    
}GLTopology;

typedef struct {
    float latitude;
    float longitude;
    float zoomLevel;
    
} MapTileParams;

static void printVec4(vec4 vector){
    printf("/n MACRO DEBUG : Color   Red : %f Blue : %f Green :%f , Alpha : %f", vector.x , vector.y , vector.z, vector.w);
}


#endif
