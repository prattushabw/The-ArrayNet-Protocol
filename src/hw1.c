#include "hw1.h"
#include <stdio.h>
#include <stdlib.h> 

// void print_packet_sf(unsigned char packet[])
// {
//     (void)packet;
// }
void print_packet_sf(unsigned char packet[]) {
    unsigned int source_address = (packet[0] << 20) + (packet[1] << 12) + (packet[2] << 4) + (packet[3] >> 4);
    unsigned int dest_address = ((packet[3] & 0x0F) << 24) + (packet[4] << 16) + (packet[5] << 8) + packet[6];
    unsigned int source_port = packet[7] >> 4;
    unsigned int dest_port = packet[7] & 0x1F;
    unsigned int fragment_offset = (packet[8] << 8) + packet[9];
    unsigned int packet_length = ((packet[9] & 0x03) << 12)+ (packet[10] << 4) + (packet[11] >> 4);
    unsigned int max_hop_count = ((packet[11]& 0x0F) << 1)+(packet[12] >> 7);
    unsigned int checksum = (packet[12] & 0x7F) << 16;
    checksum += (packet[13] << 8) + (packet[14]); 
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
    printf("Payload:");
    int payload_index = 16;
    while (payload_index < packet_length) {
        int payload_value = (packet[payload_index] << 24) + (packet[payload_index+1] << 16) +
        (packet[payload_index+2] << 8) + packet[payload_index+3];
        printf(" %d", payload_value);
        payload_index += 4;
    }
}

unsigned int compute_checksum_sf(unsigned char packet[])
{
    int divisor = (1 << 23) - 1;
    unsigned int source_address = (packet[0] << 20) + (packet[1] << 12) + (packet[2] << 4) + (packet[3] >> 4);
    unsigned int dest_address = ((packet[3] & 0x0F) << 24) + (packet[4] << 16) + (packet[5] << 8) + packet[6];
    unsigned int source_port = packet[7] >> 4;
    unsigned int dest_port = packet[7] & 0x1F;
    unsigned int fragment_offset = (packet[8] << 8) + packet[9];
    unsigned int packet_length = ((packet[9] & 0x03) << 12)+ (packet[10] << 4) + (packet[11] >> 4);
    unsigned int max_hop_count = ((packet[11]& 0x0F) << 1)+(packet[12] >> 7);
    
    unsigned int compression_scheme = ((packet[15] & 0xC0) >> 6);
    unsigned int traffic_class = packet[15] & 0x3F;
    
    unsigned long sum=source_address +dest_address+source_port+dest_port +fragment_offset+packet_length+max_hop_count+traffic_class; 
    
    // Payload
 
    int payload_index = 16;
    while (payload_index < packet_length) {
        int payload_value = (packet[payload_index] << 24) + (packet[payload_index+1] << 16) +
        (packet[payload_index+2] << 8) + packet[payload_index+3];
        sum+=abs(payload_value);
        payload_index += 4;
    }
    
    return sum%divisor;
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
