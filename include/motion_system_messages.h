#pragma once

#include <stdint.h>

// Ensure structures are packed with no padding bytes
#pragma pack(push, 1)

/**
 * Motion System Messaging structures and constants
 * Converted from C++ to C with descriptive comments.
 * Namespace scs::motion_man replaced with appropriate prefixes.
 */

// Message framing bytes
#define MS_FRAME_SOH 0x01
#define MS_FRAME_STX 0x02
#define MS_FRAME_ETX 0x03
#define MS_FRAME_NWA 0x10

// Header structure for all messages (3 bytes)
typedef struct
{
    uint8_t soh; // Start of Header
    uint8_t nwa; // Node/Address field (usually fixed)
    uint8_t stx; // Start of Text
} MotionSystemMessageHeader;

// Footer structure for all messages (2 bytes)
typedef struct
{
    uint8_t checksum; // Checksum byte
    uint8_t etx;      // End of Text
} MotionSystemMessageFooter;

// Data received from the Motion System (37 bytes)
typedef struct
{
    uint8_t motion_status;        // Bitwise status flags
    uint8_t motion_control;       // Bitwise control flags
    uint8_t spare;                // Spare / reserved byte
    uint16_t error_interlock;     // Interlock error flags
    uint32_t error_msg1;          // Priority 1 fault flags
    uint32_t error_msg2;          // Priority 2 fault flags
    uint16_t error_indram_x1;     // Indramat X1 error code
    uint16_t error_indram_x2;     // Indramat X2 error code
    uint16_t error_indram_y1;     // Indramat Y1 error code
    uint16_t error_indram_y2;     // Indramat Y2 error code
    uint8_t washout_x;            // Washout X status
    uint8_t washout_y;            // Washout Y status
    uint16_t x;                   // Position X
    uint16_t x_dot;               // Velocity X
    uint16_t x_ddot;              // Acceleration X
    uint16_t y;                   // Position Y
    uint16_t y_dot;               // Velocity Y
    uint16_t y_ddot;              // Acceleration Y
    uint16_t life_counter;        // Life counter value (monitor life counter, increment it per trans.)
} DataFromMotionSystem;

// Complete message received from the Motion System (42 bytes)
typedef struct
{
    MotionSystemMessageHeader header;
    DataFromMotionSystem data;
    MotionSystemMessageFooter footer;
} MessageFromMotionSystem;

// Data sent to the Motion System (19 bytes)
typedef struct
{
    uint8_t control_state; // Command or control state
    uint16_t x;            // X position for SIM_START and SIM_RUN
    uint16_t x_lim1;       // X limit 1
    uint16_t x_lim2;       // X limit 2
    uint16_t x_cycle_time; // X cycle time
    uint16_t y;            // Y position for SIM_START and SIM_RUN
    uint16_t y_lim1;       // Y limit 1
    uint16_t y_lim2;       // Y limit 2
    uint16_t y_cycle_time; // Y cycle time
    uint16_t life_counter; // Life counter value
} DataToMotionSystem;

// Complete message sent to the Motion System (24 bytes)
typedef struct
{
    MotionSystemMessageHeader header;
    DataToMotionSystem data;
    MotionSystemMessageFooter footer;
} MessageToMotionSystem;

// Message sizes including framing bytes
#define MS_FROM_MESSAGE_SIZE 42
#define MS_TO_MESSAGE_SIZE 24

// Motion System status bit positions
#define MS_STATE_BPOS_INTERLOCK      0
#define MS_STATE_BPOS_FAULT          1
#define MS_STATE_BPOS_POWER_FAIL     2
#define MS_STATE_BPOS_INIT_SETUP     3
#define MS_STATE_BPOS_MCU_MODE       4
#define MS_STATE_BPOS_MS_START_POS   5
#define MS_STATE_BPOS_MS_ONLINE      6
#define MS_STATE_BPOS_MS_INIT_MODE   7

// Motion System control bit positions
#define MS_CONTROL_BPOS_LAMP_ON      0
#define MS_CONTROL_BPOS_LAMP_ZERO    2
#define MS_CONTROL_BPOS_LAMP_OFF     4
#define MS_CONTROL_BPOS_LAMP_SPARE   6

// Interlock error bit positions
#define MS_INTERLOCK_ERROR_SETTLE_NOT_READY 0
#define MS_INTERLOCK_ERROR_DOOR             1
#define MS_INTERLOCK_ERROR_GANGWAY          2
#define MS_INTERLOCK_ERROR_LOCK_BOLTING_X1  3
#define MS_INTERLOCK_ERROR_LOCK_BOLTING_X2  4
#define MS_INTERLOCK_ERROR_LOCK_BOLTING_Y1  5
#define MS_INTERLOCK_ERROR_LOCK_BOLTING_Y2  6

