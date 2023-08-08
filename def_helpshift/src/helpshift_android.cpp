#if defined(DM_PLATFORM_ANDROID)

#include "com_defold_helpshift_HelpshiftJNI.h"
#include <dmsdk/dlib/android.h>
#include <dmsdk/sdk.h>

#include "helpshift_callback_private.h"

JNIEXPORT void JNICALL Java_com_defold_hgpoint_HelpshiftJNI_helpshiftAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    dmLogInfo("Java_com_defold_hgpoint_HelpshiftJNI_helpshiftAddToQueue");
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmHelpshift::AddToQueueCallback((dmHelpshift::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmHelpshift {

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    env->CallVoidMethod(instance, method);
}
static void CallVoidMethodCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = NULL;
    if (cstr1)
    {
        jstr1 = env->NewStringUTF(cstr1);
    }

    jstring jstr2 = NULL;
    if (cstr2)
    {
        jstr2 = env->NewStringUTF(cstr2);
    }

    env->CallVoidMethod(instance, method, jstr1, jstr2);

    if (cstr1)
    {
        env->DeleteLocalRef(jstr1);
    }

    if (cstr2)
    {
        env->DeleteLocalRef(jstr2);
    }
}

static void CallVoidMethodCharCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2, const char* cstr3)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = NULL;
    if (cstr1)
    {
        jstr1 = env->NewStringUTF(cstr1);
    }

    jstring jstr2 = NULL;
    if (cstr2)
    {
        jstr2 = env->NewStringUTF(cstr2);
    }

    jstring jstr3 = NULL;
    if (cstr3)
    {
        jstr3 = env->NewStringUTF(cstr3);
    }

    env->CallVoidMethod(instance, method, jstr1, jstr2, jstr3);

    if (cstr1)
    {
        env->DeleteLocalRef(jstr1);
    }

    if (cstr2)
    {
        env->DeleteLocalRef(jstr2);
    }

    if (cstr3)
    {
        env->DeleteLocalRef(jstr3);
    }
}

struct HelpshiftJniBridge
{
    jobject         m_HelpshiftJniBridgeJNI;
    jmethodID       m_Initialize;
    jmethodID       m_AddUserData;
    jmethodID       m_ShowConversation;
    jmethodID       m_showFAQ;
};

static HelpshiftJniBridge g_HelpShift;

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    dmLogInfo("Helpshift InitJNIMethods");
    g_HelpShift.m_Initialize = env->GetMethodID(cls, "Initialize", "(Ljava/lang/String;Ljava/lang/String;)V");
    g_HelpShift.m_AddUserData = env->GetMethodID(cls, "AddUserData", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    g_HelpShift.m_ShowConversation = env->GetMethodID(cls, "ShowConversation", "()V");
    g_HelpShift.m_showFAQ = env->GetMethodID(cls, "showFAQ", "()V");
    dmLogInfo("Helpshift InitJNIMethods end");
}

void Initialize_Ext()
{
    dmLogInfo("Helpshift Initialize_Ext");
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.hgpoint.HelpshiftJNI");
    InitJNIMethods(env, cls);
    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_HelpShift.m_HelpshiftJniBridgeJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
    dmLogInfo("Helpshift Initialize_Ext end");
}

void Initialize(const char* domain, const char* app_id)
{
    dmLogInfo("Helpshift Initialize");
    CallVoidMethodCharChar(g_HelpShift.m_HelpshiftJniBridgeJNI, g_HelpShift.m_Initialize, domain, app_id);
    dmLogInfo("Helpshift Initialize end");
}

void AddUserData(const char* key, const char* type, const char* value)
{
    dmLogInfo("Helpshift AddUserData");
    CallVoidMethodCharCharChar(g_HelpShift.m_HelpshiftJniBridgeJNI, g_HelpShift.m_AddUserData, key, type, value);
    dmLogInfo("Helpshift AddUserData end");
}

void ShowConversation()
{
    dmLogInfo("Helpshift Showconversation");
    CallVoidMethod(g_HelpShift.m_HelpshiftJniBridgeJNI, g_HelpShift.m_ShowConversation);
    dmLogInfo("Helpshift Showconversation end");
}

void ShowFAQ()
{
    dmLogInfo("Helpshift ShowFAQ");
    CallVoidMethod(g_HelpShift.m_HelpshiftJniBridgeJNI, g_HelpShift.m_showFAQ);
    dmLogInfo("Helpshift ShowFAQ end");
}

} // namespace

#endif // platform
