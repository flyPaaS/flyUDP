//
//  DeviceTool.m
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/28.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "DeviceTool.h"
#import <AudioToolbox/AudioToolbox.h>

@implementation DeviceTool


+ (BOOL)isHeadphone
{
    UInt32 propertySize = sizeof(CFStringRef);
    CFStringRef state = nil;
    AudioSessionGetProperty(kAudioSessionProperty_AudioRoute
                            ,&propertySize,&state);
    //return @"Headphone" or @"Speaker" and so on.
    //根据状态判断是否为耳机状态
    if ([(__bridge NSString *)state isEqualToString:@"Headphone"] ||[(__bridge NSString *)state isEqualToString:@"HeadsetInOut"])
    {
        return YES;
    }else {
        return NO;
    }
}


@end
