#include "YlService.h"
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>

using namespace android;

int main(int argc , char** argv) {


YlService::instance();

ProcessState::self()->startThreadPool();
IPCThreadState::self()->joinThreadPool();


}
