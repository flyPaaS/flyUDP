//
//  MainViewController.m
//  UdpPush
//
//  Created by KCMac on 2017/6/13.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "MainViewController.h"

@interface MainViewController ()<UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate>
{
    NSInteger _streamIndex;
    NSInteger _segmentSelectIndex;
    NSInteger _ipSelectIndex;
}

@property (strong, nonatomic) NSString *srsIpAdress;
@property (strong, nonatomic) NSString *sessionId;
@property (strong, nonatomic) NSMutableArray *ipArrays;
@property (strong, nonatomic) NSMutableArray *sessionArrays;
@property (strong,nonatomic) NSMutableArray *tempArrays;

@property (weak, nonatomic) IBOutlet UIButton *pullBtn;
@property (weak, nonatomic) IBOutlet UITableView *serIpTableView;
@property (weak, nonatomic) IBOutlet UITableView *serInfoTableView;
@property (weak, nonatomic) IBOutlet UILabel *versionLabel;
@property(nonatomic,strong) UISegmentedControl *streamSegmentedControl;
@property (strong, nonatomic) UIBarButtonItem *rightButtonItem;
@property (strong, nonatomic) IBOutlet UILabel *topLabel;
@property (strong, nonatomic) IBOutlet UIButton *refreshBtn;

@end

@implementation MainViewController

- (void)awakeFromNib {
    [super awakeFromNib];
    self.serIpTableView.contentInset = UIEdgeInsetsMake(-35, 0, 0, 0);
    self.serInfoTableView.contentInset = UIEdgeInsetsMake(-20, 0, 0, 0);
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    if (_streamIndex == 0) {
        [self updateSession];
    }
}


- (void)viewDidLoad {
    [super viewDidLoad];
    _tempArrays = [NSMutableArray new];
    _sessionArrays = [NSMutableArray new];
    self.title = nil;
    
    _segmentSelectIndex = 0;
    _streamIndex = 0;
    _ipSelectIndex = -1;
    [self getSerIps];
    
    NSArray *segItems = @[@"Push",@"pull"];
    _streamSegmentedControl = [[UISegmentedControl alloc] initWithItems:segItems];
    _streamSegmentedControl.frame = CGRectMake(0, 0, 160, 30);
    self.navigationItem.titleView = _streamSegmentedControl;
    _streamSegmentedControl.selectedSegmentIndex = 0;
    [_streamSegmentedControl addTarget:self action:@selector(segmentedChanged:) forControlEvents:UIControlEventValueChanged];
    self.streamSegmentedControl.selectedSegmentIndex = 0;
    
    self.refreshBtn.hidden = YES;
    self.serInfoTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.versionLabel.text = [self getVersionNum];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(enterForeground)
                                                 name:UIApplicationWillEnterForegroundNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(enterBackground)
                                                 name:UIApplicationDidEnterBackgroundNotification
                                               object:nil];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark-
