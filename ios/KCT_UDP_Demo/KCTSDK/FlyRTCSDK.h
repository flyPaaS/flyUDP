//
//  FlyRTCSDK.h
//  UdpPush
//
//  Created by KCMac on 2017/6/14.
//  Copyright © 2017年 flypass. All rights reserved.
//

#ifndef FlyRTCSDK_hpp
#define FlyRTCSDK_hpp

#include <stdio.h>
#include "ViGoEngine.h"

void Vigo_init(ME_cb_vtable_t cb_table);
void Vigo_destroy(void);
void Vigo_start(const char *ip, int audioport, int videoport, void *hLocal, void *hRemote,int remoteWidth,int remoteHeight);
void Vigo_stop(void);
void Vigo_setLoudspeakerStatus(bool status);
#endif /* FlyRTCSDK_hpp */
