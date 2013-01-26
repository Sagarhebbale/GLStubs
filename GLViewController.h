//
//  GLViewController.h
//  Incantor
//
//  Created by Sagar on 11/5/12.
//  Copyright (c) 2012 Sagar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "MapTileDownloader.h"


@interface GLViewController : UIViewController<TileDownloadDelegate>{
    
    GLView *mainGLView;
    MapTileDownloader *tileDownloader;
    
    
}
@property(nonatomic, retain)GLView *mainGLView;
@property(nonatomic, retain)MapTileDownloader *tileDownloader;




@end
