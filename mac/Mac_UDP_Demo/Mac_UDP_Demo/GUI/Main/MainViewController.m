//
//  MainViewController.m
//  Mac_UDP_Demo
//
//  Created by KCMac on 2017/6/20.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "MainViewController.h"

@interface MainViewController ()<NSTableViewDelegate,NSTableViewDataSource>
{
    NSInteger _ipSelectIndex;
    NSInteger _streamIndex;
    NSInteger _sendIndex;
    BOOL _isPlaying;
}

@property(nonatomic,strong) NSMutableArray *sourceArrays;
@property(nonatomic,strong) NSString *sessionId;
@property (strong, nonatomic) NSMutableArray *sessionArrays;

@property(nonatomic,weak) IBOutlet NSSegmentedControl *streamSegment;
@property(nonatomic,weak) IBOutlet NSTextField *topTextField;
@property(nonatomic,weak) IBOutlet NSTableView *serIpTableView;
@property(nonatomic,weak) IBOutlet NSView *refreshView;
@property(nonatomic,weak) IBOutlet NSButton *refreshButton;
@property(nonatomic,weak) IBOutlet NSProgressIndicator *refreshProgressInd;
@property(nonatomic,weak) IBOutlet NSBox *leftBox;
@property(nonatomic,weak) IBOutlet NSBox *rightBox;
@property(nonatomic,strong) NSOpenGLView *videoLocationView;
@property(nonatomic,strong) NSOpenGLView *videoRemoteView;
@property(nonatomic,weak) IBOutlet NSTextView *textView;
@property(nonatomic,weak) IBOutlet NSButton *radioBtn0;
@property(nonatomic,weak) IBOutlet NSButton *radioBtn1;
@property(nonatomic,weak) IBOutlet NSButton *startBtn;
@property(nonatomic,weak) IBOutlet NSButton *stopBtn;
@property(nonatomic,weak) IBOutlet NSProgressIndicator *progressInd;
@property(nonatomic,weak) IBOutlet NSTextField *loadLabel;
@property(nonatomic,weak) NSTextField *noSessionTipTextField;

@end

static MainViewController *selfPtr = nil;

@implementation MainViewController

- (void)viewDidAppear {
    [super viewDidAppear];
    
    AppDelegate *delegate = NSApp.delegate;
    delegate.appWindow = [self.view window];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //Data
    _ipSelectIndex = 0;
    _streamIndex = 0;
    _sendIndex = 0;
    _sessionArrays = [NSMutableArray new];
    [self getSerIps];
    
    selfPtr = self;
    
    //View
    self.streamSegment.integerValue = _streamIndex;
    self.refreshView.hidden = YES;
    self.topTextField.stringValue = @"选择会话中转服务器";
    
    self.sessionId = [self createSessionId];
    self.textView.textColor = [NSColor redColor];
    self.progressInd.hidden = YES;
    self.loadLabel.stringValue = @"";
    // Do view setup here.
}


#pragma mark---TableView Delegate
- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row
{
    return 45;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    if (_streamIndex == 1) {
        return self.sessionArrays.count;
    }
    return self.sourceArrays.count;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    IpTalbeCellView *cell = [tableView makeViewWithIdentifier:@"IpTalbeCellView" owner:nil];
    if (_streamIndex == 0) {
        NSDictionary *ipDict = [self.sourceArrays objectAtIndex:row];
        NSString *ssip = [ipDict objectForKey:@"ssip"];
        NSString *ssname = [ipDict objectForKey:@"ssname"];
        cell.addrTextFiled.stringValue = [NSString stringWithFormat:@"%@(%@)",ssip,ssname];
    } else {
        NSDictionary *ipDict = [self.sessionArrays objectAtIndex:row];
        NSString *sessionId = [ipDict objectForKey:@"sessionId"];
        NSString *ssname = [ipDict objectForKey:@"ssname"];
        cell.addrTextFiled.stringValue = [NSString stringWithFormat:@"%@(%@)",ssname,sessionId];
    }
    
    NSImage *image;
    if (_ipSelectIndex == row) {
        image = [NSImage imageNamed:@"checkBtn.png"];
    } else {
        image = [NSImage imageNamed:@"uncheckBtn.png"];
    }
    [cell.button2 setImage:image];
    [cell.button2 setTarget:self];
    [cell.button2 setAction:@selector(cellButtonPress:)];
    cell.button2.tag = row;
    return cell;
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    NSInteger row = self.serIpTableView.selectedRow;
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        return;
    }
    [self changeState:row];
    _ipSelectIndex = row;
}


