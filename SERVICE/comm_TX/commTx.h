/*
 * commTx.h
 *
 * Created: 8/9/2018 12:59:56 PM
 *  Author: ebrahim
 *
 */ 

#ifndef COMMTX_H_
#define COMMTX_H_

#include "commTxConfg.h" // channels
#include <common\ebra_common.h>

/*
* the comm_tx is used to transmit large data
* the way it works similar to comm_Rx 
* init the hardware
* let the ISR sent the bytes
* checking in the dissaptcher if it reach to last data byte or not
*/
typedef void (*Call_back_t)(); // this cll back to user fun to indicate that the data have been sent 
typedef struct
{
	Call_back_t commtx_compelete;
	uint8 *ptr_Data2Sent;
	uint16 Num_bytes2sent;
	Comm_Channel_t Channel_Select;
} CommTx_DataCfgType;


void comm_TxInit(CommTx_DataCfgType* ptr_struct);
// must called before dispathcer

void comm_TxDisspatcher();
// should be called in infinty loop 

void comm_TxRest();
#endif /* COMMTX_H_ */
