//
//  SessionItem.h
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/9/21.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SessionItem : NSObject
@property (nonatomic,strong) NSString *ssip;
@property (nonatomic,strong) NSString *sessionId;
@property (nonatomic,strong) NSString *ssname;
@property (nonatomic,assign) double rtt;

@end
