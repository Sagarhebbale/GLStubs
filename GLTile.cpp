//
//  GLTile.cpp
//  Incantor
//
//  Created by Sagar on 11/14/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#include "GLTile.hpp"


GLTile *makeTile(){
    
    
    return new GLTile;
}

Vertex GLTile:: vertexMake(vec3 position, vec4 color){
    
    Vertex ret;
    ret.Position = position;
    ret.Color = color;
    
    return ret;
}

void GLTile::enableDataSource(bool isDataSource){
    this->setNeedsVertexData(isDataSource);
}

void GLTile::setNullVertices(){
    if(!this->needsVertexData){
        this->firstVertex = NULL_VERTEX;
        this->secondVertex = NULL_VERTEX;
        this->thirdVertex = NULL_VERTEX;
        this->fourthVertex = NULL_VERTEX;
        this->vertices = {firstVertex , secondVertex , thirdVertex , fourthVertex};
        
    }
}

void GLTile::createTile(float argTileWidth, float argTileHeight, vec4 colors, GLTopology argTopology){
    if(this->needsVertexData){
        this->vertexIndices.resize(4);
        this->tileWidth = argTileWidth*SCREEN_RIGHTBOUNDS*2/SCREEN_X_RES;
        this->tileHeight = argTileHeight*SCREEN_TOPBOUNDS*2/SCREEN_Y_RES;
        this->setVerticesForWidthAndHeight(argTileWidth, argTileHeight, colors);
        //argTopology = topology;
        switch (topology) {
            case kGLTriangleStrip:
                this->vertexIndices = {0 , 1 , 2 , 3};
                break;
            case kGLTrianles:
                this->vertexIndices = {0 , 1 , 2 , 1 , 2 , 3};
            default:
                this->vertexIndices = {0 , 1 , 2 , 3};
                break;
                
        }
    }
    else{
        cout<<"Check for data";
        exit(0);
    }
}


void GLTile::setVerticesForWidthAndHeight(float width, float height, vec4 color){
    vector<int> colorIndices;
    this->firstVertex = vertexMake(vec3(0 , height , 0), color);
    this->origin = firstVertex.Position;
    printf("\nFirst vertex x : %f , y: %f , z:%f",firstVertex.Position.x , firstVertex.Position.y ,firstVertex.Position.z);
    this->secondVertex = vertexMake(vec3(0 , 0, 0), color);
    printf("\nSecond vertex x : %f , y: %f , z:%f",secondVertex.Position.x , secondVertex.Position.y ,secondVertex.Position.z);
    this->thirdVertex = vertexMake(vec3(width , height, 0), color);
    printf("\nThird vertex x : %f , y: %f , z:%f",thirdVertex.Position.x , thirdVertex.Position.y ,thirdVertex.Position.z);
    this->fourthVertex = vertexMake(vec3(width , 0 , 0), color);
    printf("\nFourth vertex x : %f , y: %f , z:%f",fourthVertex.Position.x , fourthVertex.Position.y ,fourthVertex.Position.z);
    
    if(this->vertices.empty()){
        this->vertices = {firstVertex , secondVertex , thirdVertex ,  fourthVertex};
        
        this->setNeedsVertexData(0);
    }
    else{
        this->reloadVertexData();
    }
}


void GLTile::setOrigin(vec3 origin){
    AbsPosition aPos;
    aPos = getAbsPosForScreenCoords(origin.x, origin.y, origin.z);
    //nPos = getNormPosition(aPos);
    this->origin.x = aPos.x;
    this->origin.y = aPos.y;
    this->origin.z = aPos.z;
    if(this->tileWidth != 0 && this->tileHeight !=0){
        this->setNeedsVertexData(1);
        this->firstVertex.Position = this->origin;
        this->secondVertex.Position = vec3(this->origin.x, this->origin.y - this->tileHeight ,this->origin.z);
        this->thirdVertex.Position = vec3(this->origin.x + this->tileWidth, this->origin.y,this->origin.z);
        this->fourthVertex.Position = vec3(this->origin.x + this->tileWidth , this->origin.y -this->tileHeight , this->origin.z);
    }
    this->reloadVertexData();
    printf("\nFirst vertex x : %f , y: %f , z:%f",this->firstVertex.Position.x , this->firstVertex.Position.y ,this->firstVertex.Position.z);
    printf("\nSecond vertex x : %f , y: %f , z:%f",this->secondVertex.Position.x , this->secondVertex.Position.y ,this->secondVertex.Position.z);
    printf("\nThird vertex x : %f , y: %f , z:%f",this->thirdVertex.Position.x , this->thirdVertex.Position.y ,this->thirdVertex.Position.z);
    printf("\nFourth vertex x : %f , y: %f , z:%f",this->fourthVertex.Position.x , this->fourthVertex.Position.y ,this->fourthVertex.Position.z);

    //this->setAbsVertices();
}

void GLTile::setNeedsVertexData(bool needsData){
    this->needsVertexData = needsData;
    if(this->needsVertexData == 1){
        this->setNullVertices();
    }
}

void GLTile::reloadVertexData(){
    this->setNeedsVertexData(1);
    this->vertices = {firstVertex , secondVertex ,  thirdVertex , fourthVertex};
    this->setNeedsVertexData(0);
}



GLTile::~GLTile(){
    this->setNullVertices();
    //this->vertices.~vector();
}

