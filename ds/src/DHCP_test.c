#include <stdio.h>  /* printf */
#include <string.h> /* memcmp */

#include "DHCP.h"
#include "utils.h"
/* #define RUN_TEST(test) test ? printf("OK: " #test "\n") : \
                              printf("FAILED:  " #test "\n"); */

void PrintIP(ip_t ip);
void TestAllocAllForSubnetMask24(p_tree_t *p_tree, ip_t answer);
void TestFreeAllForSubnetMask24(p_tree_t *p_tree);
void TestAllocAllForSubnetMask29(p_tree_t *p_tree, ip_t answer);
void TestAllocAllForSubnetMask20(p_tree_t *p_tree, ip_t answer);
void TestFreeAllForSubnetMask20(p_tree_t *p_tree);

int main()
{
    ip_t dhcp_ip_mask_24 = { 0xC0, 0xA8, 0x20, 0xFE };
    ip_t broadcast_ip_mask_24 = { 0xC0, 0xA8, 0x20, 0xFF };
    ip_t network_ip_mask_24 = { 0xC0, 0xA8, 0x20, 0x0 };
    ip_t request_ip = { 0xC0, 0xA8, 0x20, 0xFB };
    ip_t answer = { 0 };
    ip_t subnet_address = { 0xC0, 0xA8, 0x20, 0x46 };
    ip_t dhcp_ip_mask_20 = { 0xC0, 0xA8, 0x3F, 0xFE };
    ip_t broadcast_ip_mask_20 = { 0xC0, 0xA8, 0x3F, 0xFF };
    ip_t network_ip_mask_20 = { 0xC0, 0xA8, 0x20, 0x0 };
    unsigned int subnet_mask = 24;
    unsigned int subnet_mask2 = 29;
    unsigned int subnet_mask3 = 20;
    p_tree_t *p_tree = NULL;

    p_tree = DHCPCreate(subnet_mask, subnet_address);
    PrintTree(p_tree);
    RUN_TEST(NULL != p_tree);
    RUN_TEST(253 == DHCPCountFree(p_tree));
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, dhcp_ip_mask_24));
    PrintTree(p_tree);
    RUN_TEST(252 == DHCPCountFree(p_tree));
    PrintIP(answer);
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, broadcast_ip_mask_24));
    PrintTree(p_tree);
    RUN_TEST(251 == DHCPCountFree(p_tree));
    PrintIP(answer);
    PrintTree(p_tree);
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, network_ip_mask_24));
    RUN_TEST(250 == DHCPCountFree(p_tree));
    PrintIP(answer);
    RUN_TEST(0 == DHCPAllocIP(p_tree, answer, request_ip));
    RUN_TEST(249 == DHCPCountFree(p_tree));
    PrintIP(answer);
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, request_ip));
    RUN_TEST(248 == DHCPCountFree(p_tree));
    PrintIP(answer);
    DHCPFreeIP(p_tree, request_ip);
    RUN_TEST(249 == DHCPCountFree(p_tree));
    RUN_TEST(0 == DHCPAllocIP(p_tree, answer, request_ip));
    RUN_TEST(248 == DHCPCountFree(p_tree));
    PrintIP(answer);
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask, subnet_address);
    RUN_TEST(NULL != p_tree);
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask, subnet_address);
    RUN_TEST(NULL != p_tree);
    TestAllocAllForSubnetMask24(p_tree, answer);
    RUN_TEST(0 == DHCPCountFree(p_tree));
    RUN_TEST(-1 == DHCPAllocIP(p_tree, answer, NULL));
    TestFreeAllForSubnetMask24(p_tree);
    RUN_TEST(253 == DHCPCountFree(p_tree));
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask2, subnet_address);
    RUN_TEST(NULL != p_tree);
    RUN_TEST(5 == DHCPCountFree(p_tree));
    TestAllocAllForSubnetMask29(p_tree, answer);
    RUN_TEST(0 == DHCPCountFree(p_tree));
    RUN_TEST(-1 == DHCPAllocIP(p_tree, answer, request_ip));
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask3, subnet_address);
    RUN_TEST(NULL != p_tree);
    RUN_TEST(4093 == DHCPCountFree(p_tree));
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, dhcp_ip_mask_20));
    RUN_TEST(4092 == DHCPCountFree(p_tree));
    PrintIP(answer);
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, broadcast_ip_mask_20));
    RUN_TEST(4091 == DHCPCountFree(p_tree));
    PrintIP(answer);
    RUN_TEST(1 == DHCPAllocIP(p_tree, answer, network_ip_mask_20));
    RUN_TEST(4090 == DHCPCountFree(p_tree));
    PrintIP(answer);
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask3, subnet_address);
    RUN_TEST(NULL != p_tree);
    RUN_TEST(4093 == DHCPCountFree(p_tree));
    TestAllocAllForSubnetMask20(p_tree, answer);
    RUN_TEST(0 == DHCPCountFree(p_tree));
    RUN_TEST(-1 == DHCPAllocIP(p_tree, answer, request_ip));
    RUN_TEST(-1 == DHCPAllocIP(p_tree, answer, NULL));
    TestFreeAllForSubnetMask20(p_tree);
    RUN_TEST(4093 == DHCPCountFree(p_tree));
    DHCPDestroy(p_tree);

    p_tree = DHCPCreate(subnet_mask, subnet_address);
    RUN_TEST(NULL != p_tree);
    /*DHCPFreeIP(p_tree, dhcp_ip_mask_24); test for assert */
    DHCPDestroy(p_tree);

    return (0);
}

