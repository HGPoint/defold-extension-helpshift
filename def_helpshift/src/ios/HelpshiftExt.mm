#import "HelpshiftExt.h"
#import <Foundation/Foundation.h>
#import <HelpshiftX/HelpshiftX.h>
#include <dmsdk/sdk.h>
#include "../helpshift_callback_private.h"

@implementation HelpshiftExt

static int WIDGET_TOGGLE = 1;
static int DATA_SDK_VISIBLE = 2;
static int CONVERSATION_START = 3;
static int DATA_MESSAGE = 4;
static int MESSAGE_ADD = 5;
static int DATA_MESSAGE_TYPE = 6;
static int DATA_MESSAGE_BODY = 7;
static int DATA_MESSAGE_TYPE_ATTACHMENT = 8;
static int DATA_MESSAGE_TYPE_TEXT = 9;
static int CSAT_SUBMIT = 10;
static int DATA_CSAT_RATING = 11;
static int DATA_ADDITIONAL_FEEDBACK = 12;
static int CONVERSATION_STATUS = 13;
static int DATA_LATEST_ISSUE_ID = 14;
static int DATA_LATEST_ISSUE_PUBLISH_ID = 15;
static int DATA_IS_ISSUE_OPEN = 16;
static int CONVERSATION_END = 17;
static int CONVERSATION_REJECTED = 18;
static int CONVERSATION_RESOLVED = 19;
static int CONVERSATION_REOPENED = 20;
static int SDK_SESSION_STARTED = 21;                         
static int SDK_SESSION_ENDED = 22;
static int RECEIVED_UNREAD_MESSAGE_COUNT = 23;
static int DATA_MESSAGE_COUNT = 24;
static int DATA_MESSAGE_COUNT_FROM_CACHE = 25;

- (instancetype)init:(NSString *)domain app_id:(NSString *)app_id
{
    self = [super init];

    self.window = dmGraphics::GetNativeiOSUIWindow();
    self.conversationCifs =[[NSMutableDictionary alloc]init];

    NSDictionary *config = @{}; // Your config
    [Helpshift installWithPlatformId:app_id
                              domain:domain
                              config:config];

    HelpshiftCallbackDelegate *delegate = [HelpshiftCallbackDelegate new];
    delegate.onEventReceived = ^(NSString* eventName, NSDictionary* eventData) {

        if (eventData){
            NSMutableDictionary *mutableDictionary = [eventData mutableCopy];
            NSData *data = [NSJSONSerialization dataWithJSONObject:eventData options:NSJSONWritingPrettyPrinted error:nil];
            NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            const char *jsonData = [jsonString cStringUsingEncoding:NSUTF8StringEncoding];

            int event = 0;
            if([eventName isEqualToString:HelpshiftEventNameWidgetToggle])
                event = WIDGET_TOGGLE;
            else if ([eventName isEqualToString:HelpshiftEventDataVisible])
                event = DATA_SDK_VISIBLE;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationStart])
                event = CONVERSATION_START;
            else if ([eventName isEqualToString:HelpshiftEventDataMessage])
                event = DATA_MESSAGE;
            else if ([eventName isEqualToString:HelpshiftEventNameMessageAdd])
                event = MESSAGE_ADD;
            else if ([eventName isEqualToString:HelpshiftEventDataMessageType])
                event = DATA_MESSAGE_TYPE;
            else if ([eventName isEqualToString:HelpshiftEventDataMessageBody])
                event = DATA_MESSAGE_BODY;
            else if ([eventName isEqualToString:HelpshiftEventDataMessageTypeAttachment])
                event = DATA_MESSAGE_TYPE_ATTACHMENT;
            else if ([eventName isEqualToString:HelpshiftEventDataMessageTypeText])
                event = DATA_MESSAGE_TYPE_TEXT;
            else if ([eventName isEqualToString:HelpshiftEventNameCSATSubmit])
                event = CSAT_SUBMIT;
            else if ([eventName isEqualToString:HelpshiftEventDataRating])
                event = DATA_CSAT_RATING;
            else if ([eventName isEqualToString:HelpshiftEventDataAdditionalFeedback])
                event = DATA_ADDITIONAL_FEEDBACK;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationStatus])
                event = CONVERSATION_STATUS;
            else if ([eventName isEqualToString:HelpshiftEventDataLatestIssueId])
                event = DATA_LATEST_ISSUE_ID;
            else if ([eventName isEqualToString:HelpshiftEventDataLatestIssuePublishId])
                event = DATA_LATEST_ISSUE_PUBLISH_ID;
            else if ([eventName isEqualToString:HelpshiftEventDataIsIssueOpen])
                event = DATA_IS_ISSUE_OPEN;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationEnd])
                event = CONVERSATION_END;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationRejected])
                event = CONVERSATION_REJECTED;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationResolved])
                event = CONVERSATION_RESOLVED;
            else if ([eventName isEqualToString:HelpshiftEventNameConversationReopened])
                event = CONVERSATION_REOPENED;
            else if ([eventName isEqualToString:HelpshiftEventNameSessionStarted])
                event = SDK_SESSION_STARTED;
            else if ([eventName isEqualToString:HelpshiftEventNameSessionEnded])
                event = SDK_SESSION_ENDED;
            else if ([eventName isEqualToString:HelpshiftEventNameReceivedUnreadMessageCount])
                event = RECEIVED_UNREAD_MESSAGE_COUNT;
            else if ([eventName isEqualToString:HelpshiftEventDataUnreadMessageCount])
                event = DATA_MESSAGE_COUNT;
            else if ([eventName isEqualToString:HelpshiftEventDataUnreadMessageCountIsFromCache])
                event = DATA_MESSAGE_COUNT_FROM_CACHE;

            dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
            dispatch_async(queue, ^{
                dmHelpshift::AddToQueueCallback((dmHelpshift::MessageId)event, jsonData);
            });
        }
    };
    
    delegate.onAuthError = ^(HelpshiftAuthenticationFailureReason reason) {
    };
    
    [Helpshift sharedInstance].delegate = delegate;
    return self;
}

-(void)ShowConversation
{
    NSDictionary *configDictionary = @{};
    [Helpshift showConversationWith:self.window.rootViewController config:configDictionary];
}

-(void)ShowFAQ
{
    NSDictionary *configDictionary = @{
        @"cifs" : self.conversationCifs
    };
    [Helpshift showFAQsWith:self.window.rootViewController config:configDictionary];
}

-(void)AddCifs:(NSString *)key type:(NSString *)type value:(NSString *)value
{
    NSDictionary *cifObj = @{
        @"type": type,
        @"value": value
    };
    
    [self.conversationCifs setObject:cifObj forKey:key];
}

-(void)RequestUnreadMessageCount
{
    [Helpshift requestUnreadMessageCount:true];
}

@end
