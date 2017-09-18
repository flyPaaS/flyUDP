//
//  AddressListItem.h
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/15.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AddressListItem : NSObject

@property (nonatomic,strong) NSString *ssip;
@property (nonatomic,strong) NSString *ssname;
@property (nonatomic,assign) double rtt;

@end
