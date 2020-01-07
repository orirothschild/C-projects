/***********************************
*                                  *
*   DS - DHCP                      *
*   written by: Hadar Klein        *
*   reviewed by: Oksana Rubanov    *
*                                  *
***********************************/
#include <stdio.h>
#include <assert.h> /* assert   */
#include <stdlib.h> /* malloc   */
#include <string.h> /* strncpy  */

#include "DHCP.h"   /* API      */
#include "utils.h"  /* utils    */


static const unsigned int g_MAX_BITS = 32;
static const size_t g_NUM_OF_BYTES = 4;
static const unsigned int g_MAX_UINT = 4294967295;
static const unsigned int g_MIN_UINT = 0;
static const unsigned int g_BYTE = 8;

#define GETHEIGHT (g_MAX_BITS - tree->subnet_mask)


enum direction
{
    LEFT = 0,
    RIGHT
};

enum fullness
{
    EMPTY = 0,
    FULL_USER,
    FULL_IMP
};

enum ip_kind
{
    BROADCAST = 0,
    DHCP
};

enum errors
{
    IP_TAKEN = -3,
    ALLOC_FAILURE = -2,
    FULL_TREE = -1,
    SUCCESSFUL = 0,
    SUCCESSFUL_DIFFERENT_ADDRESS = 1
};

typedef struct prefix_tree_node p_tree_node_t;


struct prefix_tree_node
{
    p_tree_node_t *children[2];
    int full_flag;
};

struct p_tree
{
    unsigned int subnet_mask;
    ip_t subnet_address;
    p_tree_node_t *root;
};


static void PrintTreeIn2DRecIMP(p_tree_node_t *node, int space);

static int DHCPCreateIMP(p_tree_t *tree);
static int DHCPAllocateNodeIPIMP(p_tree_node_t *node, const ip_t ip,
                                 unsigned int height, ip_t out_ip,
                                 enum fullness full_flag);
static p_tree_node_t *DHCPCreateNodeIMP(p_tree_node_t *l_child,
                                        p_tree_node_t *r_child,
                                        enum fullness full_flag);
static void DHCPDestroyIMP(p_tree_node_t *root);
static void DHCPFreeIPIMP(p_tree_node_t *node, ip_t ip,
                          unsigned int height);
static unsigned int DHCPCountIMP(p_tree_node_t *node, unsigned int height);
static void DHCPUpdateFullFlagIMP(p_tree_node_t *node, enum fullness full_flag);
static p_tree_node_t *DHCPGetRootIMP(const p_tree_t *tree);
static void DHCPInitReservedIPsIMP(p_tree_t *tree, ip_t network, ip_t broadcast,
                                   ip_t dhcp);
static int DHCPAreArraysIdenticalIMP(ip_t req_ip, ip_t reserved_ip);
static enum direction DHCPGetSideIMP(p_tree_node_t *node, const ip_t ip,
                                     unsigned int height);
static void DHCPSetBitIMP(enum direction side, ip_t ip,
                          unsigned int height);
static int DHCPDoesChildExistIMP(p_tree_node_t *node);
static unsigned int DHCPPowerTwoIMP(unsigned int num);
static void DHCPBuildReservedAddressesIMP(p_tree_t *tree,
										  ip_t address,
										  enum ip_kind kind);
static void DHCPBuildSubnetAddressIMP(p_tree_t *tree, ip_t subnet_address);


p_tree_t *DHCPCreate(unsigned int subnet_mask, ip_t subnet_address)
{
    p_tree_t *tree = NULL;
    p_tree_node_t *root = NULL;
    ip_t temp = {0};

    assert(30 >= subnet_mask);

    strncpy((char *)temp, (const char *)subnet_address,
             g_NUM_OF_BYTES);

    tree = (p_tree_t *)malloc(sizeof(p_tree_t));
    if (NULL == tree)
    {
        return NULL;
    }

    root = DHCPCreateNodeIMP(NULL, NULL, EMPTY);
    if (NULL == root)
    {
        free(tree);

        return NULL;
    }

    tree->root = root;
    tree->subnet_mask = subnet_mask;
   
    DHCPBuildSubnetAddressIMP(tree, temp);

    if (ALLOC_FAILURE == DHCPCreateIMP(tree))
    {
        DHCPDestroy(tree);
        
        return NULL;
    }

    return tree;
}


void DHCPDestroy(p_tree_t *tree)
{
    p_tree_node_t *root = NULL;

    assert(NULL != tree);

    DHCPDestroyIMP(DHCPGetRootIMP(tree));

    free(tree);
}


int DHCPAllocIP(p_tree_t *tree, ip_t out_ip, const ip_t requested_ip)
{
    int height = GETHEIGHT;
    int result = 0;
    enum fullness full_flag = FULL_USER;

    assert(NULL != tree);

    strncpy((char *)out_ip, (const char *)tree->subnet_address, g_NUM_OF_BYTES);

    if (NULL != requested_ip)
    {
        result = DHCPAllocateNodeIPIMP(DHCPGetRootIMP(tree), requested_ip,
                                       height, out_ip, full_flag);
    }
    
    if (FULL_TREE == result || NULL == requested_ip)
    {
        result = DHCPAllocateNodeIPIMP(DHCPGetRootIMP(tree), NULL, height,
                                       out_ip, full_flag);

        if (SUCCESSFUL == result && NULL != requested_ip)
        {
            return SUCCESSFUL_DIFFERENT_ADDRESS;
        }
    }

    return result;
}


