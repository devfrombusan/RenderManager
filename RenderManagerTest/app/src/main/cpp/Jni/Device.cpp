#include "Device.hpp"

namespace Java {

    void Exit(JNIEnv *env, jobject mainActivity) {

        jfieldID render = env->GetFieldID(env->GetObjectClass(mainActivity), "RenderThread",
                                          "Ljava/lang/Thread;");
        jobject thread = env->GetObjectField(mainActivity, render);
        jmethodID interrupted = env->GetMethodID(env->GetObjectClass(thread), "interrupt", "()V");
        env->CallVoidMethod(thread, interrupted);


        jfieldID update = env->GetFieldID(env->GetObjectClass(mainActivity), "UpdateThread",
                                          "Ljava/lang/Thread;");
        thread = env->GetObjectField(mainActivity, update);
        interrupted = env->GetMethodID(env->GetObjectClass(thread), "interrupt", "()V");
        env->CallVoidMethod(thread, interrupted);
    }
}

namespace Device{
    std::string devicePath;
    float windowWidth = 0.0f;
    float windowHeight = 0.0f;
    int year = 0;
    int month = 0;
    int day = 0;
    bool sound = true;
}
