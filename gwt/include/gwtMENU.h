#ifndef gwtMENU_H
#define gwtMENU_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtMENU.h,v 1.3 2005-02-15 12:17:52 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * mella     16-Sep-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * gwtMENU class declaration file.
 */


#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

#include "gwtWIDGET.h"
#include "gwtXML_PRODUCER.h"
#include "gwtMENUITEM.h"

/*
 * Class declaration
 */

/**
 * Constructs a new gwtMENU.
 */
class gwtMENU : public gwtWIDGET, public gwtXML_PRODUCER
{
public:
    gwtMENU(string label);
    ~gwtMENU();
    virtual string GetXmlBlock();
    virtual void AddMenu(gwtMENU *menu);
    virtual void AddMenuItem(gwtMENUITEM *item);
    virtual void Show();
    virtual void SetProducerId(string id);
protected:

private:    
    
};




#endif /*!gwtMENU_H*/

/*___oOo___*/
