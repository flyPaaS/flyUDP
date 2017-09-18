//
//  UDPPingTool.m
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/15.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "UDPPingTool.h"

@interface UDPPingTool ()
{
    dispatch_queue_t _udpQueue;
}

@end

@implementation UDPPingTool

- (instancetype)init {
    self = [super init];
    if (self) {
        _udpQueue = dispatch_queue_create("udpSend", NULL);
    }
    return self;
}

- (void)setPingArray:(NSArray *)ipArray {
    [self stopPing];
    
}

- (void)startPing {
    
}

- (void)stopPing {
    
}



@end
