#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "IYlService.h"
#include "utils/String16.h"

namespace android {

namespace {

enum {
    EX_SECURITY = -1,
    EX_BAD_PARCELABLE = -2,
    EX_ILLEGAL_ARGUMENT = -3,
    EX_NULL_POINTER = -4,
    EX_ILLEGAL_STATE = -5,
    EX_HAS_REPLY_HEADER = -128,  // special; see below
};

static bool readExceptionCode(Parcel& reply) {
    int32_t exceptionCode = reply.readExceptionCode();

    if (exceptionCode != 0) {
        const char* errorMsg;
        switch(exceptionCode) {
            case EX_SECURITY:
                errorMsg = "Security";
                break;
            case EX_BAD_PARCELABLE:
                errorMsg = "BadParcelable";
                break;
            case EX_NULL_POINTER:
                errorMsg = "NullPointer";
                break;
            case EX_ILLEGAL_STATE:
                errorMsg = "IllegalState";
                break;
            // Binder should be handling this code inside Parcel::readException
            // but lets have a to-string here anyway just in case.
            case EX_HAS_REPLY_HEADER:
                errorMsg = "HasReplyHeader";
                break;
            default:
                errorMsg = "Unknown";
        }

        ALOGE("Binder transmission error %s (%d)", errorMsg, exceptionCode);
        return true;
    }

    return false;
}

}

class BpYlService: public BpInterface<IYlService>
{
public:
    BpYlService(const sp<IBinder>& impl)
        : BpInterface<IYlService>(impl)
    {
    }
    virtual String16 getStringOfYl()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IYlService::getInterfaceDescriptor());
        remote()->transact(BnYlService::GET_NUMBER_OF_YL, data, &reply);

		if (readExceptionCode(reply)) return String16();
        return reply.readString16();
    }
};

IMPLEMENT_META_INTERFACE(YlService, "android.hardware.IYlService");

status_t BnYlService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case GET_NUMBER_OF_YL: {
            CHECK_INTERFACE(IYlService, data, reply);
            reply->writeNoException();
            reply->writeString16(getStringOfYl());
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}

