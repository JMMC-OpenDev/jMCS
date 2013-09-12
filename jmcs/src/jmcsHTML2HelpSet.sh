#!/bin/bash
################################################################################
#                  jMCS project ( http://www.jmmc.fr/dev/jmcs )
################################################################################
#  Copyright (c) 2013, CNRS. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#      - Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      - Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      - Neither the name of the CNRS nor the names of its contributors may be
#        used to endorse or promote products derived from this software without
#        specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL CNRS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
################################################################################

#/**
# @file
# Generates a HelpSet Jar file which contains .hs, .jhm and .toc files from
# a HTML folder. This shell script uses java script jmcsGenerateHelpsetFromHtml and jhelpdev software.
#
# @synopsis
# jmcsHTML2HelpSet CVS_documentation_module_name...
#
# @param CVS_documentation_module_name : One (or several) name(s) of CVS module(s) that contains Latex documentation
# 
# @details
# =>>>>>>>>>>>>>>>>>>>>>decrire precisement checkout modul tmp/ make jhelpdev jar lib/[module_name]-doc.jar
#
# @warning
# Don't forget to add lib/[module_name]-doc.jar file in the Makefile
#
# @usedfiles
# @filename fr.jmcs.mcs.gui.jmcsGenerateHelpsetFromHtml : Calls the fonctions used to create .hs, .jhm and .toc files
# 
# @ex
# @code
# jmcsHTML2HelpSet.sh JMMC-GEN-0000-0001 JMMC-MAN-0000-0001
# @endcode
# */

# The two vars below are used to make documentation.xml (the jhelpdev project main file)
header="<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE jhelpdev PUBLIC \"-//jhelpdev.sourcefore.net//JHelpDev Configuration Settings 1.2\" \"http://jhelpdev.sourceforge.net/dtd/jhelpdev_1_2.dtd\"><!--generated by JHelpDev Version: 0.62, 10 November 2006, see jhelpdev.sourceforge.org--><jhelpdev version=\"1.2\"><config><project>documentation</project><projectdir>"
footer="</projectdir><startpage>index.html</startpage><popupicon></popupicon></config><view> <helptitle>Help</helptitle><toc showing=\"yes\" label=\"TOC\"/><index showing=\"yes\" label=\"Index\"/><search showing=\"yes\" label=\"Search\"/></view><encoding value=\"UTF-8\"/></jhelpdev>"

# Latex tempory folder, we checkout all CVS modules into it
latex_tempory_folder=../doc/tmp

# Name of the current module
module_name=$(ctooGetModuleName)

# HelpSet jar file name
# Pattern : [module-name]-doc.jar
jar_name=$module_name"-doc.jar"

# Check that there is 1 argument at least
if [ $# -le 0 ]; then
    echo "Error : Please specify at least one documentation reference to get associted module..."
    exit 1
fi

# Remove tmp folder if exists
# in order to avoid previous files inclusion
if [ -e $latex_tempory_folder ]; then
    if [ -d $latex_tempory_folder ]; then
        rm -rf $latex_tempory_folder
    fi
fi

# Create Latex tempory folder
mkdir $latex_tempory_folder

# Go into this folder because CVS checkout
# doesn't accept an absolute path and 
# path like ../xx/ too...
cd $latex_tempory_folder

repos="https://svn.jmmc.fr/jmmc-doc/trunk"

echo "Checkout each documentation modules ..."
# For each module
for module in $@
do
    if [ -d "$module" ]
    then
        module_doc=$(basename $module)"-doc"
        echo "Copying html pages from $module to $module_doc..."
        cp -r $module $module_doc
        module=$(basename $module)
    else
        echo "Configuring $module ..."

        # CVS export
        svn co "$repos/$module"
        # Exit if export failed
        if [ $? -eq 1 ]; then
            exit 1;
        fi

        # Compile it and force HTML generation according to default makefile convention
        make -C $module/ all $module

        # Move the compilation generated
        # files in module co folder
        module_doc=$module"-doc"
        mv $module/$module $module"-doc"
        rm -rf $module

    fi

    # Remove all unsed file to avoid generated
    # errors with jhelpdev
    rm $module_doc/*.css $module_doc/*.aux $module_doc/*.log
    rm $module_doc/*.tex $module_doc/*.pl $module_doc/*.eps
    rm $module_doc/$module".html"
    rm -rf $module_doc/WARNINGS

    #echo "Cleaning HTML files with Tidy ..."
    # Parse and correct HTML with Tidy
    #java -jar $INTROOT/lib/Tidy.jar -utf8 -m -i -e -asxml $module_doc/*.html


    # Remove -doc extension
    mv $module_doc $module
done

echo "Jhelpdev configuration ..."
# Created the jhelpdev XML project file
touch documentation.xml
echo $header$(pwd)$footer > documentation.xml 

# Launch jhelpdev
java -classpath $(mkfMakeJavaClasspath) jmcsGenerateHelpsetFromHtml documentation.xml

# try to get one better TOC if only one latex module is given
HTMLINDEXFILE="$(basename $@)/index.html"
if [ -e "$HTMLINDEXFILE" ]
then
    echo "Trying to build TOC with latex index"
    INDEXFILE="$(basename $@)/index.xml"
    # tidy html file
    cp $HTMLINDEXFILE $INDEXFILE
    java -jar $INTROOT/lib/Tidy.jar -utf8 -m -i -asxml $INDEXFILE
    
    DIRNAME="$(dirname $INDEXFILE)"
    DOCTOC="documentationTOC.xml"
    if grep LaTeX2HTML $INDEXFILE &> /dev/null
    then
        XSLTFILE=$(miscLocateFile jmcsLatexIndex2HsTOC.xsl)
        mv $DOCTOC $DOCTOC.bac
        xsltproc --nonet -o $DOCTOC --stringparam directory "$DIRNAME" $XSLTFILE $INDEXFILE 
        xsltproc --nonet --stringparam directory "$DIRNAME" $XSLTFILE $INDEXFILE 

    fi
else
    ls $(basename $@)
    echo "Nothing found as latex index"
fi


echo "Jar construction ..."
# Create the helpset jar file
OUTPUT_JAR=../../lib/$jar_name
jar cf $OUTPUT_JAR *
echo "  '$OUTPUT_JAR' generated"


# Return to doc folder and remove Latex tempory folder folder
# in order to avoid later files inclusion
cd ../
#rm -rf tmp

# Remove jhelpdev tmp folder if exists
# in order to permit to an other person
# to use the script, as Jhelpdev allways creates
# /tmp/JavaHelpSearch
jhelpdev_tmp_folder=/tmp/JavaHelpSearch
if [ -e $jhelpdev_tmp_folder ]; then
    if [ -d $jhelpdev_tmp_folder ]; then
        rm -rf $jhelpdev_tmp_folder
    fi
fi

echo "Done"
#___oOo___
