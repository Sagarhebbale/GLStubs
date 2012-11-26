//
//  RenderEngine2.cpp
//  Incantor
//
//  Created by Sagar on 11/3/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "IRenderingEngine.hpp"
#include "Quaternion.hpp"
#include <vector>
#include <iostream>
#define STRINGIFY(A)  #A
#include "/Users/moveablecode/Desktop/Incantor.git/Incantor /Shaders/Simplevert.glsl"
#include "/Users/moveablecode/Desktop/Incantor.git/Incantor /Shaders/Simplefrag.glsl"
#include "GLTileManager.hpp"
#include "GLMacros.h"


static const float AnimationDuration = 0.25f;
using namespace std;



struct Animation {
    Quaternion Start;
    Quaternion End;
    Quaternion Current;
    float Elapsed;
    float Duration;
};


class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
    void OnFingerUp(ivec2 location);
    void OnFingerDown(ivec2 location);
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
private:
    GLuint BuildShader(const char* source, GLenum shaderType) const;
    GLuint BuildProgram(const char* vShader, const char* fShader) const;
    GLTileManager tileManager;
    std::vector<vector<GLTile>> plane;
    Animation m_animation;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_colorRenderbuffer;
    GLuint m_depthRenderbuffer;
    GLfloat m_rotationAngle;
    GLfloat m_scale;
    vec3 m_translate;
    ivec2 m_pivotPoint;
    float tileSize;
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_tileIndexCount;
    
};

IRenderingEngine* CreateRenderer2()
{
    return new RenderingEngine2();
}

RenderingEngine2::RenderingEngine2() : m_rotationAngle(0), m_scale(1), m_translate(0,0,0)
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1, &m_colorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
}


void RenderingEngine2::Initialize(int width, int height)
{   //create and initialize the tile manager
    float leftBounds , topBounds;
    leftBounds = -4.15;
    topBounds = 6.3;
    //m_pivotPoint = ivec2(width / 2, height / 2);
    /*tileManager = GLTileManager();
    tileSize = 0.5;
    tileManager.initialize(tileSize);
    plane = tileManager.createPlane(vec2(leftBounds ,topBounds),abs(2*leftBounds), abs(2*topBounds));*/
    GLTile tile;
    tile = tile.createTile(3, vec4(1,0,0,1), kGLTriangleStrip);
    
    
    
    // Create the depth buffer.
    glGenRenderbuffers(1, &m_depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER,
                             GL_DEPTH_COMPONENT16,
                             width,
                             height);
    
    // Create the framebuffer object; attach the depth and color buffers.
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                 GL_COLOR_ATTACHMENT0,
                                 GL_RENDERBUFFER,
                                 m_colorRenderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                 GL_DEPTH_ATTACHMENT,
                                 GL_RENDERBUFFER,
                                 m_depthRenderbuffer);
    
    // Bind the color buffer for rendering.
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
    
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    
    m_simpleProgram = BuildProgram(SimpleVertexShader,
                                   SimpleFragmentShader);
    glUseProgram(m_simpleProgram);
    
    // Set the projection matrix.
    GLint projectionUniform = glGetUniformLocation(m_simpleProgram,
                                                   "Projection");
    vec2 rect;
    rect = vec2(width , height);
    float size = 0.1*tanf(Deg_to_Rad(45.0) / 2.0);
    printf("size : %f", size);
    mat4 projectionMatrix = mat4:: Frustum(-size,                                    
               size,                                      
               -size / (rect.x / rect.y),   
               size / (rect.x/ rect.y),    
               .01,                                      
               1000.0);                                          

    glUniformMatrix4fv(projectionUniform, 1, 0,
                       projectionMatrix.Pointer());
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 tile.tile.size() * sizeof(tile.tile[0]),
                 &tile.tile[0],
                 GL_STATIC_DRAW);
    
    // Create the VBO for the indices.
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 tile.tileIndices.size()  * sizeof(tile.tileIndices[0]),
                 &tile.tileIndices[0],
                 GL_STATIC_DRAW);
   
}


