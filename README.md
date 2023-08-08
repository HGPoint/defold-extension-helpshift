
---@class helpshift
---@field initialize fun(domain:string, app_id:string):void
---@field set_callback fun(callback:fun(context:any, event_id:number, data:table)):void
---@field showConversation fun():void
---@field showFAQ fun():void
---@field add_userdata fun(key:string, string:string, value:string):void
---@field WIDGET_TOGGLE 1
---@field DATA_SDK_VISIBLE 2
---@field CONVERSATION_START 3
---@field DATA_MESSAGE 4
---@field MESSAGE_ADD 5
---@field DATA_MESSAGE_TYPE 6
---@field DATA_MESSAGE_BODY 7
---@field DATA_MESSAGE_TYPE_ATTACHMENT 8
---@field DATA_MESSAGE_TYPE_TEXT 9
---@field CSAT_SUBMIT 10
---@field DATA_CSAT_RATING 11
---@field DATA_ADDITIONAL_FEEDBACK 12
---@field CONVERSATION_STATUS 13
---@field DATA_LATEST_ISSUE_ID 14
---@field DATA_LATEST_ISSUE_PUBLISH_ID 15
---@field DATA_IS_ISSUE_OPEN 16
---@field CONVERSATION_END 17
---@field CONVERSATION_REJECTED 18
---@field CONVERSATION_RESOLVED 19
---@field CONVERSATION_REOPENED 20
---@field SDK_SESSION_STARTED 21
---@field SDK_SESSION_ENDED 22
---@field RECEIVED_UNREAD_MESSAGE_COUNT 23
---@field DATA_MESSAGE_COUNT 24
---@field DATA_MESSAGE_COUNT_FROM_CACHE 25
helpshift = {}