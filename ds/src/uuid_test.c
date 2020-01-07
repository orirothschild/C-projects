#include <stdio.h> /* printf */

#include "uuid.h"
#include "uuid_test_funcs.h"
#include "utils.h"


int main()
{
    RUN_TEST(TestUUID_Create());
    RUN_TEST(TestUUID_IsBadUID_True());
    RUN_TEST(TestUUID_IsBadUID_False());
    RUN_TEST(TestUUID_IsSameUID_True());
    RUN_TEST(TestUUID_IsSameUID_False());
    
    return (0);
}


int TestUUID_Create()
{
    uuid_t id = UUIDCreate();
    
    if (0 == UUIDIsBadUID(id))
    {
        return (PASS);
    }
    
    return (FAIL);
}


int TestUUID_IsBadUID_True()
{
    uuid_t id = UUIDCreate();
    id.time_val = (time_t)-1;
    id.counter = 0;
    id.pid = 0;
    
    if (1 == UUIDIsBadUID(id))
    {
        return (PASS);
    }
    
    return (FAIL);
}


int TestUUID_IsBadUID_False()
{
    uuid_t id = UUIDCreate();
    id.time_val = 1;
    id.counter = 1;
    id.pid = 1;
    
    if (0 == UUIDIsBadUID(id))
    {
        return (PASS);
    }
    
    return (FAIL);
}


int TestUUID_IsSameUID_True()
{
    uuid_t id1 = UUIDCreate();
    uuid_t id2 = UUIDCreate();
    
    id1.time_val = 1;
    id1.counter = 1;
    id1.pid = 1;
        
    id2.time_val = 1;
    id2.counter = 1;
    id2.pid = 1;
    
    if (1 == UUIDIsSameUID(id1,id2))
    {
        return (PASS);
    }
    
    return (FAIL);
}


int TestUUID_IsSameUID_False()
{
    uuid_t id1 = UUIDCreate();
    uuid_t id2 = UUIDCreate();
    
    id1.time_val = 0;
    id1.counter = 1;
    id1.pid = 1;
        
    id2.time_val = 1;
    id2.counter = 1;
    id2.pid = 1;
    
    if (0 == UUIDIsSameUID(id1,id2))
    {
        return (PASS);
    }
    
    return (FAIL);
}

