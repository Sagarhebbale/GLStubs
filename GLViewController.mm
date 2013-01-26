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
@synthesize tileDownloader;
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
    self.tileDownloader = [MapTileDownloader sharedInstance];
    self.tileDownloader.delegate = self;
    CGRect mainScreenBounds = [[UIScreen mainScreen] bounds];
    mainGLView = [[GLView alloc] initWithFrame:mainScreenBounds];
   
    
    
    
    
	// Do any additional setup after loading the view.
}

-(void)viewDidAppear:(BOOL)animated{
     self.view = mainGLView;
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dealloc{
    
    [super dealloc];
}

-(void)didDownloadMapTile:(UIImage *)tileImage{
    UIImageView *tileView = [[UIImageView alloc] initWithImage:tileImage];
    tileView.frame = CGRectMake(50, 50, 100, 100);
    [self.mainGLView addSubview:tileView];
    [tileView release];
    //self.view = mainGLView;
    //[self.view setNeedsDisplay];
}

-(void)couldNotDownLoadTile:(NSError *)error{
    
}

@end
