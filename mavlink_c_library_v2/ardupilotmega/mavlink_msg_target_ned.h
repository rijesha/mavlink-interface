#pragma once
// MESSAGE TARGET_NED PACKING

#define MAVLINK_MSG_ID_TARGET_NED 404


typedef struct __mavlink_target_ned_t {
 float north; /*<  north */
 float east; /*<  east */
 float down; /*<  down */
 float yaw; /*<  yaw in degrees*/
 float angle_in_frame; /*<  angle_in_frame in degrees*/
 float desired_north; /*<  desired_north */
 float desired_east; /*<  desired_east */
 float desired_down; /*<  desired_down */
 float desired_angle_in_frame; /*<  desired_angle_in_frame in degrees*/
} mavlink_target_ned_t;

#define MAVLINK_MSG_ID_TARGET_NED_LEN 36
#define MAVLINK_MSG_ID_TARGET_NED_MIN_LEN 36
#define MAVLINK_MSG_ID_404_LEN 36
#define MAVLINK_MSG_ID_404_MIN_LEN 36

#define MAVLINK_MSG_ID_TARGET_NED_CRC 52
#define MAVLINK_MSG_ID_404_CRC 52



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_NED { \
    404, \
    "TARGET_NED", \
    9, \
    {  { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_target_ned_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_target_ned_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_target_ned_t, down) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_target_ned_t, yaw) }, \
         { "angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_target_ned_t, angle_in_frame) }, \
         { "desired_north", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_target_ned_t, desired_north) }, \
         { "desired_east", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_ned_t, desired_east) }, \
         { "desired_down", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_ned_t, desired_down) }, \
         { "desired_angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_ned_t, desired_angle_in_frame) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_NED { \
    "TARGET_NED", \
    9, \
    {  { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_target_ned_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_target_ned_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_target_ned_t, down) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_target_ned_t, yaw) }, \
         { "angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_target_ned_t, angle_in_frame) }, \
         { "desired_north", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_target_ned_t, desired_north) }, \
         { "desired_east", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_ned_t, desired_east) }, \
         { "desired_down", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_ned_t, desired_down) }, \
         { "desired_angle_in_frame", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_ned_t, desired_angle_in_frame) }, \
         } \
}
#endif

/**
 * @brief Pack a target_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param north  north 
 * @param east  east 
 * @param down  down 
 * @param yaw  yaw in degrees
 * @param angle_in_frame  angle_in_frame in degrees
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float north, float east, float down, float yaw, float angle_in_frame, float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_NED_LEN];
    _mav_put_float(buf, 0, north);
    _mav_put_float(buf, 4, east);
    _mav_put_float(buf, 8, down);
    _mav_put_float(buf, 12, yaw);
    _mav_put_float(buf, 16, angle_in_frame);
    _mav_put_float(buf, 20, desired_north);
    _mav_put_float(buf, 24, desired_east);
    _mav_put_float(buf, 28, desired_down);
    _mav_put_float(buf, 32, desired_angle_in_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_NED_LEN);
#else
    mavlink_target_ned_t packet;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.angle_in_frame = angle_in_frame;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_NED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
}

/**
 * @brief Pack a target_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param north  north 
 * @param east  east 
 * @param down  down 
 * @param yaw  yaw in degrees
 * @param angle_in_frame  angle_in_frame in degrees
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float north,float east,float down,float yaw,float angle_in_frame,float desired_north,float desired_east,float desired_down,float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_NED_LEN];
    _mav_put_float(buf, 0, north);
    _mav_put_float(buf, 4, east);
    _mav_put_float(buf, 8, down);
    _mav_put_float(buf, 12, yaw);
    _mav_put_float(buf, 16, angle_in_frame);
    _mav_put_float(buf, 20, desired_north);
    _mav_put_float(buf, 24, desired_east);
    _mav_put_float(buf, 28, desired_down);
    _mav_put_float(buf, 32, desired_angle_in_frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_NED_LEN);
#else
    mavlink_target_ned_t packet;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.angle_in_frame = angle_in_frame;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_NED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
}

/**
 * @brief Encode a target_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_ned_t* target_ned)
{
    return mavlink_msg_target_ned_pack(system_id, component_id, msg, target_ned->north, target_ned->east, target_ned->down, target_ned->yaw, target_ned->angle_in_frame, target_ned->desired_north, target_ned->desired_east, target_ned->desired_down, target_ned->desired_angle_in_frame);
}

/**
 * @brief Encode a target_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_ned_t* target_ned)
{
    return mavlink_msg_target_ned_pack_chan(system_id, component_id, chan, msg, target_ned->north, target_ned->east, target_ned->down, target_ned->yaw, target_ned->angle_in_frame, target_ned->desired_north, target_ned->desired_east, target_ned->desired_down, target_ned->desired_angle_in_frame);
}

/**
 * @brief Send a target_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param north  north 
 * @param east  east 
 * @param down  down 
 * @param yaw  yaw in degrees
 * @param angle_in_frame  angle_in_frame in degrees
 * @param desired_north  desired_north 
 * @param desired_east  desired_east 
 * @param desired_down  desired_down 
 * @param desired_angle_in_frame  desired_angle_in_frame in degrees
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_ned_send(mavlink_channel_t chan, float north, float east, float down, float yaw, float angle_in_frame, float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_NED_LEN];
    _mav_put_float(buf, 0, north);
    _mav_put_float(buf, 4, east);
    _mav_put_float(buf, 8, down);
    _mav_put_float(buf, 12, yaw);
    _mav_put_float(buf, 16, angle_in_frame);
    _mav_put_float(buf, 20, desired_north);
    _mav_put_float(buf, 24, desired_east);
    _mav_put_float(buf, 28, desired_down);
    _mav_put_float(buf, 32, desired_angle_in_frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_NED, buf, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
#else
    mavlink_target_ned_t packet;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.angle_in_frame = angle_in_frame;
    packet.desired_north = desired_north;
    packet.desired_east = desired_east;
    packet.desired_down = desired_down;
    packet.desired_angle_in_frame = desired_angle_in_frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_NED, (const char *)&packet, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
#endif
}

/**
 * @brief Send a target_ned message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_ned_send_struct(mavlink_channel_t chan, const mavlink_target_ned_t* target_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_ned_send(chan, target_ned->north, target_ned->east, target_ned->down, target_ned->yaw, target_ned->angle_in_frame, target_ned->desired_north, target_ned->desired_east, target_ned->desired_down, target_ned->desired_angle_in_frame);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_NED, (const char *)target_ned, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float north, float east, float down, float yaw, float angle_in_frame, float desired_north, float desired_east, float desired_down, float desired_angle_in_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, north);
    _mav_put_float(buf, 4, east);
    _mav_put_float(buf, 8, down);
    _mav_put_float(buf, 12, yaw);
    _mav_put_float(buf, 16, angle_in_frame);
    _mav_put_float(buf, 20, desired_north);
    _mav_put_float(buf, 24, desired_east);
    _mav_put_float(buf, 28, desired_down);
    _mav_put_float(buf, 32, desired_angle_in_frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_NED, buf, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
#else
    mavlink_target_ned_t *packet = (mavlink_target_ned_t *)msgbuf;
    packet->north = north;
    packet->east = east;
    packet->down = down;
    packet->yaw = yaw;
    packet->angle_in_frame = angle_in_frame;
    packet->desired_north = desired_north;
    packet->desired_east = desired_east;
    packet->desired_down = desired_down;
    packet->desired_angle_in_frame = desired_angle_in_frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_NED, (const char *)packet, MAVLINK_MSG_ID_TARGET_NED_MIN_LEN, MAVLINK_MSG_ID_TARGET_NED_LEN, MAVLINK_MSG_ID_TARGET_NED_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_NED UNPACKING


/**
 * @brief Get field north from target_ned message
 *
 * @return  north 
 */
static inline float mavlink_msg_target_ned_get_north(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field east from target_ned message
 *
 * @return  east 
 */
static inline float mavlink_msg_target_ned_get_east(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field down from target_ned message
 *
 * @return  down 
 */
static inline float mavlink_msg_target_ned_get_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field yaw from target_ned message
 *
 * @return  yaw in degrees
 */
static inline float mavlink_msg_target_ned_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field angle_in_frame from target_ned message
 *
 * @return  angle_in_frame in degrees
 */
static inline float mavlink_msg_target_ned_get_angle_in_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field desired_north from target_ned message
 *
 * @return  desired_north 
 */
static inline float mavlink_msg_target_ned_get_desired_north(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field desired_east from target_ned message
 *
 * @return  desired_east 
 */
static inline float mavlink_msg_target_ned_get_desired_east(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field desired_down from target_ned message
 *
 * @return  desired_down 
 */
static inline float mavlink_msg_target_ned_get_desired_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field desired_angle_in_frame from target_ned message
 *
 * @return  desired_angle_in_frame in degrees
 */
static inline float mavlink_msg_target_ned_get_desired_angle_in_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a target_ned message into a struct
 *
 * @param msg The message to decode
 * @param target_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_ned_decode(const mavlink_message_t* msg, mavlink_target_ned_t* target_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_ned->north = mavlink_msg_target_ned_get_north(msg);
    target_ned->east = mavlink_msg_target_ned_get_east(msg);
    target_ned->down = mavlink_msg_target_ned_get_down(msg);
    target_ned->yaw = mavlink_msg_target_ned_get_yaw(msg);
    target_ned->angle_in_frame = mavlink_msg_target_ned_get_angle_in_frame(msg);
    target_ned->desired_north = mavlink_msg_target_ned_get_desired_north(msg);
    target_ned->desired_east = mavlink_msg_target_ned_get_desired_east(msg);
    target_ned->desired_down = mavlink_msg_target_ned_get_desired_down(msg);
    target_ned->desired_angle_in_frame = mavlink_msg_target_ned_get_desired_angle_in_frame(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_NED_LEN? msg->len : MAVLINK_MSG_ID_TARGET_NED_LEN;
        memset(target_ned, 0, MAVLINK_MSG_ID_TARGET_NED_LEN);
    memcpy(target_ned, _MAV_PAYLOAD(msg), len);
#endif
}
