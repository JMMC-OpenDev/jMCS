#! /bin/sh
#*******************************************************************************
# JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
#*******************************************************************************
#   NAME
#   mkfMakeJavaDependencies - create the makefile to build an executable
# 
#   SYNOPSIS
#
#   mkfMakeJavaDependencies <jarfile> 
# 
#   DESCRIPTION
#   Utility used by mkfMakefile to create the makefile to build a Java 
#   Jarfile, based upon the java compiler and the jar archival tool.
#   It is not intended to be used as a standalone command.
#
#
#   (1) see also GNU Make 3.64, 4.3.5 pag 37
#
#
#   The .djar itself depends to Makefile.
#
#   The rules is written to standard output.
#
#   <jarfile>     The name of the destination jarfile
#                 (Without directory)
#
#
#   FILES
#   $MCSROOT/include/mkfMakefile   
#
#   ENVIRONMENT
#
#   RETURN VALUES
#
#   SEE ALSO 
#   mkfMakefile, Makefile, (GNU) make
#
#   BUGS    
#

jarName=$1
dirList=$2
extraList=$3
compilerFlags=$4
debug=$5

destDir=../object/${jarName}/

echo "# Dependency file for program: ${jarName}"
echo "# Created automatically by mkfMakeJavaDependencies -  `date '+%d.%m.%y %T'`"
echo "# DO NOT EDIT THIS FILE"
echo "../object/${jarName}.djar: Makefile"
echo ""

if [ "${JAVAC}" == "" ]
then
    JAVAC=javac
fi

    if [ "${debug}" == "on" ]
	then
	compilerFlags=`echo $compilerFlags | sed -e 's/-g //;s/-g[:a-z]*//'`
	compilerFlags="$compilerFlags -g"
    fi

if [ "${MAKE_PURIFY}" != "" -o "${MAKE_PURE}" != "" ]
then
    if [ "${RATIONAL_DIR}" != "" ]
    then
	PURIFY_ADDITION="export ATLTGT=${RATIONAL_DIR}/targets/jdk1.4.0 ;  export PATH=\$\$ATLTGT/cmd:\${PATH} ; "
	mkdir -p ${destDir}/javi.jir
	cp -r ${RATIONAL_DIR}/targets/jdk1.4.0/lib/com ${destDir}/javi.jir/
	cp -r ${RATIONAL_DIR}/targets/xml/java/lib/com ${destDir}/javi.jir/
    fi
fi

if [ "${dirList}" != "" ]
then
    #
    # prepare the list of all objects (full filename)
    for member in ${dirList}
    do
	javaList=`(find ${member} -name \*.java | tr '\n' ' '  )`
        oList="${oList} ${javaList} "
	if [ ${member} = "." ]
	then
	    cList="${cList} *.class "
	else
	    cList="${cList} ${member} "
	fi
    done
    #
    currentLocation=`\pwd | sed "s/\/.*\///"`
    # prepare the list with the 'src/test' at the front, for DEBUG=on
    for member in ${oList}
    do
        sList="${sList} $currentLocation/${member} "
    done

# define the dependency file dependent to the Makefile
    echo "../lib/${jarName}.jar: ${oList}"
    echo "	@echo \"== Making ${jarName}.jar\""
    echo "	\$(AT)mkdir -p ${destDir}"
    echo "	\$(AT)javac -version"
    echo "	\$(AT)echo  \" with compiler flags : '${compilerFlags}'\""
    echo "	\$(AT)${PURIFY_ADDITION} CLASSPATH=`mkfMakeJavaClasspath`:.; export CLASSPATH ; ${JAVAC} ${compilerFlags} -d ${destDir} \$?"
    echo "	\$(AT)(cd ${destDir}; jar cf ../../lib/${jarName}.jar ${cList} )"

if [  "${MAKE_PURE}" != "" -o "${MAKE_PURIFY}" != "" ]
then 
    if [  "${RATIONAL_DIR}" != "" ]
	then
	echo "	\$(AT)(cd ${destDir}; jar uf ../../lib/${jarName}.jar com/rational )"
    fi
fi

    if [ "${debug}" == "on" ]
	then
	echo "	\$(AT)cd ..; jar uf lib/${jarName}.jar ${sList}"
    fi

    if [ "${extraList}" != "" ]
	then
        echo "	\$(AT)jar uf ../lib/${jarName}.jar ${extraList} "
    fi
   

else
    echo "../lib/${jarName}.jar: "
    echo "	@echo \"== Making ${jarName}.jar\""
    echo "	@echo \" ${jarName}_DIR is not defined. Nothing to do here.\""
    echo "	@echo \" Makefile should define the action for target  '${jarName}:'\""
fi
# ___oOo___
