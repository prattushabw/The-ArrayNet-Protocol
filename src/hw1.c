#include "hw1.h"
#include <stdio.h>
#include <stdlib.h> 

void print_packet_sf(unsigned char packet[]) {
    unsigned int source_address = (packet[0] << 20) + (packet[1] << 12) + (packet[2] << 4) + (packet[3] >> 4);
    unsigned int dest_address = ((packet[3] & 0x0F) << 24) + (packet[4] << 16) + (packet[5] << 8) + packet[6];
    unsigned int source_port = packet[7] >> 4;
    unsigned int dest_port = packet[7] & 0x0F;
    unsigned int fragment_offset = (packet[8] << 6) + (packet[9] >> 2);
    unsigned int packet_length = ((packet[9] & 0x03) << 12) + (packet[10] << 4) + (packet[11] >> 4);
    unsigned int max_hop_count = ((packet[11]& 0x0F) << 1) + (packet[12] >> 7);
    unsigned int checksum = ((packet[12] & 0x7F) << 16) + (packet[13] << 8) + (packet[14]); 
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
    unsigned int payload_index = 16;
    while (payload_index < packet_length) {
        int payload_value = (packet[payload_index] << 24) + (packet[payload_index+1] << 16) +
        (packet[payload_index+2] << 8) + packet[payload_index+3];
        printf(" %d", payload_value);
        payload_index += 4;
    }
    printf("\n");
    
}

unsigned int compute_checksum_sf(unsigned char packet[])
{
    int divisor = (1 << 23) - 1;
    unsigned int source_address = (packet[0] << 20) | (packet[1] << 12) + (packet[2] << 4) + (packet[3] >> 4);
    unsigned int dest_address = ((packet[3] & 0x0F) << 24) + (packet[4] << 16) + (packet[5] << 8) + packet[6];
    unsigned int source_port = packet[7] >> 4;
    unsigned int dest_port = packet[7] & 0x0F;
    unsigned int fragment_offset = (packet[8] << 6) + (packet[9] >> 2);
    unsigned int packet_length = ((packet[9] & 0x03) << 12) + (packet[10] << 4) + (packet[11] >> 4);
    unsigned int max_hop_count = ((packet[11]& 0x0F) << 1) + (packet[12] >> 7);
    unsigned int compression_scheme = ((packet[15] & 0xC0) >> 6);
    unsigned int traffic_class = packet[15] & 0x3F;
    
    unsigned long sum=source_address +dest_address+source_port+dest_port +fragment_offset+packet_length+max_hop_count+compression_scheme+traffic_class; 
    
    // Payload
    unsigned int payload_index = 16;
    while (payload_index < packet_length) {
        int payload_value = (packet[payload_index] << 24) + (packet[payload_index+1] << 16) +
        (packet[payload_index+2] << 8) + packet[payload_index+3];
        sum+=abs(payload_value);
        payload_index += 4;
    }
    
    return sum%divisor;
}

unsigned int reconstruct_array_sf(unsigned char *packets[], unsigned int packets_len, int *array, unsigned int array_len) {
        unsigned int written_integers = 0;
    
        for (unsigned int i = 0; i < packets_len; i++) {
            unsigned char *packet = packets[i];
    
            // checksum of the packet
            unsigned int expected_checksum = compute_checksum_sf(packet);
    
            // Extract checksum from the packet
           
            unsigned int checksum = ((packet[12] & 0x7F) << 16) + (packet[13] << 8) + (packet[14]); 
    
            // If checksum matches, extract payload and write to array
            if (expected_checksum == checksum) {
                unsigned int fragment_offset = (packet[8] << 6) + (packet[9] >> 2);
                unsigned int payload_index = fragment_offset / 4; //sizeof(int) where to start replacing from
                unsigned int payload_start = 16; 
    
                // Extract packet lengths
                unsigned int packet_length = ((packet[9] & 0x03) << 12) + (packet[10] << 4) + (packet[11] >> 4);
    
                // Iterate over payload bytes and convert them to integers
                while (payload_start < packet_length && payload_index < array_len) {
                    // Convert 4 payload bytes to integer
                    int payload_value = (packet[payload_start] << 24) + (packet[payload_start+1] << 16) +
                    (packet[payload_start+2] << 8) + packet[payload_start+3];

                    // Write payload value to array at appropriate index
                    array[payload_index] = payload_value;
    
                    // Move to next payload block and array index
                    payload_start += 4;
                    payload_index+=1;
                    written_integers+=1;
                    
                }
               
            } 
            
        }
    
        return written_integers;
    }
    