#pragma mark----private
- (void)getSerIps
{
    NSString *url = @"http://59.110.10.28:8097/v3/getudprelay?";
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url]];
    request.HTTPMethod = @"GET";
    //[MBProgressHUD showMessage:@"正在获取推流服务器列表" toView:self.view];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        //[MBProgressHUD hideHUDForView:self.view];
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSLog(@"--srs  %@",dict);
            NSNumber *result = [dict objectForKey:@"result"];
            if ([result intValue] == 200) {
                NSArray *ips = [dict objectForKey:@"ss"];
                self.sourceArrays = [NSMutableArray arrayWithArray:ips];
                [self getStreamList:self.sourceArrays needReload:NO];
                _ipSelectIndex = 0;
                dispatch_async(dispatch_get_main_queue(), ^{
                    //[MBProgressHUD showSuccess:@"获取成功"];
                    [self.serIpTableView reloadData];
                });
            } else {
                //[MBProgressHUD showError:@"获取失败"];
            }
            
        } else {
            //[MBProgressHUD showError:@"获取失败"];
        }
    }];
}


- (void)getStreamList:(NSMutableArray *)serverIpArray needReload:(BOOL)needReload
{
    if (needReload) {
        self.refreshButton.enabled = NO;
        self.refreshProgressInd.hidden = NO;
    }
    [self.sessionArrays removeAllObjects];
    
    NSInteger count = serverIpArray.count;
    __block NSInteger kT = 0;
    for (int i = 0; i< serverIpArray.count; i++) {
        NSDictionary *dict = [serverIpArray objectAtIndex:i];
        NSString *ipAdress = [dict objectForKey:@"ssip"];
        NSString *ssname = [dict objectForKey:@"ssname"];
        NSString *url = [NSString stringWithFormat:@"http://%@:8095/udprelay/v1/getStreamList",ipAdress];
        NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url]];
        request.HTTPMethod = @"GET";
        [request setTimeoutInterval:3.0];
        [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
            
            if (data) {
                NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
                NSArray *list = [dict objectForKey:@"list"];
                //NSLog(@"-%d-%@-list:%@",i,ipItem.ssname,dict);
                for (int i = 0; i < list.count; i++) {
                    NSMutableDictionary *subDic = [[NSMutableDictionary alloc] init];
                    [subDic setObject:ipAdress forKey:@"ssip"];
                    [subDic setObject:ssname forKey:@"ssname"];
                    [subDic setObject:[list objectAtIndex:i] forKey:@"sessionId"];
                    
                    [self.sessionArrays addObject:subDic];
                }
                
                if (list.count != 0) {
                    [self.serIpTableView reloadData];
                }
            }
            kT++;
            if (needReload && (kT== count)) {
                self.refreshProgressInd.hidden = YES;
                self.refreshButton.enabled = YES;
                if (self.sessionArrays.count == 0) {
                    if (!self.noSessionTipTextField) {
                        NSRect tableRect = self.serIpTableView.frame;
                        NSRect rect = NSMakeRect((tableRect.size.width-120)/2, (tableRect.size.height-30)/2, 120, 30);
                        NSTextField *filed = [[NSTextField alloc] initWithFrame:rect];
                        filed.editable = NO;
                        self.noSessionTipTextField = filed;
                        self.noSessionTipTextField.bordered = NO;
                        self.noSessionTipTextField.textColor = [NSColor redColor];
                        self.noSessionTipTextField.stringValue = @"会话列表为空";
                        [self.serIpTableView reloadData];
                        self.noSessionTipTextField.font = [NSFont systemFontOfSize:15.0];
                        self.noSessionTipTextField.backgroundColor = [NSColor clearColor];
                        [self.serIpTableView addSubview:self.noSessionTipTextField];
                    }
                } else {
                    if (self.noSessionTipTextField) {
                        [self.noSessionTipTextField removeFromSuperview];
                        self.noSessionTipTextField = nil;
                    }
                }
            }
        }];
    }
}


