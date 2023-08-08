#pragma once

namespace dmHelpshift {

    void Initialize_Ext();
    void Initialize(const char* domain, const char* app_id);
    void AddUserData(const char* key,const char* type, const char* value);
    void ShowConversation();
    void ShowFAQ();
    void RequestUnreadMessageCount();
}