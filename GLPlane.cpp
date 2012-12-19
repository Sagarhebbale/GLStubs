//
//  GLPlane.cpp
//  Incantor
//
//  Created by Sagar on 11/28/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLPlane.hpp"

/*GLPlane GLPlane::createPlaneAt(float argTileSize , vec2 origin){
    int numberOfStrips = (int)((planeHeight/tileSize) +1);
    printf("Number of strips : %d", numberOfStrips);
    plane.resize(numberOfStrips);
    stripIndices.resize(numberOfStrips);
    float xPos = origin.x;
    float yPos = origin.y;
    int i =0;
    for(i =0; i<numberOfStrips;i++){
        if(yPos <= planeHeight){
            //GLStrip strip(kStriporientationHorizontal , 10 , kGLTriangleStrip);
            printf("\nStrip number : %d",i);
            strip = strip.createTileStrip(planeWidth, vec2(xPos , yPos));
            stripIndices.at(i) = i;
            printf("Strip Index : %d",stripIndices.at(i));
            yPos -=  tileSize;
            plane.at(i) = strip;
            stripIndices.at(i) = i;
        }
        else
            break;
        
    }
    
    return *this;
}*/
