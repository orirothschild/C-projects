/* RC5 */
#ifndef ILRD_DHCP_H
#define ILRD_DHCP_H

typedef unsigned char ip_t[4];

typedef struct p_tree p_tree_t;


/*
* create a DHCP tree and reserves needed addresses
* Return Value: a pointer to a DHCP prefix tree, creates the saved addresses,
                NULL if allocation failure
* Parameters  : subnet_mask: a subnet_mask
                subnet_address: the subnet address
* Input       : -
* Time Complexity: O(logn)
*/
p_tree_t *DHCPCreate(unsigned int subnet_mask, ip_t subnet_address);


/*
* Destroys the DHCP tree
* Return Value: - 
* Parameters  : tree: a prefix tree
* Input       : tree cannot be NULL
* Time Complexity: O(n)
*/
void DHCPDestroy(p_tree_t *tree);


/*
* Counts the number of allocatable IP addresses in the DHCP tree
* Return Value: the number of allocatable addresses
* Parameters  : tree: a DHCP prefix tree
* Input       : tree cannot be NULL
* Time Complexity: O(1/2 2^n)
*/
int DHCPCountFree(const p_tree_t *tree);


/*
* Attempts to allocate an address in the DHCP tree. User may request to receive
  a specific address using [requested_ip_address], or leave it NULL otherwise.
* Return Value:  0 on success,
                 1 on success in a different address thanrequested,
                -1 if the dhcp server is full,
                -2 on allocation failure
* Parameters  : tree: a DHCP prefix tree
                ip_address: out-parameter containing the given address if 
                successful, a different address if succesful with a different 
                address
                requested_ip_address: the user's requested ip address
* Input       : tree cannot be NULL
* Time Complexity: O(logn)
*/
int DHCPAllocIP(p_tree_t *tree, ip_t ip_address,
                const ip_t requested_ip_address);


/*
* Frees the given ip address
* Return Value: -
* Parameters  : tree: a DHCP prefix tree
                ip : an allocated address.
* Input       : tree cannot be NULL
* NOTES: UNDEFINED BEHAVIOR: if the address given is not an address returned by 
                             DHCPAllocIP()
* Time Complexity: O(logn)
*/
void DHCPFreeIP(p_tree_t *tree, ip_t ip);


void PrintTree(p_tree_t *tree);

#endif /* DHCP_H */
