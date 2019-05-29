#include "PremiumService.h"
#include "World/World.h"

PremiumService::PremiumService() :
        m_serviceType(SERVICE_UNKNOWN)
{
}

PremiumService::PremiumService(ServiceType type) :
        m_serviceType(type)
{

}

PremiumService::PremiumService(ServiceType type, uint32 setTime, uint32 endTime):
        m_serviceType(type),
        m_setTime(setTime),
        m_endTime(endTime)
{

}

bool PremiumService::IsActive()
{
    return m_endTime > sWorld->GetGameTime();
}

void PremiumService::SetServiceType(ServiceType type)
{
    m_serviceType = type;
}

bool PremiumService::Update(uint32 setTime, uint32 endTime)
{
    bool updated = false;
    if (m_setTime != setTime)
    {
        m_setTime = setTime;
        updated = true;
    }

    if (m_endTime != endTime)
    {
        m_endTime = endTime;
        updated = true;
    }

    return updated;
}

