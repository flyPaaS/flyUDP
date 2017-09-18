//
//  ConfigViewController.h
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/31.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ConfigViewController : UIViewController
typedef void(^sysConfigBlock)(void);


@property (nonatomic,copy) sysConfigBlock block;
@property(assign,nonatomic) NSInteger bitRateValue;

@end
