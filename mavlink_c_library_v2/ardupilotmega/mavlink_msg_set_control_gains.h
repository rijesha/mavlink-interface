#pragma once
// MESSAGE SET_CONTROL_GAINS PACKING

#define MAVLINK_MSG_ID_SET_CONTROL_GAINS 402


typedef struct __mavlink_set_control_gains_t {
 float pos_pgain; /*<  pos_pgain*/
 float pos_pgain_z; /*<  pos_pgain_z*/
 float vel_pgain; /*<  vel_pgain*/
 float vel_igain; /*<  vel_igain*/
 float vel_pgain_z; /*<  vel_pgain_z*/
 float vel_igain_z; /*<  vel_igain_z*/
 float yaw_pgain; /*<  yaw_pgain*/
} mavlink_set_control_gains_t;

#define MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN 28
#define MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN 28
#define MAVLINK_MSG_ID_402_LEN 28
#define MAVLINK_MSG_ID_402_MIN_LEN 28

#define MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC 250
#define MAVLINK_MSG_ID_402_CRC 250



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_CONTROL_GAINS { \
    402, \
    "SET_CONTROL_GAINS", \
    7, \
    {  { "pos_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_control_gains_t, pos_pgain) }, \
         { "pos_pgain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_control_gains_t, pos_pgain_z) }, \
         { "vel_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_control_gains_t, vel_pgain) }, \
         { "vel_igain", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_set_control_gains_t, vel_igain) }, \
         { "vel_pgain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_set_control_gains_t, vel_pgain_z) }, \
         { "vel_igain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_set_control_gains_t, vel_igain_z) }, \
         { "yaw_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_set_control_gains_t, yaw_pgain) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_CONTROL_GAINS { \
    "SET_CONTROL_GAINS", \
    7, \
    {  { "pos_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_control_gains_t, pos_pgain) }, \
         { "pos_pgain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_control_gains_t, pos_pgain_z) }, \
         { "vel_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_control_gains_t, vel_pgain) }, \
         { "vel_igain", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_set_control_gains_t, vel_igain) }, \
         { "vel_pgain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_set_control_gains_t, vel_pgain_z) }, \
         { "vel_igain_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_set_control_gains_t, vel_igain_z) }, \
         { "yaw_pgain", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_set_control_gains_t, yaw_pgain) }, \
         } \
}
#endif

/**
 * @brief Pack a set_control_gains message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_pgain  pos_pgain
 * @param pos_pgain_z  pos_pgain_z
 * @param vel_pgain  vel_pgain
 * @param vel_igain  vel_igain
 * @param vel_pgain_z  vel_pgain_z
 * @param vel_igain_z  vel_igain_z
 * @param yaw_pgain  yaw_pgain
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_control_gains_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float pos_pgain, float pos_pgain_z, float vel_pgain, float vel_igain, float vel_pgain_z, float vel_igain_z, float yaw_pgain)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN];
    _mav_put_float(buf, 0, pos_pgain);
    _mav_put_float(buf, 4, pos_pgain_z);
    _mav_put_float(buf, 8, vel_pgain);
    _mav_put_float(buf, 12, vel_igain);
    _mav_put_float(buf, 16, vel_pgain_z);
    _mav_put_float(buf, 20, vel_igain_z);
    _mav_put_float(buf, 24, yaw_pgain);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN);
#else
    mavlink_set_control_gains_t packet;
    packet.pos_pgain = pos_pgain;
    packet.pos_pgain_z = pos_pgain_z;
    packet.vel_pgain = vel_pgain;
    packet.vel_igain = vel_igain;
    packet.vel_pgain_z = vel_pgain_z;
    packet.vel_igain_z = vel_igain_z;
    packet.yaw_pgain = yaw_pgain;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_CONTROL_GAINS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
}

/**
 * @brief Pack a set_control_gains message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_pgain  pos_pgain
 * @param pos_pgain_z  pos_pgain_z
 * @param vel_pgain  vel_pgain
 * @param vel_igain  vel_igain
 * @param vel_pgain_z  vel_pgain_z
 * @param vel_igain_z  vel_igain_z
 * @param yaw_pgain  yaw_pgain
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_control_gains_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float pos_pgain,float pos_pgain_z,float vel_pgain,float vel_igain,float vel_pgain_z,float vel_igain_z,float yaw_pgain)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN];
    _mav_put_float(buf, 0, pos_pgain);
    _mav_put_float(buf, 4, pos_pgain_z);
    _mav_put_float(buf, 8, vel_pgain);
    _mav_put_float(buf, 12, vel_igain);
    _mav_put_float(buf, 16, vel_pgain_z);
    _mav_put_float(buf, 20, vel_igain_z);
    _mav_put_float(buf, 24, yaw_pgain);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN);
#else
    mavlink_set_control_gains_t packet;
    packet.pos_pgain = pos_pgain;
    packet.pos_pgain_z = pos_pgain_z;
    packet.vel_pgain = vel_pgain;
    packet.vel_igain = vel_igain;
    packet.vel_pgain_z = vel_pgain_z;
    packet.vel_igain_z = vel_igain_z;
    packet.yaw_pgain = yaw_pgain;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_CONTROL_GAINS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
}

/**
 * @brief Encode a set_control_gains struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_control_gains C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_control_gains_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_control_gains_t* set_control_gains)
{
    return mavlink_msg_set_control_gains_pack(system_id, component_id, msg, set_control_gains->pos_pgain, set_control_gains->pos_pgain_z, set_control_gains->vel_pgain, set_control_gains->vel_igain, set_control_gains->vel_pgain_z, set_control_gains->vel_igain_z, set_control_gains->yaw_pgain);
}

/**
 * @brief Encode a set_control_gains struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_control_gains C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_control_gains_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_control_gains_t* set_control_gains)
{
    return mavlink_msg_set_control_gains_pack_chan(system_id, component_id, chan, msg, set_control_gains->pos_pgain, set_control_gains->pos_pgain_z, set_control_gains->vel_pgain, set_control_gains->vel_igain, set_control_gains->vel_pgain_z, set_control_gains->vel_igain_z, set_control_gains->yaw_pgain);
}

/**
 * @brief Send a set_control_gains message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_pgain  pos_pgain
 * @param pos_pgain_z  pos_pgain_z
 * @param vel_pgain  vel_pgain
 * @param vel_igain  vel_igain
 * @param vel_pgain_z  vel_pgain_z
 * @param vel_igain_z  vel_igain_z
 * @param yaw_pgain  yaw_pgain
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_control_gains_send(mavlink_channel_t chan, float pos_pgain, float pos_pgain_z, float vel_pgain, float vel_igain, float vel_pgain_z, float vel_igain_z, float yaw_pgain)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN];
    _mav_put_float(buf, 0, pos_pgain);
    _mav_put_float(buf, 4, pos_pgain_z);
    _mav_put_float(buf, 8, vel_pgain);
    _mav_put_float(buf, 12, vel_igain);
    _mav_put_float(buf, 16, vel_pgain_z);
    _mav_put_float(buf, 20, vel_igain_z);
    _mav_put_float(buf, 24, yaw_pgain);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS, buf, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
#else
    mavlink_set_control_gains_t packet;
    packet.pos_pgain = pos_pgain;
    packet.pos_pgain_z = pos_pgain_z;
    packet.vel_pgain = vel_pgain;
    packet.vel_igain = vel_igain;
    packet.vel_pgain_z = vel_pgain_z;
    packet.vel_igain_z = vel_igain_z;
    packet.yaw_pgain = yaw_pgain;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS, (const char *)&packet, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
#endif
}

/**
 * @brief Send a set_control_gains message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_control_gains_send_struct(mavlink_channel_t chan, const mavlink_set_control_gains_t* set_control_gains)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_control_gains_send(chan, set_control_gains->pos_pgain, set_control_gains->pos_pgain_z, set_control_gains->vel_pgain, set_control_gains->vel_igain, set_control_gains->vel_pgain_z, set_control_gains->vel_igain_z, set_control_gains->yaw_pgain);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS, (const char *)set_control_gains, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_control_gains_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float pos_pgain, float pos_pgain_z, float vel_pgain, float vel_igain, float vel_pgain_z, float vel_igain_z, float yaw_pgain)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, pos_pgain);
    _mav_put_float(buf, 4, pos_pgain_z);
    _mav_put_float(buf, 8, vel_pgain);
    _mav_put_float(buf, 12, vel_igain);
    _mav_put_float(buf, 16, vel_pgain_z);
    _mav_put_float(buf, 20, vel_igain_z);
    _mav_put_float(buf, 24, yaw_pgain);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS, buf, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
#else
    mavlink_set_control_gains_t *packet = (mavlink_set_control_gains_t *)msgbuf;
    packet->pos_pgain = pos_pgain;
    packet->pos_pgain_z = pos_pgain_z;
    packet->vel_pgain = vel_pgain;
    packet->vel_igain = vel_igain;
    packet->vel_pgain_z = vel_pgain_z;
    packet->vel_igain_z = vel_igain_z;
    packet->yaw_pgain = yaw_pgain;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_CONTROL_GAINS, (const char *)packet, MAVLINK_MSG_ID_SET_CONTROL_GAINS_MIN_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN, MAVLINK_MSG_ID_SET_CONTROL_GAINS_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_CONTROL_GAINS UNPACKING


/**
 * @brief Get field pos_pgain from set_control_gains message
 *
 * @return  pos_pgain
 */
static inline float mavlink_msg_set_control_gains_get_pos_pgain(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pos_pgain_z from set_control_gains message
 *
 * @return  pos_pgain_z
 */
static inline float mavlink_msg_set_control_gains_get_pos_pgain_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field vel_pgain from set_control_gains message
 *
 * @return  vel_pgain
 */
static inline float mavlink_msg_set_control_gains_get_vel_pgain(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field vel_igain from set_control_gains message
 *
 * @return  vel_igain
 */
static inline float mavlink_msg_set_control_gains_get_vel_igain(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field vel_pgain_z from set_control_gains message
 *
 * @return  vel_pgain_z
 */
static inline float mavlink_msg_set_control_gains_get_vel_pgain_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vel_igain_z from set_control_gains message
 *
 * @return  vel_igain_z
 */
static inline float mavlink_msg_set_control_gains_get_vel_igain_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field yaw_pgain from set_control_gains message
 *
 * @return  yaw_pgain
 */
static inline float mavlink_msg_set_control_gains_get_yaw_pgain(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Decode a set_control_gains message into a struct
 *
 * @param msg The message to decode
 * @param set_control_gains C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_control_gains_decode(const mavlink_message_t* msg, mavlink_set_control_gains_t* set_control_gains)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_control_gains->pos_pgain = mavlink_msg_set_control_gains_get_pos_pgain(msg);
    set_control_gains->pos_pgain_z = mavlink_msg_set_control_gains_get_pos_pgain_z(msg);
    set_control_gains->vel_pgain = mavlink_msg_set_control_gains_get_vel_pgain(msg);
    set_control_gains->vel_igain = mavlink_msg_set_control_gains_get_vel_igain(msg);
    set_control_gains->vel_pgain_z = mavlink_msg_set_control_gains_get_vel_pgain_z(msg);
    set_control_gains->vel_igain_z = mavlink_msg_set_control_gains_get_vel_igain_z(msg);
    set_control_gains->yaw_pgain = mavlink_msg_set_control_gains_get_yaw_pgain(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN? msg->len : MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN;
        memset(set_control_gains, 0, MAVLINK_MSG_ID_SET_CONTROL_GAINS_LEN);
    memcpy(set_control_gains, _MAV_PAYLOAD(msg), len);
#endif
}
