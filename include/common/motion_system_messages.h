//header file for motion system messages
// This file defines the structures and constants used for communication with the motion system.
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
{ // confidential data structure
    uint8_t x1;     
    uint8_t x2;     
    uint8_t x3;     
    uint16_t x4;    
    uint32_t x5;    
    uint32_t x6;    
    uint16_t x7;     
    uint16_t x8;     
    uint16_t x9;     
    uint16_t x10;    
    uint8_t x11;           
    uint8_t x12;           
    uint16_t x13;          
    uint16_t x14;              
    uint16_t x15;              
    uint16_t x16;              
    uint16_t x17;                
    uint16_t x18;            
    uint16_t x19;
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
    //confidential data structure
    uint8_t y1; 
    uint16_t y2;            
    uint16_t y3;            
    uint16_t y4;            
    uint16_t y5;            
    uint16_t y6;            
    uint16_t y7;            
    uint16_t y8;            
    uint16_t y9;            
    uint16_t y10;           
} DataToMotionSystem;

// Complete message sent to the Motion System (24 bytes)
typedef struct
{
    MotionSystemMessageHeader header;
    DataToMotionSystem data;
    MotionSystemMessageFooter footer;
} MessageToMotionSystem;

#pragma pack(pop)