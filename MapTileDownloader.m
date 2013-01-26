//
//  MapTileDownloader.m
//  Incantor
//
//  Created by Sagar on 1/23/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import "MapTileDownloader.h"
#define ZOOM_LEVEL 14.0
static MapTileDownloader *sharedInstance = nil;

@interface MapTileDownloader(){
    NSString *paramString;
    
}
-(NSString *)getUrlFromParams:(MapTileParams)params;
@property(nonatomic , retain)NSString *paramString;
@end

@implementation MapTileDownloader
@synthesize mapRequestQueue;
@synthesize baseUrl;
@synthesize paramString;
@synthesize mapData;
@synthesize mapLocationController;
@synthesize currentLocation;
@synthesize currentMapTile;
@synthesize delegate;
//@synthesize currentTileParams;



#pragma mark Singleton Methods
+ (id)sharedInstance {
    @synchronized(self) {
        if(sharedInstance == nil)
            sharedInstance = [[super allocWithZone:NULL] init];
    }
    return sharedInstance;
}
+ (id)allocWithZone:(NSZone *)zone {
    return [[self sharedInstance] retain];
}
- (id)copyWithZone:(NSZone *)zone {
    return self;
}
- (id)retain {
    return self;
}
- (unsigned)retainCount {
    return UINT_MAX; //denotes an object that cannot be released
}
- (oneway void)release {
    // never release
}
- (id)autorelease {
    return self;
}

- (void)dealloc {
    // Should never be called, but just here for clarity really.
    [mapRequestQueue release];
    [baseUrl release];
    [mapData release];
    [mapLocationController release];
    [currentLocation release];
    [currentMapTile release];
    [super dealloc];
}

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
        self.mapLocationController = [Location sharedInstance];
        mapLocationController.delegate = self;
        mapLocationController.locMgr.desiredAccuracy = kCLLocationAccuracyBest;
        [mapLocationController.locMgr startUpdatingLocation];
    }
    return self;
}

-(void)grabTileForParams:(MapTileParams)mapParams{
    if(self.baseUrl){
        if (![self mapRequestQueue]) {
            [self setMapRequestQueue:[[[NSOperationQueue alloc] init] autorelease]];
        }
        NSString *urlString = [[self getUrlFromParams:mapParams] retain];
        NSURL *url = [NSURL URLWithString:urlString];
        NSLog(@"FINAL URL : %@", url);
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
    self.currentMapTile = [UIImage imageWithData:mapData];
    
}

-(void)setCurrentMapTile:(UIImage *)argCurrentMapTile{
    
    if(currentMapTile){
        currentMapTile = NULL;
        [currentMapTile release];
    }
    currentMapTile = argCurrentMapTile;
    [delegate didDownloadMapTile:currentMapTile];
}

-(UIImage *)currentMapTile{
    
    if(currentMapTile)
        return currentMapTile;
    else
        return NULL;
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
    [delegate couldNotDownLoadTile:error];
}


-(NSString *)getUrlFromParams:(MapTileParams)params{
    
    NSString *latStringVal = [NSString stringWithFormat:@"%.15f",params.latitude];
    NSString *longStringVal = [NSString stringWithFormat:@"%.15f",params.longitude];
    NSString *zoomStringVal = [[[NSDecimalNumber alloc] initWithDouble:params.zoomLevel] stringValue];
    self.paramString = [[NSString alloc] initWithFormat:@"%@%@,%@,%@/20X20.png",self.baseUrl,latStringVal,longStringVal,zoomStringVal];
    //self.paramString = [self.baseUrl stringByAppendingString:self.paramString];
    NSLog(@"URL : %@", self.paramString);
    return self.paramString ;
    
    
}

-(void)setCurrentMapParamsWithLat:(long double)lat longitude:(long double)longi andZoomLevel:(float)zoomLevel{
    currentTileParams.latitude = lat;
    currentTileParams.longitude = longi;
    currentTileParams.zoomLevel = zoomLevel;
    [self grabTileForParams:currentTileParams];
}

-(void)locationUpdate:(CLLocation *)location{
    self.currentLocation = location;
    [self setCurrentMapParamsWithLat:location.coordinate.longitude longitude:location.coordinate.latitude
                        andZoomLevel:ZOOM_LEVEL];
    
    
    
}

-(void)locationError:(NSError *)error{
    NSError *locationServiceError = [error retain];
    if(error){
        UIAlertView *locationErrorAlert = [[UIAlertView alloc] initWithTitle:@"Location Services Error" message:@"Unable to find your location, check to activate necessary services" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [locationErrorAlert show];
            [locationErrorAlert release];
    }
    [locationServiceError release];
}
@end