void DHCPFreeIP(p_tree_t *tree, ip_t ip)
{
    size_t height = GETHEIGHT;
    ip_t network = {0};
    ip_t broadcast = {0};
    ip_t dhcp = {0};

    assert(NULL != tree);

    DHCPInitReservedIPsIMP(tree, network, broadcast, dhcp);

    assert(False == DHCPAreArraysIdenticalIMP(ip, network));
    assert(False == DHCPAreArraysIdenticalIMP(ip, broadcast));
    assert(False == DHCPAreArraysIdenticalIMP(ip, dhcp));

    DHCPFreeIPIMP(DHCPGetRootIMP(tree), ip, height);
}


int DHCPCountFree(const p_tree_t *tree)
{
    unsigned int height = GETHEIGHT;

    assert(NULL != tree);

    return DHCPPowerTwoIMP(height) - DHCPCountIMP(DHCPGetRootIMP(tree), height);
}


/******************************************************************************/
static int DHCPCreateIMP(p_tree_t *tree)
{
    ip_t network = {0};
    ip_t broadcast = {0};
    ip_t dhcp = {0};
    ip_t out_ip = {0};
    int height = GETHEIGHT;
    int result = SUCCESSFUL;
    enum fullness full_flag = FULL_IMP;

    assert(NULL != tree);
    
    DHCPInitReservedIPsIMP(tree, network, broadcast, dhcp);

    result = DHCPAllocateNodeIPIMP(DHCPGetRootIMP(tree), network,
                                   height, out_ip, full_flag);
    if (ALLOC_FAILURE == result)
    {
        return ALLOC_FAILURE;
    }

    result = DHCPAllocateNodeIPIMP(DHCPGetRootIMP(tree), broadcast,
                                   height, out_ip, full_flag);
    if (ALLOC_FAILURE == result)
    {
        return ALLOC_FAILURE;
    }

    result = DHCPAllocateNodeIPIMP(DHCPGetRootIMP(tree), dhcp,
                                   height, out_ip, full_flag);
    if (ALLOC_FAILURE == result)
    {
        return ALLOC_FAILURE;
    }

    return result;
}


static int DHCPAllocateNodeIPIMP(p_tree_node_t *node, const ip_t ip,
                                 unsigned int height, ip_t out_ip,
                                 enum fullness full_flag)
{
    enum direction side = LEFT;
    int result = 0;

    assert(NULL != node);

    if (FULL_USER == node->full_flag || FULL_IMP == node->full_flag)
    {
        return FULL_TREE;
    }

    if (0 == height)
    {
        node->full_flag = full_flag;
        return SUCCESSFUL;
    }

    side = DHCPGetSideIMP(node, ip, height);

    if (NULL == node->children[side])
    {
        node->children[side] = DHCPCreateNodeIMP(NULL, NULL, EMPTY);
        if (NULL == node->children[side])
        {
            return ALLOC_FAILURE;
        }
    }

    result = DHCPAllocateNodeIPIMP(node->children[side], ip, height - 1, out_ip,
                                full_flag);
    if (SUCCESSFUL == result)
    {
        DHCPSetBitIMP(side, out_ip, height);
        DHCPUpdateFullFlagIMP(node, full_flag);
    }
    
    return result;
}


static p_tree_node_t *DHCPCreateNodeIMP(p_tree_node_t *l_child,
                                        p_tree_node_t *r_child,
                                        enum fullness full_flag)
{
    p_tree_node_t *new_node = NULL;

