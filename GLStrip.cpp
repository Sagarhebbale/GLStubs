//
//  GLStrip.cpp
//  Incantor
//
//  Created by Sagar on 11/27/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLStrip.hpp"



void GLStrip::setDrawMode(StripDrawMode argDrawMode){
    this->drawMode = argDrawMode;
    this->setNeedsData(1);
    
}

void GLStrip::setNeedsData(bool argNeedsData){
    this->needsData = argNeedsData;
    if(this->needsData == 0){
        this->fillStripColors();
        this->draw();
    }
}

void GLStrip::fillStripColors(){
    if(this->tileColorMode == kTileColorModePlain){
        this->tileColor = vec4(1,0,0,1);
        this->altTileColor = vec4(0,1,0,1);
        this->tileVertexColors.resize(0);
    }
    else{
        this->tileVertexColors.resize(4);
        vec4 colorOne = vec4(1,0,0,1);
        vec4 colorTwo = vec4(0,1,0,1);
        vec4 colorThree = vec4(0,0,1,1);
        vec4 colorFour = vec4(0,1,1,1);
        this->tileVertexColors = {colorOne , colorTwo , colorThree , colorFour};
    }
}

void GLStrip::setStriporigin(vec3 argOrigin){
    this->stripOrigin =argOrigin;
    this->setNullTiles();
    if(this->stripWidth != 0 && this->tileCount != 0 && this->tileSize !=0){
        this->setNeedsData(0);
    }
    else{
        cout<<"Data insufficient to make strip, exit app";
        exit(0);
    }
    
}

void GLStrip::setTileSize(float size){
    this->tileSize = size;
}

void GLStrip::setTileColorMode(TileColorMode argColorMode){
    this->tileColorMode = argColorMode;
}

void GLStrip::setStripWidth(float width){
    if(this->drawMode == kmodeStripWidth){
        if(this->tileSize != 0 ){
            this->stripWidth = width;
            this->tileCount = width/(this->tileSize);
        }
        else{
            cout<<"Set tile size before setting strip width";
        }
    }
    else
        cout<<"Cannot set Strip width in this draw mode";
}

void GLStrip::setStripCount(int count){
    if(this->drawMode == kmodeStripCount){
        if(this->tileSize != 0 ){
            this->tileCount = count;
            this->stripWidth = count*(this->tileSize);
        }
        else{
            cout<<"Set tile size before setting strip count";
        }
        
    }
    else
        cout<<"Cannot set Strip Count in this draw mode";
}

void GLStrip::setNullTiles(){
    if(this->drawMode == kmodeStripCount){
        this->tiles.resize(this->tileCount);
        
    }
    if(this->drawMode == kmodeStripWidth){
        int count = (int)((this->stripWidth/this->tileSize) + 1);
        this->tiles.resize(count);
        
    }
}
void GLStrip::setVertices(){
    if(this->tiles.empty() == 0){
        GLTile currentTile;
        vector<Vertex> stripVertices;
        stripVertices.resize(tiles.size()*2 +1);
        int j;
        j=0;
        for(int i=0;i<this->tiles.size();i++){
            if(i == tiles.size() -1){
                j++;
                stripVertices.at(j) = currentTile.thirdVertex;
                j++;
                stripVertices.at(j) = currentTile.fourthVertex;
                break;
            }
            currentTile = tiles.at(i);
            stripVertices.at(j) = currentTile.firstVertex;
            j++;
            stripVertices.at(j) = currentTile.secondVertex;
            
            j++;
        }
        this->vertices = stripVertices;
       }
    else{
        cout<<"Fatal error, api cannot determine point of error";
    }
}

