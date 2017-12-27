#include <stdio.h>
#include <time.h>
#include <pcap.h>
#include <WinSock2.h>

//#pragma comment(lib,"ws2_32.lib")

struct ethernet_header
{
	u_int8_t ether_dhost[6]; // Destination MAC address.
	u_int8_t ether_shost[6]; // Source MAC address.
	u_int16_t ether_type;    // Protocol Type.
};

struct ip_header
{
#if defined(WORDS_BIENDIAN)   
	u_int8_t   ip_version : 4,
		ip_header_length : 4;
#else   
	u_int8_t   ip_header_length : 4,
		ip_version : 4;
#endif   
	u_int8_t    ip_tos;
	u_int16_t   ip_length;
	u_int16_t   ip_id;
	u_int16_t   ip_off;
	u_int8_t    ip_ttl;
	u_int8_t    ip_protocol;
	u_int16_t   ip_checksum;
	struct in_addr ip_souce_address;
	struct in_addr ip_destination_address;
};

void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content);
void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content);
void stamp_to_standard(int stampTime);

int main()
{
	printf("***** This is a simple packet catcher based on WinPcap. *****\n");

	pcap_if_t *allAdapters;
	pcap_if_t *adapter;
	char errorBuffer[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allAdapters, errorBuffer) == -1)
	{
		fprintf(stderr, "\nError in pcap_findalldevs_ex function: %s\n", errorBuffer);

		return -1;
	}
	if (allAdapters == NULL)
	{
		printf("No adapters foud! Make sure WinPcap is installed.\n");

		return 0;
	}

	// Print all adapters.
	printf("All Adapters:\n");
	int crtAdapter = 0;
	for (adapter = allAdapters;adapter != NULL;adapter = adapter->next)
	{
		printf("%d.%s", ++crtAdapter, adapter->name);
		printf("-- %s\n\n", adapter->description);
	}
	printf("\n");

	// Input the adapter number which was wanted to supervise.
	int adapterNumber;
	printf("Please enter the adapter number between 1 and %d: ", crtAdapter);
	scanf("%d", &adapterNumber);
	if (adapterNumber < 1 || adapterNumber > crtAdapter)
	{
		printf("Adapter number out of range. Program exit.\n");

		pcap_freealldevs(allAdapters);

		return -1;
	}
	
	// Get the adapter by the inputed adapter number.
	pcap_t *adapterHandle;
	adapter = allAdapters;
	for (crtAdapter = 0;crtAdapter < adapterNumber - 1;crtAdapter++)
	{
		adapter = adapter->next;
	}

	// Get the adapter specificator.
	adapterHandle = pcap_open(
		adapter->name,						// Adapter name.
		65536,								// The biggest packages' size that will be catched.
		PCAP_OPENFLAG_PROMISCUOUS,			// Promisc Mode.
		1000,								// Read Timeout time.
		NULL,								// Authentication.
		errorBuffer							// Error buffer.
	);
	if (adapterHandle == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter.Program exit.\n", adapter->name);

		pcap_freealldevs(allAdapters);

		return -1;
	}

	printf("Capture session started on adapter %s:\n", adapter->name);
	pcap_freealldevs(allAdapters);

	//struct pcap_pkthdr *packetHeader;
	//const u_char *packetData;

	////Just print Frame Header.
	//int retValue;
	//while ((retValue = pcap_next_ex(
	//	adapterHandle,
	//	&packetHeader,
	//	&packetData
	//)) >= 0)
	//{
	//	if (retValue == 0)
	//	{
	//		continue;
	//	}

	//	printf("Frame Header:\n");
	//	printf("Length of packet: %d\n", packetHeader->len);
	//	printf("Length of portion present: %d\n", packetHeader->caplen);
	//	printf("Time stamp: %d\n", packetHeader->ts.tv_sec);
	//	printf("\n");
	//}

	//if (retValue == -1)
	//{
	//	printf("Error reading the packets: %s\nProgram exit.\n", pcap_geterr(adapterHandle));

	//	return -1;
	//}

	// Only catch 10 packets.
	pcap_loop(adapterHandle, 10, ethernet_protocol_packet_callback, NULL);

	pcap_close(adapterHandle);

	return 0;
}

