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

@interface MapTileDownloader : NSObject{
    NSOperationQueue *mapRequestQueue;
    NSString *baseUrl;
    NSData *mapData;
}

@property(nonatomic , retain)NSOperationQueue *mapRequestQueue;
@property(nonatomic , retain)NSString *baseUrl;
@property(nonatomic , retain)NSData *mapData;


-(id)initWithBaseUrl:(NSString *)url;
-(void)grabTileForParams:(MapTileParams)mapParams;

@end
