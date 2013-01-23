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
    self.tileDownloader = [[MapTileDownloader alloc] init];
    
    
    
    
	// Do any additional setup after loading the view.
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dealloc{
    
    [super dealloc];
}

@end
