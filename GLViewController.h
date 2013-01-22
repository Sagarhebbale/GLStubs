//
//  GLViewController.h
//  Incantor
//
//  Created by Sagar on 11/5/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LocationController.h"
#import "GLView.h"

@interface GLViewController : UIViewController<LocationControllerDelegate>{
    
    GLView *mainGLView;
    LocationController *mapLocationController;
    CLLocationDegrees currentLatitude;
    CLLocationDegrees currentLongitude;
    
    
}

@property(nonatomic, retain)GLView *mainGLView;
@property(nonatomic , retain)LocationController *mapLocationController;
@property(nonatomic)CLLocationDegrees currentLatitude;
@property(nonatomic)CLLocationDegrees currentLongitude;


@end
