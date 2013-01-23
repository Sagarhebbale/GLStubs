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



@interface GLView : UIView{
    
    EAGLContext *m_context;
    IRenderingEngine *m_renderingEngine;
    float m_timestamp;
    
 
}




-(void)drawView: (CADisplayLink *)displayLink;
-(void)didRotate: (NSNotification *)notification;
-(void)setUpDraw;

@end
