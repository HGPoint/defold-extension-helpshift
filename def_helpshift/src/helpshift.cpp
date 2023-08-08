// helpshift.cpp
// Extension lib defines
#define EXTENSION_NAME Helpshift
#define LIB_NAME "Helpshift"
#define MODULE_NAME "helpshift"

// include the Defold SDK
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "helpshift_callback_private.h"

namespace dmHelpshift {

static int Lua_Initialize(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for helpshift domain '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* domain = luaL_checkstring(L, 1);

    if (lua_type(L, 2) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for helpshift app_id '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, msg);
        return 0;
    }
    const char* app_id = luaL_checkstring(L, 2);
    Initialize(domain, app_id);
    return 0;
}


static int Lua_AddUserData(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for helpshift cif key '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* key = luaL_checkstring(L, 1);

    if (lua_type(L, 2) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for helpshift cif type '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, msg);
        return 0;
    }
    const char* type = luaL_checkstring(L, 2);

    if (lua_type(L, 3) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for helpshift cif value '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, msg);
        return 0;
    }
    const char* value = luaL_checkstring(L, 3);
    
    AddUserData(key, type, value);
    return 0;
}

static int Lua_ShowConversation(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    ShowConversation();
    return 0;
}

static int Lua_ShowFAQ(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    ShowFAQ();
    return 0;
}

static int Lua_SetCallback(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Lua_RequestUnreadMessageCount(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    RequestUnreadMessageCount();
    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"showConversation", Lua_ShowConversation},
    {"showFAQ", Lua_ShowFAQ},
    {"set_callback", Lua_SetCallback},
    {"add_userdata", Lua_AddUserData},
    {"request_unread_message_count", Lua_RequestUnreadMessageCount},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(WIDGET_TOGGLE)
    SETCONSTANT(DATA_SDK_VISIBLE)
    SETCONSTANT(CONVERSATION_START)
    SETCONSTANT(DATA_MESSAGE)
    SETCONSTANT(MESSAGE_ADD)
    SETCONSTANT(DATA_MESSAGE_TYPE)
    SETCONSTANT(DATA_MESSAGE_BODY)
    SETCONSTANT(DATA_MESSAGE_TYPE_ATTACHMENT)
    SETCONSTANT(DATA_MESSAGE_TYPE_TEXT)
    SETCONSTANT(CSAT_SUBMIT)
    SETCONSTANT(DATA_CSAT_RATING)
    SETCONSTANT(DATA_ADDITIONAL_FEEDBACK)
    SETCONSTANT(CONVERSATION_STATUS)
    SETCONSTANT(DATA_LATEST_ISSUE_ID)
    SETCONSTANT(DATA_LATEST_ISSUE_PUBLISH_ID)
    SETCONSTANT(DATA_IS_ISSUE_OPEN)
    SETCONSTANT(CONVERSATION_END)
    SETCONSTANT(CONVERSATION_REJECTED)
    SETCONSTANT(CONVERSATION_RESOLVED)
    SETCONSTANT(CONVERSATION_REOPENED)
    SETCONSTANT(SDK_SESSION_STARTED)
    SETCONSTANT(SDK_SESSION_ENDED)
    SETCONSTANT(RECEIVED_UNREAD_MESSAGE_COUNT)
    SETCONSTANT(DATA_MESSAGE_COUNT)
    SETCONSTANT(DATA_MESSAGE_COUNT_FROM_CACHE)
#undef SETCONSTANT

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeHelpshift(dmExtension::AppParams* params)
{
    dmLogInfo("AppInitializeHelpshift");
    Initialize_Ext();
    dmLogInfo("AppInitializeHelpshift end");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeHelpshift(dmExtension::Params* params)
{
    // Init Lua
    dmLogInfo("InitializeHelpshift");
    LuaInit(params->m_L);
    InitializeCallback();
    dmLogInfo("Registered %s Extension", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeHelpshift(dmExtension::AppParams* params)
{
    dmLogInfo("AppFinalizeHelpshift");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeHelpshift(dmExtension::Params* params)
{
    dmLogInfo("FinalizeHelpshift");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnUpdateHelpshift(dmExtension::Params* params)
{
    // dmLogInfo("OnUpdateHelpshift");
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

static void OnEventHelpshift(dmExtension::Params* params, const dmExtension::Event* event)
{
    switch(event->m_Event)
    {
        case dmExtension::EVENT_ID_ACTIVATEAPP:
            dmLogInfo("OnEventHelpshift - EVENT_ID_ACTIVATEAPP");
            break;
        case dmExtension::EVENT_ID_DEACTIVATEAPP:
            dmLogInfo("OnEventHelpshift - EVENT_ID_DEACTIVATEAPP");
            break;
        case dmExtension::EVENT_ID_ICONIFYAPP:
            dmLogInfo("OnEventHelpshift - EVENT_ID_ICONIFYAPP");
            break;
        case dmExtension::EVENT_ID_DEICONIFYAPP:
            dmLogInfo("OnEventHelpshift - EVENT_ID_DEICONIFYAPP");
            break;
        default:
            dmLogWarning("OnEventHelpshift - Unknown event id");
            break;
    }
}

}
// Defold SDK uses a macro for setting up extension entry points:
//
// DM_DECLARE_EXTENSION(symbol, name, app_init, app_final, init, update, on_event, final)

// Helpshift is the C++ symbol that holds all relevant extension data.
// It must match the name field in the `ext.manifest`
// DM_DECLARE_EXTENSION(Helpshift, LIB_NAME, AppInitializeHelpshift, AppFinalizeHelpshift, InitializeHelpshift, OnUpdateHelpshift, OnEventHelpshift, FinalizeHelpshift)
DM_DECLARE_EXTENSION(Helpshift, LIB_NAME, dmHelpshift::AppInitializeHelpshift, dmHelpshift::AppFinalizeHelpshift, dmHelpshift::InitializeHelpshift, dmHelpshift::OnUpdateHelpshift, dmHelpshift::OnEventHelpshift, dmHelpshift::FinalizeHelpshift)

#else // platform

static dmExtension::Result InitializeHelpshift(dmExtension::Params *params) {
    dmLogInfo("Registered extension Helpshift (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeHelpshift(dmExtension::Params *params) {
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME,
LIB_NAME, 0, 0, InitializeHelpshift, 0, 0, FinalizeHelpshift)

#endif // platform
