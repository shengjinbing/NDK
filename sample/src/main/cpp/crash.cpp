#include <stdio.h>
#include <jni.h>
/**
 extern "C"
在 c++ 中使用 c 代码

JNIEXPORT
宏定义：#define JNIEXPORT __attribute__ ((visibility ("default")))
在 Linux/Unix/Mac os/Android 这种类 Unix 系统中，定义为__attribute__ ((visibility ("default")))
GCC 有个visibility属性, 该属性是说, 启用这个属性:
当-fvisibility=hidden时，动态库中的函数默认是被隐藏的即 hidden。
当-fvisibility=default时，动态库中的函数默认是可见的。

JNICALL
宏定义，在 Linux/Unix/Mac os/Android 这种类 Unix 系统中，它是个空的宏定义：
#define JNICALL，所以在 android 上删除它也可以。
快捷生成 .h 代码

JNIEnv
JNIEnv类型实际上代表了Java环境，通过这个 JNIEnv* 指针，就可以对 Java 端的代码进行操作：
调用 Java 函数
操作 Java 对象
JNIEnv 的本质是一个与线程相关的结构体，里面存放了大量的 JNI 函数指针：

JavaVM
JavaVM : JavaVM 是 Java虚拟机在 JNI 层的代表, JNI 全局只有一个
JNIEnv : JavaVM 在线程中的代表, 每个线程都有一个, JNI 中可能有很多个 JNIEnv，同时 JNIEnv
          具有线程相关性，也就是 B 线程无法使用 A 线程的 JNIEnv。

jobject thiz
这个 object 指向该 native 方法的 this 实例，比如我们在 MainActivity 调用的下面的 native 函数中打印一下
thiz 的 className

 */

#define  LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__);

/**
 * 引起 crash
 */
void Crash() {
    volatile int *a = (int *) (NULL);
    *a = 1;
}

extern "C"//在 c++ 中使用 c 代码
JNIEXPORT void JNICALL
Java_com_dodola_breakpad_MainActivity_crash(JNIEnv *env, jobject thiz) {
    Crash();
    // 1. 获取 thiz 的 class，也就是 java 中的 Class 信息
    jclass thisclass = env->GetObjectClass(thiz);
    // 2. 根据 Class 获取 getClass 方法的 methodID，第三个参数是签名(params)return
    jmethodID jmethodId = env->GetMethodID(thisclass, "getClass", "()Ljava/lang/Class;");
    // 3. 执行 getClass 方法，获得 Class 对象
    jobject clazz_instance = env->CallObjectMethod(thiz, jmethodId);
    // 4. 获取 Class 实例
    jclass clazz = env->GetObjectClass(clazz_instance);
    // 5. 根据 class  的 methodID
    jmethodID mid_getName = env->GetMethodID(clazz, "getName", "()Ljava/lang/String;");
    // 6. 调用 getName 方法
    jstring name = static_cast<jstring>(env->CallObjectMethod(clazz_instance, mid_getName));
    //LOGE("class name:%s", env->GetStringUTFChars(name, 0));

}



