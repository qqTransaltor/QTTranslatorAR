//
//  QTARTranslateManager.h
//  QTTranslator
//
//  Created by yiqiwang(王一棋) on 2019/2/19.
//  Copyright © 2019 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QTLanguageDefine.h"

NS_ASSUME_NONNULL_BEGIN



@protocol QTARTranslateManagerDelegate <NSObject>

/**
 * AR翻译开启的回调
 * AR引擎的回调 一定会收到
 */
- (void)didStart;

/**
 * AR翻译状态切换的回调
 * @param status AR翻译状态 类型为 QTTranslateARStatus 见文件 QTTranslateDefine.h
 * NOTE：为UI线程，在这个回调做大量操作可能阻塞camera图片渲染
 */
- (void)statusDidChange:(QTTranslateARStatus)status;

/**
 * AR翻译关闭的回调
 * AR引擎的回调 有时会收不到
 */
- (void)didStop;

@end

@interface QTARTranslateManager : NSObject

/**
 * 手机稳定检测采用率
 * 默认 1/10, 每秒 10 次。
 * 请开始AR翻译前设置，一旦开启设置无效
 */
@property (nonatomic, assign) NSTimeInterval stableDetectionInterval;

/**
 * 手机稳定检测 连续稳定多少次判断为稳定
 * 默认 5 次。
 * 请开始AR翻译前设置，一旦开启设置无效
*/
@property (nonatomic, assign) NSUInteger stableLimit;

/**
 * 手机稳定检测阈值 超过阈值即判定摇晃
 * 默认 1.05。
 * 请开始AR翻译前设置，一旦开启设置无效
*/
@property (nonatomic, assign) CGFloat stableAccelerameterLimit;

/**
 * AR翻译语言对设置
 * configure之前必须设置
 * resume之后可以更新
 * source 翻译的源语言类型。具体种类见 QTLangType，通过 langAbbrFromType(QTLangType) 方法构造
 * target 翻译的目标语言类型。具体种类见 QTLangType，通过 langAbbrFromType(QTLangType) 方法构造
 * AR翻译支持中文到 （英、日、韩、西班牙、法、德、越、马来、意大利、葡萄牙）的互译
 */
@property (nonatomic, strong) QTLanguagePair *languagePair;

/**
 * 初始化AR翻译引擎
 * @param controller 传入依赖的viewController用来展示
 */
- (instancetype)initWithController:(UIViewController * _Nonnull )controller
                          delegate:(id<QTARTranslateManagerDelegate> _Nullable)delegate;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-synthesis"
/**
 * 废弃 请使用 configure 接口
 */
- (void)configureWithSource:(NSString *)source target:(NSString *)target NS_UNAVAILABLE;
#pragma clang diagnostic pop

/**
 * 配置AR翻译引擎
 * 调用此方法前，请确保 languagePair 参数已经设置
 */
- (void)configure;

/**
 * 获取当前视频帧
 * 若AR引擎未开启，返回为nil
 */
- (UIImage *)getCurrentFrame;

/**
 * 开始AR翻译引擎
 */
- (void)resume;

/**
 * 暂停AR翻译引擎
 */
- (void)pause;

/**
 * 释放AR翻译引擎
 */
- (void)releaseEngine;

@end

NS_ASSUME_NONNULL_END
