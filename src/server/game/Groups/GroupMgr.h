

#ifndef _GROUPMGR_H
#define _GROUPMGR_H

#include "Group.h"

class GroupMgr
{
    friend class ACE_Singleton<GroupMgr, ACE_Null_Mutex>;
private:
    GroupMgr();
    ~GroupMgr();

public:
    typedef std::map<uint32, Group*> GroupContainer;

    Group* GetGroupByGUID(uint32 guid) const;

    void InitGroupIds();
    void RegisterGroupId(uint32 groupId);
    uint32 GenerateGroupId();

    void LoadGroups();
    void AddGroup(Group* group);
    void RemoveGroup(Group* group);


protected:
    typedef std::vector<bool> GroupIds;
    GroupIds         _groupIds;
    uint32           _nextGroupId;
    GroupContainer   GroupStore;
};

#define sGroupMgr ACE_Singleton<GroupMgr, ACE_Null_Mutex>::instance()

#endif
