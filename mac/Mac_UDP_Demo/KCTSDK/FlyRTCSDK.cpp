//
//  FlyRTCSDK.cpp
//  UdpPush
//
//  Created by KCMac on 2017/6/14.
//  Copyright © 2017年 flypass. All rights reserved.
//

#include "FlyRTCSDK.h"


using namespace gl_media_engine;

ViGoEngine* g_pAVEngine = NULL;
static bool g_enableVideo = true;
static int g_LoadFlag = FALSE;




static int ConvertEmodelValueToString(ME_emodel_info_t* emodel);


void Vigo_init(ME_cb_vtable_t cb_table)
{
    if (g_LoadFlag)
    {
        return;
    }
    g_pAVEngine = new ViGoEngine();
    if (g_pAVEngine)
    {
//        ME_cb_vtable_t cb_table;
//        cb_table.event_cb = on_vogo_cb;
//        cb_table.log_cb = NULL;
//        cb_table.send_cb = NULL;
//        cb_table.screenshot_cb = NULL;
//        // ◊¢≤·ªÿµ˜
//        g_cb = cb;
        
        g_pAVEngine->callback_vtable(&cb_table);
        g_pAVEngine->init(0);
        //g_pAVEngine->callbacktips((me_tips_data_cb_f)tips_callback);
        g_LoadFlag = TRUE;
    }
}

void Vigo_destroy(void)
{
    if (g_LoadFlag)
    {
        if (g_pAVEngine)
        {
            g_pAVEngine->destroy();
            delete g_pAVEngine;
            g_pAVEngine = NULL;
        }
        g_LoadFlag = FALSE;
    }
}

void Vigo_start(const char *ip, int audioport, int videoport, void *hLocal, void *hRemote)
{
    if (g_pAVEngine)
    {
        ME_audio_stream_info_t audio_param;
        memset(&audio_param, 0, sizeof(audio_param));
        audio_param.ucExTransportEnable = false;
        //strcpy_s(audio_param.cRemoteAudioIp, ip);
        strcpy(audio_param.cRemoteAudioIp, ip);
        audio_param.iRemoteAudioPort = audioport;
        audio_param.iLocalAudioPort = 0;
        audio_param.iPayLoadType = 18;
        
        unsigned short mulriple = 1;
        unsigned short offset = 1;
        
        g_pAVEngine->create_audio_stream();
        g_pAVEngine->set_audio_stream(&audio_param);
        g_pAVEngine->set_audio_fec(mulriple, offset);
        g_pAVEngine->enable_audio_playout(true);
        g_pAVEngine->enable_audio_receive(true);
        g_pAVEngine->enable_audio_send(true);
        g_pAVEngine->set_state(4);
        
        if (g_enableVideo)
        {
            ME_video_stream_info_t video_para;
            memset(&video_para, 0, sizeof(video_para));
            //strcpy_s(video_para.cRemoteVideoIp, ip);
            strcpy(video_para.cRemoteVideoIp, ip);
            video_para.iLocalVideoPort = 2;
            video_para.iRemoteVideoPort = videoport;
            video_para.iPayLoadType = 121;  // H.264->121 , H.265->125
            
            ME_video_render_param_t stVideoRenderConfig;
            g_pAVEngine->get_config(ME_VIDEO_RENDER_CFG_MODULE_ID, &stVideoRenderConfig);
            stVideoRenderConfig.pWindowRemote = hRemote;
            stVideoRenderConfig.pWindowLocal = hLocal;
            stVideoRenderConfig.remoteWidth = 352;
            stVideoRenderConfig.remoteHeight = 288;
            stVideoRenderConfig.renderMode = 1;
            g_pAVEngine->set_config(ME_VIDEO_RENDER_CFG_MODULE_ID, &stVideoRenderConfig);
            
            // set Video codec config*;
             ME_video_enc_param_t stEnc;
            g_pAVEngine->get_config(ME_VIDEO_ENC_CFG_MODULE_ID, &stEnc);
            stEnc.usWidth = 480;
            stEnc.usHeight = 360;
            stEnc.ucMaxFramerate = 30;
            stEnc.usMaxBitrate = 2000;
            stEnc.usStartBitrate =350;
            stEnc.usMinBitrate = 30;
            stEnc.ucUseHwEnc = 0;
            stEnc.ucUseHwDec = 0;
            g_pAVEngine->set_config(ME_VIDEO_ENC_CFG_MODULE_ID, &stEnc);
            
            //set
            ME_video_camera_param_t param;
            memset(&param, 0, sizeof(ME_video_camera_param_t));
            g_pAVEngine->video_get_camera_state(&param);
            param.usCameraIdx = -1;
            param.usRotateAngle = -1;
            param.ucMaxFps = 30;
            param.usWidth = 640;
            param.usHeight = 480;
            
            g_pAVEngine->video_set_camera(&param);
            
            g_pAVEngine->video_create_stream();
            g_pAVEngine->video_set_stream(&video_para);
            g_pAVEngine->video_start(31);
        }
    }
}

void Vigo_stop(void)
{
    if (g_pAVEngine)
    {
        g_pAVEngine->video_stop(31);
        g_pAVEngine->delete_audio_stream();
        
        if (g_enableVideo)
        {
            g_pAVEngine->video_delete_stream();
        }
        
    }
}



int ConvertEmodelValueToString(ME_emodel_info_t* emodel)
{
    char tmp_buff[128] = { 0 };
    
    if (emodel == NULL)
        return -1;
    
    sprintf(tmp_buff, "EMODEL: M=\"%.2lf,%.2lf,%.2lf\"\r\n", \
              emodel->emodel_mos.min, emodel->emodel_mos.max, \
              emodel->emodel_mos.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "T=\"%.2lf,%.2lf,%.2lf\"\r\n", \
              emodel->emodel_tr.min, emodel->emodel_tr.max, \
              emodel->emodel_tr.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "P=\"%.2lf,%.2lf,%.2lf\"\r\n", \
              emodel->emodel_ppl.min, emodel->emodel_ppl.max, \
              emodel->emodel_ppl.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "B=\"%.2lf,%.2lf,%.2lf\"\r\n", \
              emodel->emodel_burstr.min, emodel->emodel_burstr.max, \
              emodel->emodel_burstr.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "I=\"%.2lf,%.2lf,%.2lf\"\r\n", \
              emodel->emodel_ie.min, emodel->emodel_ie.max, \
              emodel->emodel_ie.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "D=\"%.2lf, %.2lf, %.2lf\"\r\n", \
              emodel->delay.min, emodel->delay.max,
              emodel->delay.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    
    memset(&tmp_buff, 0x00, sizeof(tmp_buff));
    sprintf(tmp_buff, "J=\"%.2lf, %.2lf, %.2lf\"\r\n", \
              emodel->jitbuf.min, emodel->jitbuf.max, \
              emodel->jitbuf.average);
    //OutputDebugStringA(tmp_buff);
    printf("----%s",tmp_buff);
    return 0;
}


void Vigo_setLoudspeakerStatus(bool status)
{
    g_pAVEngine->set_loudspeaker_status(status);
}


void Vigo_setLogFile(const char* filepath)
{
    g_pAVEngine->set_debug_level(0x40ff);
    g_pAVEngine->set_log_file_path(filepath);
}

//g_pVideoEngine->VideoSetCamera(param)
