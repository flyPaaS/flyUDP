//
//  ConfigViewController.m
//  KCT_UDP_Demo
//
//  Created by KCMac on 2017/8/31.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "ConfigViewController.h"

@interface ConfigViewController ()

@property(strong,nonatomic) NSMutableArray *videoCellArray;
@property(strong,nonatomic) NSArray *bitRateArray;


@property(strong,nonatomic) IBOutlet UITableView *tableView;

@end

@implementation ConfigViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"config";
    //data
    
    self.videoCellArray = [NSMutableArray new];
    self.bitRateArray = @[@"200",@"500",@"600",@"700",@"800",@"900",@"1000",@"1100",@"1200",@"1300",@"1400",@"1500",@"1600",@"1700",@"1800",@"1900",@"2000"];
    
    
    UIBarButtonItem *buttonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(setting)];
    self.navigationItem.rightBarButtonItem = buttonItem;
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"codec"];
    //self.tableView.backgroundColor = [UIColor redColor];
    self.tableView.contentInset = UIEdgeInsetsMake(-50,0,0,0);
    
    // Do any additional setup after loading the view.
}


#pragma mark-----button
- (void)setting
{
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    [userDefault setObject:[NSNumber numberWithInteger:self.bitRateValue] forKey:kBitRateIndex];
    [userDefault synchronize];
    [self.navigationController popViewControllerAnimated:YES];
}


#pragma mark----tableview
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}


- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return @"码率设置";
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 320, 24)];
    label.text = @"";
    return label;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 45;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return self.bitRateArray.count;
}


- (void)tableView:(UITableView *)aTableView didSelectRowAtIndexPath:(NSIndexPath *)anIndexPath
{
    for (int i = 0; i<self.videoCellArray.count; i++) {
        UITableViewCell *cell = (UITableViewCell *)[self.videoCellArray objectAtIndex:i];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    UITableViewCell *cell = [aTableView cellForRowAtIndexPath:anIndexPath];
    cell.accessoryType = UITableViewCellAccessoryCheckmark;
    NSString *bit = [self.bitRateArray objectAtIndex:anIndexPath.row];
    self.bitRateValue = [bit integerValue];
}


- (UITableViewCell *)tableView:(UITableView *)aTableView cellForRowAtIndexPath:(NSIndexPath *)anIndexPath
{
    
    UITableViewCell *cell = [aTableView dequeueReusableCellWithIdentifier:@"codec" forIndexPath:anIndexPath];
    
    NSString *title = [self.bitRateArray objectAtIndex:anIndexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@kbps",title];
    if ([title integerValue] == self.bitRateValue) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    } else
    {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    if (![self.videoCellArray containsObject:cell])
    {
        [self.videoCellArray addObject:cell];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