void PrintIP(ip_t ip)
{
    int i = 0;

    for (i = 0; i < 4; ++i)
    {
        printf("%d.", ip[i]);
    }
    printf("\n");
}

void TestAllocAllForSubnetMask24(p_tree_t *p_tree, ip_t answer)
{
    ip_t first_ip = { 0xC0, 0xA8, 0x20, 0x1 };
    int free_address = 0;

    for (free_address = DHCPCountFree(p_tree); free_address > 0; --free_address)
    {
        RUN_TEST(0 == DHCPAllocIP(p_tree, answer, NULL));
        RUN_TEST(0 == memcmp(first_ip, answer, 4));
        ++first_ip[3];
    }
}

void TestFreeAllForSubnetMask24(p_tree_t *p_tree)
{
    int i = 0;
    ip_t ip = { 0xC0, 0xA8, 0x20, 0x1 };
    ip_t dhcp_ip = { 0xC0, 0xA8, 0x20, 0xFE };
    ip_t broadcast_ip = { 0xC0, 0xA8, 0x20, 0xFF };
    ip_t network_ip = { 0xC0, 0xA8, 0x20, 0x0 };

    while (i < 253)
    {
        if (0 != memcmp(ip, dhcp_ip, 4) &&
            0 != memcmp(ip, broadcast_ip, 4) &&
            0 != memcmp(ip, network_ip, 4))
        {
            RUN_TEST(i == DHCPCountFree(p_tree));
            DHCPFreeIP(p_tree, ip);
            ++i;
        }

        ++ip[3];
    }
}

void TestAllocAllForSubnetMask29(p_tree_t *p_tree, ip_t answer)
{
    ip_t first_ip = { 0xC0, 0xA8, 0x20, 0x41 };
    int free_address = 0;

    for (free_address = DHCPCountFree(p_tree); free_address > 0; --free_address)
    {
        RUN_TEST(0 == DHCPAllocIP(p_tree, answer, NULL));
        RUN_TEST(0 == memcmp(first_ip, answer, 4));
        ++first_ip[3];
    }
}

void TestAllocAllForSubnetMask20(p_tree_t *p_tree, ip_t answer)
{
    ip_t first_ip = { 0xC0, 0xA8, 0x20, 0x1 };
    int free_address = 0;

    for (free_address = DHCPCountFree(p_tree); free_address > 0; --free_address)
    {
        RUN_TEST(0 == DHCPAllocIP(p_tree, answer, NULL));
        RUN_TEST(0 == memcmp(first_ip, answer, 4));
        if (first_ip[3] == 255)
        {
            ++first_ip[2];
            first_ip[3] = 0x0;
            continue;    
        }

        ++first_ip[3];
    }
}

void TestFreeAllForSubnetMask20(p_tree_t *p_tree)
{
    int i = 0;
    ip_t ip = { 0xC0, 0xA8, 0x20, 0x1 };
    ip_t dhcp_ip = { 0xC0, 0xA8, 0x3F, 0xFE };
    ip_t broadcast_ip = { 0xC0, 0xA8, 0x3F, 0xFF };
    ip_t network_ip = { 0xC0, 0xA8, 0x20, 0x0 };

    while (i < 4093)
    {
        if (0 != memcmp(ip, dhcp_ip, 4) &&
            0 != memcmp(ip, broadcast_ip, 4) &&
            0 != memcmp(ip, network_ip, 4))
        {
            RUN_TEST(i == DHCPCountFree(p_tree));
            DHCPFreeIP(p_tree, ip);
            ++i;
        }

        if (ip[3] == 255)
        {
            ++ip[2];
            ip[3] = 0x0;
            continue;    
        }

        ++ip[3];
    }
}