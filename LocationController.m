//
//  LocationManager.m
//  Incantor
//
//  Created by Sagar on 1/22/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import "LocationController.h"

@implementation LocationController

@synthesize locMgr, delegate;

-(id)init {
	self = [super init];
    
	if(self != nil) {
		self.locMgr = [[CLLocationManager alloc] init];// Create new instance of locMgr
        self.locMgr.desiredAccuracy = kCLLocationAccuracyBest;
        self.locMgr.distanceFilter = kCLLocationAccuracyBest;
		self.locMgr.delegate = self; // Set the delegate as self.
	}
    
	return self;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
	if([self.delegate conformsToProtocol:@protocol(LocationControllerDelegate)]) {  // Check if the class assigning itself as the delegate conforms to our protocol.  If not, the message will go nowhere.  Not good.
        if((oldLocation.coordinate.latitude != newLocation.coordinate.latitude) || (oldLocation.coordinate.longitude != oldLocation.coordinate.longitude)){
            NSLog(@"Location Services Update. Lat:%f Long:%f",newLocation.coordinate.latitude,newLocation.coordinate.longitude);
            [self.delegate locationUpdate:newLocation];
        }
		
	}
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
	if([self.delegate conformsToProtocol:@protocol(LocationControllerDelegate)]) {  // Check if the class assigning itself as the delegate conforms to our protocol.  If not, the message will go nowhere.  Not good.
		[self.delegate locationError:error];
	}
}

- (void)dealloc {
	[locMgr release];
	[super dealloc];
}
@end
