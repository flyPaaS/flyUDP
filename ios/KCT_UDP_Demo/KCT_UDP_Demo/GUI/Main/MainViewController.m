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
@property (weak, nonatomic) IBOutlet UIButton *pullBtn;
@property (weak, nonatomic) IBOutlet UITableView *serIpTableView;
@property (weak, nonatomic) IBOutlet UITableView *serInfoTableView;
@property (weak, nonatomic) IBOutlet UILabel *versionLabel;
@property(nonatomic,strong)UISegmentedControl *streamSegmentedControl;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *labelTopConstraint;
@property (strong, nonatomic) UITextField *portField;
@property (strong, nonatomic) UITextField *sessionIdField;
@property (strong, nonatomic) NSMutableArray *ipArrays;
@property (strong,nonatomic) NSMutableArray *tempArrays;

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
    
    self.versionLabel.text = [self getVersionNum];
    
    UIBarButtonItem *buttonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemEdit target:self action:@selector(configSetting)];
    self.navigationItem.rightBarButtonItem = buttonItem;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
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

#pragma mark----TableView


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (tableView == self.serIpTableView) {
        return self.ipArrays.count;
    } else {
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
        if (row == pushListTypeSegment) {
            return 80;
        }
        return 44;
    }
    return 44;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger row = indexPath.row;
    
    if (tableView == self.serInfoTableView) {
        UITableViewCell *resultCell = nil;
        LabelAndTextCell *cell = nil;
        SegmentCell *cell2 = nil;
        
        if (row < pushListTypeSegment) {
            cell = [tableView dequeueReusableCellWithIdentifier:@"LabelAndTextCell"];
            switch (row) {
                    /*
                case pushListTypeServerIP:
                {
                    cell.label.text = @"服务器IP:";
                    cell.field.tag = 100;
                    cell.field.text = @"183.60.189.169";
                }
                    break;*/
                case pushListTypeServerPort:
                {
                    cell.label.text = @"服务器端口:";
                    cell.field.text = @"8095";
                    self.portField = cell.field;
                }
                    break;
                case pushListTypeSession:
                {
                    cell.label.text = @"分配的会话ID:";
                    cell.field.text = self.sessionId;
                    if (_streamIndex == 0) {
                        cell.field.enabled = NO;
                    } else {
                        cell.field.enabled = YES;
                        cell.field.placeholder = @"输入sessionId";
                    }
                    
                    self.sessionIdField = cell.field;
                }
                    break;
                default:
                    break;
            }
            resultCell = cell;
            cell.field.delegate = self;
            
        } else {
            cell2 = [tableView dequeueReusableCellWithIdentifier:@"segmetCell"];
            [cell2.segmentedContrl addTarget:self action:@selector(segmentedChanged:) forControlEvents:UIControlEventValueChanged];
            resultCell = cell2;
        }
        resultCell.selectionStyle = UITableViewCellSelectionStyleNone;
        return resultCell;
    } else {
        RadioCell *cell = [tableView dequeueReusableCellWithIdentifier:@"RadioCell"];
        AddressListItem *item = [self.ipArrays objectAtIndex:row];
        //NSDictionary *dic =[self.ipArrays objectAtIndex:row];
        NSString *title = item.ssip;
        NSString *ssname = item.ssname;
        double rtt = item.rtt;
        cell.label.text = [NSString stringWithFormat:@"%@(%@)",title,ssname];
        //cell.label.text = [NSString stringWithFormat:@"%@(%f)",title,rtt];
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
        [self pingAddressItem:row];
    }
}

#pragma mark---TextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}


#pragma mark--Button

- (void)segmentedChanged:(id)sender {
    UISegmentedControl *segment = (UISegmentedControl *)sender;
    if (segment == self.streamSegmentedControl) {
        _streamIndex = segment.selectedSegmentIndex;
        [self.serInfoTableView reloadData];
        if (_streamIndex == 0) {
            [self updateSession];
            [self.pullBtn setTitle:@"Push" forState:UIControlStateNormal];
        } else {
            self.sessionId = nil;
            self.sessionIdField.text = @"";
            [self.pullBtn setTitle:@"Pull" forState:UIControlStateNormal];
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
    [self pingAddressItem:tag];
}

- (IBAction)pushClick:(id)sender
{
    if (_streamIndex == 0) {
        [self streamPush];
    } else {
        if (self.sessionIdField.text == nil || [self.sessionIdField.text isEqualToString:@""]) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"sessionId不能为空" message:@"请输入sessionId" preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
            return;
        }
//        if ([self.sessionId isEqualToString:self.sessionIdField.text]) {
//            [MBProgressHUD showSuccess:@"请确保跟push的sessionid一致"];
//            return;
//        }
        self.sessionId = self.sessionIdField.text;
        [self streamPull];
    }
    
}

- (void)back:(id)sender
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)configSetting
{
    UIStoryboard *board = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    ConfigViewController *configVC = [board instantiateViewControllerWithIdentifier:@"ConfigViewController"];
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSNumber *index = [userDefault objectForKey:kBitRateIndex];
    configVC.bitRateValue = [index integerValue];
    [self.navigationController pushViewController:configVC animated:YES];
}

