/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: timlogTest.c,v 1.5 2005-02-15 10:33:08 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2005/02/15 10:30:55  gzins
 * Fixed wrong history log
 *
 * Revision 1.3  2005/02/15 10:27:46  gzins
 * Added CVS log as file modification history
 *
 * gzins     17-Dec-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * Test program for timer log facility.
 */

static char *rcsId="@(#) $Id: timlogTest.c,v 1.5 2005-02-15 10:33:08 gzins Exp $"; 
static void *use_rcsId = ((void)&use_rcsId,(void *) &rcsId);

/* 
 * System Headers 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * MCS Headers 
 */
#include "mcs.h"
#include "log.h"
#include "err.h"

/*
 * Local Headers 
 */
#include "timlog.h"
#include "timlogPrivate.h"

/* 
 * Main
 */

int main (int argc, char *argv[])
{
    /* Initializes MCS services */
    if (mcsInit(argv[0]) == mcsFAILURE)
    {
        /* Error handling if necessary */
        
        /* Exit from the application with mcsFAILURE */
        exit (EXIT_FAILURE);
    }

    /* Start ACTION */
    timlogInfoStart("ACTION_1");
    timlogInfoStart("ACTION_2");

    sleep (1);
    timlogStop("ACTION_2");
    
    sleep (1);
    timlogStop("ACTION_2");
 
    sleep (1);
    timlogStop("ACTION_1");
 
    timlogClear();

    /* Close MCS services */
    mcsExit();
    
    /* Exit from the application with mcsSUCCESS */
    exit (EXIT_SUCCESS);
}


/*___oOo___*/
