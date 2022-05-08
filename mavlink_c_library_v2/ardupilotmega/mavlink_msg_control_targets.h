#pragma once
// MESSAGE CONTROL_TARGETS PACKING

#define MAVLINK_MSG_ID_CONTROL_TARGETS 406


typedef struct __mavlink_control_targets_t {
 float current_vel_n; /*<  vel_n */
 float current_vel_e; /*<  vel_e */
 float current_vel_d; /*<  vel_d */
 float vel_n; /*<  vel_n */
 float vel_e; /*<  vel_e */
 float vel_d; /*<  vel_d */
 float acc_n; /*<  acc_n */
 float acc_e; /*<  acc_e */
 float acc_d; /*<  acc_d */
 float roll; /*<  roll in degrees*/
 float pitch; /*<  pitch in degrees*/
} mavlink_control_targets_t;

#define MAVLINK_MSG_ID_CONTROL_TARGETS_LEN 44
#define MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN 44
#define MAVLINK_MSG_ID_406_LEN 44
#define MAVLINK_MSG_ID_406_MIN_LEN 44

#define MAVLINK_MSG_ID_CONTROL_TARGETS_CRC 133
#define MAVLINK_MSG_ID_406_CRC 133



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CONTROL_TARGETS { \
    406, \
    "CONTROL_TARGETS", \
    11, \
    {  { "current_vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_control_targets_t, current_vel_n) }, \
         { "current_vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_control_targets_t, current_vel_e) }, \
         { "current_vel_d", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_control_targets_t, current_vel_d) }, \
         { "vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_control_targets_t, vel_n) }, \
         { "vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_control_targets_t, vel_e) }, \
         { "vel_d", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_control_targets_t, vel_d) }, \
         { "acc_n", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_control_targets_t, acc_n) }, \
         { "acc_e", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_control_targets_t, acc_e) }, \
         { "acc_d", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_control_targets_t, acc_d) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_control_targets_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_control_targets_t, pitch) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CONTROL_TARGETS { \
    "CONTROL_TARGETS", \
    11, \
    {  { "current_vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_control_targets_t, current_vel_n) }, \
         { "current_vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_control_targets_t, current_vel_e) }, \
         { "current_vel_d", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_control_targets_t, current_vel_d) }, \
         { "vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_control_targets_t, vel_n) }, \
         { "vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_control_targets_t, vel_e) }, \
         { "vel_d", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_control_targets_t, vel_d) }, \
         { "acc_n", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_control_targets_t, acc_n) }, \
         { "acc_e", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_control_targets_t, acc_e) }, \
         { "acc_d", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_control_targets_t, acc_d) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_control_targets_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_control_targets_t, pitch) }, \
         } \
}
#endif

