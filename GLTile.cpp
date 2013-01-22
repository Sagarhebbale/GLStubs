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

void GLTile::setColorMode(TileColorMode argColorMode){
    this->colorMode = argColorMode;
    this->setNeedsVertexData(1);
}

GLTile GLTile::createTileWithMixedColor(float size, vector<vec4> vertexColors, GLTopology argTopology){
    if(this->needsVertexData){
        if(this->colorMode == kTileColorModeMixed){
            this->vertexIndices.resize(4);
            this->tileSize = size;
            this->setVertices(size,vertexColors);
            argTopology = topology;
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
            return *this;
        }
        else{
            cout<<"Cannot call mixed plain tile in this color mode";
            exit(0);
        }
    }
    else{
        cout<<"Check for data";
        exit(0);
    }
    
}


GLTile GLTile::createPlainTile(float size , vec4 color , GLTopology argTopology){
    if(this->needsVertexData){
        if(this->colorMode == kTileColorModePlain){
            this->vertexIndices.resize(4);
            vector<vec4> colors;
            colors.resize(1);
            colors.at(0) = color;
            this->tileSize = size;
            this->setVertices(size, colors);
            argTopology = topology;
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
            
            return *this;
            
        }
        else{
            cout<<"Cannot call create plain tile in this color mode";
            exit(0);
            
        }
    }
    else{
        cout<<"Check for data";
        exit(0);
    }
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

void GLTile::setVertices(float size, vector<vec4>colors){
    vector<int> colorIndices;
    if(this->colorMode == kTileColorModePlain){
        printVec4(colors.at(0));
        this->firstVertex = vertexMake(vec3(0 , size , 0), colors.at(0));
        this->origin = firstVertex.Position;
        printf("\nFirst vertex x : %f , y: %f , z:%f",firstVertex.Position.x , firstVertex.Position.y ,firstVertex.Position.z);
        this->secondVertex = vertexMake(vec3(0 , 0, 0), colors.at(0));
        printf("\nSecond vertex x : %f , y: %f , z:%f",secondVertex.Position.x , secondVertex.Position.y ,secondVertex.Position.z);
        this->thirdVertex = vertexMake(vec3(size , size, 0), colors.at(0));
        printf("\nThird vertex x : %f , y: %f , z:%f",thirdVertex.Position.x , thirdVertex.Position.y ,thirdVertex.Position.z);
        this->fourthVertex = vertexMake(vec3(size , 0 , 0), colors.at(0));
        printf("\nFourth vertex x : %f , y: %f , z:%f",fourthVertex.Position.x , fourthVertex.Position.y ,fourthVertex.Position.z);
    }
    else{
        if(colors.size() == 4){
            firstVertex = vertexMake(vec3(0 , size , 0), colors.at(0));
            this->origin = firstVertex.Position;
            printf("\nFirst vertex x : %f , y: %f , z:%f",firstVertex.Position.x , firstVertex.Position.y ,firstVertex.Position.z);
            this->secondVertex = vertexMake(vec3(0 , 0, 0), colors.at(1));
            printf("\nSecond vertex x : %f , y: %f , z:%f",secondVertex.Position.x , secondVertex.Position.y ,secondVertex.Position.z);
            this->thirdVertex = vertexMake(vec3(size , size, 0), colors.at(2));
            printf("\nThird vertex x : %f , y: %f , z:%f",thirdVertex.Position.x , thirdVertex.Position.y ,thirdVertex.Position.z);
            this->fourthVertex = vertexMake(vec3(size , 0 , 0), colors.at(3));
            printf("\nFourth vertex x : %f , y: %f , z:%f",fourthVertex.Position.x , fourthVertex.Position.y ,fourthVertex.Position.z);
        }
        else{
            cout<<"Colors not given correctly to make mixedcolor tile";
        }
       
    }
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
    if(this->tileSize != 0){
        this->setNeedsVertexData(1);
        this->firstVertex.Position = origin;
        this->secondVertex.Position = vec3(origin.x, origin.y - this->tileSize ,origin.z);
        this->thirdVertex.Position = vec3(origin.x + this->tileSize, origin.y,origin.z);
        this->fourthVertex.Position = vec3(origin.x + this->tileSize , origin.y -this->tileSize , origin.z);
    }
   this->reloadVertexData();
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

