//
//  MapTileDownloader.m
//  Incantor
//
//  Created by Sagar on 1/23/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import "MapTileDownloader.h"

@interface MapTileDownloader(){
    
}
-(NSString *)getUrlFromParams:(MapTileParams)params;
@end

@implementation MapTileDownloader
@synthesize mapRequestQueue;
@synthesize baseUrl;
@synthesize mapData;

-(id)initWithBaseUrl:(NSString *)url{
    self = [super init];
    if(self){
        
        self.baseUrl = baseUrl;
    }
    
    return self;
}

-(id)init{
    self = [super init];
    if(self){
        self.baseUrl = MAP_REQUEST_BASE_URL;
    }
}

-(void)grabTileForParams:(MapTileParams)mapParams{
    if(self.baseUrl){
        if (![self mapRequestQueue]) {
            [self setMapRequestQueue:[[[NSOperationQueue alloc] init] autorelease]];
        }
        NSString *urlString = [[self getUrlFromParams:mapParams] retain];
        NSURL *url = [NSURL URLWithString:urlString];
        [urlString release];
        ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
        [request setDelegate:self];
        [request setDidFinishSelector:@selector(requestDone:)];
        [request setDidFailSelector:@selector(requestWentWrong:)];
        [[self mapRequestQueue] addOperation:request]; //queue is an NSOperationQueue
    }
}

- (void)requestDone:(ASIHTTPRequest *)request
{
    NSData *response = [request responseData];
    self.mapData = response;
    
}

-(NSData *)mapData{
    if(self.mapData){
        return self.mapData;
    }
    else
        return NULL;
}

- (void)requestWentWrong:(ASIHTTPRequest *)request
{
    NSError *error = [request error];
    if(error){
        UIAlertView *mapDownloadError = [[UIAlertView alloc] initWithTitle:@"Map Download Error" message:@"There was a problem in downloading the map content. Check if your internet is enabled" delegate:self cancelButtonTitle:@"Canel" otherButtonTitles: nil];
        [mapDownloadError show];
        [mapDownloadError release];
    }
}


-(NSString *)getUrlFromParams:(MapTileParams)params{
    
    NSString *latStringVal = [[NSNumber numberWithFloat:params.latitude] stringValue];
    NSString *longStringVal = [[NSNumber numberWithFloat:params.longitude] stringValue];
    NSString *zoomStringVal = [[NSNumber numberWithFloat:params.zoomLevel] stringValue];
    
    
    
    
}

@end
