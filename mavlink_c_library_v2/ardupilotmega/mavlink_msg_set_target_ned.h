#pragma once
// MESSAGE SET_TARGET_NED PACKING

#define MAVLINK_MSG_ID_SET_TARGET_NED 405


typedef struct __mavlink_set_target_ned_t {
 float desired_north; /*<  desired_north */
 float desired_east; /*<  desired_east */
 float desired_down; /*<  desired_down */
 float desired_angle_in_frame; /*<  desired_angle_in_frame in degrees*/
} mavlink_set_target_ned_t;

#define MAVLINK_MSG_ID_SET_TARGET_NED_LEN 16
#define MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN 16
#define MAVLINK_MSG_ID_405_LEN 16
#define MAVLINK_MSG_ID_405_MIN_LEN 16

#define MAVLINK_MSG_ID_SET_TARGET_NED_CRC 255
#define MAVLINK_MSG_ID_405_CRC 255



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_TARGET_NED { \
    405, \
    "SET_TARGET_NED", \
    4, \
    {  { "desired_north", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_target_ned_t, desired_north) }, \
         { "desired_east", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_target_ned_t, desired_east) }, \
         { "desired_down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_target_ned_t, desired_down) }, \
         { "desired_angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_set_target_ned_t, desired_angle_in_frame) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_TARGET_NED { \
    "SET_TARGET_NED", \
    4, \
    {  { "desired_north", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_target_ned_t, desired_north) }, \
         { "desired_east", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_target_ned_t, desired_east) }, \
         { "desired_down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_set_target_ned_t, desired_down) }, \
         { "desired_angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_set_target_ned_t, desired_angle_in_frame) }, \
         } \
}
#endif

/**
 * @brief Pack a set_target_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_target_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_TARGET_NED_LEN];
    _mav_put_float(buf, 0, desired_north);
    _mav_put_float(buf, 4, desired_east);
    _mav_put_float(buf, 8, desired_down);
    _mav_put_float(buf, 12, desired_angle_in_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_TARGET_NED_LEN);
#else
    mavlink_set_target_ned_t packet;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_TARGET_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_TARGET_NED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
}

/**
 * @brief Pack a set_target_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_target_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float desired_north,float desired_east,float desired_down,float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_TARGET_NED_LEN];
    _mav_put_float(buf, 0, desired_north);
    _mav_put_float(buf, 4, desired_east);
    _mav_put_float(buf, 8, desired_down);
    _mav_put_float(buf, 12, desired_angle_in_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_TARGET_NED_LEN);
#else
    mavlink_set_target_ned_t packet;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_TARGET_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_TARGET_NED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
}

/**
 * @brief Encode a set_target_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_target_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_target_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_target_ned_t* set_target_ned)
{
    return mavlink_msg_set_target_ned_pack(system_id, component_id, msg, set_target_ned->desired_north, set_target_ned->desired_east, set_target_ned->desired_down, set_target_ned->desired_angle_in_frame);
}

/**
 * @brief Encode a set_target_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_target_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_target_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_target_ned_t* set_target_ned)
{
    return mavlink_msg_set_target_ned_pack_chan(system_id, component_id, chan, msg, set_target_ned->desired_north, set_target_ned->desired_east, set_target_ned->desired_down, set_target_ned->desired_angle_in_frame);
}

/**
 * @brief Send a set_target_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_target_ned_send(mavlink_channel_t chan, float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_TARGET_NED_LEN];
    _mav_put_float(buf, 0, desired_north);
    _mav_put_float(buf, 4, desired_east);
    _mav_put_float(buf, 8, desired_down);
    _mav_put_float(buf, 12, desired_angle_in_frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_TARGET_NED, buf, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
#else
    mavlink_set_target_ned_t packet;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_TARGET_NED, (const char *)&packet, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
#endif
}

/**
 * @brief Send a set_target_ned message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_target_ned_send_struct(mavlink_channel_t chan, const mavlink_set_target_ned_t* set_target_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_target_ned_send(chan, set_target_ned->desired_north, set_target_ned->desired_east, set_target_ned->desired_down, set_target_ned->desired_angle_in_frame);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_TARGET_NED, (const char *)set_target_ned, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_TARGET_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_target_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, desired_north);
    _mav_put_float(buf, 4, desired_east);
    _mav_put_float(buf, 8, desired_down);
    _mav_put_float(buf, 12, desired_angle_in_frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_TARGET_NED, buf, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
#else
    mavlink_set_target_ned_t *packet = (mavlink_set_target_ned_t *)msgbuf;
    packet->desired_north = desired_north;
    packet->desired_east = desired_east;
    packet->desired_down = desired_down;
    packet->desired_angle_in_frame = desired_angle_in_frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_TARGET_NED, (const char *)packet, MAVLINK_MSG_ID_SET_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_LEN, MAVLINK_MSG_ID_SET_TARGET_NED_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_TARGET_NED UNPACKING


/**
 * @brief Get field desired_north from set_target_ned message
 *
 * @return  desired_north 
 */
static inline float mavlink_msg_set_target_ned_get_desired_north(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field desired_east from set_target_ned message
 *
 * @return  desired_east 
 */
static inline float mavlink_msg_set_target_ned_get_desired_east(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field desired_down from set_target_ned message
 *
 * @return  desired_down 
 */
static inline float mavlink_msg_set_target_ned_get_desired_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field desired_angle_in_frame from set_target_ned message
 *
 * @return  desired_angle_in_frame in degrees
 */
static inline float mavlink_msg_set_target_ned_get_desired_angle_in_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a set_target_ned message into a struct
 *
 * @param msg The message to decode
 * @param set_target_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_target_ned_decode(const mavlink_message_t* msg, mavlink_set_target_ned_t* set_target_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_target_ned->desired_north = mavlink_msg_set_target_ned_get_desired_north(msg);
    set_target_ned->desired_east = mavlink_msg_set_target_ned_get_desired_east(msg);
    set_target_ned->desired_down = mavlink_msg_set_target_ned_get_desired_down(msg);
    set_target_ned->desired_angle_in_frame = mavlink_msg_set_target_ned_get_desired_angle_in_frame(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_TARGET_NED_LEN? msg->len : MAVLINK_MSG_ID_SET_TARGET_NED_LEN;
        memset(set_target_ned, 0, MAVLINK_MSG_ID_SET_TARGET_NED_LEN);
    memcpy(set_target_ned, _MAV_PAYLOAD(msg), len);
#endif
}