// unsigned int packetize_array_sf(int *array, unsigned int array_len, unsigned char *packets[], unsigned int packets_len,
//                           unsigned int max_payload, unsigned int src_addr, unsigned int dest_addr,
//                           unsigned int src_port, unsigned int dest_port, unsigned int maximum_hop_count,
//                           unsigned int compression_scheme, unsigned int traffic_class)
// {

//     unsigned int num_packets = (array_len*4) / max_payload;
//     // (array_len+(max_payload/4)-1/(max_payload/4));
//     // (array_len*4) / max_payload;

//     if ((array_len*4) %max_payload!=0){
//         num_packets++;
//     }
//     if (num_packets > packets_len) {
//         num_packets = packets_len; // Adjust the number of packets if packets_len is not enough
//     }
//     unsigned int payload_start = 0;
//     unsigned int payload_end = max_payload/4;
//     unsigned int payload_end_final=0;
//     unsigned int  packet_size=0;

//     if (payload_end > array_len) {
//         payload_end_final = array_len%(max_payload/4); // Adjust payload_end if it exceeds array_len
//     }
//     for (unsigned int i = 0; i < num_packets; ++i) {
//         if ((i!=num_packets-1)||(payload_end_final==0)){
//             packet_size=16+payload_end*4;
//         }else{
//             packet_size=16+((array_len*4) % max_payload);
//         }

//         // Allocate memory for the packet
//         packets[i] = malloc(16+max_payload); // 36 bytes for the header and payload (max_payload <= 20 implies packet_length <= 36)

//         // Set header fields
//         packets[i][0] = (src_addr >> 20) & 0xFF;
//         packets[i][1] = (src_addr >> 12) & 0xFF;
//         packets[i][2] = (src_addr >> 4) & 0xFF;
//         packets[i][3] = ((src_addr & 0xF) << 4) | ((dest_addr >> 24) & 0xF);
//         packets[i][4] = (dest_addr >> 16) & 0xFF;
//         packets[i][5] = (dest_addr >> 8) & 0xFF;
//         packets[i][6] = dest_addr & 0xFF;
//         packets[i][7] = (src_port << 4) | (dest_port & 0xF);
//         packets[i][8] = (i * max_payload) >> 6; // Fragment Offset
        
//         packets[i][12] = ((maximum_hop_count & 0x01) << 7);
//         packets[i][15]=((compression_scheme & 0x03) << 6) | (traffic_class & 0x3F);
        
        
//         //filling payload WRONG
//         for (unsigned int j = payload_start; j < payload_end; ++j) {
//             packets[i][16 + (j - payload_start) * 4] = (array[(i*max_payload/4)+j-payload_start] >> 24) & 0xFF;
//             packets[i][17 + (j - payload_start) * 4] = (array[(i*max_payload/4)+j-payload_start] >> 16) & 0xFF;
//             packets[i][18 + (j - payload_start) * 4] = (array[(i*max_payload/4)+j-payload_start] >> 8) & 0xFF;
//             packets[i][19 + (j - payload_start) * 4] = array[(i*max_payload/4)+j-payload_start] & 0xFF; 
//         }
//         packets[i][9] = ((i * max_payload) & 0x3F) << 2 | (packet_size >> 12); //packet length
//         packets[i][10] = (packet_size& 0xFF)>>4 ; //packet length
//         packets[i][11] = (packet_size& 0xF) << 4 | ((maximum_hop_count & 0x1E) >> 1); //packet length 
        
