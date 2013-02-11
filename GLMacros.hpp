//
//  GLMacros.h
//  Incantor
//
//  Created by Sagar on 11/26/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef Incantor_GLMacros_h
#define Incantor_GLMacros_h
#define SCREEN_X_RES 320
#define SCREEN_Y_RES 480
#define NULL_VERTEX vertexMake(vec3(0,0,0) , vec4(0,0,0,0));
#define SCREEN_LEFTBOUNDS -4.2
#define SCREEN_RIGHTBOUNDS 4.2
#define SCREEN_TOPBOUNDS 6.25
#define SCREEN_BOTTOMBOUNDS -6.25
#define SREEN_INTO_BOUNDS -10
#define SCREEN_OUT_BOUNDS 10
#define NORM_X_BOUNDS 1
#define NORM_Y_BOUNDS 1.48
#define TILE_WIDTH 120
#define TILE_HEIGHT 120*1.66
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

typedef struct{
    float x;
    float y;
    float z;
} AbsPosition;

static inline AbsPosition getAbsPosForScreenCoords(float x , float y , float z){
    AbsPosition absPos;
    float openGLX , openGLY;
    openGLX = x * (2*SCREEN_RIGHTBOUNDS)/SCREEN_X_RES;
    openGLY = y * (2*SCREEN_TOPBOUNDS)/SCREEN_Y_RES;
    
    if(x >= SCREEN_X_RES/2 && y <= SCREEN_Y_RES/2){
            absPos.x =  openGLX - SCREEN_RIGHTBOUNDS ;
            absPos.y = -openGLY + SCREEN_TOPBOUNDS;
        }
    if(x < SCREEN_X_RES/2 && y <= SCREEN_Y_RES/2){
            absPos.x = SCREEN_LEFTBOUNDS + openGLX;
            absPos.y = -openGLY + SCREEN_TOPBOUNDS;
        }
        
    if(x < SCREEN_X_RES/2 && y > SCREEN_Y_RES/2){
           absPos.x = -SCREEN_LEFTBOUNDS + openGLX;
           absPos.y = -(SCREEN_BOTTOMBOUNDS + openGLY);
        }
        
    if(x >= SCREEN_X_RES/2 && y > SCREEN_Y_RES/2){
             absPos.x =  openGLX - SCREEN_RIGHTBOUNDS;
             absPos.y = -(SCREEN_BOTTOMBOUNDS + openGLY);
        }

    
    if(x == 0)
        absPos.x = SCREEN_LEFTBOUNDS;
    if(y == 0)
        absPos.y = SCREEN_TOPBOUNDS;
    absPos.z = z;
    
        
    printf("\nABSOLUTE FROM SCREEN CO_ORDINATES  x : %f , y : %f , z : %f",absPos.x, absPos.y , absPos.z );
    
    return absPos;
    
}



#endif
