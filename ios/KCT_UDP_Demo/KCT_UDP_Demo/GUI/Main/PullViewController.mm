//
//  PullViewController.m
//  UdpPush
//
//  Created by KCMac on 2017/6/14.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "PullViewController.h"
#import "VideoView.h"

static void on_vogo_cb(int ev_type, int ev_reason, const char* something, void* param, int size);
static PullViewController *selfPtr;

@interface PullViewController ()
{
    
}

@property (strong,nonatomic)UIView *localView;
@property (strong,nonatomic)UIView *remoteView;
@property (strong,nonatomic) UITextView * informationLabel; // 展示信息的label

@end

@implementation PullViewController

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    CGRect localRect = self.localViewBgView.bounds;
    CGRect remoteRect = self.remoteViewBgView.bounds;
    NSLog(@"----%f------%f",remoteRect.size.width,remoteRect.size.height);
    _localView = [VideoView allocAndInitWithFrame:localRect];
    _remoteView = [VideoView allocAndInitWithFrame:remoteRect];
    
    [self.localViewBgView addSubview:self.localView];
    [self.remoteViewBgView addSubview:self.remoteView];
    UITapGestureRecognizer * thirdTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(thirdTap:)];
    thirdTap.numberOfTapsRequired = 3;
    thirdTap.numberOfTouchesRequired = 1;
    [self.localView addGestureRecognizer:thirdTap];
    void *local = (__bridge void*)self.localView;
    void *remote = (__bridge void*)self.remoteView;
    
    NSString *strip = [self.apinfoDict objectForKey:@"ip"];
    const char *ip = [strip UTF8String];
    
    NSNumber *aportNum = [self.apinfoDict objectForKey:@"aport"];
    NSNumber *vportNum = [self.apinfoDict objectForKey:@"vport"];
    int aport = [aportNum intValue];
    int vport = [vportNum intValue];
    if (strip == nil || aportNum == nil || vportNum == nil) {
        
    } else {
        Vigo_start(ip, aport, vport,local,remote,remoteRect.size.width,remoteRect.size.height);
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    selfPtr = self;
    self.title = [NSString stringWithFormat:@"Pull(%@)",self.sessionId];
    
    UIBarButtonItem *barButtonItemLeft=[[UIBarButtonItem alloc] initWithTitle:@"返回" style:UIBarButtonItemStylePlain target:self action:@selector(back:)];
    [[self navigationItem] setLeftBarButtonItem:barButtonItemLeft];
    
    [self.view addSubview:self.informationLabel];
    
    [self.view bringSubviewToFront:self.buttonBgView];
    self.buttonBgView.hidden = YES;
    
    //stream
    ME_cb_vtable_t cb_table;
    cb_table.event_cb = on_vogo_cb;
    cb_table.log_cb = NULL;
    cb_table.send_cb = NULL;
    cb_table.screenshot_cb = NULL;
    
    
    Vigo_init(cb_table);
    
    
    
    
    
    //Vigo_setLoudspeakerStatus(0);
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark---lazy
- (UITextView *)informationLabel{
    if (_informationLabel == nil) {
        _informationLabel = [[UITextView alloc] initWithFrame:CGRectMake(0,84, 300, 300)];
        //_informationLabel.numberOfLines = 0;
        //_informationLabel.hidden = YES;
        _informationLabel.editable = NO;
        _informationLabel.font = [UIFont systemFontOfSize:12];
        _informationLabel.textColor = [UIColor redColor];
        _informationLabel.backgroundColor = [UIColor clearColor];
    }
    return _informationLabel;
}

#pragma mark---button
- (void)back:(id)sender
{
    [self.remoteView removeFromSuperview];
    [self.localView removeFromSuperview];
    self.remoteView = nil;
    self.localView = nil;
    Vigo_stop();
    Vigo_destroy();
    self.block();
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)thirdTap:(UITapGestureRecognizer *)thirdTap{
    NSLog(@"1个触摸点 3次点击事件触发");
    self.informationLabel.hidden = NO;
}

- (IBAction)switchCameraButtonClick:(UIButton *)button
{
    
    if (button.tag == 1) {
        /**
         @author WLS, 15-12-14 15:12:42
         后置摄像头
         */
        Vigo_setCamera(0);
        button.tag = 0;
    }else if (button.tag == 0){
        /**
         @author WLS, 15-12-14 15:12:49
         
         前置摄像头
         */
        Vigo_setCamera(1);
        button.tag = 1;
    }
}

- (IBAction)audioButtonClick:(UIButton *)button
{
    if ([DeviceTool isHeadphone]) {
        //处于耳机模式 不允许设置免提
        return;
    }
    
    BOOL returnValue = Vigo_getLoudspeakerStatus();
    if (returnValue == NO) {
        Vigo_setLoudspeakerStatus(1);
        self.handFreeButton.selected = YES;
    } else {
        Vigo_setLoudspeakerStatus(0);
        self.handFreeButton.selected = NO;
    }
}


void on_vogo_cb(int ev_type, int ev_reason, const char* something, void* param, int size)
{
    //printf("----ev_type: %d  log :%s\n",ev_type,something);
    
    __block void *copyParam = NULL;
    if (param != NULL) {
        if (size == sizeof(ME_video_network_state_t)){
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
                    selfPtr.informationLabel.text = strState;
                    if ([selfPtr.buttonBgView isHidden]) {
                        selfPtr.buttonBgView.hidden = NO;
                    }
                });
            }
        }
    }
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
