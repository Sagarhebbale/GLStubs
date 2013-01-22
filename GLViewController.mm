//
//  GLViewController.m
//  Incantor
//
//  Created by Sagar on 11/5/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import "GLViewController.h"

@interface GLViewController ()


@end

@implementation GLViewController
@synthesize currentLatitude;
@synthesize currentLongitude;
@synthesize mapLocationController;
@synthesize mainGLView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}



- (void)viewDidLoad
{
    [super viewDidLoad];
    CGRect mainScreenBounds = [[UIScreen mainScreen] bounds];
    mainGLView = [[GLView alloc] initWithFrame:mainScreenBounds];
    self.view = mainGLView;
    mapLocationController = [[LocationController alloc] init];
    mapLocationController.delegate = self;
    [mapLocationController.locMgr startUpdatingLocation];
    
	// Do any additional setup after loading the view.
}


-(void)locationUpdate:(CLLocation *)location{
    NSLog(@"Lat : %f Long : %f", location.coordinate.latitude, location.coordinate.longitude);
    self.currentLatitude = location.coordinate.latitude;
    self.currentLongitude = location.coordinate.longitude;
}

- (void)locationError:(NSError *)error {
	 NSLog(@"Location ERROR : %@", error.description);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
