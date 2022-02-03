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
 
 g++ -std=c++14 -pthread -I mavlink_c_library_v2/common -o mavlink_udp mavlink_udp_example.cpp && ./mavlink_udp 127.0.0.1

 the rt library is needed for the clock_gettime on linux
 */
/* These headers are for QNX, but should all be standard on unix/linux */
#include "include/udp_device.h"

#include <errno.h>
#include <string.h>
#include <time.h>
#include <thread>
#include <mavlink.h>

#include <sys/time.h>

std::thread read_thread;

void got_mavlink_msg_cb(const mavlink_message_t &msg)
{
	printf("Received packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
}

int main(int argc, char *argv[])
{
	char help[] = "--help";
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

	UdpDevice udp_device(target_ip, 14568);
	//UdpClient udp_device(14568);
	
	read_thread = std::thread([&udp_device]()
							  {
								  mavlink_message_t msg;
								  while (true)
								  {
									  if (udp_device.read_message(msg))
									  {
										  printf("Received packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
									  }
								  }
							  });

	for (;;)
	{
		mavlink_message_t msg;
		mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
		udp_device.write_message(msg);
		udp_device.write_message(msg);

		/* Send Status */
		mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
		udp_device.write_message(msg);

		/* Send Local Position */
		mavlink_msg_local_position_ned_pack(1, 200, &msg, microsSinceEpoch(), 0, 1, 2, 3, 4, 5);
		udp_device.write_message(msg);

		/* Send attitude */
		mavlink_msg_attitude_pack(1, 200, &msg, microsSinceEpoch(), 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
		udp_device.write_message(msg);
		
        printf("sending data\n");
		sleep(1);
	}
}

uint64_t microsSinceEpoch()
{
	struct timeval tv;

	uint64_t micros = 0;

	gettimeofday(&tv, NULL);
	micros = ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

	return micros;
}
