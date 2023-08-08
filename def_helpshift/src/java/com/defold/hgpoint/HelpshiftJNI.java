package com.defold.hgpoint;

import android.util.Log;
import android.app.Activity;
import android.app.Application;
import android.content.pm.ActivityInfo;
import com.helpshift.Helpshift;
import com.helpshift.HelpshiftEvent;
import com.helpshift.HelpshiftEventsListener;
import com.helpshift.HelpshiftAuthenticationFailureReason;

import java.util.Currency;
import java.util.HashMap;
import java.util.Map;
import java.util.Locale;
import org.json.JSONObject;
import org.json.JSONException;
import androidx.annotation.NonNull;

import com.defold.hgpoint.JSONConvector;


public class HelpshiftJNI {
    private static final String TAG = "Helpshift";

    public static native void helpshiftAddToQueue(int msg, String json);

    private static final int   WIDGET_TOGGLE = 1;
    private static final int   DATA_SDK_VISIBLE = 2;
    private static final int   CONVERSATION_START = 3;
    private static final int   DATA_MESSAGE = 4;
    private static final int   MESSAGE_ADD = 5;
    private static final int   DATA_MESSAGE_TYPE = 6;
    private static final int   DATA_MESSAGE_BODY = 7;
    private static final int   DATA_MESSAGE_TYPE_ATTACHMENT = 8;
    private static final int   DATA_MESSAGE_TYPE_TEXT = 9;
    private static final int   CSAT_SUBMIT = 10;
    private static final int   DATA_CSAT_RATING = 11;
    private static final int   DATA_ADDITIONAL_FEEDBACK = 12;
    private static final int   CONVERSATION_STATUS = 13;
    private static final int   DATA_LATEST_ISSUE_ID = 14;
    private static final int   DATA_LATEST_ISSUE_PUBLISH_ID = 15;
    private static final int   DATA_IS_ISSUE_OPEN = 16;
    private static final int   CONVERSATION_END = 17;
    private static final int   CONVERSATION_REJECTED = 18;
    private static final int   CONVERSATION_RESOLVED = 19;
    private static final int   CONVERSATION_REOPENED = 20;
    private static final int   SDK_SESSION_STARTED = 21;                         
    private static final int   SDK_SESSION_ENDED = 22;
    private static final int   RECEIVED_UNREAD_MESSAGE_COUNT = 23;
    private static final int   DATA_MESSAGE_COUNT = 24;
    private static final int   DATA_MESSAGE_COUNT_FROM_CACHE = 25;

    private Activity activity;
    private Application application;

    
    HashMap<String, Object> faqData = new HashMap<>();
    HashMap<String, Object> userData = new HashMap<>();
    HashMap<String, Object> cifMap = new HashMap<>();
    

    public HelpshiftJNI(Activity activity) {
        this.activity = activity;
        this.application = activity.getApplication();
    }

