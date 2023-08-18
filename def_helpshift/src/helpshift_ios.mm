#if defined(DM_PLATFORM_IOS)

#import <HelpshiftX/HelpshiftX.h>
#include "helpshift_callback_private.h"
#include "ios/HelpshiftExt.h"

namespace dmHelpshift {

static HelpshiftExt *helpshiftExtInstance = nil;

void Initialize_Ext()
{
}

void Initialize(const char* domain, const char* app_id)
{
    NSString* objCdomain = [NSString stringWithUTF8String:domain];
    NSString* objCappId = [NSString stringWithUTF8String:app_id];
    helpshiftExtInstance = [[HelpshiftExt alloc] init:objCdomain app_id:objCappId];
}

void AddUserData(const char* key, const char* type, const char* value)
{
    NSString* objCkey = [NSString stringWithUTF8String:key];
    NSString* objCtype = [NSString stringWithUTF8String:type];
    NSString* objCvalue = [NSString stringWithUTF8String:value];
    [helpshiftExtInstance AddCifs:objCkey type:objCtype value:objCvalue];
}

void ShowConversation()
{
    [helpshiftExtInstance ShowConversation];
}

void ShowFAQ()
{
    [helpshiftExtInstance ShowFAQ];
}

void RequestUnreadMessageCount()
{
    [helpshiftExtInstance RequestUnreadMessageCount];
}

} // namespace

#endif // platform
