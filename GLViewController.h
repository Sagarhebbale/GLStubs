//
//  GLViewController.h
//  Incantor
//
//  Created by Sagar on 11/5/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "LocationController.h"

@interface GLViewController : UIViewController<LocationControllerDelegate>{
    
    GLView *mainGLView;
    BOOL hasLocation;
    BOOL checkedLocation;
    LocationController *mapLocationController;
    CLLocation *currentLocation;
    
}
@property(nonatomic, retain)GLView *mainGLView;
@property (nonatomic) BOOL hasLocation;
@property(nonatomic) BOOL checkedLocation;
@property(nonatomic , retain) CLLocation *currentLocation;
@property(nonatomic , retain)LocationController *mapLocationController;



@end
