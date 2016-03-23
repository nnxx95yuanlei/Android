#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>



namespace android {

class IYlService : public IInterface
{
public:

    enum {
        GET_NUMBER_OF_YL = IBinder::FIRST_CALL_TRANSACTION,
    };
    DECLARE_META_INTERFACE(YlService);
    virtual String16 getStringOfYl() = 0;

};

class BnYlService: public BnInterface<IYlService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}
