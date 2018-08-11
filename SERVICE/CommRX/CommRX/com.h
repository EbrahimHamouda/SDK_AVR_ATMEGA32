/*
 * com.h
 *
 *  Created on: Aug 4, 2018
 *      Author: EbrahimHamouda
 */

#ifndef SERVICE_COM_H_
#define SERVICE_COM_H_

#include "ebra_common.h"
#include "USART.h"

#define FRAME__SIZE			100
#define COMMAND_SIZE		1
#define HEADER_SIZE			3
#define CS_SIZE				3
#define RX_DATA_MAX_SIZE	(FRAME__SIZE - HEADER_SIZE - CS_SIZE - COMMAND_SIZE)

typedef enum 
{
	IDLE,
	CHEACK_HEADER, RECEIVE_BYTE, RECEIVE_COMPLETE
} RX_StateType;

typedef struct 
{
	uint8 header[HEADER_SIZE];
	uint8 cmd[COMMAND_SIZE];
	uint8 data[RX_DATA_MAX_SIZE];
	uint8 cs[CS_SIZE];
} RX_FrameStruct;

void Comm_RxInit(void (*ptr_Fu_ProcessDataRX)(uint8* Rx_data),uint8* User_header);
void RX_CommFree();
void RX_com_dispatch();

#endif /* SERVICE_COM_H_  */
