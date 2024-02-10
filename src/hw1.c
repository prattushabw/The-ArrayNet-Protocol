#include "hw1.h"

// void print_packet_sf(unsigned char packet[])
// {
//     (void)packet;
// }
void print_packet_sf(unsigned char packet[]) {
    unsigned int source_address = (packet[0] << 24) | (packet[1] << 16) | (packet[2] << 8) | packet[3];
    unsigned int dest_address = (packet[4] << 24) | (packet[5] << 16) | (packet[6] << 8) | packet[7];
    unsigned int source_port = (packet[8] >> 4) & 0x0F;
    unsigned int dest_port = packet[8] & 0x0F;
    unsigned int fragment_offset = (packet[9] << 8) | packet[10];
    unsigned int packet_length = (packet[11] << 8) | packet[12];
    unsigned int max_hop_count = (packet[13] >> 3) & 0x1F;
    unsigned int checksum = (packet[13] & 0x07) << 16 | (packet[14] << 8) | packet[15];
    unsigned int compression_scheme = (packet[13] >> 1) & 0x03;
    unsigned int traffic_class = ((packet[14] & 0x80) >> 2) | ((packet[14] & 0x7E) >> 1) | (packet[14] & 0x01);
    
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
    for (int i = 16; i < packet_length; i += 4) {
        int payload_int = (packet[i] << 24) | (packet[i + 1] << 16) | (packet[i + 2] << 8) | packet[i + 3];
        printf("%d ", payload_int);
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
