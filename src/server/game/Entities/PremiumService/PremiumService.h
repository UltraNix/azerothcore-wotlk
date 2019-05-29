#ifndef HELLGROUND_PREMIUMSERVICE_H
#define HELLGROUND_PREMIUMSERVICE_H

#include "SharedDefines.h"

class PremiumService
{
public:
    PremiumService();
    PremiumService(ServiceType type);
    PremiumService(ServiceType type, uint32 setTime, uint32 endTime);

    bool IsActive();
    void SetServiceType(ServiceType);
    bool Update(uint32 setTime, uint32 endTime);

    uint32 GetEndTime() const { return m_endTime; }

private:
    ServiceType m_serviceType = SERVICE_UNKNOWN;
    uint32 m_setTime = 0;
    uint32 m_endTime = 0;
};

#endif //HELLGROUND_PREMIUMSERVICE_H
