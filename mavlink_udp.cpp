/*******************************************************************************
 Copyright (C) 2010  Bryan Godbolt godbolt ( a t ) ualberta.ca
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ****************************************************************************/
/*
 This program sends some data to qgroundcontrol using the mavlink protocol.  The sent packets
 cause qgroundcontrol to respond with heartbeats.  Any settings or custom commands sent from
 qgroundcontrol are printed by this program along with the heartbeats.
 
 
 I compiled this program sucessfully on Ubuntu 10.04 with the following command
 
 gcc -I ../../pixhawk/mavlink/include -o udp-server udp-server-test.c
 
 the rt library is needed for the clock_gettime on linux
 */
/* These headers are for QNX, but should all be standard on unix/linux */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

/* This assumes you have the mavlink headers on your include path
 or in the same folder as this source file */
#include <mavlink.h>

#define BUFFER_LENGTH 2041 // minimum buffer size that can be used with qnx (I don't know why)

uint64_t microsSinceEpoch();

#if (defined __QNX__) | (defined __QNXNTO__)
/* QNX specific headers */
#include <unix.h>
#else
/* Linux / MacOS POSIX timer headers */
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdbool.h> /* required for the definition of bool in C99 */
#endif

class UdpDevice
{
private:
	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	struct sockaddr_in gcAddr;
	struct sockaddr_in locAddr;
	//struct sockaddr_in fromAddr;
	uint8_t send_buf[BUFFER_LENGTH];
	uint8_t recv_buf[BUFFER_LENGTH];

	socklen_t fromlen = sizeof(gcAddr);

public:
	UdpDevice(char *target_ip, int local_addr_port = 14551, int target_port = 14550)
	{
		memset(&locAddr, 0, sizeof(locAddr));
		locAddr.sin_family = AF_INET;
		locAddr.sin_addr.s_addr = INADDR_ANY;
		locAddr.sin_port = htons(local_addr_port);

		/* Bind the socket to port - necessary to receive packets from qgroundcontrol */
		if (-1 == bind(sock, (struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
		{
			perror("error bind failed");
			close(sock);
			exit(EXIT_FAILURE);
		}

		/* Attempt to make it non blocking */
#if (defined __QNX__) | (defined __QNXNTO__)
		if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
		if (fcntl(sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

		{
			fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
			close(sock);
			exit(EXIT_FAILURE);
		}

		memset(&gcAddr, 0, sizeof(gcAddr));
		gcAddr.sin_family = AF_INET;
		gcAddr.sin_addr.s_addr = inet_addr(target_ip);
		gcAddr.sin_port = htons(target_port);
	};

	void send_message(mavlink_message_t &msg)
	{
		uint16_t len = mavlink_msg_to_send_buffer(send_buf, &msg);
		auto bytes_sent = sendto(sock, send_buf, len, 0, (struct sockaddr *)&gcAddr, sizeof(struct sockaddr_in));
	}

	void receive_data()
	{
		memset(recv_buf, 0, BUFFER_LENGTH);
		ssize_t recsize = recvfrom(sock, (void *)recv_buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);
		if (recsize > 0)
		{
			// Something received - print out all bytes and parse packet
			mavlink_message_t msg;
			mavlink_status_t status;

			printf("Bytes Received: %d\nDatagram: ", (int)recsize);
			for (int i = 0; i < recsize; ++i)
			{
				uint8_t temp = recv_buf[i];
				printf("%02x ", (unsigned char)temp);
				if (mavlink_parse_char(MAVLINK_COMM_0, recv_buf[i], &msg, &status))
				{
					// Packet received
					printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
				}
			}
			printf("\n");
		}
		sleep(1); // Sleep one second
	}
};

int main(int argc, char *argv[])
{

	char help[] = "--help";

	float position[6] = {};

	char target_ip[100];

	// Check if --help flag was used
	if ((argc == 2) && (strcmp(argv[1], help) == 0))
	{
		printf("\n");
		printf("\tUsage:\n\n");
		printf("\t");
		printf("%s", argv[0]);
		printf(" <ip address of QGroundControl>\n");
		printf("\tDefault for localhost: udp-server 127.0.0.1\n\n");
		exit(EXIT_FAILURE);
	}

	// Change the target ip if parameter was given
	strcpy(target_ip, "127.0.0.1");
	if (argc == 2)
	{
		strcpy(target_ip, argv[1]);
	}

	UdpDevice udp_device(target_ip);

	for (;;)
	{
		mavlink_message_t msg;
		mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
		udp_device.send_message(msg);

		/* Send Status */
		mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
		udp_device.send_message(msg);

		/* Send Local Position */
		mavlink_msg_local_position_ned_pack(1, 200, &msg, microsSinceEpoch(), 0, 1, 2, 3, 4, 5);
		udp_device.send_message(msg);

		/* Send attitude */
		mavlink_msg_attitude_pack(1, 200, &msg, microsSinceEpoch(), 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
		udp_device.send_message(msg);
		
		udp_device.receive_data();
	}
}

/* QNX timer version */
#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t microsSinceEpoch()
{

	struct timespec time;

	uint64_t micros = 0;

	clock_gettime(CLOCK_REALTIME, &time);
	micros = (uint64_t)time.tv_sec * 1000000 + time.tv_nsec / 1000;

	return micros;
}
#else
uint64_t microsSinceEpoch()
{

	struct timeval tv;

	uint64_t micros = 0;

	gettimeofday(&tv, NULL);
	micros = ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

	return micros;
}
#endif
