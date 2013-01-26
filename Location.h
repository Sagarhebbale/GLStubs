//
//  Location.h
//  Incantor
//
//  Created by Sagar on 1/25/13.
//  Copyright (c) 2013 Sagar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@protocol LocationControllerDelegate
@required
- (void)locationUpdate:(CLLocation *)location; // Our location updates are sent here
- (void)locationError:(NSError *)error;

// Any errors are sent here
@end

@interface Location : NSObject<CLLocationManagerDelegate>{
    CLLocationManager *locMgr;
	id delegate;
}


@property (nonatomic, assign) id delegate;
@property (nonatomic , retain)CLLocationManager *locMgr;

+ (id)sharedInstance;

@end