
/*
 * \file     mailbox.h
 *
 * \brief    This file contains the function prototypes for Mail box access
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
 
#ifndef      __MAIL_BOX_H__
#define      __MAIL_BOX_H__

#include "hw_control_AM335x.h"
#include "hw_mailbox.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************** MACROS ***************************/

/*	User Id's	*/
#define MAILBOX_USER_A8 		0
#define MAILBOX_USER_PRU0 		1
#define MAILBOX_USER_PRU1 		2
#define MAILBOX_USER_CM3WKUP 	3

/*	Mailbox Queue's	*/
#define	MAILBOX_QUEUE_0			0
#define	MAILBOX_QUEUE_1			1
#define	MAILBOX_QUEUE_2			2
#define	MAILBOX_QUEUE_3			3
#define	MAILBOX_QUEUE_4			4
#define	MAILBOX_QUEUE_5			5
#define	MAILBOX_QUEUE_6			6
#define	MAILBOX_QUEUE_7			7
	
#define MESSAGE_VALID			0
#define MESSAGE_INVALID			1


/*****************************************************************************
**                   FUNCTION DECLARATIONS                                   
*****************************************************************************/

/*	Queue Access API's	*/

void MBresetMailbox(unsigned int baseAdd);

void MBconfigIdleMode(unsigned int baseAdd, unsigned int idleMode);

unsigned int MBgetMessage(unsigned int baseAdd, unsigned int queueId, unsigned int *msgPtr);

unsigned int MBsendMessage(unsigned int baseAdd, unsigned int queueId, unsigned int msg);


/*	Mailbox user(hw using mailbox) access API's	*/
void MBenableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBenableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

void MBdisableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBdisableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

unsigned int MBgetNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
unsigned int MBgetQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

void MBclrNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBclrQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

unsigned int MBgetRawNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
unsigned int MBgetRawQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);


#ifdef __cplusplus
}
#endif

#endif

