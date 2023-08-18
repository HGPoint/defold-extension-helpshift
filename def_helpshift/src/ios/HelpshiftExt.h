#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "HelpshiftCallbackDelegate.h"
#include <dmsdk/sdk.h>


NS_ASSUME_NONNULL_BEGIN

@interface HelpshiftExt : NSObject

@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) NSMutableDictionary *conversationCifs;


-(instancetype)init:(NSString *)domain app_id:(NSString *)app_id;
-(void)ShowConversation;
-(void)ShowFAQ;
-(void)AddCifs:(NSString *)key type:(NSString *)type value:(NSString *)value;
-(void)RequestUnreadMessageCount;
@end

NS_ASSUME_NONNULL_END
