#!/usr/bin/python
#*******************************************************************************
# JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
#*******************************************************************************
""" This script aims to launch multiple requests based onto an input file that must be 
given as first parameter. All sections are executed until user specified some on
command line.
The config file must contain the minimum line:
[DEFAULT]
command=msgSendCommand sclsvrServer GETCAL

Then following section will 
"""

import ConfigParser
import os
import sys
import os.path
import os
from optparse import OptionParser

Id="@(#) $Id: cmdBatch.py,v 1.8 2009-02-03 09:57:16 mella Exp $"

class MyParser(ConfigParser.ConfigParser):
    #make option get case sensitive especially for parameter name
    def optionxform(self, option):
        return option

def main(filename,requiredSections, resultDir, dryRun):
    config = MyParser()
    try:
        config.readfp(open(filename))
    except Exception  ,e:
        print("Problem reading " + filename)
        print('Exception was:', e)
        return

    # Start to build batch list for every section
    batchList=[]
    defaultCommand = config.defaults()["command"]
    # Remove command to sections else every commands will  getnext arg:
    # -command XXX as argument
    config.remove_option("DEFAULT", "command")
  
    # check if all requestedSections exist in the batch file
    for requestedSection in requestedSections:
        if config.sections().count(requestedSection)<1:
            print("Undefined section '%s'"%(requestedSection,))

    for currentSection in config.sections():
        if len(requiredSections)>0:
            if requiredSections.count(currentSection)<1:
                continue
        
        # Choose right command for this section        
        if config.has_option(currentSection,"command"):
            command=config.get(currentSection,"command")
            config.remove_option(currentSection, "command")
        else:
            command=defaultCommand
            
        cmd = command
        cmd += ' "'

        # And append to cmd every option  -optionName Value ...
        for n,v in config.items(currentSection):
            if n and v:
                cmd += "-"+n+" "+v+" "
            else: 
                sys.stderr.write("ERROR: Missing value for '%s' item into '%s' section"%(n,currentSection))
                sys.exit(1)
        cmd += ' "'

        # Store new batch results into file.out and file.err
        # " are placed for case were section includes spaces
        batchList.append( cmd + ' > "' + resultDir + os.path.sep +
                currentSection + '.out"' \
                              + ' 2> "' + resultDir + os.path.sep + currentSection + '.err"' )  
        t=open(resultDir+os.path.sep+currentSection+".cmd", "w")
        t.write(cmd)

    # Execute batch line by line
    for cmd in batchList:
        print(cmd)
        if not dryRun:
          os.system(cmd)

if __name__ == '__main__':
    usage="""usage: %prog [options] configFile.cfg [sectionName1] [sectionName2] [...]"""
    parser = OptionParser(usage=usage)
    parser.add_option("-d", "--directory", dest="resultDir", metavar="DIR",
                      default="results", help="Output results in given directory instead of default 'results'")
    parser.add_option("-n", "--dryRun", action="store_true", dest="dryRun", default=False,  
            help="Output commands instead of running them")

    (options, args) = parser.parse_args()
    
    if len(args) < 1:
        parser.print_help()
        sys.exit(1)

    if not os.path.isfile(args[0]) :
        sys.stderr.write("File not found '%s'"%(args[0],))
        sys.exit(1)

    requestedSections=args[1:]

    try:
        print("This batch will loop on batch file '%s'." % (args[0],))
        if len(requestedSections):
            print("For given sections:")
            print(requestedSections)
        print("Output directory for results '%s'"%(options.resultDir,))
        
        # uncomment next line if you want to allow user to control-c the
        # execution
        # print("Press Control-C to stop process now or something else to \
        # continue")
        # raw_input()
        
        if not os.path.isdir(options.resultDir) :
            try:
                os.mkdir(options.resultDir)
                print("'%s' directory has been created." %(options.resultDir,) )
            except:
                sys.stderr.write( "Failed to create '%s' directory.%s" %(options.resultDir,os.linesep))
    except:
        sys.stderr.write("Usage: %s <inputscript.cfg>%s"%(sys.argv[0],os.linesep))
        sys.exit(1)
    
    main(args[0], requestedSections, options.resultDir, options.dryRun)
