/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * \file
 * Brief description of the c procedure file, which ends at this dot.
 * 
 * OPTIONAL detailed description of the c procedure file follows here.
 *
 * \usedfiles
 * OPTIONAL. If files are used, for each one, name, and usage description.
 * \filename fileName1 :  usage description of fileName1
 * \filename fileName2 :  usage description of fileName2
 * 
 * \n
 * \env
 * OPTIONAL. If needed, environmental variables accessed by the program. For
 * each variable, name, and usage description, as below.
 * \envvar envVar1 :  usage description of envVar1
 * \envvar envVar2 :  usage description of envVar2
 * 
 * \n
 * \warning OPTIONAL. Warning if any (software requirements, ...)
 *
 * \n
 * \ex
 * OPTIONAL. Code example if needed
 * \n Brief example description.
 * \code
 * Insert your code example here
 * \endcode
 *
 * \sa OPTIONAL. See also section, in which you can refer other documented
 * entities. Doxygen will create the link automatically. For example, 
 * \sa modcMain.c
 * 
 * \bug OPTIONAL. Bugs list if it exists.
 * \bug For example, description of the first bug
 * \bug For example, description of the second bug
 * 
 * \todo OPTIONAL. Things to forsee list, if needed. For example, add
 * modcProc3.
 * 
 */




/* 
 * System Headers 
 */
#include <stdio.h>
#include <string.h>


/*
 * MCS Headers 
 */
#include "mcs.h"
#include "log.h"

/*
 * Local Headers 
 */
#include "modcPrivate.h"
#include "modc.h"


/* 
 * Local variables
 */

static mcsBYTES8 string;    /**< Brief description of the variable, ends at 
                              this dot. OPTIONAL detailed description of 
                              the variable follows here. */

/* 
 * Local functions declaration 
 */

/* IMPORTANT : doxygen extracted documentation for local functions is located
 * just below in this file. It's why a normal documentation block (beginning
 * with 1 slash and 1 star) is used here with a brief description (just to
 * know a little about the function) and NOT A DOXYGEN DOCUMENTATION BLOCK
 * (beginning with 1 slash and 2 stars).
 */

/* Brief description of the procedure */
static mcsCOMPL_STAT modcSub(mcsINT8 x, mcsINT8 y);


/* 
 * Local functions definition
 */

/**
 * Brief description of the function, which ends at this dot.
 *
 * OPTIONAL detailed description of the function follows here.
 *
 * \param x description of parameter x. In the example, a number.
 * \param y description of parameter y. In the example, a number.
 * 
 * \n
 * \return Description of the return value. In the example, mcsSUCCESS on successful completion. Otherwise mcsFAILURE is returned. 
 *
 * \n
 * \err
 * If error handling system is used.
 * The possible errors are :
 * \errname modcERR_ERROR_1
 * \errname modcERR_ERROR_2
 * 
 */
static mcsCOMPL_STAT modcSub(mcsINT8 x, mcsINT8 y)
{
    logTrace("modcSub()");
        
    mcsINT8 z;
    z=x-y;
    logTest("%d - %d = %d\n", x, y, z);

    return mcsSUCCESS;
}


/*
 * Public functions definition
 */

/**
 * Brief description of the function, which ends at this dot.
 *
 * OPTIONAL detailed description of the function follows here.
 *
 * \param a description of parameter a. In the example, a string.
 * \param b description of parameter b. In the example, an integer.
 *
 * \n
 * \return Description of the return value. In the example, mcsSUCCESS on successful completion. Otherwise mcsFAILURE is returned. 
 *
 * \n
 * \err
 * If error handling system is used.
 * The possible errors are :
 * \errname modcERR_ERROR_1
 * \errname modcERR_ERROR_3
 * 
 * \n
 * \usedfiles
 * OPTIONAL. If files are used, for each one, name, and usage description.
 * \filename fileName1 :  usage description of fileName1
 * \filename fileName2 :  usage description of fileName2
 *
 * \n
 * \env
 * OPTIONAL. If needed, environmental variables accessed by the program. For
 * each variable, name, and usage description, as below.
 * \envvar envVar1 :  usage description of envVar1
 * \envvar envVar2 :  usage description of envVar2
 * 
 * \n
 * \warning OPTIONAL. Warning if any (software requirements, ...). For example
 * parameter b is a 8 bit integer.
 *
 * \n
 * \ex 
 * OPTIONAL. Code example if needed
 * \n Brief example description.
 * \code
 * Insert your code example here
 * \endcode
 *
 * \sa OPTIONAL. See also section, in witch you can refer other documented
 * entities. Doxygen will create the link automatically. For example,
 * modcProc2, modcCOLOR
 * 
 * \bug OPTIONAL. Bugs list if it exists.
 * \bug For example, the function doesn't deal with special characters.
 * \bug For example, the function crashes if the buffer size is greater
 * than 1024.
 *
 * \todo OPTIONAL. Things to forsee list.
 * \todo For example, correct bugs.
 * \todo For example, extend the function with file1 and file 2.
 *
 */
mcsCOMPL_STAT modcProc1(mcsBYTES32 a, mcsINT8 b)
{
    logTrace("modcProc1()");
    
    /* Print out parameters */
    logTest("a = %s and b = %i\n", a, b);
    /* Use the local function modcSub */
    mcsINT8 integer = 3;
    logTest("=> call modcSub local function : ");
    if (modcSub(b, integer) == mcsFAILURE)
    {
        logTest("ERROR modcSub\n");
    }
        
    return mcsSUCCESS;
}


/**
 * Brief description of the function, which ends at this dot.
 *
 * OPTIONAL detailed description of the function follows here.
 *
 * \param c description of parameter c. In the example, a string.
 *
 * \n
 * \return Description of the return value. In the example, mcsSUCCESS on successful completion. Otherwise mcsFAILURE is returned. 
 *
 * \n
 * \err
 * If error handling system is used.
 * The possible errors are :
 * \errname modcERR_ERROR_2
 * \errname modcERR_ERROR_3
 * 
 * \n
 * \sa OPTIONAL. See also section, in witch you can refer other documented
 * entities. Doxygen will create the link automatically. For example
 * modcProc1.
 * 
 */
mcsCOMPL_STAT modcProc2(mcsBYTES8 c)
{
    logTrace("modcProc2()");
    
    /* Print out the parameter */
    logTest("c = %s\n", c);
    /* Print out the local variable string */
    strcpy (string, "modcProc2");
    logTest("modcProc.c local variable string = %s\n", string);
        
    return mcsSUCCESS;
}


/*___oOo___*/
