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

GLTile GLTile::createTile(float size , vec4 color , GLTopology argTopology){
    this->vertexIndices.resize(4);
    firstVertex = vertexMake(vec3(0 , size , 0), color);
    printf("\nFirst vertex x : %f , y: %f , z:%f",firstVertex.Position.x , firstVertex.Position.y ,firstVertex.Position.z);
    secondVertex = vertexMake(vec3(0 , 0, 0), color);
    printf("\nSecond vertex x : %f , y: %f , z:%f",secondVertex.Position.x , secondVertex.Position.y ,secondVertex.Position.z);
    thirdVertex = vertexMake(vec3(size , size, 0), color);
    printf("\nThird vertex x : %f , y: %f , z:%f",thirdVertex.Position.x , thirdVertex.Position.y ,thirdVertex.Position.z);
    fourthVertex = vertexMake(vec3(size , 0 , 0), color);
    printf("\nFourth vertex x : %f , y: %f , z:%f",fourthVertex.Position.x , fourthVertex.Position.y ,fourthVertex.Position.z);
    vector<Vertex>retTile = {firstVertex , secondVertex , thirdVertex , fourthVertex};
    this->tile = retTile;
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

GLTile GLTile::setTileColor(GLTile tile , vec4 color){
    
    vector<Vertex>::iterator vertex = tile.tile.begin();
    GLTile newTile;
    while(vertex != tile.tile.end()){
        vertex->Color = color;
        vertex++;
    }
    newTile.tile = tile.tile;
    return newTile;
    
}

GLTile GLTile::setTileOrigin(GLTile tile , vec3 origin){
    vector<Vertex>::iterator vertex = tile.tile.begin();
    GLTile newTile;
    float y1 = vertex->Position.y;
    vertex++;
    float y2 = vertex->Position.y;
    float size = y1-y2;
    vec4 tileColor = vertex->Color;
    firstVertex = vertexMake(origin, tileColor);
    secondVertex = vertexMake(vec3(origin.x , origin.y - size , 0),tileColor);
    thirdVertex = vertexMake(vec3(origin.x + size , origin.y , 0), tileColor);
    fourthVertex = vertexMake(vec3(origin.x + size , origin.y - size , 0), tileColor);
    vector<Vertex>tempTile = {firstVertex , secondVertex , thirdVertex ,fourthVertex};
    newTile.tile = tempTile;
    return newTile;
}