/**
 * @brief Pack a control_targets message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param current_vel_n  vel_n 
 * @param current_vel_e  vel_e 
 * @param current_vel_d  vel_d 
 * @param vel_n  vel_n 
 * @param vel_e  vel_e 
 * @param vel_d  vel_d 
 * @param acc_n  acc_n 
 * @param acc_e  acc_e 
 * @param acc_d  acc_d 
 * @param roll  roll in degrees
 * @param pitch  pitch in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_targets_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float current_vel_n, float current_vel_e, float current_vel_d, float vel_n, float vel_e, float vel_d, float acc_n, float acc_e, float acc_d, float roll, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONTROL_TARGETS_LEN];
    _mav_put_float(buf, 0, current_vel_n);
    _mav_put_float(buf, 4, current_vel_e);
    _mav_put_float(buf, 8, current_vel_d);
    _mav_put_float(buf, 12, vel_n);
    _mav_put_float(buf, 16, vel_e);
    _mav_put_float(buf, 20, vel_d);
    _mav_put_float(buf, 24, acc_n);
    _mav_put_float(buf, 28, acc_e);
    _mav_put_float(buf, 32, acc_d);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN);
#else
    mavlink_control_targets_t packet;
    packet.current_vel_n = current_vel_n;
    packet.current_vel_e = current_vel_e;
    packet.current_vel_d = current_vel_d;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_d = vel_d;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.roll = roll;
    packet.pitch = pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONTROL_TARGETS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
}

/**
 * @brief Pack a control_targets message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param current_vel_n  vel_n 
 * @param current_vel_e  vel_e 
 * @param current_vel_d  vel_d 
 * @param vel_n  vel_n 
 * @param vel_e  vel_e 
 * @param vel_d  vel_d 
 * @param acc_n  acc_n 
 * @param acc_e  acc_e 
 * @param acc_d  acc_d 
 * @param roll  roll in degrees
 * @param pitch  pitch in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_targets_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float current_vel_n,float current_vel_e,float current_vel_d,float vel_n,float vel_e,float vel_d,float acc_n,float acc_e,float acc_d,float roll,float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONTROL_TARGETS_LEN];
    _mav_put_float(buf, 0, current_vel_n);
    _mav_put_float(buf, 4, current_vel_e);
    _mav_put_float(buf, 8, current_vel_d);
    _mav_put_float(buf, 12, vel_n);
    _mav_put_float(buf, 16, vel_e);
    _mav_put_float(buf, 20, vel_d);
    _mav_put_float(buf, 24, acc_n);
    _mav_put_float(buf, 28, acc_e);
    _mav_put_float(buf, 32, acc_d);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN);
#else
    mavlink_control_targets_t packet;
    packet.current_vel_n = current_vel_n;
    packet.current_vel_e = current_vel_e;
    packet.current_vel_d = current_vel_d;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_d = vel_d;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.roll = roll;
    packet.pitch = pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONTROL_TARGETS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
}

/**
 * @brief Encode a control_targets struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param control_targets C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_targets_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_control_targets_t* control_targets)
{
    return mavlink_msg_control_targets_pack(system_id, component_id, msg, control_targets->current_vel_n, control_targets->current_vel_e, control_targets->current_vel_d, control_targets->vel_n, control_targets->vel_e, control_targets->vel_d, control_targets->acc_n, control_targets->acc_e, control_targets->acc_d, control_targets->roll, control_targets->pitch);
}

/**
 * @brief Encode a control_targets struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param control_targets C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_targets_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_control_targets_t* control_targets)
{
    return mavlink_msg_control_targets_pack_chan(system_id, component_id, chan, msg, control_targets->current_vel_n, control_targets->current_vel_e, control_targets->current_vel_d, control_targets->vel_n, control_targets->vel_e, control_targets->vel_d, control_targets->acc_n, control_targets->acc_e, control_targets->acc_d, control_targets->roll, control_targets->pitch);
}

/**
 * @brief Send a control_targets message
 * @param chan MAVLink channel to send the message
 *
 * @param current_vel_n  vel_n 
 * @param current_vel_e  vel_e 
 * @param current_vel_d  vel_d 
 * @param vel_n  vel_n 
 * @param vel_e  vel_e 
 * @param vel_d  vel_d 
 * @param acc_n  acc_n 
 * @param acc_e  acc_e 
 * @param acc_d  acc_d 
 * @param roll  roll in degrees
 * @param pitch  pitch in degrees
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_control_targets_send(mavlink_channel_t chan, float current_vel_n, float current_vel_e, float current_vel_d, float vel_n, float vel_e, float vel_d, float acc_n, float acc_e, float acc_d, float roll, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONTROL_TARGETS_LEN];
    _mav_put_float(buf, 0, current_vel_n);
    _mav_put_float(buf, 4, current_vel_e);
    _mav_put_float(buf, 8, current_vel_d);
    _mav_put_float(buf, 12, vel_n);
    _mav_put_float(buf, 16, vel_e);
    _mav_put_float(buf, 20, vel_d);
    _mav_put_float(buf, 24, acc_n);
    _mav_put_float(buf, 28, acc_e);
    _mav_put_float(buf, 32, acc_d);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TARGETS, buf, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
#else
    mavlink_control_targets_t packet;
    packet.current_vel_n = current_vel_n;
    packet.current_vel_e = current_vel_e;
    packet.current_vel_d = current_vel_d;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_d = vel_d;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.roll = roll;
    packet.pitch = pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TARGETS, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
#endif
}

/**
 * @brief Send a control_targets message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_control_targets_send_struct(mavlink_channel_t chan, const mavlink_control_targets_t* control_targets)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_control_targets_send(chan, control_targets->current_vel_n, control_targets->current_vel_e, control_targets->current_vel_d, control_targets->vel_n, control_targets->vel_e, control_targets->vel_d, control_targets->acc_n, control_targets->acc_e, control_targets->acc_d, control_targets->roll, control_targets->pitch);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TARGETS, (const char *)control_targets, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
#endif
}

#if MAVLINK_MSG_ID_CONTROL_TARGETS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_control_targets_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float current_vel_n, float current_vel_e, float current_vel_d, float vel_n, float vel_e, float vel_d, float acc_n, float acc_e, float acc_d, float roll, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, current_vel_n);
    _mav_put_float(buf, 4, current_vel_e);
    _mav_put_float(buf, 8, current_vel_d);
    _mav_put_float(buf, 12, vel_n);
    _mav_put_float(buf, 16, vel_e);
    _mav_put_float(buf, 20, vel_d);
    _mav_put_float(buf, 24, acc_n);
    _mav_put_float(buf, 28, acc_e);
    _mav_put_float(buf, 32, acc_d);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TARGETS, buf, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
#else
    mavlink_control_targets_t *packet = (mavlink_control_targets_t *)msgbuf;
    packet->current_vel_n = current_vel_n;
    packet->current_vel_e = current_vel_e;
    packet->current_vel_d = current_vel_d;
    packet->vel_n = vel_n;
    packet->vel_e = vel_e;
    packet->vel_d = vel_d;
    packet->acc_n = acc_n;
    packet->acc_e = acc_e;
    packet->acc_d = acc_d;
    packet->roll = roll;
    packet->pitch = pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TARGETS, (const char *)packet, MAVLINK_MSG_ID_CONTROL_TARGETS_MIN_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN, MAVLINK_MSG_ID_CONTROL_TARGETS_CRC);
#endif
}
#endif

#endif

// MESSAGE CONTROL_TARGETS UNPACKING


/**
 * @brief Get field current_vel_n from control_targets message
 *
 * @return  vel_n 
 */
