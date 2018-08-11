/*
 * commTx.h
 *
 * Created: 8/9/2018 12:59:56 PM
 *  Author: ebrahim
 *
 */ 

#ifndef COMMTX_H_
#define COMMTX_H_

#include "ebra_common.h"
#include "USART.h"

typedef struct
{
	void (*Call_back_commtx_compelete)();
	uint8 *ptr_Data2Sent;
	uint16 N_Byte2Sent;
} CommTx_DataCfgType;


void comm_TxInit(CommTx_DataCfgType* ptr_struct);

void comm_TxDisspatch();

void comm_TxRest();
#endif /* COMMTX_H_ */