#pragma mark--------TableView-----------


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (tableView == self.serIpTableView) {
        if (_streamIndex == 1) {
            return self.sessionArrays.count;
        }
        return self.ipArrays.count;
    } else {
        if (_streamIndex == 1) {
            return 2;
        }
        return pushListTypeCounts;
    }
    return pushListTypeCounts;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger row = indexPath.row;
    if (tableView == self.serIpTableView) {
        return 44;
    } else {
        if (_streamIndex == 1 && row == 0) {
            return 60;
        }
        return 44;
    }
    return 44;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger row = indexPath.row;
    
    if (tableView == self.serInfoTableView) {
        if (_streamIndex == 0) {
            UITableViewCell *resultCell = nil;
            SegmentCell *cell2 = nil;
            cell2 = [tableView dequeueReusableCellWithIdentifier:@"segmetCell"];
            [cell2.segmentedContrl addTarget:self action:@selector(segmentedChanged:) forControlEvents:UIControlEventValueChanged];
            resultCell = cell2;
            resultCell.selectionStyle = UITableViewCellSelectionStyleNone;
            return resultCell;
        } else {
            UITableViewCell *resultCell = nil;
            switch (row) {
                case 0:
                {
                    RefreshTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"RefreshTableViewCell"];
                    [cell.button addTarget:self action:@selector(refreshSessionList) forControlEvents:UIControlEventTouchUpInside];
                    resultCell = cell;
                }
                    break;
                case 1:
                {
                    SegmentCell *cell2 = nil;
                    cell2 = [tableView dequeueReusableCellWithIdentifier:@"segmetCell"];
                    [cell2.segmentedContrl addTarget:self action:@selector(segmentedChanged:) forControlEvents:UIControlEventValueChanged];
                    resultCell = cell2;
                }
                    break;
                default:
                    break;
            }
            resultCell.selectionStyle = UITableViewCellSelectionStyleNone;
            return resultCell;
        }
    } else {
        RadioCell *cell = [tableView dequeueReusableCellWithIdentifier:@"RadioCell"];
        if (_streamIndex == 0) {
            AddressListItem *item = [self.ipArrays objectAtIndex:row];
            NSString *title = item.ssip;
            NSString *ssname = item.ssname;
            //double rtt = item.rtt;
            cell.label.text = [NSString stringWithFormat:@"%@(%@)",title,ssname];
        } else {
            SessionItem *item = [self.sessionArrays objectAtIndex:row];
            cell.label.text = [NSString stringWithFormat:@"%@(%@)",item.ssname,item.sessionId];
        }
        
        if (row == _ipSelectIndex) {
            [cell.button setImage:[UIImage imageNamed:@"checkBtn.png"] forState:UIControlStateNormal];
        } else {
            [cell.button setImage:[UIImage imageNamed:@"unCheckBtn.png"] forState:UIControlStateNormal];
        }
        [cell.button addTarget:self action:@selector(radioButtonSelect:) forControlEvents:UIControlEventTouchUpInside];
        cell.button.tag = row;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        return cell;
    }
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView == self.serIpTableView) {
        NSInteger row = indexPath.row;
        [self changeCellState:row];
        _ipSelectIndex = row;
        if (_streamIndex == 0) {
            [self pingAddressItem:row];
        }
    }
}

#pragma mark---TextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

#pragma mark-
#pragma mark----------Button Event-------------

- (void)segmentedChanged:(id)sender {
    UISegmentedControl *segment = (UISegmentedControl *)sender;
    if (segment == self.streamSegmentedControl) {
        _ipSelectIndex = -1;
        _streamIndex = segment.selectedSegmentIndex;
        [self.serInfoTableView reloadData];
        [self.serIpTableView reloadData];
        if (_streamIndex == 0) {
            [self updateSession];
            [self.pullBtn setTitle:@"Push" forState:UIControlStateNormal];
            self.navigationItem.rightBarButtonItem = nil;
            self.topLabel.text = @"选择会话中转服务器";
        } else {
            self.sessionId = nil;
            [self.pullBtn setTitle:@"Pull" forState:UIControlStateNormal];
            self.navigationItem.rightBarButtonItem = self.rightButtonItem;
            self.topLabel.text = @"选择会话";
        }
        
    } else {
        _segmentSelectIndex = segment.selectedSegmentIndex;
    }
}

- (void)radioButtonSelect:(id)sender {
    UIButton *btn = (UIButton *)sender;
    NSInteger tag = btn.tag;
    _ipSelectIndex = tag;
    [self changeCellState:tag];
    if (_streamIndex == 0) {
        [self pingAddressItem:tag];
    }
}

- (IBAction)pushClick:(id)sender
{
    if (_ipSelectIndex == -1) {
        return;
    }
    
    if (_streamIndex == 0) {
        [self streamPush];
    } else {
        [self streamPull];
    }
    
}

