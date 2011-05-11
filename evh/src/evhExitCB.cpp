/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * \file
 * Definition of the EXIT callback.
 */

static char *rcsId __attribute__ ((unused)) ="@(#) $Id: evhExitCB.cpp,v 1.2 2006-05-11 13:04:18 mella Exp $";
/* 
 * System Headers 
 */
#include <iostream>
using namespace std;

/*
 * MCS Headers 
 */
#include "mcs.h"
#include "log.h"
#include "err.h"

/*
 * Local Headers 
 */
#include "evhSERVER.h"
#include "evhPrivate.h"

/**
 * Callback method for EXIT command.
 * 
 * Just send an 'OK' reply.
 *
 * \return evhCB_NO_DELETE.
 */
evhCB_COMPL_STAT evhSERVER::ExitCB(msgMESSAGE &msg, void*)
{
    logExtDbg("evhSERVER::ExitCB()");

    // Set the reply buffer
    msg.SetBody("OK");

    // Send reply
    SendReply(msg);

    return evhCB_NO_DELETE;
}

/*___oOo___*/
