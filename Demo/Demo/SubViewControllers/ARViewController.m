//
//  ARViewController.m
//  Demo
//
//  Created by yiqiwang(王一棋) on 2019/1/28.
//  Copyright © 2019 tencent. All rights reserved.
//

#import "ARViewController.h"
#import <QTTranslator/QTTranslator.h>

@interface ARViewController () <QTARTranslateManagerDelegate>

@property (nonatomic, strong) QTARTranslateManager *manager;
@property (nonatomic, strong) UIButton *controlButton;

@end

@implementation ARViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setup];
    [self initUI];
}

- (void)setup {
    self.manager = [[QTARTranslateManager alloc] initWithController:self delegate:self];
    [self.manager setLanguagePair:[[QTLanguagePair alloc] initWithSource:QTLangTypeZh target:QTLangTypeJp]];
    [self.manager configure];
}

- (void)initUI {
    self.view.backgroundColor = UIColor.whiteColor;

    CGSize buttonSize = CGSizeMake(100, 40);
    self.controlButton = [[UIButton alloc] initWithFrame:CGRectMake(CGRectGetMaxX(self.view.frame) / 2.0 - buttonSize.width / 2.0,
                                                                    CGRectGetMaxY(self.view.frame) - buttonSize.height,
                                                                    buttonSize.width,
                                                                    buttonSize.height)];
    [self.view addSubview:self.controlButton];
    self.controlButton.backgroundColor = UIColor.whiteColor;
    [self.controlButton setTitleColor:UIColor.blackColor forState:UIControlStateNormal];
    [self.controlButton setTitle:@"打开" forState:UIControlStateNormal];
    [self.controlButton setTitle:@"关闭" forState:UIControlStateSelected];
    [self.controlButton addTarget:self
                           action:@selector(onButtonClicked:)
                 forControlEvents:UIControlEventTouchUpInside];
}

//- (void)viewWillAppear:(BOOL)animated {
//    [super viewWillAppear:animated];
//
//    [self.manager resume];
//}
//
//- (void)viewWillDisappear:(BOOL)animated {
//    [super viewWillDisappear:animated];
//
//    [self.manager pause];
//}

- (void)dealloc {
    [self.manager releaseEngine];
    self.manager = nil;
}

#pragma mark - Action

- (void)onButtonClicked:(UIButton *)sender {
    sender.selected = !sender.selected;
    sender.selected ? [self.manager resume] : [self.manager pause];
}

#pragma mark - QTARTranslateManagerDelegate

- (void)didStart {
//    NSLog(@"%s", __FUNCTION__);
}

- (void)statusDidChange:(QTTranslateARStatus)status {
//    NSLog(@"%s %@", __FUNCTION__, @(status));
}

- (void)didStop {
//    NSLog(@"%s", __FUNCTION__);
}
@end
