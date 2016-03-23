#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "utils/Log.h"
#include "JNIHelp.h"
#include "utils/StrongPointer.h"
#include <binder/IServiceManager.h>
#include "IYlService.h"
#include <utils/RefBase.h>
#include "utils/String16.h"
#include "utils/String8.h"




namespace android {

class NativeYlManager : public virtual RefBase {
public:
	NativeYlManager();
	virtual sp<IYlService> getYlService();
	virtual String16 getStringOfYl();
    static void* nativeInit();

	virtual ~NativeYlManager() {};
private:
	void* mPtr;


};

NativeYlManager::NativeYlManager() {

}

String16 NativeYlManager::getStringOfYl() {
	sp<IYlService> yl = this->getYlService();
	return yl->getStringOfYl();
}


sp<IYlService> NativeYlManager::getYlService() {
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> b = sm->getService(String16("android.yuanlei"));
	sp<IYlService> yl = interface_cast<IYlService>(b);
	yl->incStrong(NULL);
	return yl;
}

void* NativeYlManager::nativeInit() {
	sp<NativeYlManager> nm = new NativeYlManager();
	nm->incStrong((void*)nativeInit);
	return (void*)nm.get();
}

















jstring yuanlei_stringFromJNI( JNIEnv* env, jobject thiz );
jstring yuanlei11_stringFromJNI( JNIEnv* env, jobject thiz );
static JNINativeMethod gMethods[] = {
    /* name, signature, funcPtr */
    { "stringFromJNI",
            "()Ljava/lang/String;",
            (void*) yuanlei_stringFromJNI },
//    { "getNumberOfYl",
//            "()Ljava/lang/String;",
//             (void*) yuanlei11_stringFromJNI },
};


NativeYlManager* manager = NULL;

jstring
yuanlei_stringFromJNI( JNIEnv* env, jobject thiz )
{
	char buffer[128];
	int fd = open("/sys/class/video4linux/v4l-subdev19/name",O_RDONLY);
	int count = read(fd,buffer,128);

	manager = (NativeYlManager*)(NativeYlManager::nativeInit());
	String16 a = manager->getStringOfYl();
	ALOGE("yuanlei read buf = %s",a.string());
	buffer[count++] = '<';
	memcpy(buffer+count,String8(a).string(),a.size());
	count += a.size();
	buffer[count++] = '>';
	buffer[count] = '\0';
    return env->NewStringUTF(buffer);
}

jstring
yuanlei11_stringFromJNI( JNIEnv* env, jobject thiz )
{
    return env->NewStringUTF( " and this is a qualcomm program");
}

jint register_android_Ahelloworld(JNIEnv* env)
{
    jclass clazz = env->FindClass("com/example/ahelloworld/MainActivity");
    jint res = env->RegisterNatives(clazz,gMethods, NELEM(gMethods));
    return res;
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    register_android_Ahelloworld(env);
    return JNI_VERSION_1_4;
}

}