#pragma mark---private

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
    self.sessionIdField.text = self.sessionId;
}

- (void)changeCellState:(NSInteger)index
{
    for (int i = 0; i < [self.ipArrays count]; i++) {
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
            NSLog(@"--srs  %@",dict);
            NSNumber *result = [dict objectForKey:@"result"];
            if ([result intValue] == 200) {
                NSArray *ips = [dict objectForKey:@"ss"];
                
                self.ipArrays = [self createAddressItem:ips];
                //[self pingAddressItem:0];
                [self pingArray:self.ipArrays];
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

- (void)streamPush
{
    NSString *port = self.portField.text;
    //NSDictionary *dict = [self.ipArrays objectAtIndex:_ipSelectIndex];
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    double rtt = item.rtt;
    //NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *ipAddr = item.ssip;
    NSString *streamPushUrl = nil;
    if (rtt < 40) {
        streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%d",ipAddr,port,self.sessionId,0];
    } else {
        streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%ld",ipAddr,port,self.sessionId,_segmentSelectIndex];
    }
    NSLog(@"---rtt : %f",rtt);
    NSLog(@"push url :%@",streamPushUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPushUrl]];
    request.HTTPMethod = @"GET";
    [MBProgressHUD showMessage:@"正在获取接入点" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:YES];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            NSLog(@"----%@",apInfo);
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [MBProgressHUD showSuccess:@"获取成功"];
                    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
                    PushViewController *pushVC = [storyboard instantiateViewControllerWithIdentifier:@"PushViewController"];
                    pushVC.apinfoDict = apInfo;
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
    NSString *port = self.portField.text;
    //NSDictionary *dict = [self.ipArrays objectAtIndex:_ipSelectIndex];
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    //NSString *ipAddr = [dict objectForKey:@"ssip"];
    double rtt = item.rtt;
    NSString *ipAddr = item.ssip;
    NSString *sessionId = self.sessionIdField.text;
    NSString *streamPullUrl = nil;
    if (rtt < 40) {
        streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@&streamCan=%d",ipAddr,port,sessionId,0];
    } else {
        streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@&streamCan=%ld",ipAddr,port,sessionId,_segmentSelectIndex];
    }
    NSLog(@"push url :%@",streamPullUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPullUrl]];
    request.HTTPMethod = @"GET";
    [MBProgressHUD showMessage:@"正在获取接入点" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:YES];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            NSLog(@"----%@",apInfo);
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [MBProgressHUD showSuccess:@"获取成功"];
                    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
                    PullViewController *pushVC = [storyboard instantiateViewControllerWithIdentifier:@"PullViewController"];
                    pushVC.apinfoDict = apInfo;
                    pushVC.sessionId = self.sessionId;
                    pushVC.block = ^{
                        [self pullStop];
                    };
                    
                    [self.navigationController pushViewController:pushVC animated:YES];
                });
            } else {
                [MBProgressHUD showError:@"获取失败"];
            }
            
        } else {
            [MBProgressHUD showError:@"获取失败"];
        }
    }];
}


- (void)streamRelease
{
    NSString *port = self.portField.text;
    //NSDictionary *dict = [self.ipArrays objectAtIndex:_ipSelectIndex];
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = item.ssip;
    //NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *streamReleaseUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamRelease?streamId=%@",ipAddr,port,self.sessionId];
    NSLog(@"push url :%@",streamReleaseUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamReleaseUrl]];
    request.HTTPMethod = @"GET";
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--streamRelease--%@",dict);
        }
    }];
}


- (void)pullStop
{
    NSString *port = self.portField.text;
    //NSDictionary *dict = [self.ipArrays objectAtIndex:_ipSelectIndex];
    AddressListItem *item = [self.ipArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = item.ssip;
    //NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *sessionId = self.sessionIdField.text;
    NSString *pullStopUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/pullStop?streamId=%@",ipAddr,port,sessionId];
    NSLog(@"push url :%@",pullStopUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:pullStopUrl]];
    request.HTTPMethod = @"GET";
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--pullStop--%@",dict);
        }
    }];
}

- (void)keyboardWillShow:(NSNotification *)info
{
    CGRect keyboardBounds = [[[info userInfo] objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGRect textRect = self.portField.frame;
    float textY = self.serInfoTableView.frame.origin.y;
    float textHeight = textRect.size.height;
    float keyboardY = keyboardBounds.origin.y;
    float space = keyboardY-(textY+textHeight+7);
    if (space > 30.0) {
        NSLog(@"---not need show %f",space);
    } else {
        self.labelTopConstraint.constant = -space-15;
    }
}

- (void)keyboardWillHide:(NSNotification *)info
{
    self.labelTopConstraint.constant = 2;
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
