//
//  AppDelegate.m
//  Mac_UDP_Demo
//
//  Created by KCMac on 2017/6/19.
//  Copyright © 2017年 flypass. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [NSApp enableRelaunchOnLogin];
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
    if (!flag) {
        [self.appWindow orderFront:nil];
    }
    
    return YES;
}


@end
