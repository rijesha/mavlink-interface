#pragma once
/* This assumes you have the mavlink headers on your include path
 or in the same folder as this source file */
#include <mavlink.h>

#define BUFFER_LENGTH \
  2041  // minimum buffer size that can be used with qnx (I don't know why)

uint64_t microsSinceEpoch();

/* Linux / MacOS POSIX timer headers */
#include <arpa/inet.h>
#include <stdbool.h> /* required for the definition of bool in C99 */
#include <functional>

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class UdpDevice {
 private:
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in gcAddr;
  struct sockaddr_in locAddr;
  // struct sockaddr_in fromAddr;
  uint8_t send_buf[BUFFER_LENGTH];
  uint8_t recv_buf[BUFFER_LENGTH];

  socklen_t fromlen = sizeof(gcAddr);

 public:
  UdpDevice(const char *target_ip, int local_addr_port = 14551,
            int target_port = 14550) {
    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(local_addr_port);

    /* Bind the socket to port - necessary to receive packets from
     * qgroundcontrol */
    if (-1 ==
        bind(sock, (struct sockaddr *)&locAddr, sizeof(struct sockaddr))) {
      perror("error bind failed");
      close(sock);
      exit(EXIT_FAILURE);
    }

    // memset(&gcAddr, 0, sizeof(gcAddr));
    // gcAddr.sin_family = AF_INET;
    // gcAddr.sin_addr.s_addr = inet_addr(target_ip);
    // gcAddr.sin_port = htons(target_port);
  };

  void write_message(const mavlink_message_t &msg) {
    uint16_t len = mavlink_msg_to_send_buffer(send_buf, &msg);
    auto bytes_sent =
        sendto(sock, send_buf, len, 0, (struct sockaddr *)&locAddr,
               sizeof(struct sockaddr_in));
    (void)bytes_sent;
  }

  bool read_message(mavlink_message_t &msg) {
    memset(recv_buf, 0, BUFFER_LENGTH);
    ssize_t recsize = recvfrom(sock, (void *)recv_buf, BUFFER_LENGTH, 0,
                               (struct sockaddr *)&locAddr, &fromlen);
    if (recsize > 0) {
      mavlink_status_t status;
      for (int i = 0; i < recsize; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, recv_buf[i], &msg, &status)) {
          return true;
        }
      }
    }
    return false;
  }
};

class UdpClient {
 private:
  int sockfd;
  uint8_t send_buffer[1024];
  uint8_t recv_buffer[1024];
  struct sockaddr_in servaddr;
  socklen_t fromlen = sizeof(sockaddr_in);

 public:
  UdpClient(int port = 14560) {
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;
  };

  void shutdown() { close(sockfd); }

  void write_message(const mavlink_message_t &msg) {
    uint16_t len = mavlink_msg_to_send_buffer(send_buffer, &msg);

    auto bytes_sent =
        sendto(sockfd, send_buffer, len, 0, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));
    (void)bytes_sent;
  }

  bool read_message(mavlink_message_t &msg) {
    memset(recv_buffer, 0, BUFFER_LENGTH);
    ssize_t recsize = recvfrom(sockfd, recv_buffer, 1024, 0,
                               (struct sockaddr *)&servaddr, &fromlen);
    if (recsize > 0) {
      mavlink_status_t status;
      for (int i = 0; i < recsize; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, recv_buffer[i], &msg, &status)) {
          return true;
        }
      }
    }
    return false;
  }
};