    public void Initialize(final String domain, final String appID) {
        Map<String, Object> config = new HashMap<>();
        config.put("enableLogging",  true);
        config.put("screenOrientation", ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        try {
            Helpshift.install(this.application,
                    appID,
                    domain,
                    config);
        } catch (Exception e) {
            android.util.Log.e("Helpshift", "install call : ", e);
        }

        Helpshift.setHelpshiftEventsListener(new HelpshiftEventsListener() {
                @Override
                public void onEventOccurred(@NonNull String eventName, Map<String, Object> data) {
                    Log.e(TAG, "onEventOccurred: " + eventName);
                    int event = 0;
                    switch(eventName){
                        case HelpshiftEvent.WIDGET_TOGGLE:
                            event = WIDGET_TOGGLE;
                            break;
                        case HelpshiftEvent.DATA_SDK_VISIBLE:
                            event = DATA_SDK_VISIBLE;
                            break;
                        case HelpshiftEvent.CONVERSATION_START:
                            event = CONVERSATION_START;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE:
                            event = DATA_MESSAGE;
                            break;
                        case HelpshiftEvent.MESSAGE_ADD:
                            event = MESSAGE_ADD;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_TYPE:
                            event = DATA_MESSAGE_TYPE;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_BODY:
                            event = DATA_MESSAGE_BODY;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_TYPE_ATTACHMENT:
                            event = DATA_MESSAGE_TYPE_ATTACHMENT;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_TYPE_TEXT:
                            event = DATA_MESSAGE_TYPE_TEXT;
                            break;
                        case HelpshiftEvent.CSAT_SUBMIT:
                            event = CSAT_SUBMIT;
                            break;
                        case HelpshiftEvent.DATA_CSAT_RATING:
                            event = DATA_CSAT_RATING;
                            break;
                        case HelpshiftEvent.DATA_ADDITIONAL_FEEDBACK:
                            event = DATA_ADDITIONAL_FEEDBACK;
                            break;
                        case HelpshiftEvent.CONVERSATION_STATUS:
                            event = CONVERSATION_STATUS;
                            break;
                        case HelpshiftEvent.DATA_LATEST_ISSUE_ID:
                            event = DATA_LATEST_ISSUE_ID;
                            break;
                        case HelpshiftEvent.DATA_LATEST_ISSUE_PUBLISH_ID:
                            event = DATA_LATEST_ISSUE_PUBLISH_ID;
                            break;
                        case HelpshiftEvent.DATA_IS_ISSUE_OPEN:
                            event = DATA_IS_ISSUE_OPEN;
                            break;
                        case HelpshiftEvent.CONVERSATION_END:
                            event = CONVERSATION_END;
                            break;
                        case HelpshiftEvent.CONVERSATION_REJECTED:
                            event = CONVERSATION_REJECTED;
                            break;
                        case HelpshiftEvent.CONVERSATION_RESOLVED:
                            event = CONVERSATION_RESOLVED;
                            break;
                        case HelpshiftEvent.CONVERSATION_REOPENED:
                            event = CONVERSATION_REOPENED;
                            break;
                        case HelpshiftEvent.SDK_SESSION_STARTED:
                            event = SDK_SESSION_STARTED;
                            break;
                        case HelpshiftEvent.SDK_SESSION_ENDED:
                            event = SDK_SESSION_ENDED;
                            break;
                        case HelpshiftEvent.RECEIVED_UNREAD_MESSAGE_COUNT:
                            event = RECEIVED_UNREAD_MESSAGE_COUNT;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_COUNT:
                            event = DATA_MESSAGE_COUNT;
                            break;
                        case HelpshiftEvent.DATA_MESSAGE_COUNT_FROM_CACHE:
                            event = DATA_MESSAGE_COUNT_FROM_CACHE;
                            break;
                    }

                    String dataStr = new String();
                    JSONConvector Convector = null;
                    try {
                        dataStr = Convector.toJSON(data);
                    }
                    catch (JSONException e) {
                        Log.e(TAG, "Unable to encode Convector.toJSON message data: " + e.getLocalizedMessage());
                    }
                    catch (IllegalAccessException e) {
                        Log.e(TAG, "Unable to encode Convector.toJSON message data: " + e.getLocalizedMessage());
                    }

                    Log.e(TAG, "onEventOccurred : dataStr: " + dataStr);

                    try {
                        JSONObject obj = new JSONObject();
                        obj.put("data", dataStr);
                        helpshiftAddToQueue(event, obj.toString());
                    } catch (JSONException e) {
                        Log.e(TAG, "Unable to encode CONVERSION_DATA_FAIL message data: " + e.getLocalizedMessage());
                    }    
                }

                @Override
                public void onUserAuthenticationFailure(HelpshiftAuthenticationFailureReason var1)
                {}
            });
    }

    public void ShowConversation() {
        userData.put("cifs", cifMap);
        Helpshift.showConversation(this.activity, userData);
    }

    public void showFAQ() {
        Helpshift.showFAQs(this.activity, faqData);
    }

    public void AddUserData(final String key, final String type, final String value) {
        Map<String, String> valued = new HashMap<>();
        valued.put("type", type);
        valued.put("value", value);
        cifMap.put(key, valued);
    }

    public void requestUnreadMessageCount() {
        Helpshift.requestUnreadMessageCount(true);
    }
}
