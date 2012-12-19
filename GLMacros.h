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

typedef enum{
    kGLTriangleStrip = 0,
    kGLTrianles,
    KGLTriangleFan,
    
}GLTopology;


#endif