- (void)back:(id)sender
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)refreshSessionList
{
    [self getStreamList:self.ipArrays needReload:YES];
}

//这个方式暂时没使用
- (void)configSetting
{
    UIStoryboard *board = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    ConfigViewController *configVC = [board instantiateViewControllerWithIdentifier:@"ConfigViewController"];
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSNumber *index = [userDefault objectForKey:kBitRateIndex];
    configVC.bitRateValue = [index integerValue];
    [self.navigationController pushViewController:configVC animated:YES];
}

#pragma mark-
#pragma mark---------private----------

- (NSString *)getVersionNum {
    NSString *result;
    NSDictionary *dic = [[NSBundle mainBundle]infoDictionary];
    result = [NSString stringWithFormat:@"V %@",[dic objectForKey:@"CFBundleShortVersionString"]];
    return result;
}


- (void)updateSession
{
    if (self.sessionId) {
        [MBProgressHUD showSuccess:@"sessionId已更新"];
    }
    self.sessionId = [self createSessionId];
}

- (void)changeCellState:(NSInteger)index
{
    NSInteger count = 0;
    count = [self.ipArrays count];
    if (_streamIndex == 1) {
        count = [self.sessionArrays count];
    }
    for (int i = 0; i < count; i++) {
        NSIndexPath *path = [NSIndexPath indexPathForRow:i inSection:0];
        RadioCell *cell = [self.serIpTableView cellForRowAtIndexPath:path];
        [cell.button setImage:[UIImage imageNamed:@"unCheckBtn.png"] forState:UIControlStateNormal];
    }
    
    //select cell
    NSIndexPath *path = [NSIndexPath indexPathForRow:index inSection:0];
    RadioCell *cell = [self.serIpTableView cellForRowAtIndexPath:path];
    [cell.button setImage:[UIImage imageNamed:@"checkBtn.png"] forState:UIControlStateNormal];
}

- (NSString *)createSessionId{
    NSMutableString *randomNum = [[NSMutableString alloc] init];
    for(int i = 0; i < 5;i++){
        int num = arc4random() % 10;
        [randomNum appendString:[NSString stringWithFormat:@"%d",num]];
    }
    NSLog(@"--create session :%@",randomNum);
    return randomNum;
}

- (void)getSerIps
{
    NSString *url = @"http://59.110.10.28:8097/v3/getudprelay?";
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url]];
    request.HTTPMethod = @"GET";
    [MBProgressHUD showMessage:@"正在获取推流服务器列表" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        [MBProgressHUD hideHUDForView:self.view];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--getSerIps rsp:  %@",dict);
            NSNumber *result = [dict objectForKey:@"result"];
            if ([result intValue] == 200) {
                NSArray *ips = [dict objectForKey:@"ss"];
                
                self.ipArrays = [self createAddressItem:ips];
                //[self pingAddressItem:0];
                [self pingArray:self.ipArrays];
                [self getStreamList:self.ipArrays needReload:NO];
                _ipSelectIndex = 0;
                dispatch_async(dispatch_get_main_queue(), ^{
                    [MBProgressHUD showSuccess:@"获取成功"];
                    [self.serIpTableView reloadData];
                });
            } else {
                [MBProgressHUD showError:@"获取失败"];
            }
            
        } else {
            [MBProgressHUD showError:@"获取失败"];
        }
    }];
}

- (NSMutableArray *)createAddressItem:(NSArray *)arrays {
    NSMutableArray *resultArray = [NSMutableArray new];
    for (NSDictionary *dic in arrays) {
        AddressListItem *item = [[AddressListItem alloc] init];
        item.ssip = [dic objectForKey:@"ssip"];
        item.ssname = [dic objectForKey:@"ssname"];
        item.rtt = 3000;
        [resultArray addObject:item];
    }
    return resultArray;
}

