#import "HelpshiftCallbackDelegate.h"

@implementation HelpshiftCallbackDelegate

- (void) handleHelpshiftEvent:(nonnull NSString *)eventName withData:(nullable NSDictionary *)data {
     
    if (_onEventReceived == nil) {
        return;
    }
    
    _onEventReceived(eventName, data);
}

- (void) authenticationFailedForUserWithReason:(HelpshiftAuthenticationFailureReason)reason {

    if (_onAuthError == nil) {
        return;
    }
    
    _onAuthError(reason);
}

@end