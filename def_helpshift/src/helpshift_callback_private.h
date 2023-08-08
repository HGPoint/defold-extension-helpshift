#if defined(DM_PLATFORM_ANDROID)
#pragma once

#include "helpshift.h"
#include <dmsdk/sdk.h>

namespace dmHelpshift {

enum MessageId
{
    WIDGET_TOGGLE = 1,
    DATA_SDK_VISIBLE = 2,
    CONVERSATION_START = 3,
    DATA_MESSAGE = 4,
    MESSAGE_ADD = 5,
    DATA_MESSAGE_TYPE = 6,
    DATA_MESSAGE_BODY = 7,
    DATA_MESSAGE_TYPE_ATTACHMENT = 8,
    DATA_MESSAGE_TYPE_TEXT = 9,
    CSAT_SUBMIT = 10,
    DATA_CSAT_RATING = 11,
    DATA_ADDITIONAL_FEEDBACK = 12,
    CONVERSATION_STATUS = 13,
    DATA_LATEST_ISSUE_ID = 14,
    DATA_LATEST_ISSUE_PUBLISH_ID = 15,
    DATA_IS_ISSUE_OPEN = 16,
    CONVERSATION_END = 17,
    CONVERSATION_REJECTED = 18,
    CONVERSATION_RESOLVED = 19,
    CONVERSATION_REOPENED = 20,
    SDK_SESSION_STARTED = 21,
    SDK_SESSION_ENDED = 22,
    RECEIVED_UNREAD_MESSAGE_COUNT = 23,
    DATA_MESSAGE_COUNT = 24,
    DATA_MESSAGE_COUNT_FROM_CACHE = 25
};

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char* json);

} // namespace

#endif // platform