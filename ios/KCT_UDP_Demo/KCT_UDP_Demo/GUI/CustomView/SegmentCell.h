//
//  SegmentCell.h
//  UdpPush
//
//  Created by KCMac on 2017/6/13.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SegmentCell : UITableViewCell

@property(nonatomic,assign) NSInteger selectIndex;
@property(nonatomic,weak) IBOutlet UISegmentedControl *segmentedContrl;

@end
