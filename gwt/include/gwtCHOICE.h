#ifndef gwtCHOICE_H
#define gwtCHOICE_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtCHOICE.h,v 1.3 2005-02-15 12:17:52 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $* mella     16-Sep-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * gwtCHOICE class declaration file.
 */


#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif
/* 
 * System Headers 
 */
#include <iostream>
#include <vector>
using namespace std;

#include "gwtWIDGET.h"

/*
 * Class declaration
 */

/**
 * Constructs a new gwtCHOICE.
 */
class gwtCHOICE : public gwtWIDGET
{
public:
    gwtCHOICE();
    gwtCHOICE(string help);
    ~gwtCHOICE();
    virtual void SetWidgetId(string id);
    virtual string GetXmlBlock();
    virtual void Changed(string value);
    virtual mcsCOMPL_STAT Add(string item);
    virtual mcsINT32 GetSelectedItem();
    virtual string GetSelectedItemValue();
    


protected:
        
private:    
    std::vector<string> _items;
    string _selectedItem;
    
};




#endif /*!gwtCHOICE_H*/

/*___oOo___*/
