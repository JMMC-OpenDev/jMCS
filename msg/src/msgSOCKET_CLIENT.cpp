/*******************************************************************************
* JMMC project
*
* "@(#) $Id: msgSOCKET_CLIENT.cpp,v 1.5 2004-12-03 17:05:50 lafrasse Exp $"
*
* who       when         what
* --------  -----------  -------------------------------------------------------
* scetre    22-Nov-2004  Created
* lafrasse  23-Nov-2004  Comment refinments, and includes cleaning
* lafrasse  03-Dec-2004  Changed port number type from mcsINT32 to mcsUINT16
*
*
*******************************************************************************/

/**
 * \file
 * msgSOCKET_CLIENT class definition.
 */

static char *rcsId="@(#) $Id: msgSOCKET_CLIENT.cpp,v 1.5 2004-12-03 17:05:50 lafrasse Exp $"; 
static void *use_rcsId = ((void)&use_rcsId,(void *) &rcsId);


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
#include "msgSOCKET_CLIENT.h"
#include "msgPrivate.h"

/*
 * Class constructor
 */
msgSOCKET_CLIENT::msgSOCKET_CLIENT()
{
}


/*
 * Class destructor
 */
msgSOCKET_CLIENT::~msgSOCKET_CLIENT()
{
}


/*
 * Public methods
 */

/**
 * Create and connect a new socket to the given host name and port number
 *
 * \param host the remote machine host name to which the socket should connect
 * \param port the remote machine port number to which the socket should connect
 *
 * \return SUCCESS on successfull completion, FAILURE otherwise
 */
mcsCOMPL_STAT msgSOCKET_CLIENT::Open(std::string host, mcsUINT16 port)
{
    logExtDbg("msgSOCKET_CLIENT::Open()");

    // Try to create a new socket
    if (Create() == FAILURE)
    {
        return FAILURE;
    }

    // Try to connect the new socket to the remote host and port
    if (Connect(host, port) == FAILURE)
    {
        return FAILURE;
    }
        
    return SUCCESS;
}


/*
 * Protected methods
 */



/*
 * Private methods
 */



/*___oOo___*/
