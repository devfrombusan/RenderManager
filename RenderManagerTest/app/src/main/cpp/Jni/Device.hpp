#include <jni.h>
#include <vector>
#include <list>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include <android/log.h>

#define printf(...) __android_log_print(ANDROID_LOG_DEBUG  , "상태", __VA_ARGS__)

#ifndef DEVICE_HPP
#define DEVICE_HPP

namespace Java {
    void Exit(JNIEnv *env, jobject mainActivity);
}

namespace Device{
    extern std::string devicePath;
    extern float windowWidth, windowHeight;
    extern int year, month, day;
    extern bool sound;
}

/*
 * device 파일 저장 경로 저장
 * */
#endif //DEVICE_HPP
