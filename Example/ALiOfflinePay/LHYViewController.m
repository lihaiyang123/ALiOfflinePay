//
//  LHYViewController.m
//  ALiOfflinePay
//
//  Created by lihaiyang123 on 09/05/2022.
//  Copyright (c) 2022 lihaiyang123. All rights reserved.
//

#import "LHYViewController.h"
#import <ALiOfflinePay/alipay_code_verify.h>
@interface LHYViewController ()

@end

@implementation LHYViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    os_adapter_layer_handler handler;
    handler.alipay_get_sys_time = &alipay_get_sys_time;
    alipay_adapter_register(&handler);
//
    // Do any additional setup after loading the view.
}
void alipay_get_sys_time(uint64_t *time_now){
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init] ;
    [formatter setDateStyle:NSDateFormatterMediumStyle];
    [formatter setTimeStyle:NSDateFormatterShortStyle];
    [formatter setDateFormat:@"YYYY-MM-dd HH:mm:ss SSS"];
    // 设置想要的格式，hh与HH的区别:分别表示12小时制,24小时制
    //设置时区,这一点对时间的处理有时很重要
    NSTimeZone* timeZone = [NSTimeZone timeZoneWithName:@"Asia/Shanghai"];
    [formatter setTimeZone:timeZone];
    NSDate *datenow = [NSDate date];
    long long timeSp = (long long)[datenow timeIntervalSince1970]*1000;
    *time_now = (uint64_t)timeSp;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
