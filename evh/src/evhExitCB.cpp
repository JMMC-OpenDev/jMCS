/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * \file
 * Definition of the EXIT callback.
 */

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
    // Set the reply buffer
    msg.SetBody("OK");

    // Send reply
    SendReply(msg);

    return evhCB_NO_DELETE;
}

/*___oOo___*/
