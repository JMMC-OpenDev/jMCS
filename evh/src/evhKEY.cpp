/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: evhKEY.cpp,v 1.3 2005-01-29 15:17:02 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * gzins     24-Sep-2004  Created
 * gzins     07-Jan-2005  Implemented Match()
 *
 ******************************************************************************/

/**
 * \file
 * Definition of the evhKEY class.
 */

static char *rcsId="@(#) $Id: evhKEY.cpp,v 1.3 2005-01-29 15:17:02 gzins Exp $"; 
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
#include "evhKEY.h"
#include "evhPrivate.h"

/**
 * Class constructor
 */
evhKEY::evhKEY(const evhTYPE type)
{
    _type = type;
}

/**
 * Copy constructor.
 */
evhKEY::evhKEY(const evhKEY &key) : fndOBJECT(key)
{
    *this = key;
}

/**
 * Class destructor
 */
evhKEY::~evhKEY()
{
}

/**
 * Assignment operator
 */
evhKEY& evhKEY::operator =( const evhKEY& key)
{
    _type   = key._type;

    return *this;
}

/*
 * Public methods
 */
/**
 * Determines whether the given key is equal to this.
 *
 * \param key element to be compared to this.
 * 
 * \return mcsTRUE if it is equal, mcsFALSE otherwise.
 */
mcsLOGICAL evhKEY::IsSame(const evhKEY& key)
{
    logExtDbg("evhKEY::IsSame()");

    return (_type == key._type)?mcsTRUE:mcsFALSE;
}

/**
 * Determines whether the given key matches to this.
 *
 * \param key element to be compared to this.
 * 
 * \return mcsTRUE if it matches, mcsFALSE otherwise.
 */
mcsLOGICAL evhKEY::Match(const evhKEY& key)
{
    logExtDbg("evhKEY::Match()");

    return (_type == key._type)?mcsTRUE:mcsFALSE;
}

/**
 * Set message type 
 *
 * \return reference to the object itself
 */
evhKEY & evhKEY::SetType(const evhTYPE type)
{
    logExtDbg("evhKEY::SetType()");

    _type = type;
    return *this;
}

/**
 * Get message type 
 *
 * \return message type 
 */
evhTYPE evhKEY::GetType() const
{
    logExtDbg("evhKEY::GetType()");

    return _type;
}
 
/*___oOo___*/
