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


@property(nonatomic,weak) IBOutlet NSSegmentedControl *streamSegment;
@property(nonatomic,weak) IBOutlet NSTableView *serIpTableView;
@property(nonatomic,weak) IBOutlet NSTextField *portField;
@property(nonatomic,weak) IBOutlet NSTextField *sessionField;
@property(nonatomic,weak) IBOutlet NSBox *leftBox;
@property(nonatomic,weak) IBOutlet NSBox *rightBox;
@property(nonatomic,strong) NSOpenGLView *videoLocationView;
@property(nonatomic,strong) NSOpenGLView *videoRemoteView;
@property(nonatomic,weak) IBOutlet NSTextView *textView;
@property(nonatomic,weak) IBOutlet NSButton *startBtn;
@property(nonatomic,weak) IBOutlet NSButton *stopBtn;
@property(nonatomic,weak) IBOutlet NSProgressIndicator *progressInd;
@property(nonatomic,weak) IBOutlet NSTextField *loadLabel;

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
    [self getSerIps];
    
    selfPtr = self;
    
    //View
    self.streamSegment.integerValue = _streamIndex;
    self.portField.stringValue = @"8095";
    self.sessionField.stringValue = [self createSessionId];
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
    return self.sourceArrays.count;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    IpTalbeCellView *cell = [tableView makeViewWithIdentifier:@"IpTalbeCellView" owner:nil];
    NSDictionary *ipDict = [self.sourceArrays objectAtIndex:row];
    NSString *ssip = [ipDict objectForKey:@"ssip"];
    NSString *ssname = [ipDict objectForKey:@"ssname"];
    cell.addrTextFiled.stringValue = [NSString stringWithFormat:@"%@(%@)",ssip,ssname];
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

- (void)streamPush
{
    NSString *port = self.portField.stringValue;
    NSDictionary *dict = [self.sourceArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    NSString *streamPushUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPush?streamId=%@&streamCan=%ld",ipAddr,port,self.sessionId,_sendIndex];
    NSLog(@"push url :%@",streamPushUrl);
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:streamPushUrl]];
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
                    [self startMedia:apInfo];
                });
            } else {
                self.loadLabel.stringValue = @"获取失败";
                _isPlaying = NO;
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
    NSString *port = self.portField.stringValue;
    NSDictionary *dict = [self.sourceArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];

    NSString *streamPullUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/streamPull?streamId=%@",ipAddr,port,self.sessionId];
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
                    [self startMedia:apInfo];
                });
            } else {
                self.loadLabel.stringValue = @"获取失败";
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
    NSString *port = self.portField.stringValue;
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
    NSString *port = self.portField.stringValue;
    NSDictionary *dict = [self.sourceArrays objectAtIndex:_ipSelectIndex];
    NSString *ipAddr = [dict objectForKey:@"ssip"];
    
    NSString *pullStopUrl = [NSString stringWithFormat:@"http://%@:%@/udprelay/v1/pullStop?streamId=%@",ipAddr,port,self.sessionId];
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


#pragma mark----Button
- (IBAction)changeValue:(id)sender
{
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        return;
    }
    NSSegmentedControl *contrl = (NSSegmentedControl *)sender;
    NSInteger index = contrl.integerValue;
    if (index == 0) {
        self.sessionField.stringValue = [self createSessionId];
        self.sessionField.editable = NO;
        [self.startBtn setTitle:@"Push"];
    } else {
        self.sessionField.editable = YES;
        self.sessionField.stringValue = @"";
        [self.startBtn setTitle:@"Pull"];
    }
    _streamIndex = index;
}

- (void)cellButtonPress:(id)sender
{
    NSButton *button = (NSButton *)sender;
    NSInteger row = button.tag;
    [self changeState:row];
    _ipSelectIndex = row;
}

- (IBAction)radioButton:(id)sender
{
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流，不能修改"];
        return;
    }
    NSButton *button = (NSButton *)sender;
    NSInteger tag = button.tag;
    _sendIndex = tag;
}

- (IBAction)pushStreamPress:(id)sender
{
    if (_isPlaying) {
        [self showAlert:@"tip" message:@"正在推流"];
        return;
    }
    _isPlaying = YES;
    self.sessionId = self.sessionField.stringValue;
    if (self.portField.stringValue == nil || [self.portField.stringValue isEqualToString:@""]) {
        [self showAlert:@"tip" message:@"port is nil"];
        return;
    }
    if (self.sessionField.stringValue == nil || [self.sessionField.stringValue isEqualToString:@""]) {
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
    _isPlaying = NO;

    self.textView.string = @"";
    if (_streamIndex == 0) {
        [self pushStop];
        self.sessionField.stringValue = [self createSessionId];
    } else {
        [self pullStop];
    }
    [self stopMedia];
}


@end
