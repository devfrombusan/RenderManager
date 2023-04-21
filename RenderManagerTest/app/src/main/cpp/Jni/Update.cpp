#include "../SampleScene/SampleScene.hpp"

std::chrono::system_clock::time_point renderStart;
std::chrono::system_clock::time_point renderEnd;
std::chrono::system_clock::time_point updateStart;
std::chrono::system_clock::time_point updateEnd;

float renderValue = 0.0f;
float updateValue = 0.0f;

bool pause = false;

extern "C" JNIEXPORT void JNICALL
Java_com_example_android_RenderManagerTest_MainActivity_Init(JNIEnv* env, jobject thiz){

    jmethodID getFileDir = env->GetMethodID(env->GetObjectClass(thiz), "getFilesDir",
                                            "()Ljava/io/File;");

    jobject file = env->CallObjectMethod(thiz, getFileDir);
    jmethodID getAbsolutePath = env->GetMethodID(env->GetObjectClass(file), "getAbsolutePath",
                                                 "()Ljava/lang/String;");

    jstring _string = (jstring) env->CallObjectMethod(file, getAbsolutePath);

    Device::devicePath = env->GetStringUTFChars(_string, nullptr);


    jmethodID getApplicationContext = env->GetMethodID(env->GetObjectClass(thiz),
                                                       "getApplicationContext",
                                                       "()Landroid/content/Context;");

    jobject context = env->CallObjectMethod(thiz, getApplicationContext);
    jmethodID getResources = env->GetMethodID(env->GetObjectClass(context), "getResources",
                                              "()Landroid/content/res/Resources;");

    jobject resources = env->CallObjectMethod(context, getResources);
    jmethodID getDisplayMetrics = env->GetMethodID(env->GetObjectClass(resources),
                                                   "getDisplayMetrics",
                                                   "()Landroid/util/DisplayMetrics;");


    jobject displayMetrics = env->CallObjectMethod(resources, getDisplayMetrics);

    jfieldID widthPixels = env->GetFieldID(env->GetObjectClass(displayMetrics), "widthPixels", "I");
    jfieldID heightPixels = env->GetFieldID(env->GetObjectClass(displayMetrics), "heightPixels",
                                            "I");

    Device::windowWidth = (float) env->GetIntField(displayMetrics, widthPixels);
    Device::windowHeight = (float) env->GetIntField(displayMetrics, heightPixels);


    if(Device::windowWidth >= Device::windowHeight) {
        float temp = Device::windowHeight;
        Device::windowHeight = Device::windowWidth;
        Device::windowWidth = temp;
    }

    renderManager = nullptr;

    if (!renderManager) renderManager = new RenderManager();
    if (!sampleScene) sampleScene = new SampleScene();

    updateStart = std::chrono::system_clock::now();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_android_RenderManagerTest_MainActivity_Update(JNIEnv* env, jobject thiz){

    updateEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> value = updateEnd - updateStart;
    updateValue = value.count();

    if (updateValue >= 0.001f) {
        updateStart = updateEnd;
        if (!pause) if (sampleScene) sampleScene->Update(env, thiz, updateValue);

    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_android_RenderManagerTest_MainActivity_Render(JNIEnv* env, jobject thiz){

    renderEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> value = renderEnd - renderStart;
    renderValue = value.count();

    if (renderValue >= 0.016f) {
        jfieldID GLES = env->GetFieldID(env->GetObjectClass(thiz), "GLES",
                                        "Lcom/example/android/RenderManagerTest/MainRender;");
        jobject mainRender = env->GetObjectField(thiz, GLES);
        jmethodID requestRender = env->GetMethodID(env->GetObjectClass(mainRender), "requestRender",
                                                   "()V");
        env->CallVoidMethod(mainRender, requestRender);
        renderStart = renderEnd;
    }

}

extern "C" JNIEXPORT void JNICALL
Java_com_example_android_RenderManagerTest_MainRender_Render(JNIEnv* env, jobject /* this */){

    if (renderManager) renderManager->Render();

}
