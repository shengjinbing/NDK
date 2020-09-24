//
// Created by lixiang on 2020/9/24.
//

#include "dynamic.h"

jint dynamicJavaFunc(
        JNIEnv *env,
        jobject thiz,
        jint i) {

    return 66;
}

static const JNINativeMethod methods[] = {
        {"dynamicJavaFunc2", "(I)I", (int *) dynamicJavaFunc}
};

static const char *mClassName = "/Users/lixiang/masterhand/HightHand/sample/src/main/java/com/dodola/breakpad/MainActivity.java";


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    // 1. 获取 JNIEnv，这个地方要注意第一个参数是个二级指针
    int result = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    // 2. 是否获取成功
    if (result != JNI_OK) {
        //LOGE("获取 env 失败");
        return JNI_VERSION_1_6;
    }
    // 3. 注册方法
    jclass classMainActivity = env->FindClass(mClassName);
    // sizeof(methods)/ sizeof(JNINativeMethod)
    result = env->RegisterNatives(classMainActivity, methods, 2);

    if (result != JNI_OK) {
        //LOGE("注册方法失败")
        return JNI_VERSION_1_2;
    }

    return JNI_VERSION_1_6;
}