- (void)pingArray:(NSMutableArray *)arrays {

    [self.tempArrays removeAllObjects];
    for (int i = 0;i<arrays.count;i++) {
        AddressListItem *item = [arrays objectAtIndex:i];
        STDPingServices *services = [[STDPingServices alloc] initWithAddress:item.ssip index:i];
        
        [services startPingWithCallBack:^(STDPingItem *pingItem, NSArray *pingItems,NSString *addr,NSInteger index) {
            if (pingItem.status != STDPingStatusFinished) {
                
            } else {
                double result = [STDPingItem getAverageRtt:pingItems];
                AddressListItem *tempItem = [arrays objectAtIndex:index];
                tempItem.rtt = result;
                
                NSLog(@"-----%@----%f",addr,result);
                
            }
        }];

        [self.tempArrays addObject:services];
    }
}


- (void)pingAddressItem:(NSInteger)row {
    //[self.tempArrays removeAllObjects];
    AddressListItem *item = [self.ipArrays objectAtIndex:row];
    if (item.rtt == 3000 || item.rtt == 0) {
        STDPingServices *services = [[STDPingServices alloc] initWithAddress:item.ssip index:row];
        
        [services startPingWithCallBack:^(STDPingItem *pingItem, NSArray *pingItems,NSString *addr,NSInteger index) {
            if (pingItem.status != STDPingStatusFinished) {
                //AddressListItem *tempItem = [self.ipArrays objectAtIndex:index];
                NSLog(@"--------%f",pingItem.timeMilliseconds);
            } else {
                double result = [STDPingItem getAverageRtt:pingItems];
                AddressListItem *tempItem = [self.ipArrays objectAtIndex:index];
                tempItem.rtt = result;
                
                NSLog(@"-----%@----%f",addr,result);
                
            }
        }];
        [self.tempArrays addObject:services];
    }
    
}

- (void)getStreamList:(NSMutableArray *)serverIpArray needReload:(BOOL)needReload
{
    if (needReload) {
        [MBProgressHUD showMessage:@"正在刷新会话列表" toView:self.view];
    }
    [self.sessionArrays removeAllObjects];
    
    NSInteger count = serverIpArray.count;
    __block NSInteger kT = 0;
    for (int i = 0; i< serverIpArray.count; i++) {
        AddressListItem *ipItem = [serverIpArray objectAtIndex:i];
        NSString *url = [NSString stringWithFormat:@"http://%@:8095/udprelay/v1/getStreamList",ipItem.ssip];
        NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url]];
        request.HTTPMethod = @"GET";
        [request setTimeoutInterval:2.0];
        [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
            
            if (data) {
                NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
                NSArray *list = [dict objectForKey:@"list"];
                //NSLog(@"-%d-%@-list:%@",i,ipItem.ssname,dict);
                for (int i = 0; i < list.count; i++) {
                    SessionItem *item = [[SessionItem alloc] init];
                    item.ssip = ipItem.ssip;
                    item.ssname = ipItem.ssname;
                    item.rtt = ipItem.rtt;
                    item.sessionId = [list objectAtIndex:i];
                    [self.sessionArrays addObject:item];
                }
            }
            
            kT++;
            if (needReload && (kT== count)) {
                [self.serIpTableView reloadData];
                
                [MBProgressHUD hideHUDForView:self.view];
                
                if (self.sessionArrays.count == 0) {
                    [MBProgressHUD showError:@"会话列表为空"];
                }
            }
        }];
    }
}


