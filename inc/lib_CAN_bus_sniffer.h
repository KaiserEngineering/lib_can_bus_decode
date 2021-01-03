/* Author : Matthew Kaiser */
#ifndef LIB_CAN_BUS_SNIFFER_H_
#define LIB_CAN_BUS_SNIFFER_H_

#include "stdio.h"
#include "lib_pid.h"
#include "lib_unit_conversion.h"

#define NUM_CAN_DECODE 25

#ifdef FORD_FOCUS_STRS_2013_2018

    #ifdef MODE1_TRANS_ACTUAL_GEAR_SUPPORTED
    #define DECODE_TRANS_ACTUAL_GEAR_PID    MODE1_TRANS_ACTUAL_GEAR
    #define DECODE_TRANS_ACTUAL_GEAR_ID     0x70
    #endif

    #ifdef MODE1_REL_ACCELERATOR_PEDAL_POS_SUPPORTED
    #define DECODE_ACCEL_PEDAL_POS_PID      MODE1_REL_ACCELERATOR_PEDAL_POS
    #define DECODE_ACCEL_PEDAL_POS_ID       0x080
    #endif

    #ifdef MODE1_ENGINE_RPM_SUPPORTED
    #define DECODE_ENGINE_RPM_PID           MODE1_ENGINE_RPM
    #define DECODE_ENGINE_RPM_ID            0x090
    #endif

    #ifdef MODE1_TURBO_INLET_PRESSURE_SUPPORTED
    #define DECODE_BOOST_PRESSURE_PID       MODE1_TURBO_INLET_PRESSURE
    #define DECODE_BOOST_PRESSURE_ID        0xF8
    #endif

    #ifdef MODE1_ENGINE_OIL_TEMPERATURE_SUPPORTED
    #define DECODE_ENGINE_OIL_TEMP_PID      MODE1_ENGINE_OIL_TEMPERATURE
    #define DECODE_ENGINE_OIL_TEMP_ID       0xF8
    #endif

    #ifdef DECODE_GAUGE_BRIGHTNESS_SUPPORTED
    #define DECODE_GAUGE_BRIGHTNESS_PID     DECODE_GAUGE_BRIGHTNESS
    #define DECODE_GAUGE_BRIGHTNESS_ID      0xC8
    #endif

    #ifdef MODE1_VEHICLE_SPEED_SUPPORTED
    #define DECODE_VEHICLE_SPEED_PID        MODE1_VEHICLE_SPEED
    #define DECODE_VEHICLE_SPEED_ID         0x130
    #endif

#endif

typedef void (*CAN_DECODE_FLAG_UPDATE)( uint16_t flag, uint8_t bit );
typedef void (*CAN_DECODE_FILTER)( uint16_t id );

typedef enum _pid_supported_status {
    PID_NOT_SUPPORTED,
    PID_SUPPORTED
} PID_SUPPORTED_STATUS, *PPID_SUPPORTED_STATUS;

typedef struct _can_decode_packet_manager {
	uint8_t status;
		#define CAN_DECODE_INIT 0x0001

	/* Number of PIDs being streamed */
    uint8_t num_pids;

    /* Callback to add a CAN bus filter */
    CAN_DECODE_FILTER filter;

    PTR_PID_DATA stream[NUM_CAN_DECODE];

} CAN_DECODE_PACKET_MANAGER, *PCAN_DECODE_PACKET_MANAGER;

PID_SUPPORTED_STATUS CAN_Decode_Supported( PTR_PID_DATA pid );
PID_SUPPORTED_STATUS CAN_Decode_Add_PID(  PCAN_DECODE_PACKET_MANAGER dev, PTR_PID_DATA pid );
float CAN_Decode_Get_Value_Byte_PID( PCAN_DECODE_PACKET_MANAGER dev, uint16_t pid );
void CAN_Decode_Add_Packet( PCAN_DECODE_PACKET_MANAGER dev, uint16_t arbitration_id, uint8_t* packet_data );
void CAN_Decode_Initialize( PCAN_DECODE_PACKET_MANAGER dev );
void CAN_Sniffer_tick( void );



#endif // LIB_CAN_BUS_DECODE_H