- (void)streamPush
{
    NSString *port = @"8095";
    NSDictionary *dict = [self.sourceArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *ssname = [dict objectForKey:@"ssname"];
    NSString *streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%ld",ipAddr,port,self.sessionId,_sendIndex];
    NSLog(@"push url :%@",streamPushUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPushUrl]];
    request.HTTPMethod = @"GET";
    //[request setTimeoutInterval:2.0];
    self.loadLabel.stringValue = @"正在获取接入点";
    self.progressInd.hidden = NO;
    self.loadLabel.hidden = NO;
    [self.progressInd startAnimation:nil];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        
        self.progressInd.hidden = YES;
        dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC);
        dispatch_after(time, dispatch_get_main_queue(), ^{
            self.loadLabel.hidden = YES;
        });
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            NSLog(@"----%@",apInfo);
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    self.loadLabel.stringValue = @"获取成功";
                    AppDelegate *appDelegate = NSApp.delegate;
                    NSString *title = [NSString stringWithFormat:@"%@(%@)",ssname,self.sessionId];
                    [appDelegate.appWindow setTitle:title];
                    [self startMedia:apInfo];
                });
            } else {
                self.loadLabel.stringValue = @"获取失败";
                _isPlaying = NO;
                self.sessionId = [self createSessionId];
            }
            
            
        } else {
            self.loadLabel.stringValue = @"获取失败";
            _isPlaying = NO;
        }
    }];
}

void on_vogo_cb(int ev_type, int ev_reason, const char* something, void* param, int size)
{
    //printf("----ev_type: %d  log :%s\n",ev_type,something);
    //printf("---size :%d    sizeof(ME_video_network_state_t) :%d",size,sizeof(ME_video_network_state_t));
    
    __block void *copyParam = NULL;
    if (param != NULL) {
        if (size == sizeof(ME_video_network_state_t)) {
            copyParam = malloc(sizeof(ME_video_network_state_t));
            memset(copyParam, 0, sizeof(ME_video_network_state_t));
            memcpy(copyParam, param, sizeof(ME_video_network_state_t));
            
            if(ev_reason == eUGo_Reason_Success && copyParam!=NULL)
            {
                char strNet[8096] = { 0 };
                char *tmpBuf = NULL;
                ME_network_state_t* netStateT = (ME_network_state_t*)copyParam;
                switch (netStateT->net_state) {
                    case eME_REASON_NETWORK_NICE:
                        tmpBuf = "nice";
                        break;
                    case eME_REASON_NETWORK_WELL:
                        tmpBuf = "well";
                        break;
                    case eME_REASON_NETWORK_GENERAL:
                        tmpBuf = "general";
                        break;
                    case eME_REASON_NETWORK_POOR:
                        tmpBuf = "poor";
                        break;
                    case eME_REASON_NETWORK_BAD:
                        tmpBuf = "bad";
                        break;
                    default:
                        tmpBuf = "unknown";
                        break;
                }
                ME_video_network_state_t* netState = (ME_video_network_state_t*)copyParam;
                sprintf(strNet, "vie state: %s, \n ice: %d, rtt: %d, \n lost: %d(s) %d(r)," \
                        " \n rate: %d(s) %d(r), \n res: %dx%d(s) %dx%d(r)," \
                        " \n frame: %d(s) %d(r) \n pt: %d(s) %d(r) \n codec: %s(s) %s(r) \n RelayCnt: %d \n",
                        tmpBuf, netState->ice, netState->rttMs,
                        netState->uplinkLost, netState->downlinkLost,
                        netState->bitrate_bps,  netState->rec_bitrate,
                        netState->width, netState->height,
                        netState->decode_width, netState->decode_height,
                        netState->target_fps, netState->decode_fps,
                        netState->EncoderPt, netState->DecoderPt,
                        netState->encCodec, netState->decCodec, netState->rtPOT_nCount);
                char rtPOT[8096] = { 0 };
                for (int i = 0; i < netState->rtPOT_nCount; i++) {
                    sprintf(rtPOT, " Relay_%d: %d(s) %d(r) \n Flow_a_%d: %dKB(s) %dKB(r) \n Flow_v_%d: %dKB(s) %dKB(r) \n", i, netState->rtPOT_SendIP[i], netState->rtPOT_RecvIP[i], i,netState->rtPOT_SendValue_a[i], netState->rtPOT_RecvValue_a[i],i, netState->rtPOT_SendValue_v[i], netState->rtPOT_RecvValue_v[i]);
                    strcat(strNet, rtPOT);
                }
                //printf("--encCodec: %s-----decCodec: %s---\n",netState->encCodec,netState->decCodec);
                NSString *strState = [NSString stringWithUTF8String:strNet];
                dispatch_async(dispatch_get_main_queue(), ^(void) {
                    selfPtr.textView.string = strState;
                });
            }
        }
    }
    
}