- (void)streamPush
{
    NSString *port = @"8095";
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    double rtt = item.rtt;
    NSString *ipAddr = item.ssip;
    NSString *ssname = item.ssname;
    NSString *streamPushUrl = nil;
    if (rtt < 40) {
        streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%d",ipAddr,port,self.sessionId,0];
    } else {
        streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%ld",ipAddr,port,self.sessionId,_segmentSelectIndex];
    }
    
    NSLog(@"push url :%@",streamPushUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPushUrl]];
    request.HTTPMethod = @"GET";
    [MBProgressHUD showMessage:@"正在获取接入点" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:YES];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            NSLog(@"--push apInfo:--%@",apInfo);
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [MBProgressHUD showSuccess:@"获取成功"];
                    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
                    PushViewController *pushVC = [storyboard instantiateViewControllerWithIdentifier:@"PushViewController"];
                    pushVC.apinfoDict = apInfo;
                    pushVC.ssname = ssname;
                    pushVC.sessionId = self.sessionId;
                    pushVC.block = ^{
                        [self streamRelease];
                    };
                    [self.navigationController pushViewController:pushVC animated:YES];
                });
            } else {
                
            }
            
            
        } else {
            
        }
    }];
}


- (void)streamPull
{
    NSString *port = @"8095";
    SessionItem *item = [self.sessionArrays objectAtIndex:_ipSelectIndex];
    double rtt = item.rtt;
    NSString *ipAddr = item.ssip;
    NSString *ssname = item.ssname;
    NSString *sessionId = item.sessionId;
    NSString *streamPullUrl = nil;
    if (rtt < 40) {
        streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@&streamCan=%d",ipAddr,port,sessionId,0];
    } else {
        streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@&streamCan=%ld",ipAddr,port,sessionId,_segmentSelectIndex];
    }
    NSLog(@"pull url :%@",streamPullUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPullUrl]];
    request.HTTPMethod = @"GET";
    [MBProgressHUD showMessage:@"正在获取接入点" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:YES];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--pull 获取接入点--%@",dict);
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [MBProgressHUD showSuccess:@"获取成功"];
                    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
                    PullViewController *pushVC = [storyboard instantiateViewControllerWithIdentifier:@"PullViewController"];
                    pushVC.apinfoDict = apInfo;
                    pushVC.sessionId = sessionId;
                    pushVC.ssname = ssname;
                    pushVC.block = ^{
                        [self pullStop];
                    };
                    
                    [self.navigationController pushViewController:pushVC animated:YES];
                });
            } else {
                NSString *resultStr = [dict objectForKey:@"result"];
                if ([resultStr isEqualToString:@"000002"]) {
                    [MBProgressHUD showError:@"该streamId被占用"];
                } else {
                    [MBProgressHUD showError:@"获取失败"];
                }
            }
            
        } else {
            [MBProgressHUD showError:@"获取失败"];
        }
    }];
}


- (void)streamRelease
{
    NSString *port = @"8095";
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = item.ssip;
    
    NSString *streamReleaseUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamRelease?streamId=%@",ipAddr,port,self.sessionId];
    NSLog(@"push release url :%@",streamReleaseUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamReleaseUrl]];
    request.HTTPMethod = @"GET";
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--streamRelease --%@",dict);
        }
    }];
    
    NSString *strTip = [NSString stringWithFormat:@"streamRelease?streamId=%@",self.sessionId];
    NSLog(@"%@",strTip);
}


- (void)pullStop
{
    NSString *port = @"8095";
    SessionItem *item = [self.sessionArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = item.ssip;
    //NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *sessionId = item.sessionId;
    NSString *pullStopUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/pullStop?streamId=%@",ipAddr,port,sessionId];
    NSLog(@"pullStop url :%@",pullStopUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:pullStopUrl]];
    request.HTTPMethod = @"GET";
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--pullStop rsp:--%@",dict);
        }
    }];
    NSString *strTip = [NSString stringWithFormat:@"pullStop?streamId=%@",sessionId];
    NSLog(@"%@",strTip);
}


- (void)enterBackground
{
    /**
     @author WLS, 15-12-08 18:12:00
     
     当系统进入后台的时候，需要将视频采集关闭，不然会出现崩溃
     */
    [VideoView enableRender:FALSE];
}

- (void)enterForeground
{
    /**
     @author WLS, 15-12-08 18:12:23
     
     当系统进入前台的时候，需要将视频采集打开
     
     */
    [VideoView enableRender:TRUE];
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
