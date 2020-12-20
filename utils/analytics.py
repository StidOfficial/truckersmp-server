#!/usr/bin/python3
import argparse
import os
import sys
import datetime
import time

from scapy.utils import RawPcapReader
from scapy.layers.l2 import Ether
from scapy.layers.inet import IP, UDP

def get_raknet_messages(payload):
    i = 0

    messages = []
    while(i < len(payload)):
        flags = payload[i]
        i = i + 1
        payload_len = int.from_bytes(payload[i:i+2], byteorder="big", signed=False)
        i = i + 2
        #message_number = int.from_bytes(payload[i:i+3], byteorder="little", signed=False)
        i = i + 3
        #ordering_index = int.from_bytes(payload[i:i+3], byteorder="little", signed=False)
        i = i + 3
        if flags == 0x60 or flags == 0x20: 
            #ordering_channel = payload[i]
            i = i + 1

        messages.append(payload[i:i+int(payload_len/8)])
        i = i + int(payload_len/8)

    return messages

def process_pcap(file_name):
    print('Opening {}...'.format(file_name))
    
    for (pkt_data, pkt_metadata,) in RawPcapReader(file_name):
        ether_pkt = Ether(pkt_data)
        if 'type' not in ether_pkt.fields:
            # LLC frames will have 'len' instead of 'type'.
            # We disregard those
            continue

        #if ether_pkt.type != 0x0800:
            # disregard non-IPv4 packets
            #continue

        ip_pkt = ether_pkt[IP]
        if ip_pkt.proto != 17:
            # Ignore non-UDP packet
            continue

        if (ip_pkt.flags == 'MF') or (ip_pkt.frag != 0):
            print('No support for fragmented IP packets')
            return False

        udp_pkt = ip_pkt[UDP]

        raknet_packet = bytes(udp_pkt.payload)
        raknet_packet_id = raknet_packet[0]

        if raknet_packet_id == 0x84:
            raknet_message = raknet_packet[4:]
            messages = get_raknet_messages(raknet_message)
            for message in messages:
                if len(message) < 2:
                    continue

                raknet_message_id = message[0]
                if raknet_message_id == 0x87:
                    raknet_message_payload = message[1:]

                    truckersmp_packet_id = raknet_message_payload[0]
                    truckersmp_packet_payload = raknet_message_payload[1:]
                    #if ip_pkt.src == "172.16.222.46" and truckersmp_packet_id == 0x8c:
                    #    continue

                    #if ip_pkt.src == "172.16.222.46" and truckersmp_packet_id != 0x9c:
                    #    continue

                    print(ip_pkt.src, "->", ip_pkt.dst, datetime.datetime.fromtimestamp(ip_pkt.time), hex(truckersmp_packet_id), truckersmp_packet_payload.hex())

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='PCAP reader')
    parser.add_argument('--pcap', metavar='<pcap file name>',
                        help='pcap file to parse', required=True)
    args = parser.parse_args()
    
    file_name = args.pcap
    if not os.path.isfile(file_name):
        print('"{}" does not exist'.format(file_name), file=sys.stderr)
        sys.exit(-1)

    process_pcap(file_name)
    sys.exit(0)