#include <cutils/log.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "YlService.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "utils/String16.h"



namespace android {


char const* YlService::getServiceName() 
{ 
    return "android.yuanlei";
}


void YlService::instance()
{
    sp<IServiceManager> sm(defaultServiceManager());
    sm->addService(String16(getServiceName()),new YlService,false);
}

void YlService::onFirstRef()
{

ALOGE("yuanlei, this is %s",__func__);


}

String16 YlService::getStringOfYl()
{
	char buffer[256];
	int fd = open("/dev/yuanlei_dev",O_RDONLY);
	int count = read(fd,buffer,256);	
	String16 a = String16(buffer);
	ALOGE("yuanlei hahahah   read buf:%s,count = %d,fd = %d",a.string(),count,fd);
    return a;
}


}
