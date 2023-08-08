#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>
/* Header for class com_defold_helpshift_HelpshiftJNI */

#ifndef COM_DEFOLD_HELPSHIFT_HELPSHIFTJNI_H
#define COM_DEFOLD_HELPSHIFT_HELPSHIFTJNI_H
#ifdef __cplusplus
extern "C" {
#endif
    /*
    * Class:     com_defold_helpshift_HelpshiftJNI
    * Method:    helpshiftAddToQueue_first_arg
    * Signature: (ILjava/lang/String;I)V
    */
    JNIEXPORT void JNICALL Java_com_defold_hgpoint_HelpshiftJNI_helpshiftAddToQueue
        (JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif

#endif