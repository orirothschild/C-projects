#include <stdio.h> /* printf */

#include "DHCP.h"
#include "DHCP_test_funcs.h"
#include "utils.h"

static unsigned int PowerTwo(unsigned int num);
static int AreArraysIdentical(ip_t req_ip, ip_t reserved_ip);

static const size_t g_NUM_OF_BYTES = 4;


int main()
{
    RUN_TEST(TEST_DHCP_CREATE());
    RUN_TEST(TEST_DHCP_ALLOC_SUCCESS1());
    RUN_TEST(TEST_DHCP_ALLOC_SUCCESS2());
    RUN_TEST(TEST_DHCP_ALLOC_SUCCESS3());
    RUN_TEST(TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL1());
    RUN_TEST(TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL2());
    RUN_TEST(TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL3());
    RUN_TEST(TEST_DHCP_FREE());



    return (0);
}



int TEST_DHCP_CREATE()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,1};

    tree = DHCPCreate(subnet_mask, subnet_address);
    /* PrintTree(tree); */
    if(NULL != tree)
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_ALLOC_SUCCESS1()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,1};
    ip_t out_ip = {0};
    unsigned int height = 32 - subnet_mask;
    unsigned int result = PowerTwo(height);
    int num_of_free_places = result - 4;


    tree = DHCPCreate(subnet_mask, subnet_address);
    /* PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree)); */
    
    DHCPAllocIP(tree, out_ip, req_ip);
    /* PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree)); */

    

    if(num_of_free_places == DHCPCountFree(tree))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_ALLOC_SUCCESS2()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,1};
    ip_t out_ip = {0};

    tree = DHCPCreate(subnet_mask, subnet_address);
    /* PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree)); */
    
    DHCPAllocIP(tree, out_ip, req_ip);
    /* PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree)); */

    if(True == AreArraysIdentical(req_ip, out_ip))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_ALLOC_SUCCESS3()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,1};
    ip_t out_ip = {0};

    tree = DHCPCreate(subnet_mask, subnet_address);
/*     PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree));
    
    DHCPAllocIP(tree, out_ip, req_ip);
    PrintTree(tree);
    printf ("%d\n", DHCPCountFree(tree)); */

    if(SUCCESS == DHCPAllocIP(tree, out_ip, req_ip))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}



int TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL1()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,0};
    ip_t out_ip = {0};
    unsigned int height = 32 - subnet_mask;
    unsigned int result = PowerTwo(height);
    int num_of_free_places = result - 4;

    tree = DHCPCreate(subnet_mask, subnet_address);

    /* PrintTree(tree); */
    DHCPAllocIP(tree, out_ip, req_ip);
    /* PrintTree(tree); */
    if(num_of_free_places == DHCPCountFree(tree))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL2()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,0};
    ip_t out_ip = {0};

    tree = DHCPCreate(subnet_mask, subnet_address);

    /* DHCPAllocIP(tree, out_ip, req_ip); */

    if(1 == DHCPAllocIP(tree, out_ip, req_ip))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_ALLOC_RESERVED_ADDRESS_FAIL3()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,15};
    
    ip_t req_ip = {192,168,14,0};
    ip_t out_ip = {0};
    ip_t test_ip = {192,168,14,1};


    tree = DHCPCreate(subnet_mask, subnet_address);

    DHCPAllocIP(tree, out_ip, req_ip);

    if(True == AreArraysIdentical(test_ip, out_ip))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}


int TEST_DHCP_FREE()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 30;
    ip_t subnet_address = {192,168,14,1};
    ip_t req_ip = {192,168,14,2};
    ip_t out_ip = {0};
    
    unsigned int height = 32 - subnet_mask;
    unsigned int result = PowerTwo(height);
    int num_of_free_places = result - 3;

    tree = DHCPCreate(subnet_mask, subnet_address);


    /* PrintTree(tree); */
    DHCPAllocIP(tree, out_ip, req_ip);
    /* PrintTree(tree); */

    DHCPFreeIP(tree, out_ip);
    /* PrintTree(tree); */


    if(num_of_free_places == DHCPCountFree(tree))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}



int TEST_DHCP_ALLOC_STUFF()
{
    p_tree_t *tree = NULL;
    int subnet_mask = 28;
    ip_t subnet_address = {192,168,14,1};
    ip_t req_ip = {192,168,14,0};
    ip_t out_ip = {0};
    unsigned int height = 32 - subnet_mask;
    unsigned int result = PowerTwo(height);
    int num_of_free_places = result - 4;


    tree = DHCPCreate(subnet_mask, subnet_address);

    DHCPAllocIP(tree, out_ip, req_ip);
    /* printf ("%d\n", DHCPCountFree(tree)); */
    /* DHCPFreeIP(tree, ip); */

    /* printf ("%d\n", DHCPCountFree(tree)); */

    if(num_of_free_places == DHCPCountFree(tree))
    {
        DHCPDestroy(tree);
        return (PASS);
    }
    
    DHCPDestroy(tree);
    return (FAIL);
}






static unsigned int PowerTwo(unsigned int num)
{
    return 1 << num;
}


static int AreArraysIdentical(ip_t req_ip, ip_t reserved_ip)
{
    unsigned int i = 0;
    
    for (i = 0; i < g_NUM_OF_BYTES; ++i)
    {
        if (req_ip[i] != reserved_ip[i])
        {
            return False;
        }
    }

    return True;
}