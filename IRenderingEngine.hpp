//
//  IRenderingEngine.hpp
//  Incantor
//
//  Created by Sagar on 10/31/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#ifndef Incantor_IRenderingEngine_hpp
#define Incantor_IRenderingEngine_hpp
#include "Vector.hpp"
// Physical orientation of a handheld device, equivalent to UIDeviceOrientation
// Physical orientation of a handheld device, equivalent to UIDeviceOrientation
enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

// Creates an instance of the renderer and sets up various OpenGL state.
struct IRenderingEngine* CreateRenderer1();
struct IRenderingEngine* CreateRenderer2();

// Interface to the OpenGL ES renderer; consumed by GLView.
struct IRenderingEngine {
    virtual void Initialize(int width, int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAnimation(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual void OnFingerUp(ivec2 location) = 0;
    virtual void OnFingerDown(ivec2 location) = 0;
    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) = 0;
    virtual void OnLocationUpdate(ivec2 newLocation) =0;
    virtual ~IRenderingEngine() {}
};
#endif
