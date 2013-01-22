//
//  GLView.h
//  Incantor
//
//  Created by Sagar on 10/31/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import "IRenderingEngine.hpp"
#import "LocationController.h"


@interface GLView : UIView<LocationControllerDelegate>{
    
    EAGLContext *m_context;
    IRenderingEngine *m_renderingEngine;
    float m_timestamp;
    LocationController *mapLocationController;
    CLLocation *currentLocation;
 
}

@property(nonatomic , retain)LocationController *mapLocationController;
@property(nonatomic , retain)CLLocation *currentLocation;

-(id)initWithFrame:(CGRect)frame andLocation:(CLLocation *)location;
-(void)drawView: (CADisplayLink *)displayLink;
-(void)didRotate: (NSNotification *)notification;
-(void)setUpDraw;

@end
