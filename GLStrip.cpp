//
//  GLStrip.cpp
//  Incantor
//
//  Created by Sagar on 11/27/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLStrip.hpp"



GLStrip GLStrip::createTileStrip(float stripWidth, vec2 origin){
    stripCount++;
    float currentX = origin.x , currentY = origin.y;
    numberOfTiles = (stripWidth/tileSize) +1;
    this->tileStrip.resize(numberOfTiles);
    this->tileIndicesInStrip.resize(numberOfTiles);
    bool switchColorBetweenTiles = 0;
    for(int i = 0 ; i<this->tileStrip.size() ; i++){
        GLTile tile;
        vec4 color;
        if (switchColorBetweenTiles == 0) {
            color = vec4(1,0,0,0);
            switchColorBetweenTiles = 1;
        }
        else{
            color = vec4(0,0,1,0);
            switchColorBetweenTiles = 0;
        }
        currentX = origin.x + i*tileSize;
        if(currentX > stripWidth)
            break;
        if(currentX <= stripWidth/2){
            tile = tile.createTile(tileSize, color , kGLTriangleStrip);
            vec3 tilePosition = vec3(currentX,currentY,0);
            printf("\n x : %f  y : %f  z : %f  count : %d" , tilePosition.x,tilePosition.y,tilePosition.z , i);
            tile = tile.setTileOrigin(tile,tilePosition );
            this->tileStrip.at(i) = tile;
            this->tileIndicesInStrip.at(i) = i;
        }
    }
    return *this;
}







