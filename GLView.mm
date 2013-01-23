//
//  GLView.mm
//  Incantor
//
//  Created by Sagar on 10/31/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import "GLView.h"

const BOOL ForceES1 = false;




@implementation GLView


+ (Class) layerClass
{
    return [CAEAGLLayer class];
}


- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!m_context || ForceES1) {
            api = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:api];
        }
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }
        
        if (api == kEAGLRenderingAPIOpenGLES1) {
            m_renderingEngine = CreateRenderer1();
        } else {
            NSLog(@"Using openGLES2.0");
            m_renderingEngine = CreateRenderer2();
        }
        
        [m_context
         renderbufferStorage:GL_RENDERBUFFER
         fromDrawable: eaglLayer];
        
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        
        [self setUpDraw];
                
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(didRotate:)
         name:UIDeviceOrientationDidChangeNotification
         object:nil];
        

    }
    return self;
}

-(void)setUpDraw{
    
    [self drawView: nil];
    m_timestamp = CACurrentMediaTime();
    
    CADisplayLink* displayLink;
    displayLink = [CADisplayLink displayLinkWithTarget:self
                                              selector:@selector(drawView:)];
    
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                      forMode:NSDefaultRunLoopMode];

}

- (void) didRotate: (NSNotification*) notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_renderingEngine->OnRotate((DeviceOrientation) orientation);
    [self drawView: nil];
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAnimation(elapsedSeconds);
    }
    
    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location  = [touch locationInView: self];
    NSLog(@"\nTime in touhDown : %f", touch.timestamp);
    m_renderingEngine->OnFingerDown(ivec2(location.x, location.y));
}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    NSLog(@"\nTime in touchEnd : %f", touch.timestamp);
    CGPoint location  = [touch locationInView: self];
    m_renderingEngine->OnFingerUp(ivec2(location.x, location.y));
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint previous  = [touch previousLocationInView: self];
    CGPoint current = [touch locationInView: self];
    NSLog(@"\nTime interval for touchMove : %f", touch.timestamp);
    m_renderingEngine->OnFingerMove(ivec2(previous.x, previous.y),
                                    ivec2(current.x, current.y));
}





@end
