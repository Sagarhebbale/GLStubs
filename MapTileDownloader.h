//
//  MapTileDownloader.h
//  Incantor
//
//  Created by Sagar on 1/23/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ASIHTTPRequest.h"
#import "GLMacros.h"
#import "Location.h"

@protocol TileDownloadDelegate <NSObject>

@required
-(void)didDownloadMapTile:(UIImage *)tileImage;
-(void)couldNotDownLoadTile:(NSError *)error;
@end

@interface MapTileDownloader : NSObject<LocationControllerDelegate>{
    NSOperationQueue *mapRequestQueue;
    NSString *baseUrl;
    NSData *mapData;
    Location *mapLocationController;
    CLLocation *currentLocation;
    MapTileParams currentTileParams;
    UIImage *currentMapTile;
    id delegate;

}

@property(nonatomic , retain)NSOperationQueue *mapRequestQueue;
@property(nonatomic , retain)NSString *baseUrl;
@property(nonatomic , retain)NSData *mapData;
@property(nonatomic , retain)Location *mapLocationController;
@property(nonatomic , retain)CLLocation *currentLocation;
@property(nonatomic , assign)UIImage *currentMapTile;
@property(nonatomic, assign)id delegate;
//@property(nonatomic , assign)MapTileParams currentTileParams;

+(id)sharedInstance;
-(id)initWithBaseUrl:(NSString *)url;
-(void)grabTileForParams:(MapTileParams)mapParams;
-(void)setCurrentMapParamsWithLat:(long double)lat longitude:(long double)longi andZoomLevel:(float)zoomLevel;

@end