void GLStrip::draw(){
    if(this->tileColorMode != kTileColorModeMixed && this->tileColorMode != kTileColorModePlain)
        this->tileColorMode = kTileColorModePlain;
    float currentX , currentY , currentZ;
    currentX = this->stripOrigin.x;
    currentY = this->stripOrigin.y;
    currentZ = this->stripOrigin.z;
    bool switchColor = 0;
    for(int i =0; i<this->tiles.size();i++){
        GLTile newTile;
        vec4 color;
        if(switchColor ==0){
            color = this->tileColor;
            switchColor = 1;
        }
        else{
            color = altTileColor;
            switchColor = 0;
        }
        
        if(this->orientation == kStriporientationHorizontal)
            currentX = this->stripOrigin.x + i*(this->tileSize);
        else
            currentY = this->stripOrigin.y - i*(this->tileSize);
        
        if(this->drawMode == kmodeStripCount){
            if(currentX > tileCount*tileSize)
                break;
        }
        if(this->drawMode == kmodeStripWidth){
            if(currentX > stripWidth)
                break;
        }
        else{
            newTile.setColorMode(this->tileColorMode);
            if(this->tileColorMode == kTileColorModePlain){
                newTile = newTile.createPlainTile(this->tileSize, color, this->stripTopology)
                ;
            }
            else if(this->tileColorMode == kTileColorModeMixed){
                newTile = newTile.createTileWithMixedColor(this->tileSize, this->tileVertexColors, this->stripTopology);
            }
            vec3 pos = vec3(currentX , currentY , currentZ);
            newTile.setOrigin(pos);
            this->tiles.at(i) = newTile;
        }
    }
    this->setVertices();
    this->printVertices(this->vertices);
    
}
void GLStrip::printVertices(std::vector<Vertex> vert){
    for(int i =0;i<vert.size();i++){
        printf("\n**********");
        printf("\nVertex Position");
        printf("\n x : %f y : %f z : %f",vert.at(i).Position.x,vert.at(i).Position.y,vert.at(i).Position.z);
        printf("\n**********");
    }
}


/*void GLStrip::setStripForStripWidth(){
 float currentX = stripOrigin.x;
 float currentY = stripOrigin.y;
 float currentZ = stripOrigin.z;
 numberOfTiles = (stripWidth/tileSize) +1;
 this->tileStrip.resize(numberOfTiles);
 this->tileIndicesInStrip.resize(numberOfTiles);
 bool switchColorBetweenTiles = 0;
 for(int i = 0 ; i<this->tileStrip.size() ; i++){
 GLTile tile;
 printf("\n****TILE START***");
 vec4 color;
 if (switchColorBetweenTiles == 0) {
 color = vec4(0,1,0,1);
 switchColorBetweenTiles = 1;
 }
 else{
 color = vec4(0,0,1,1);
 switchColorBetweenTiles = 0;
 }
 currentX = this->stripOrigin.x + i*(this->tileSize);
 if(currentX > stripWidth)
 break;
 if(currentX <= stripWidth/2){
 //tile = tile.createTile(tileSize, color , kGLTriangleStrip);
 vec3 tilePosition = vec3(currentX,currentY,currentZ);
 
 printf("\n x : %f  y : %f  z : %f  count : %d" , tilePosition.x,tilePosition.y,tilePosition.z , i);
 
 tile = tile.setTileOrigin(tile,tilePosition );
 this->tileStrip.at(i) = tile;
 this->tileIndicesInStrip.at(i) = i;
 printf("\n****TILE END***");
 }
 }
 }*/


/*void GLStrip::setStripForStripCount(){
 float currentX = stripOrigin.x;
 float currentY = stripOrigin.y;
 float currentZ = stripOrigin.z;
 this->stripWidth = (this->tileCount) * tileSize;
 this->tileStrip.resize(tileCount);
 this->tileIndicesInStrip.resize(tileCount);
 bool switchColorBetweenTiles = 0;
 float currentTileCount;
 currentTileCount = 0;
 for(int i = 0 ; i<this->tileStrip.size() ; i++){
 GLTile tile;
 currentTileCount++;
 printf("\n****TILE START***");
 vec4 color;
 if (switchColorBetweenTiles == 0) {
 color = vec4(1,0,0,0);
 switchColorBetweenTiles = 1;
 }
 else{
 color = vec4(0,0,1,0);
 switchColorBetweenTiles = 0;
 }
 currentX = this->stripOrigin.x + i*(this->tileSize);
 if(currentTileCount <= this->tileCount){
 //tile = tile.createTile(this->tileSize, color, this->stripTopology);
 vec3 tileOrigin = vec3(currentX , currentY , currentZ);
 tile = tile.setTileOrigin(tile, tileOrigin);
 printf("\n x : %f  y : %f  z : %f  count : %d" , tileOrigin.x,tileOrigin.y,tileOrigin.z , i);
 this->tileStrip.at(i) = tile;
 this->tileIndicesInStrip.at(i) = i;
 printf("\n****TILE END***");
 }
 
 }
 
 }*/

/*vector<GLTile> GLStrip::getStrip(){
 
 if(!this->tileStrip.empty())
 return this->tileStrip;
 else{
 vector<GLTile> emptyVector;
 return emptyVector;
 }
 }
 
 size_t GLStrip::getStripPointerSize(){
 if(!this->tileStrip.empty()){
 return (((this->tileCount)+1)*4*sizeof(Vertex));
 
 }
 else{
 cout<<"Cant return pointer size as the strip isnt initialized";
 return NULL;
 }
 }*/







