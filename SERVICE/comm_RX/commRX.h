/*
 * com.h
 *
 *  Created on: Aug 4, 2018
 *      Author: EbrahimHamouda
 */

#ifndef SERVICE_COM_H_
#define SERVICE_COM_H_

#include <common\ebra_common.h>
#include "CommRxConfg.h"

/*
* the comm_Rx is a commponent  in service layer to manage the communication of bigger data
* the way it works
* first take initialize values to init_ hardware
* second it wait till the first interrupt occur 
* then buffer data in each interrupt 
* the dissaptcher is to check some alograthim and call user fun when it finishes
*/

typedef void (*Call_BackCommRX_t)(uint8*,uint16) ; 
// ptr_funcation_take 2 variables "pointer to uint8 of buffer" and  "uint16 num of bytes recevied " return nothing

typedef struct 
{
	Call_BackCommRX_t ptr_user_fun; // application fun
	RX_Channel_t channel; // channel used to receive
	uint8 cofm_letter; // the confirmation letter to ack the message  
} RX_cfg_t; 

void Comm_RxInit(RX_cfg_t* ptr_cfg_str);
// this funcation is used to make a new reciving by passing a fun to indicate the receving has finished and channel used and confirmation letter

void RX_CommFree();
// it must be called at the function u passed to free the comm_rx to re-used the buffer													

void RX_com_dispatch();
//this funcation is always called in the infinity loop 

#endif /* SERVICE_COM_H_  */
