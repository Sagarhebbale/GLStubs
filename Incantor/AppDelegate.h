//
//  AppDelegate.h
//  Incantor
//
//  Created by Sagar on 10/29/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLViewController.h"
#import "GLView.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>{
    
    GLViewController *m_viewController;
    UIWindow *m_window;
}

@property (strong, nonatomic) UIWindow *m_window;

@end
