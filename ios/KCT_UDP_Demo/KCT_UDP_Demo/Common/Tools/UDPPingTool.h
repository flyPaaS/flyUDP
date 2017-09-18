//
//  UDPPingTool.h
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/15.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UDPPingTool : NSObject


- (void)setPingArray:(NSArray *)ipArray;
- (void)startPing;
- (void)stopPing;

@end