- (void)startMedia:(NSDictionary *)apinfoDict
{
    CGRect localRect = self.leftBox.bounds;
    CGRect remoteRect = self.rightBox.bounds;
    self.videoLocationView = [MacVideoView allocAndInitWithFrame:localRect];
    self.videoRemoteView = [MacVideoView allocAndInitWithFrame:remoteRect];
    [self.leftBox addSubview:self.videoLocationView];
    [self.rightBox addSubview:self.videoRemoteView];
    
    //stream
    ME_cb_vtable_t cb_table;
    cb_table.event_cb = on_vogo_cb;
    cb_table.log_cb = NULL;
    cb_table.send_cb = NULL;
    cb_table.screenshot_cb = NULL;
    
    Vigo_init(cb_table);
    [self startLog];
    Vigo_setLoudspeakerStatus(1);
    NSString *strip = [apinfoDict objectForKey:@"ip"];
    const char *ip = [strip UTF8String];
    
    NSNumber *aportNum = [apinfoDict objectForKey:@"aport"];
    NSNumber *vportNum = [apinfoDict objectForKey:@"vport"];
    int aport = [aportNum intValue];
    int vport = [vportNum intValue];
    
    void *local = (__bridge void*)self.videoLocationView;
    void *remote = (__bridge void*)self.videoRemoteView;
    
    Vigo_start(ip, aport, vport,local,remote);
}

- (void)stopMedia
{
    Vigo_stop();
    Vigo_destroy();
    [self.videoLocationView removeFromSuperview];
    [self.videoRemoteView removeFromSuperview];
    self.videoLocationView = nil;
    self.videoRemoteView = nil;
}

- (void)streamPull
{
    NSString *port = @"8095";
    NSDictionary *dict = [self.sessionArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *ssname = [dict objectForKey:@"ssname"];
    NSString *sessionId = [dict objectForKey:@"sessionId"];

    NSString *streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@",ipAddr,port,sessionId];
    NSLog(@"push url :%@",streamPullUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPullUrl]];
    request.HTTPMethod = @"GET";
    
    self.loadLabel.stringValue = @"正在获取接入点";
    self.progressInd.hidden = NO;
    self.loadLabel.hidden = NO;
    [self.progressInd startAnimation:nil];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        
        self.progressInd.hidden = YES;
        dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC);
        dispatch_after(time, dispatch_get_main_queue(), ^{
            self.loadLabel.hidden = YES;
        });
        if (data) {
            NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
            NSDictionary *apInfo = [dict objectForKey:@"apinfo"];
            NSLog(@"----%@",apInfo);
            if (apInfo) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    self.loadLabel.stringValue = @"获取成功";
                    AppDelegate *appDelegate = NSApp.delegate;
                    NSString *title = [NSString stringWithFormat:@"%@(%@)",ssname,sessionId];
                    [appDelegate.appWindow setTitle:title];
                    [self startMedia:apInfo];
                });
            } else {
                NSString *resultStr = [dict objectForKey:@"result"];
                if ([resultStr isEqualToString:@"000002"]) {
                    self.loadLabel.stringValue = @"该streamId被占用";
                } else {
                    self.loadLabel.stringValue = @"获取失败";
                }
                
                _isPlaying = NO;
            }
            
        } else {
            self.loadLabel.stringValue = @"获取失败";
            _isPlaying = NO;
        }
    }];
}


