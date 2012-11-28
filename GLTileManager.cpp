//
//  GLTileManager.cpp
//  Incantor
//
//  Created by Sagar on 11/8/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLTileManager.hpp"

GLTileManager* createTileManager(){
    
    return new GLTileManager;
}

void GLTileManager::initialize(float argtileSize){
 
    tileCount = 0;
    tileSize =  argtileSize;
    
}



vector<vector<GLTile>> GLTileManager::createPlane(vec2 origin, float width , float height){
    vector<vector<GLTile>> plane;
    int numberOfStrips = (int)((height/tileSize) +1);
    printf("Number of strips : %d", numberOfStrips);
    plane.resize(numberOfStrips);
    stripIndices.resize(numberOfStrips);
    float xPos = origin.x;
    float yPos = origin.y;
    int i =0;
    for(i =0; i<numberOfStrips;i++){
        if(yPos <= height){
            vector<GLTile>strip;
            printf("\nStrip number : %d",i);
            strip = this->createTileStrip(width, vec2(xPos , yPos));
            stripIndices.at(i) = i;
            printf("Strip Index : %d",stripIndices.at(i));
            yPos -=  tileSize;
            plane.at(i) = strip;
        }
        else
            break;
       
    }
    this->generatePlaneVertexIndices();
    return plane;
}


vector<GLTile> GLTileManager::createTileStrip(float stripWidth, vec2 origin){
    
    vector<GLTile> tileStrip;
    float currentX = origin.x , currentY = origin.y;
    tileStrip.resize(stripWidth/tileSize +1);
    bool switchColorBetweenTiles = 0;
    for(int i = 0 ; i<tileStrip.size() ; i++){
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
            tileCount++;
            vec3 tilePosition = vec3(currentX,currentY,0);
            printf("\n x : %f  y : %f  z : %f  count : %d" , tilePosition.x,tilePosition.y,tilePosition.z , i);
            tile = tile.setTileOrigin(tile,tilePosition );
            tileStrip.at(i) = tile;
        }
    }

    return tileStrip;
}