// Priority 1 fault bit positions
#define MS_WZD_EMERG_STOP_RELAY       0
#define MS_WZD_INDRAMAT_X1            1
#define MS_WZD_INDRAMAT_X2            2
#define MS_WZD_INDRAMAT_Y1            3
#define MS_WZD_INDRAMAT_Y2            4
#define MS_WZD_ZERO_SENSOR_CPU_SPS    5
#define MS_WZD_CPU_ID                 6
#define MS_WZD_INDRAMAT_LWL           7
#define MS_WZD_COMM_SIMULATION        8
#define MS_WZD_COM_CPU                9
#define MS_WZD_CPU_IS_DEAD            10
#define MS_WZD_CPU_NOT_READY          11

// Priority 2 fault bit positions
#define MS_ZD_LIMIT_SENSOR_XPLUS           0
#define MS_ZD_LIMIT_SENSOR_XMINUS          1
#define MS_ZD_LIMIT_SENSOR_YPLUS           2
#define MS_ZD_LIMIT_SENSOR_YMINUS          3
#define MS_ZD_TEMP_MS_OFF                  4
#define MS_ZD_GANGWAY_MOTOR                5
#define MS_ZD_EMERG_OFF_LIMIT_XPLUS        6
#define MS_ZD_EMERG_OFF_LIMIT_XMINUS       7
#define MS_ZD_EMERG_OFF_LIMIT_YPLUS        8
#define MS_ZD_EMERG_OFF_LIMIT_YMINUS       9
#define MS_ZD_LIMIT_SENSOR_X               10
#define MS_ZD_LIMIT_SENSOR_Y               11
#define MS_ZD_LIMIT_SENSOR_GANGWAY         12
#define MS_ZD_ZERO_SENSOR_XPLUS_X          13
#define MS_ZD_ZERO_SENSOR_XMINUS_X         14
#define MS_ZD_ZERO_SENSOR_YPLUS_Y          15
#define MS_ZD_ZERO_SENSOR_YMINUS_Y         16
#define MS_ZD_CPU_NO_REF                   17
#define MS_ZD_ZERO_POS_ROUGH_FINE_X        18
#define MS_ZD_ZERO_POS_ROUGH_FINE_Y        19
#define MS_ZD_POWER_FAILURE                20

// Motion System control status enum (command codes)
typedef enum
{
    MSCS_NO_ACTION = 0x00,

    // Simulation related commands
    MSCS_SIM_INIT = 0x01,
    MSCS_SIM_START = 0x02,
    MSCS_SIM_RUN = 0x03,
    MSCS_SIM_ZERO = 0x04,
    MSCS_SIM_OFF = 0x05,

    // Sinus X tests
    MSCS_SINUS_X_INIT = 0x11,
    MSCS_SINUS_X_START = 0x12,
    MSCS_SINUS_X_RUN = 0x13,
    MSCS_SINUS_X_ZERO = 0x14,
    MSCS_SINUS_X_OFF = 0x15,

    // Ramp X tests
    MSCS_RAMP_X_INIT = 0x21,
    MSCS_RAMP_X_START = 0x22,
    MSCS_RAMP_X_RUN = 0x23,
    MSCS_RAMP_X_ZERO = 0x24,
    MSCS_RAMP_X_OFF = 0x25,

    // Transition X tests
    MSCS_TRANSITION_X_INIT = 0x31,
    MSCS_TRANSITION_X_START = 0x32,
    MSCS_TRANSITION_X_RUN = 0x33,
    MSCS_TRANSITION_X_ZERO = 0x34,
    MSCS_TRANSITION_X_OFF = 0x35,

    // Sinus Y tests
    MSCS_SINUS_Y_INIT = 0x41,
    MSCS_SINUS_Y_START = 0x42,
    MSCS_SINUS_Y_RUN = 0x43,
    MSCS_SINUS_Y_ZERO = 0x44,
    MSCS_SINUS_Y_OFF = 0x45,

    // Ramp Y tests
    MSCS_RAMP_Y_INIT = 0x51,
    MSCS_RAMP_Y_START = 0x52,
    MSCS_RAMP_Y_RUN = 0x53,
    MSCS_RAMP_Y_ZERO = 0x54,
    MSCS_RAMP_Y_OFF = 0x55,

    // Transition Y tests
    MSCS_TRANSITION_Y_INIT = 0x61,
    MSCS_TRANSITION_Y_START = 0x62,
    MSCS_TRANSITION_Y_RUN = 0x63,
    MSCS_TRANSITION_Y_ZERO = 0x64,
    MSCS_TRANSITION_Y_OFF = 0x65

} MOTION_SYSTEM_CONTROL_STATUS;

#pragma pack(pop)