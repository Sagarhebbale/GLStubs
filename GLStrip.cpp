//
//  GLStrip.cpp
//  Incantor
//
//  Created by Sagar on 11/27/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLStrip.hpp"

//

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
            if(count ==1)
                cout<<"cannot generate a strip using a single tile. Consider rendering a tile instead";
            
            this->tileCount = count;
            this->stripWidth = count*(this->tileSize);
            this->tiles.resize(count);
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
        int count = (int)((this->stripWidth/this->tileSize));
        this->tiles.resize(count);
        
    }
}

void GLStrip::setVertices(){
    if(this->tiles.empty() == 0){
        GLTile currentTile;
        vector<Vertex> stripVertices;
        stripVertices.resize(2*(tiles.size() - 1) + 4);
        int j;
        j=0;
        int i;
        for(i=0;i<this->tiles.size();i++){
            currentTile = this->tiles.at(i);
            if(i == this->tiles.size() - 1){
                stripVertices.at(j) = currentTile.firstVertex;
                j++;
                stripVertices.at(j) = currentTile.secondVertex;
                j++;
                stripVertices.at(j) = currentTile.thirdVertex;
                j++;
                stripVertices.at(j) = currentTile.fourthVertex;
                break;
            }
            stripVertices.at(j) = currentTile.firstVertex;
            j++;
            stripVertices.at(j) = currentTile.secondVertex;
            j++;
            }
        this->vertices = stripVertices;
        this->setVertexIndices();
       }
    
    else{
        cout<<"Fatal error, api cannot determine point of error";
    }
}

void GLStrip::setVertexIndices(){
    vertexIndices.resize(this->vertices.size());
    for(int i =0;i < this->vertices.size();i++){
        this->vertexIndices.at(i) = i;
    }
    this->printVertexIndices();

}

vector<Vertex> GLStrip::getVertices(){
    if(this->needsData == 0 && this->vertices.empty() == 0){
        return this->vertices;
    }
    else{
        vector<Vertex> nullVertices;
        return nullVertices;
    }
        
    
}

vector<char> GLStrip::getVertexIndices(){
    if(this->needsData == 0 && this->vertices.empty() == 0){
        return this->vertexIndices;
    }
    else{
        vector<char> nullIndices;
        return nullIndices;
    }
    
}

void GLStrip::printVertexIndices(){
    if(this->vertexIndices.empty() == 0){
        for(int i = 0; i< this->vertexIndices.size(); i++){
            printf("\n VertexIndex : %d",this->vertexIndices.at(i));
        }
    }
    else{
        cout<<"set vertices to print vertex indices";
    }
}
void GLStrip::draw(){
    if(this->tileColorMode != kTileColorModeMixed && this->tileColorMode != kTileColorModePlain)
        this->tileColorMode = kTileColorModePlain;
    float currentX , currentY , currentZ;
    int count = 0;
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
            color = this->altTileColor;
            switchColor = 0;
        }
        currentX = this->stripOrigin.x + i*(this->tileSize);
        if(this->drawMode == kmodeStripCount){
            if(i == (this->tileCount) )
                break;
        }
        
               
        newTile.setColorMode(this->tileColorMode);
        newTile = newTile.createPlainTile(this->tileSize, color, this->stripTopology);
        count++;
        vec3 pos = vec3(currentX , currentY , currentZ);
        printf("\n$$$n x : %f y : %f z : %f",pos.x,pos.y,pos.z);
        newTile.setOrigin(pos);
        this->tiles.at(i) = newTile;
        
        
        
        
    }
    printf("\nCount : %d", count);
    this->setVertices();
    //this->printVertices(this->vertices);
    
}
void GLStrip::printVertices(std::vector<Vertex> vert){
    for(int i =0;i<vert.size();i++){
        printf("\n**********");
        printf("\nVertex Position");
        printf("\n x : %f y : %f z : %f",vert.at(i).Position.x,vert.at(i).Position.y,vert.at(i).Position.z);
        printf("\n**********");
    }
}