static inline float mavlink_msg_control_targets_get_current_vel_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field current_vel_e from control_targets message
 *
 * @return  vel_e 
 */
static inline float mavlink_msg_control_targets_get_current_vel_e(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field current_vel_d from control_targets message
 *
 * @return  vel_d 
 */
static inline float mavlink_msg_control_targets_get_current_vel_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field vel_n from control_targets message
 *
 * @return  vel_n 
 */
static inline float mavlink_msg_control_targets_get_vel_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field vel_e from control_targets message
 *
 * @return  vel_e 
 */
static inline float mavlink_msg_control_targets_get_vel_e(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vel_d from control_targets message
 *
 * @return  vel_d 
 */
static inline float mavlink_msg_control_targets_get_vel_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field acc_n from control_targets message
 *
 * @return  acc_n 
 */
static inline float mavlink_msg_control_targets_get_acc_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field acc_e from control_targets message
 *
 * @return  acc_e 
 */
static inline float mavlink_msg_control_targets_get_acc_e(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field acc_d from control_targets message
 *
 * @return  acc_d 
 */
static inline float mavlink_msg_control_targets_get_acc_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field roll from control_targets message
 *
 * @return  roll in degrees
 */
static inline float mavlink_msg_control_targets_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field pitch from control_targets message
 *
 * @return  pitch in degrees
 */
static inline float mavlink_msg_control_targets_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Decode a control_targets message into a struct
 *
 * @param msg The message to decode
 * @param control_targets C-struct to decode the message contents into
 */
static inline void mavlink_msg_control_targets_decode(const mavlink_message_t* msg, mavlink_control_targets_t* control_targets)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    control_targets->current_vel_n = mavlink_msg_control_targets_get_current_vel_n(msg);
    control_targets->current_vel_e = mavlink_msg_control_targets_get_current_vel_e(msg);
    control_targets->current_vel_d = mavlink_msg_control_targets_get_current_vel_d(msg);
    control_targets->vel_n = mavlink_msg_control_targets_get_vel_n(msg);
    control_targets->vel_e = mavlink_msg_control_targets_get_vel_e(msg);
    control_targets->vel_d = mavlink_msg_control_targets_get_vel_d(msg);
    control_targets->acc_n = mavlink_msg_control_targets_get_acc_n(msg);
    control_targets->acc_e = mavlink_msg_control_targets_get_acc_e(msg);
    control_targets->acc_d = mavlink_msg_control_targets_get_acc_d(msg);
    control_targets->roll = mavlink_msg_control_targets_get_roll(msg);
    control_targets->pitch = mavlink_msg_control_targets_get_pitch(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CONTROL_TARGETS_LEN? msg->len : MAVLINK_MSG_ID_CONTROL_TARGETS_LEN;
        memset(control_targets, 0, MAVLINK_MSG_ID_CONTROL_TARGETS_LEN);
    memcpy(control_targets, _MAV_PAYLOAD(msg), len);
#endif
}