//         // Calculate Checksum
//         unsigned int checksum = compute_checksum_sf(packets[i]);
//         packets[i][12] |= (checksum >> 16) & 0x7F;
//         packets[i][13] = (checksum >> 8) & 0xFF; // Wrong
//         packets[i][14] = checksum & 0xFF;
//     }

//     return num_packets;
// }
unsigned int packetize_array_sf(int *array, unsigned int array_len, unsigned char *packets[], unsigned int packets_len,
                          unsigned int max_payload, unsigned int src_addr, unsigned int dest_addr,
                          unsigned int src_port, unsigned int dest_port, unsigned int maximum_hop_count,
                          unsigned int compression_scheme, unsigned int traffic_class)
{

    unsigned int num_packets = (array_len*4) / max_payload;
    if ((array_len*4) % max_payload != 0){
        num_packets++;
    }
    if (num_packets > packets_len) {
        num_packets = packets_len; // Adjust the number of packets if packets_len is not enough
    }
    unsigned int payload_start = 0;
    unsigned int payload_end = max_payload/4;
    unsigned int payload_end_final = 0;
    unsigned int packet_size = 0;

    if (payload_end > array_len) {
        payload_end_final = array_len % (max_payload/4); // Adjust payload_end if it exceeds array_len
    }
    for (unsigned int i = 0; i < num_packets; ++i) {
        if ((i != num_packets-1) || (payload_end_final == 0)){
            packet_size = 16 + payload_end*4;
        } else {
            packet_size = 16 + ((array_len*4) % max_payload);
        }

        // Allocate memory for the packet
        packets[i] = malloc(packet_size); // Adjusted size based on packet_size

        // Set header fields
        packets[i][0] = (src_addr >> 20) & 0xFF;
        packets[i][1] = (src_addr >> 12) & 0xFF;
        packets[i][2] = (src_addr >> 4) & 0xFF;
        packets[i][3] = ((src_addr & 0xF) << 4) | ((dest_addr >> 24) & 0xF);
        packets[i][4] = (dest_addr >> 16) & 0xFF;
        packets[i][5] = (dest_addr >> 8) & 0xFF;
        packets[i][6] = dest_addr & 0xFF;
        packets[i][7] = (src_port << 4) | (dest_port & 0xF);
        packets[i][8] = (i * max_payload) >> 6; // Fragment Offset
        
        packets[i][12] = ((maximum_hop_count & 0x01) << 7);
        packets[i][15] = ((compression_scheme & 0x03) << 6) | (traffic_class & 0x3F);
        
        
        // Filling payload
        for (unsigned int j = payload_start; j < payload_end; ++j) {
            unsigned int array_index = (i * (max_payload/4)) + j;
            if (array_index < array_len) {
                unsigned int payload_index = (j - payload_start) * 4;
                packets[i][16 + payload_index] = (array[array_index] >> 24) & 0xFF;
                packets[i][17 + payload_index] = (array[array_index] >> 16) & 0xFF;
                packets[i][18 + payload_index] = (array[array_index] >> 8) & 0xFF;
                packets[i][19 + payload_index] = array[array_index] & 0xFF;
            }
        }
        
        packets[i][9] = ((i * max_payload) & 0x3F) << 2 | (packet_size >> 12); // Packet length
        packets[i][10] = (packet_size >> 4) & 0xFF;
        packets[i][11] = (packet_size & 0xF) << 4 | ((maximum_hop_count & 0x1E) >> 1); // Packet length 
        
        // Calculate Checksum
        unsigned int checksum = compute_checksum_sf(packets[i]);
        packets[i][12] |= (checksum >> 16) & 0x7F;
        packets[i][13] = (checksum >> 8) & 0xFF;
        packets[i][14] = checksum & 0xFF;
    }

    return num_packets;
}

