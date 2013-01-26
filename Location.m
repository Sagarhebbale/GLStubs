//
//  Location.m
//  Incantor
//
//  Created by Sagar on 1/25/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import "Location.h"

static Location *sharedLocation = nil;

@implementation Location
@synthesize delegate;
@synthesize locMgr;

#pragma mark Singleton Methods
+ (id)sharedInstance {
    @synchronized(self) {
        if(sharedLocation == nil)
            sharedLocation = [[super allocWithZone:NULL] init];
    }
    return sharedLocation;
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
- (id)init {
    if (self = [super init]) {
        locMgr = [[CLLocationManager alloc] init];// Create new instance of locMgr
        locMgr.desiredAccuracy = kCLLocationAccuracyBest;
        locMgr.distanceFilter = kCLLocationAccuracyBest;
		locMgr.delegate = self; // Set the delegate as self.
    }
    return self;
}
- (void)dealloc {
    // Should never be called, but just here for clarity really.
    //[someProperty release];
    [super dealloc];
}

#pragma Location Delegates

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
	if([self.delegate conformsToProtocol:@protocol(LocationControllerDelegate)]) {  // Check if the class assigning itself as the delegate conforms to our protocol.  If not, the message will go nowhere.  Not good.
        if((oldLocation.coordinate.latitude != newLocation.coordinate.latitude) || (oldLocation.coordinate.longitude != oldLocation.coordinate.longitude)){
            NSLog(@"Location Services Update. Lat:%.14f Long:%.14f",newLocation.coordinate.latitude,newLocation.coordinate.longitude);
            [self.delegate locationUpdate:newLocation];
        }
		
	}
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
	if([self.delegate conformsToProtocol:@protocol(LocationControllerDelegate)]) {  // Check if the class assigning itself as the delegate conforms to our protocol.  If not, the message will go nowhere.  Not good.
		[self.delegate locationError:error];
	}
}



@end