    new_node = (p_tree_node_t *)malloc(sizeof(p_tree_node_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->full_flag = full_flag;
    new_node->children[LEFT] = l_child;
    new_node->children[RIGHT] = r_child;

    return new_node;
}


static void DHCPDestroyIMP(p_tree_node_t *root)
{
    if (NULL == root)
    {
        return;
    }
    
    DHCPDestroyIMP(root->children[LEFT]);
    DHCPDestroyIMP(root->children[RIGHT]);

    free(root);
    return;
}


static void DHCPFreeIPIMP(p_tree_node_t *node, ip_t ip,
                          unsigned int height)
{
    enum direction side = 0;

    assert(NULL != node);
    assert(FULL_IMP != node->full_flag);
    
    if (0 == height)
    {
        node->full_flag = EMPTY;
        
        return;
    }

    side = DHCPGetSideIMP(node, ip, height);

    DHCPFreeIPIMP(node->children[side], ip, height - 1);
    node->full_flag = 0;
}


static unsigned int DHCPCountIMP(p_tree_node_t *node, unsigned int height)
{
    if (NULL == node)
    {
        return 0;
    }
    if (FULL_USER == node->full_flag || FULL_IMP == node->full_flag)
    {   
        return DHCPPowerTwoIMP(height);
    }

    return DHCPCountIMP(node->children[LEFT], height - 1) +  
           DHCPCountIMP(node->children[RIGHT], height - 1);
}


/******************************************************************************/
static void DHCPUpdateFullFlagIMP(p_tree_node_t *node, enum fullness full_flag)
{
    int l_child_fullness = 0;
    int r_child_fullness = 0;

    assert(NULL != node);

    l_child_fullness = DHCPDoesChildExistIMP(node->children[LEFT]);
    r_child_fullness = DHCPDoesChildExistIMP(node->children[RIGHT]);

    if (EMPTY != l_child_fullness)
    {
        if (EMPTY != r_child_fullness)
        {
            node->full_flag = full_flag;
            
            return;
        }

        node->full_flag = EMPTY;
    }
}


static int DHCPDoesChildExistIMP(p_tree_node_t *node)
{
    if (NULL == node)
    {
        return EMPTY;
    }

    return node->full_flag;
}


static p_tree_node_t *DHCPGetRootIMP(const p_tree_t *tree)
{
    assert(NULL != tree);

    return tree->root;
}


static void DHCPBuildSubnetAddressIMP(p_tree_t *tree, ip_t subnet_address)
{
	unsigned int i = 0;	
	unsigned int height_reminder = 0;
	unsigned int index = 3;

    assert(NULL != tree);

	for (i = 0; i < (GETHEIGHT / g_BYTE); ++i)
	{
		subnet_address[index-i] &= 0;
	}

	height_reminder = GETHEIGHT % g_BYTE;
	if (0 < height_reminder)
	{
		subnet_address[index-i] &= 0xff << height_reminder;
	}

    strncpy((char *)tree->subnet_address, (const char *)subnet_address,
             g_NUM_OF_BYTES);
}


static void DHCPBuildReservedAddressesIMP(p_tree_t *tree,
										  ip_t address,
										  enum ip_kind kind)
{
	unsigned int index = 3;
	unsigned int i = 0;

    assert(NULL != tree);

	for (i = 0; i < (GETHEIGHT - 1) / g_BYTE; ++i)
	{
		address[index - i] |= 0xff;
	}
	if (0 < ((GETHEIGHT - 1) % g_BYTE))
	{
		address[index-i] |= 0xff >> ((g_BYTE - 1) - ((GETHEIGHT - 1) % g_BYTE));
	}
	if (DHCP == kind)
	{
		address[index] -= 1;
	}
}

static void DHCPInitReservedIPsIMP(p_tree_t *tree, ip_t network, ip_t broadcast,
                                   ip_t dhcp)
{
    DHCPBuildReservedAddressesIMP(tree, broadcast, BROADCAST);
    DHCPBuildReservedAddressesIMP(tree, dhcp, DHCP);
    strncpy((char *)network, (const char *)tree->subnet_address,
            g_NUM_OF_BYTES);
}


static int DHCPAreArraysIdenticalIMP(ip_t req_ip, ip_t reserved_ip)
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


static enum direction DHCPGetSideIMP(p_tree_node_t *node, const ip_t ip,
                                     unsigned int height)
{
    int idx = 0;
    int bit_idx = 0;
    unsigned char mask = 1;

    assert(NULL != node);

    if (NULL == ip)
    {
        if (NULL == node->children[LEFT] || 
            EMPTY == node->children[LEFT]->full_flag)
        {
            return LEFT;
        }
        else
        {
            return RIGHT;
        }
    }
    else
    {
        idx = g_NUM_OF_BYTES - 1 - ((height - 1) / 8);
        bit_idx = (height - 1) % 8;

        mask <<= bit_idx;

        if ((ip[idx] & mask) == mask)
        {
            return RIGHT;
        }

        return LEFT;
    }
}


static void DHCPSetBitIMP(enum direction side, ip_t ip,
                          unsigned int height)
{
    int idx = 0;
    int bit_idx = 0;
    unsigned char mask = 1;

    idx = g_NUM_OF_BYTES - 1 - ((height - 1) / 8);
    bit_idx = (height - 1) % 8;

    if (LEFT == side)
    {
        ip[idx] &= ~(mask << bit_idx);
    }
    else
    {
        ip[idx] |= mask << bit_idx;
    }
}


static unsigned int DHCPPowerTwoIMP(unsigned int num)
{
    return 1 << num;
}


/******************************************************************************/
void PrintTree(p_tree_t *tree)
{
   PrintTreeIn2DRecIMP(tree->root , -1);
}


static void PrintTreeIn2DRecIMP(p_tree_node_t *node, int space)
{
   int i = 0;

   if (node == NULL)
   {
       return;
   }

   PrintTreeIn2DRecIMP(node->children[RIGHT], ++space);

   printf("\n");
   for (i = 0; i < space; ++i)
   {
       printf("\t");
   }

   printf("%p\n", (void *)node);

   for (i = 0; i < space; ++i)
   {
       printf("\t");
   }
   
   printf("%d\n", node->full_flag);

   PrintTreeIn2DRecIMP(node->children[LEFT], space);
}

