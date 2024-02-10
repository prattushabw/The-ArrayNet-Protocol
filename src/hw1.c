#include "hw1.h"
#include <stdio.h>
#include <stdlib.h> 

// void print_packet_sf(unsigned char packet[])
// {
//     (void)packet;
// }
void print_packet_sf(unsigned char packet[]) {
    unsigned int source_address = ((packet[0] & 0x7F) << 21) | (packet[1] << 13) | (packet[2] << 5) | (packet[3] >> 3);
    unsigned int dest_address = ((packet[3] & 0x07) << 25) | (packet[4] << 17) | (packet[5] << 9) | (packet[6] >> 7);
    unsigned int source_port = (packet[6] & 0x7F) << 1 | (packet[7] >> 7);
    unsigned int dest_port = packet[7] & 0x1F;
    unsigned int fragment_offset = ((packet[8] & 0x3F) << 8) | (packet[9] & 0xFF);
    unsigned int packet_length = ((packet[9] & 0x1F) << 9) | (packet[10] << 1) | (packet[11] >> 7);
    unsigned int max_hop_count = ((packet[11] & 0x7F) >> 2);
    unsigned int checksum = ((packet[11] & 0x03) << 21) | (packet[12] << 13) | (packet[13] << 5) | (packet[14] >> 3);
    unsigned int compression_scheme = ((packet[15] & 0xC0) >> 6);
    unsigned int traffic_class = packet[15] & 0x3F;
    
    printf("Source Address: %u\n", source_address);
    printf("Destination Address: %u\n", dest_address);
    printf("Source Port: %u\n", source_port);
    printf("Destination Port: %u\n", dest_port);
    printf("Fragment Offset: %u\n", fragment_offset);
    printf("Packet Length: %u\n", packet_length);
    printf("Maximum Hop Count: %u\n", max_hop_count);
    printf("Checksum: %u\n", checksum);
    printf("Compression Scheme: %u\n", compression_scheme);
    printf("Traffic Class: %u\n", traffic_class);
    
    // Payload
    printf("Payload: ");
    int payload_start = 16;
    while (payload_start < packet_length) {
        int payload_int = (packet[payload_start] << 24) | (packet[payload_start + 1] << 16) | (packet[payload_start + 2] << 8) | packet[payload_start + 3];
        printf("%d ", payload_int);
        payload_start += 4;
    }
    printf("\n");
}

unsigned int compute_checksum_sf(unsigned char packet[])
{
    (void)packet;
    return -1;
}

unsigned int reconstruct_array_sf(unsigned char *packets[], unsigned int packets_len, int *array, unsigned int array_len) {
    (void)packets;
    (void)packets_len;
    (void)array;
    (void)array_len;
    return -1;
}

unsigned int packetize_array_sf(int *array, unsigned int array_len, unsigned char *packets[], unsigned int packets_len,
                          unsigned int max_payload, unsigned int src_addr, unsigned int dest_addr,
                          unsigned int src_port, unsigned int dest_port, unsigned int maximum_hop_count,
                          unsigned int compression_scheme, unsigned int traffic_class)
{
    (void)array;
    (void)array_len;
    (void)packets;
    (void)packets_len;
    (void)max_payload;
    (void)src_addr;
    (void)dest_addr;
    (void)src_port;
    (void)dest_port;
    (void)maximum_hop_count;
    (void)compression_scheme;
    (void)traffic_class;
    return -1;
}