void RenderingEngine2::OnRotate(DeviceOrientation orientation)
{
    vec3 direction;
    
    switch (orientation) {
        case DeviceOrientationUnknown:
        case DeviceOrientationPortrait:
            direction = vec3(0, 1, 0);
            break;
            
        case DeviceOrientationPortraitUpsideDown:
            direction = vec3(0, -1, 0);
            break;
            
        case DeviceOrientationFaceDown:
            direction = vec3(0, 0, -1);
            break;
            
        case DeviceOrientationFaceUp:
            direction = vec3(0, 0, 1);
            break;
            
        case DeviceOrientationLandscapeLeft:
            direction = vec3(+1, 0, 0);
            break;
            
        case DeviceOrientationLandscapeRight:
            direction = vec3(-1, 0, 0);
            break;
    }
    
    m_animation.Elapsed = 0;
    m_animation.Start = m_animation.Current = m_animation.End;
    m_animation.End = Quaternion::CreateFromVectors(vec3(0, 1, 0), direction);
}



void RenderingEngine2::UpdateAnimation(float timeStep)
{
    if (m_animation.Current == m_animation.End)
        return;
    
    m_animation.Elapsed += timeStep;
    if (m_animation.Elapsed >= AnimationDuration) {
        m_animation.Current = m_animation.End;
    } else {
        float mu = m_animation.Elapsed / AnimationDuration;
        m_animation.Current = m_animation.Start.Slerp(mu, m_animation.End);
    }
}

GLuint RenderingEngine2::BuildProgram(const char* vertexShaderSource,
                                      const char* fragmentShaderSource) const
{
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return programHandle;
}

GLuint RenderingEngine2::BuildShader(const char* source, GLenum shaderType) const
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return shaderHandle;
}

void RenderingEngine2::OnFingerUp(ivec2 location)
{
    m_scale = 1.0f;
}

void RenderingEngine2::OnFingerDown(ivec2 location)
{
    m_scale = 1.0f;
    OnFingerMove(location, location);
}

void RenderingEngine2::OnFingerMove(ivec2 previous, ivec2 location)
{
    /*vec2 direction = vec2(location - m_pivotPoint).Normalized();
    
    // Flip the Y axis because pixel coords increase towards the bottom.
    direction.y = -direction.y;
    
    m_rotationAngle = std::acos(direction.y) * 180.0f / 3.14159f;
    if (direction.x > 0)
        m_rotationAngle = -m_rotationAngle;*/
    m_translate = vec3((location.x - previous.x), (location.y - previous.y), 0);
}

void RenderingEngine2::Render() const
{
    GLuint positionSlot = glGetAttribLocation(m_simpleProgram,
                                              "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram,
                                           "SourceColor");
    
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);
    
    mat4 rotation = mat4::Rotate(0);
    mat4 scale = mat4::Scale(m_scale);
    mat4 translation = mat4::Translate(m_translate.x/20 , m_translate.y/20 , m_translate.z);
    
    // Set the model-view matrix.
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram,
                                                  "Modelview");
    mat4 modelviewMatrix = scale*rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    GLsizei stride = sizeof(Vertex);
    const GLvoid* colorOffset = (GLvoid*) sizeof(vec3);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, colorOffset);
    glEnableVertexAttribArray(positionSlot);
    
    const GLvoid* bodyOffset = 0;
    
    
    glEnableVertexAttribArray(colorSlot);
    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_BYTE, bodyOffset);
    glDisableVertexAttribArray(colorSlot);
    glVertexAttrib4f(colorSlot, 1, 1, 1, 1);
    //glDrawElements(GL_TRIANGLES, m_diskIndexCount, GL_UNSIGNED_BYTE, diskOffset);*/
    
    glDisableVertexAttribArray(positionSlot);
   
    /*for(int i = 0; i<plane.size() ; i++){
        vector<GLTile> strip;
        strip = plane.at(i);
        for(int j = 0; j<strip.size();j++){
            GLsizei stride = sizeof(Vertex);
            const GLvoid* pCoords = &strip[j].tile.front().Position.x;
            const GLvoid* pColors = &strip[j].tile.front().Color.x;
            glVertexAttribPointer(positionSlot, 3, GL_FLOAT,
                                  GL_FALSE, stride, pCoords);
            glVertexAttribPointer(colorSlot, 4, GL_FLOAT,
                                  GL_FALSE, stride, pColors);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, strip[j].tile.size());
        }
        
       
        
    }*/
    
   
   
}