- (void)pushStop
{
    NSString *port = @"8095";
    NSDictionary *dict = [self.sourceArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    
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
    NSString *port = @"8095";
    NSDictionary *dict = [self.sessionArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *sessionId = [dict objectForKey:@"sessionId"];
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


- (void)changeState:(NSInteger)index
{
    [self.serIpTableView enumerateAvailableRowViewsUsingBlock:^(__kindof NSTableRowView * _Nonnull rowView, NSInteger row) {
        IpTalbeCellView *cell = [rowView viewAtColumn:0];
        NSButton *button = cell.button2;
        NSImage *image;
        if (row == index) {
            image = [NSImage imageNamed:@"checkBtn.png"];
        } else {
            image = [NSImage imageNamed:@"uncheckBtn.png"];
        }
    
        [button setImage:image];
    }];
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

- (void)showAlert:(NSString *)title message:(NSString *)message
{
    NSAlert *alert = [NSAlert alertWithMessageText:title defaultButton:@"确定" alternateButton:nil otherButton:nil informativeTextWithFormat:message];
    [alert runModal];
}

- (void)startLog
{
    NSString * file = [self getLogFileWithName:@"MediaEngineLog"];
    const char *path = [file cStringUsingEncoding:NSASCIIStringEncoding];
    Vigo_setLogFile(path);
}


- (NSString *)getLogFileWithName:(NSString *)name{
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    documentsDirectory = [documentsDirectory stringByAppendingPathComponent:name];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:documentsDirectory])
    {
        NSError *err = nil;
        [fileManager createDirectoryAtPath:documentsDirectory withIntermediateDirectories:YES attributes:nil error:&err];
        
        NSString *filePathMe = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.txt",name]];
        //查找文件，如果不存在，就创建一个文件
        if (![fileManager fileExistsAtPath:filePathMe])
        {
            [fileManager createFileAtPath:filePathMe contents:nil attributes:nil];
            
        }else{
            //如果文件存在并且它的大小大于10M，则删除并且重新创建一个
            long long filesizes  = [[fileManager attributesOfItemAtPath:filePathMe error:nil] fileSize];
            if ((filesizes/(1024.0*1024.0))>10) {
                
                //删除当前文件
                [fileManager removeItemAtPath:filePathMe error:nil];
                //重新创建一个文件
                [fileManager createFileAtPath:filePathMe contents:nil attributes:nil];
            }
            
        }
        
        if (err) {
            
            return @"";
        } else   {
            return [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.txt",name]];
        }
    }  else {
        return [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.txt",name]];
    }
    
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    
}

#pragma mark-
#pragma mark----Button----
- (IBAction)segmentedControlAction:(id)sender
{
    NSSegmentedControl *contrl = (NSSegmentedControl *)sender;
    NSInteger index = contrl.integerValue;
    
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        contrl.selectedSegment = _streamIndex;
        return;
    }
    
    if (index == 0) {
        self.sessionId = [self createSessionId];
        
        [self.startBtn setTitle:@"Push"];
        self.topTextField.stringValue = @"选择会话中转服务器";
        self.refreshView.hidden = YES;
    } else {
        
        [self.startBtn setTitle:@"Pull"];
        self.topTextField.stringValue = @"选择会话";
        self.refreshView.hidden = NO;
    }
    _streamIndex = index;
    _ipSelectIndex = -1;
    [self.serIpTableView reloadData];
    AppDelegate *appDelegate = NSApp.delegate;
    [appDelegate.appWindow setTitle:@"flyUDP"];
}

- (void)cellButtonPress:(id)sender
{
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        return;
    }
    NSButton *button = (NSButton *)sender;
    NSInteger row = button.tag;
    [self changeState:row];
    _ipSelectIndex = row;
}

- (IBAction)radioButton:(id)sender
{
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        if (_sendIndex == 0) {
            [self.radioBtn0 setState:1];
            [self.radioBtn1 setState:0];
        } else {
            [self.radioBtn0 setState:0];
            [self.radioBtn1 setState:1];
        }
        return;
    }
    NSButton *button = (NSButton *)sender;
    NSInteger tag = button.tag;
    _sendIndex = tag;
}

- (IBAction)refreshButton:(id)sender
{
    [self getStreamList:self.sourceArrays needReload:YES];
}

- (IBAction)pushStreamPress:(id)sender
{
    if (_ipSelectIndex == -1) {
        return;
    }
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流"];
        return;
    }
    _isPlaying = YES;

    if (self.sessionId == nil || [self.sessionId isEqualToString:@""]) {
        [self showAlert:@"tip" message:@"sesstion is nil"];
        return;
    }
    
    if (_streamIndex == 0) {
        [self streamPush];
        
    } else {
        [self streamPull];
    }
}


- (IBAction)stopStreamPress:(id)sender
{
    if (_ipSelectIndex == -1) {
        return;
    }
    if (!_isPlaying) {
        return;
    }
    _isPlaying = NO;

    if (_streamIndex == 0) {
        [self pushStop];
        self.sessionId = [self createSessionId];
    } else {
        [self pullStop];
    }
    
    [self stopMedia];
    AppDelegate *appDelegate = NSApp.delegate;
    [appDelegate.appWindow setTitle:@"flyUDP"];
    
    dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, 0.3*NSEC_PER_SEC);
    dispatch_after(time, dispatch_get_main_queue(), ^{
        self.textView.string = @"";
    });
}


@end
