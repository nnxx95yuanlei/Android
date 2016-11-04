#include "IYlService.h"


namespace android {

class YlService : public BnYlService {

public:
    YlService(){};

    static void instance();
    
    virtual void onFirstRef();

    virtual String16 getStringOfYl();

    static char const* getServiceName();



};


}
