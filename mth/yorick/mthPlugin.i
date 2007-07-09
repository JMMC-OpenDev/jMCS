/*******************************************************************************
* JMMC project - MCS mathematical library plugin 
*
* Yorick plugin for MCS mathematical library
*
* "@(#) $Id: mthPlugin.i,v 1.1 2007-07-09 12:52:42 gzins Exp $"
*
* History
* -------
* $Log: not supported by cvs2svn $
*/

local package_mthPlugin;
/* DOCUMENT package_mthPlugin -- mthPlugin.i
  Low level mth functions
*/

// Wrapper to C sub-routines 
#include "mthWrapper.i"

/********************* AMBER Data Reduction routines *********************
*
* A complete mth interface has been generated automatically from the library
* header file and is named mthWrapper.i 
* Here is the routines which have to be used to call the mth interface 
*/

/************************************************************************/

func mthPlugin(void)
/* DOCUMENT mthPlugin(void)
    
  DESCRIPTION
    mth plugin low level routines

  VERSION
    $Revision: 1.1 $
    
  FUNCTIONS
    - _mthLinInterp : Performs linear interpolation 

  SEE ALSO
    mth
*/
{
    version = strpart(strtok("$Revision: 1.1 $",":")(2),2:-2);
    if (am_subroutine())
    {
        help, mthPlugin;
    }   
    return version;
}

/************************************************************************/


/************************************************************************/

func mthInterp(x, y, xp)
/* DOCUMENT mthInterp(x, y, xp)

  DESCRIPTION
    Returns the list of interpolated values corresponding to xp abscissae, and
    which lie on the piecewise linear curve; i.e. it performs the same treatment
    than interp yorick function, excepted that it has been optimized for one
    dimensional array.

  CAUTION
    The array y and y must be one dimensional, have numberof(x)>=2, and be
    monotonically increasing

  PARAMETERS
    - x  : abscissae of curve
    - y  : ordinates of curve 
    - xp : abscissae to be interpolated

  RETURN VALUES
    List of interpolated values 

  EXAMPLES
    > x = array(double, 1000);
    > y = array(double, 1000);
    > xp = array(double, 1000);
    > ...
    > yp = mthInterp(x, y, xp);
    ...

  SEE ALSO
    interp
*/
{
    // Check dimension of input arrays 
    // Must be one dimensional array
    if ((dimsof(x)(1) != 1) || (dimsof(y)(1) != 1) || (dimsof(xp)(1) != 1))
    {
        exit("mthInterp - x, y and xp must be one dimensional");
    }
    // Must have at least 2 points 
    if (dimsof(x)(2) < 2) 
    {
        exit("mthInterp - x must contain at least 2 points");
    }
    // Must have same dimension 
    if ((dimsof(y)(2) != dimsof(x)(2)))
    {
        exit("mthInterp - x and y must have same dimension");
    }
    
    // Check array type
    if ((typeof(x) != "double") || 
        (typeof(y) != "double") || 
        (typeof(xp) != "double") )
    {
        exit("mthInterp - x, y and xp must be double");
    }

    // Allocate arry for yp
    yp = array(double, dimsof(xp)(2));

    // Call C-function
    status = __mthLinInterp(dimsof(x)(2), &x, &y, dimsof(xp)(2), &xp, &yp);
    if (status == 1)
    {
        error("mthInterp - could not perform linear interpolation");
    }

    return yp;
}