// Analyze Ethernet packets.
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	u_short ethernet_type;
	struct ethernet_header *ethernet_protocol;
	u_char *mac_string;
	static int packet_number = 1;

	printf("**************************************************\n");
	printf("Catched No.%d packet.\n", packet_number);

	printf("Catched Time: ");											// Catched Time
	stamp_to_standard(packet_header->ts.tv_sec);

	printf("Packet Length: ");
	printf("%d\n", packet_header->len);

	printf("---------- Ethernet  Protocol ----------\n");
	ethernet_protocol = (struct ethernet_header*)packet_content;		// Get the packet data.  

	printf("Ethernet type: ");
	ethernet_type = ntohs(ethernet_protocol->ether_type);				// Get the ethernet type.
	printf("%04x\n", ethernet_type);
	switch (ethernet_type)
	{
	case 0x0800: printf("Upper layer protocol is IP protocol.\n");break;
	case 0x0806: printf("Upper layer protocol is ARP protocol.\n");break;
	case 0x8035: printf("Upper layer protocol is RARP protocol.\n");break;
	default:break;
	}

	printf("Source MAC address: ");
	mac_string = ethernet_protocol->ether_shost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));

	printf("Destination MAC address: ");
	mac_string = ethernet_protocol->ether_dhost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));

	if (ethernet_type == 0x0800)										// Continue to analyse IP protocol.
	{
		ip_protocol_packet_callback(argument, packet_header, packet_content);
	}
	printf("----------------------------------------\n");
	printf("\n");

	packet_number++;
}

// Analyse IP packets.
void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	struct ip_header *ip_protocol;
	u_int header_length;
	u_int offset;
	u_char tos;
	u_int16_t checksum;

	ip_protocol = (struct ip_header *) (packet_content + 14);			// MAC address is 14 bit, add 14 to get IP header.
	checksum = ntohs(ip_protocol->ip_checksum);							// Check sum.
	header_length = ip_protocol->ip_header_length;						// IP Header length.
	tos = ip_protocol->ip_tos;											// IP tos.
	offset = ntohs(ip_protocol->ip_off);								// IP offset.

	printf("-------- IP Protocol --------\n");
	printf("IP version: %d\n", ip_protocol->ip_version);
	printf("Header length: %d\n", header_length);
	printf("IP tos: %d\n", tos);
	printf("Total length: %d\n", ntohs(ip_protocol->ip_length));
	printf("IP id: %d\n", ntohs(ip_protocol->ip_id));
	printf("IP offset: %d\n", (offset & 0x1fff) * 8);
	printf("IP TTL: %d\n", ip_protocol->ip_ttl);
	printf("Upper protocol: %d\n", ip_protocol->ip_protocol);
	switch (ip_protocol->ip_protocol)
	{
	case 1: printf("Upper protocol is ICMP protocol.\n");break;
	case 2: printf("Upper protocol is IGMP protocol.\n");break;
	case 6: printf("Upper protocol is TCP protocol.\n");break;
	case 17: printf("Upper protocol is UDP protocol.\n");break;
	default:break;
	}

	printf("Check sum: %d\n", checksum);
	printf("Source IP address: %s\n", inet_ntoa(ip_protocol->ip_souce_address));
	printf("Destination IP address: %s\n", inet_ntoa(ip_protocol->ip_destination_address));

	printf("-----------------------------\n");
}

// Time stamp to standard time.
void stamp_to_standard(int stampTime)
{
	time_t tick = (time_t)stampTime;
	struct tm TM;
	char standardTime[100];
	
	TM = *localtime(&tick);
	strftime(standardTime, sizeof(standardTime), "%Y-%m-%d %H:%M:%S", &TM);
	printf("%s\n", standardTime);

	return;
}