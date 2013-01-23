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
#import "LocationController.h"

@interface MapTileDownloader : NSObject<LocationControllerDelegate>{
    NSOperationQueue *mapRequestQueue;
    NSString *baseUrl;
    NSData *mapData;
    LocationController *mapLocationController;
    CLLocation *currentLocation;
    MapTileParams currentTileParams;
    UIImage *currentMapTile;

}

@property(nonatomic , retain)NSOperationQueue *mapRequestQueue;
@property(nonatomic , retain)NSString *baseUrl;
@property(nonatomic , retain)NSData *mapData;
@property(nonatomic , retain)LocationController *mapLocationController;
@property(nonatomic , retain)CLLocation *currentLocation;
@property(nonatomic , assign)UIImage *currentMapTile;
//@property(nonatomic , assign)MapTileParams currentTileParams;


-(id)initWithBaseUrl:(NSString *)url;
-(void)grabTileForParams:(MapTileParams)mapParams;
-(void)setCurrentMapParamsWithLat:(double)lat longitude:(double)longi andZoomLevel:(float)zoomLevel;

@end
