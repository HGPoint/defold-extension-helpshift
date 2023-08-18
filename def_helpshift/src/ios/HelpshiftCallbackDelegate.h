#pragma once

#import <HelpshiftX/HelpshiftX.h>

@interface HelpshiftCallbackDelegate : NSObject <HelpshiftDelegate>

@property (nonatomic, copy) void (^onEventReceived)(NSString* eventName, NSDictionary* eventData);

@property (nonatomic, copy) void (^onAuthError)(HelpshiftAuthenticationFailureReason reason);

@end