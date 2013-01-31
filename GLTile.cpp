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
        this->tileWidth = argTileWidth;
        this->tileHeight = argTileHeight;
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
    this->origin = origin;
    if(this->tileWidth != 0 && this->tileHeight !=0){
        this->setNeedsVertexData(1);
        this->firstVertex.Position = origin;
        this->secondVertex.Position = vec3(origin.x, origin.y - this->tileHeight ,origin.z);
        this->thirdVertex.Position = vec3(origin.x + this->tileWidth, origin.y,origin.z);
        this->fourthVertex.Position = vec3(origin.x + this->tileWidth , origin.y -this->tileHeight , origin.z);
    }
    this->reloadVertexData();
    this->setAbsVertices();
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

void GLTile::setAbsVertices(){
    if(!this->vertices.empty()){
        this->absVertices.resize(this->vertices.size());
        for(int i =0;i<this->vertices.size();i++){
            NormPosition nPos;
            nPos.x = this->vertices.at(i).Position.x;
            nPos.y = this->vertices.at(i).Position.y;
            nPos.z = this->vertices.at(i).Position.z;
            AbsPosition aPos;
            aPos = getAbsPosition(nPos);
            this->absVertices.at(i).Position.x = aPos.x;
            this->absVertices.at(i).Position.y = (SCREEN_RIGHTBOUNDS*aPos.y)/SCREEN_TOPBOUNDS;
            this->absVertices.at(i).Position.z = aPos.z;
            this->absVertices.at(i).Color = this->vertices.at(i).Color;
        }
        
    }
}


GLTile::~GLTile(){
    this->setNullVertices();
    //this->vertices.~vector();
}

