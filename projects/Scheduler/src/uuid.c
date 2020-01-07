/***********************************
*                                  *
*   DS - UUID                      *
*   written by: Hadar Klein        *
*   reviewed by: Yoni Wainsztok    *
*                                  *
***********************************/

#include "uuid.h"
#include "utils.h"

const uuid_t g_bad_uuid = {-1, 0, 0};


uuid_t UUIDCreate()
{
    static size_t counter = 0;
    uuid_t uuid = {0};
    
    uuid.time_val = time(NULL);
    uuid.pid = getpid();
    uuid.counter = ++counter;
    
    if (uuid.time_val == (time_t)-1)
    {
        uuid.counter = 0;
        uuid.pid = 0;
    }
    
    return (uuid);
}


int UUIDIsSameUID(uuid_t uuid1, uuid_t uuid2)
{
    if ((uuid1.time_val == uuid2.time_val) &&
        (uuid1.counter == uuid2.counter) &&
        (uuid1.pid == uuid2.pid))
    {
        return (True);
    }
    
    return (False);
}


int UUIDIsBadUID(uuid_t uuid)
{
    if ((uuid.time_val == g_bad_uuid.time_val) ||
        (uuid.counter == g_bad_uuid.counter) ||
        (uuid.pid == g_bad_uuid.pid))
    {
        return (True);
    }
    
    return (False);
}
