//
//  GLViewController.h
//  Incantor
//
//  Created by Sagar on 11/5/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface GLViewController : UIViewController{
    
    GLView *mainGLView;
}

@property(nonatomic, retain)GLView *mainGLView;

@end
