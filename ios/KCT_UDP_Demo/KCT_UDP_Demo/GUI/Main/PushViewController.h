//
//  PushViewController.h
//  UdpPush
//
//  Created by KCMac on 2017/6/14.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^stopPullStreamBlock)(void);

@interface PushViewController : UIViewController

@property (nonatomic,weak) IBOutlet UIView *remoteViewBgView;
@property (nonatomic,weak) IBOutlet UIView *localViewBgView;

@property (nonatomic,strong) NSDictionary *apinfoDict;
@property (nonatomic,strong) NSString *sessionId;
@property (nonatomic,copy) stopPullStreamBlock block;

@end
