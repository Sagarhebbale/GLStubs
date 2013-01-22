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
@synthesize currentLocation;
@synthesize mainGLView;
@synthesize mapLocationController;
@synthesize hasLocation;
@synthesize checkedLocation;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
       
        // Custom initialization
    }
    return self;
}

-(void)setHasLocation:(BOOL)argHasLocation{
    hasLocation = argHasLocation;
    if(hasLocation == YES && self.checkedLocation == NO){
        CGRect mainScreenBounds = [[UIScreen mainScreen] bounds];
        mainGLView = [[GLView alloc] initWithFrame:mainScreenBounds andLocation:self.currentLocation];
        self.view = mainGLView;
        [self.mapLocationController.locMgr stopUpdatingLocation];
    }
    else{
        UIAlertView *locationErroeAlert = [[UIAlertView alloc] initWithTitle:@"Location Service Error" message:@"Cannot render map witout location. Check to activate Location services" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Ok", nil];
        [locationErroeAlert show];
        [locationErroeAlert release];
    }
}

-(void)locationUpdate:(CLLocation *)location{
    if(location!=NULL){
        self.hasLocation = YES;
        self.checkedLocation = YES;
        self.currentLocation = location;
    }
    else{
        self.hasLocation = NO;
        self.checkedLocation=NO;
    }
    
}
-(void)locationError:(NSError *)error{
    self.hasLocation = NO;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.mapLocationController = [[LocationController alloc] init];
    self.mapLocationController.delegate = self ;
    self.mapLocationController.locMgr.desiredAccuracy = kCLLocationAccuracyBest;
    [self.mapLocationController.locMgr startUpdatingLocation];
    
    
    
    
	// Do any additional setup after loading the view.
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dealloc{
    [mapLocationController release];
    [super dealloc];
}

@end
