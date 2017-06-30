/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * @file
 * Dynamically resizing memory buffer.
 *
 * A Dynamic Buffer is a raw buffer with automatic memory management.\n
 * It can be used to store any type of data, such as numbers, images, etc...\n
 * Some specialized methods are also provided to easily store a null-terminated
 * string, as well as several '\\n' terminated lines.
 *
 * A Dynamic Buffer provide the following data manipulation capabilities :
 * @li loading from and saving to files,
 * @li insert and append,
 * @li replace and delete.
 *
 * @warning A Dynamic Buffer <b> must be initialised and destroyed </b> before
 * and after use with miscDynBufInit() and miscDynBufDestroy() functions.
 *
 * \n @b Code @b Example:
 * \n A C program using a Dynamic Buffer.
 * @code
 * #include "miscDynBuf.h"
 *
 * int main (int argc, char *argv[])
 * {
 *     miscDYN_BUF dynBuf;
 *     char tab1[3] = {0, 1, 2};
 *
 *     /# Initialise the Dynamic Buffer, MANDATORY before Dynamic Buffer use #/
 *     miscDynBufInit(&dynBuf);
 *
 *     /# Add bytes at the end of the Dynamic Buffer #/
 *     miscDynBufAppendBytes(&dynBuf, (char*)tab1, 3 * sizeof(int));
 *     .
 *     . ...
 *     .
 *     char tab2[7] = {3, 4, 5, 6, 7, 8, 9};
 *     miscDynBufAppendBytes(&dynBuf, (char*)tab2, 7 * sizeof(int));
 *     .
 *     . ...
 *     .
 *     /# Reset a Dynamic Buffer #/
 *     miscDynBufReset(&dynBuf);
 *
 *     /# Add a string at the end of the Dynamic Buffer #/
 *     char *tmp = "bytes to";
 *     miscDynBufAppendString(&dynBuf, tmp);
 *     tmp = " append...";
 *     miscDynBufAppendString(&dynBuf, tmp);
 *     printf("DynBuf contains '%s'.\n", miscDynBufGetBuffer(&dynBuf));
 *
 *     /# Destroy the Dynamic Buffer, MANDATORY after Dynamic Buffer use #/
 *     miscDynBufDestroy(&dynBuf);
 *
 *     exit (EXIT_mcsSUCCESS);
 * }
 * @endcode
 */


/* Needed to preclude warnings on popen() and pclose() */
#define  _BSD_SOURCE 1

/*
 * System Headers
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


/*
 * MCS Headers
 */
#include "mcs.h"
#include "err.h"


/*
 * Local Headers
 */
#include "miscDynBuf.h"
#include "miscString.h"
#include "miscPrivate.h"
#include "miscErrors.h"

/*
 * Local functions declaration
 */
static mcsLOGICAL miscDynBufIsInitialised(const miscDYN_BUF *dynBuf);

static mcsCOMPL_STAT miscDynBufChkPositionParam(const miscDYN_BUF *dynBuf,
                                                const miscDynSIZE  position);

static mcsCOMPL_STAT miscDynBufChkFromToParams(const miscDYN_BUF *dynBuf,
                                               const miscDynSIZE  from,
                                               const miscDynSIZE  to);

static miscDynSIZE miscDynBufChkStringParam(const char *str);


/*
 * Local functions definition
 */

/**
 * Verify if a Dynamic Buffer has already been initialized.
 *
 * This function is only used internally.
 *
 * @param dynBuf address of Dynamic Buffer structure
 *
 * @return mcsTRUE if the given Dynamic Buffer has already been initialized,
 * mcsFALSE otherwise.
 */
static mcsLOGICAL miscDynBufIsInitialised(const miscDYN_BUF *dynBuf)
{
    /* Test the 'dynBuf' pointer validity */
    if (dynBuf == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "dynBuf");
        return mcsFALSE;
    }

    /*
     * Test the 'pointer to itself' and 'structure identifier magic number'
     * validity...
     */
    if (dynBuf->thisPointer != dynBuf ||
            dynBuf->magicStructureId != miscDYN_BUF_MAGIC_STRUCTURE_ID)
    {
        return mcsFALSE;
    }

    return mcsTRUE;
}

/**
 * Verify if a Dynamic Buffer has already been initialized, and if the given
 * 'position' is correct (eg. inside the Dynamic Buffer range).
 *
 * This function is only used internally by funtions receiving 'position'
 * parameter.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param position a position inside the Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
static mcsCOMPL_STAT miscDynBufChkPositionParam(const miscDYN_BUF *dynBuf,
                                                const miscDynSIZE  position)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return mcsFAILURE;
    }

    /* Test the position parameter validity... */
    if (position < miscDYN_BUF_BEGINNING_POSITION ||
            position > dynBuf->storedBytes)
    {
        errAdd(miscERR_DYN_BUF_BAD_POSITION, "position");
        return mcsFAILURE;
    }

    return mcsSUCCESS;
}

/**
 * Verify if a Dynamic Buffer has already been initialized, and if the given
 * 'from' and 'to' position are correct (eg. inside the Dynamic Buffer range,
 * and 'from' parameterlower than 'to' parameter).
 *
 * This function is only used internally by funtions receiving 'from' and 'to'
 * parameters.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param from a position inside the Dynamic Buffer
 * @param to a position inside the Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
static mcsCOMPL_STAT miscDynBufChkFromToParams(const miscDYN_BUF *dynBuf,
                                               const miscDynSIZE  from,
                                               const miscDynSIZE  to)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return mcsFAILURE;
    }

    /* Test the 'from' parameter validity */
    if (from < miscDYN_BUF_BEGINNING_POSITION || from > dynBuf->storedBytes)
    {
        errAdd(miscERR_DYN_BUF_BAD_POSITION, "from");
        return mcsFAILURE;
    }

    /* Test the 'to' parameter validity */
    if ((to < miscDYN_BUF_BEGINNING_POSITION) || (to > dynBuf->storedBytes))
    {
        errAdd(miscERR_DYN_BUF_BAD_POSITION, "to");
        return mcsFAILURE;
    }

    /* Test the 'from' and 'to' parameters validity against each other */
    if (to < from)
    {
        errAdd(miscERR_DYN_BUF_BAD_FROM_TO);
        return mcsFAILURE;
    }

    return mcsSUCCESS;
}

/**
 * Verify if a received string (a null terminated char array) is valid or not.
 *
 * @param str address of the string, already allocated extern buffer
 *
 * @return string length, or 0 if it is not valid
 */
static miscDynSIZE miscDynBufChkStringParam(const char *str)
{
    /* Test the 'str' parameter validity */
    if (str == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "str");
        return 0;
    }

    /*
     * Return the number of bytes stored in the received string including its
     * ending '\0'
     */
    return (strlen(str) + 1);
}


/*
 * Public functions definition
 */

/**
 * Initialize a Dynamic Buffer.
 *
 * @warning A Dynamic Buffer <b> must be initialised </b> before use.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufInit(miscDYN_BUF *dynBuf)
{
    /* Test the 'dynBuf' parameter validity... */
    if (dynBuf == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "dynBuf");
        return mcsFAILURE;
    }

    /* Initialize all the structure with '0' */
    memset(dynBuf, 0, sizeof (miscDYN_BUF));

    /* Set its 'pointer to itself' correctly */
    dynBuf->thisPointer = dynBuf;

    /* Set its 'structure identifier magic number' correctly */
    dynBuf->magicStructureId = miscDYN_BUF_MAGIC_STRUCTURE_ID;

    /* Set its 'comment pattern' to nothing */
    dynBuf->commentPattern[0] = '\0';

    return mcsSUCCESS;
}

mcsCOMPL_STAT miscDynBufReserve(miscDYN_BUF       *dynBuf,
                                const miscDynSIZE  length)
{
    /* Expand the received Dynamic Buffer size */
    miscDynSIZE bytesToAlloc;
    bytesToAlloc = length - (dynBuf->allocatedBytes - dynBuf->storedBytes);

    /* If the current buffer already has sufficient length... */
    if (bytesToAlloc <= 0)
    {
        /* Do nothing */
        return mcsSUCCESS;
    }
    return miscDynBufAlloc(dynBuf, bytesToAlloc);
}

/**
 * Smartly allocate and add a number of bytes to a Dynamic Buffer.
 *
 * If the Dynamic Buffer already has some allocated bytes, its length is
 * automatically expanded, with the previous content remaining untouched.
 *
 * Newly allocated bytes will all be set to '0'.
 *
 * @remark The call to this function is optional, as a Dynamic Buffer will
 * expand itself on demand when invoquing other miscDynBuf functions as
 * miscDynBufAppendBytes(), miscDynBufInsertBytesAt(), etc...
 * So, this function call is only usefull when you know by advance the maximum
 * bytes length the Dynamic Buffer could reach accross its entire life, and thus
 * want to minimize the CPU time spent to expand the Dynamic Buffer
 * allocated memory on demand.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param length number of bytes by which the Dynamic Buffer should be expanded
 * (if less than or equal to 0, nothing is done).
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufAlloc(miscDYN_BUF *dynBuf, const miscDynSIZE length)
{
    /* If the current buffer already has sufficient length... */
    if (length <= 0)
    {
        /* Do nothing */
        return mcsSUCCESS;
    }

    char *newBuf = NULL;

    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /* new total size */
    miscDynSIZE newAllocSize = 0;
    miscDynSIZE minNewSize = 0;

    /* If the buffer has no memory allocated... */
    if (dynBuf->allocatedBytes == 0)
    {
        /* allocate at least 512 bytes */
        newAllocSize = mcsMAX(length, 512);

        /* Allocate the desired length */
        if ((dynBuf->dynBuf = calloc(newAllocSize, sizeof (char))) == NULL)
        {
            printf("calloc failed with size = %lu\n", newAllocSize);
            errAdd(miscERR_ALLOC);
            return mcsFAILURE;
        }
    }
    else
    {
        /* The buffer needs to be expanded : Get more memory */
        minNewSize = dynBuf->allocatedBytes + length;

        /* reallocate at least 512 bytes or needed length */
        newAllocSize = mcsMAX(minNewSize, 512);
        /* enlarge buffer enough to avoid excessive reallocation */
        if (minNewSize < 4 * 1024 * 1024) /* 4Mb */
        {
            /* grow by x2 */
            newAllocSize = mcsMAX(newAllocSize, minNewSize * 2);
        }
        else if (minNewSize < 64 * 1024 * 1024) /* 64Mb */
        {
            /* grow by x1.5 */
            newAllocSize = mcsMAX(newAllocSize, (minNewSize * 3) / 2);
        }
        else
        {
            /* grow by 10% */
            newAllocSize = mcsMAX(newAllocSize, minNewSize + minNewSize / 10);
        }

        /* printf("miscDynBufAlloc(realloc) %d reserved; %d needed\n", newAllocSize, minNewSize); */

        if ((newBuf = realloc(dynBuf->dynBuf, newAllocSize)) == NULL)
        {
            printf("realloc failed with size = %lu\n", newAllocSize);
            errAdd(miscERR_ALLOC);
            return mcsFAILURE;
        }

        /* Store the expanded buffer address */
        dynBuf->dynBuf = newBuf;
    }

    /* Set the buffer allocated length value */
    dynBuf->allocatedBytes = newAllocSize;

    return mcsSUCCESS;
}

/**
 * Deallocate the unused allocated memory of a Dynamic Buffer.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufStrip(miscDYN_BUF *dynBuf)
{
    char *newBuf = NULL;

    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /* If the received Dynamic Buffer needs to be stripped */
    if (dynBuf->storedBytes < dynBuf->allocatedBytes)
    {
        /* If the Dynamic Buffer needs to be completely freed */
        if (dynBuf->storedBytes == 0)
        {
            /* De-allocate it */
            if (dynBuf->dynBuf == NULL)
            {
                errAdd(miscERR_NULL_PARAM, "dynBuf->dynBuf");
                return mcsFAILURE;
            }

            free(dynBuf->dynBuf);
        }
        else
        {
            /* Give back the unused memory */
            if ((newBuf = realloc(dynBuf->dynBuf, dynBuf->storedBytes)) == NULL)
            {
                errAdd(miscERR_ALLOC);
                return mcsFAILURE;
            }
        }

        /* Store the new buffer address */
        dynBuf->dynBuf = newBuf;

        /* Update the buffer allocated length value */
        dynBuf->allocatedBytes = dynBuf->storedBytes;
    }

    return mcsSUCCESS;
}

/**
 * Reset a Dynamic Buffer.
 *
 * Possibly allocated memory remains untouched, until the reseted Dynamic Buffer
 * is reused to store new data.
 *
 * @param dynBuf the address of a Dynamic Buffer structure
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufReset(miscDYN_BUF *dynBuf)
{
    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /*
     * Update the Dynamic Buffer stored bytes number value, to make it act as if
     * there were nothing in the buffer
     */
    dynBuf->storedBytes = 0;

    if (dynBuf->allocatedBytes != 0)
    {
        /* ensure first char is '\0' */
        dynBuf->dynBuf[0] = '\0';
    }

    return mcsSUCCESS;
}

/**
 * Destroy a Dynamic Buffer.
 *
 * Possibly allocated memory is freed and zeroed - so be sure that it is
 * desirable to delete the data contained inside the buffer.
 *
 * @warning A Dynamic Buffer <b> must be destroyed </b> after use.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufDestroy(miscDYN_BUF *dynBuf)
{
    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /* If some memory was allocated... */
    if (dynBuf->allocatedBytes != 0)
    {
        /* Free the allocated memory */
        free(dynBuf->dynBuf);
    }

    /* Initialize all the structure with '0' */
    memset((char *) dynBuf, 0, sizeof (miscDYN_BUF));

    return mcsSUCCESS;
}

/**
 * Give back the number of bytes stored in a Dynamic Buffer.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param storedBytes address of the extern variable which will contain the
 * number of stored bytes in the Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufGetNbStoredBytes(const miscDYN_BUF *dynBuf,
                                         miscDynSIZE       *storedBytes)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return mcsFAILURE;
    }

    /* Return the Dynamic Buffer stored bytes number */
    *storedBytes = dynBuf->storedBytes;

    return mcsSUCCESS;
}

/**
 * Give back the number of bytes allocated in a Dynamic Buffer.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param allocatedBytes address of the extern variable which will contain
 * the number of allocated bytes in the Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufGetNbAllocatedBytes(const miscDYN_BUF *dynBuf,
                                            miscDynSIZE       *allocatedBytes)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return mcsFAILURE;
    }

    /* Return the Dynamic Buffer allocated bytes number */
    *allocatedBytes = dynBuf->allocatedBytes;

    return mcsSUCCESS;
}

/**
 * Return the Dynamic Buffer internal bytes buffer.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 *
 * @return a pointer to the Dynamic Buffer internal buffer, or NULL if an error
 * occurred
 */
char* miscDynBufGetBuffer(const miscDYN_BUF *dynBuf)
{
    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return ((char*) NULL);
    }

    /* Return the Dynamic Buffer buffer address */
    return dynBuf->dynBuf;
}

/**
 * Give back a Dynamic Buffer byte stored at a given position.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param byte address of the receiving, already allocated extern byte that will
 * hold the seeked Dynamic Buffer byte
 * @param position position of the Dynamic Buffer seeked byte
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufGetByteAt(const miscDYN_BUF *dynBuf,
                                  char              *byte,
                                  const miscDynSIZE  position)
{
    /* Test the 'dynBuf' and 'position' parameters validity */
    if (miscDynBufChkPositionParam(dynBuf, position) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Test the 'write to' byte buffer address parameter validity */
    if (byte == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "byte");
        return mcsFAILURE;
    }

    /* Write back the seeked character inside the byte buffer parameter */
    *byte = dynBuf->dynBuf[position - miscDYN_BUF_BEGINNING_POSITION];

    return mcsSUCCESS;
}

/**
 * Give back a part of a Dynamic Buffer in an already allocated extern buffer.
 *
 * @warning
 * - You must ensure by yourself that the extern buffer has enough memory
 * allocated to hold all the requested data before calling this function.
 * - The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param bytes address of the receiving, already allocated extern buffer
 * @param from first Dynamic Buffer byte to be copied in the extern buffer
 * @param to last Dynamic Buffer byte to be copied in the extern buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufGetBytesFromTo(const miscDYN_BUF *dynBuf,
                                       char              *bytes,
                                       const miscDynSIZE  from,
                                       const miscDynSIZE  to)
{
    /* Test the 'bytes' parameter validity */
    if (bytes == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "bytes");
        return mcsFAILURE;
    }

    /* Test the 'dynBuf', 'from' and 'to' parameters validity */
    if (miscDynBufChkFromToParams(dynBuf, from, to) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Compute the number of Dynamic Buffer bytes to be copied */
    miscDynSIZE lengthToCopy = (to - from) + 1;

    /* Compute the first 'to be read' Dynamic Buffer byte position */
    char *positionToReadFrom = dynBuf->dynBuf +
            (from - miscDYN_BUF_BEGINNING_POSITION);

    /* Copy the Dynamic Buffer desired part in the extern buffer */
    if (memcpy(bytes, positionToReadFrom, lengthToCopy) == NULL)
    {
        errAdd(miscERR_ALLOC);
        return mcsFAILURE;
    }

    return mcsSUCCESS;
}

/**
 * Give back a part of a Dynamic Buffer as a null terminated string in an
 * already allocated extern buffer.
 *
 * @warning
 * - You must ensure by yourself that the extern buffer has enough memory
 * allocated to hold all the requested data before calling this function.
 * - The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param str address of the receiving, already allocated extern buffer
 * @param from first Dynamic Buffer byte to be copied in the extern string
 * @param to last Dynamic Buffer byte to be copied in the extern string
 *
 * \return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 *
 * \n
 * @sa miscDynBufGetBytesFromTo().
 */
mcsCOMPL_STAT miscDynBufGetStringFromTo(const miscDYN_BUF *dynBuf,
                                        char              *str,
                                        const miscDynSIZE  from,
                                        const miscDynSIZE  to)
{
    /* Get the requested bytes array from the Dynamic Buffer */
    if (miscDynBufGetBytesFromTo(dynBuf, str, from, to) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Compute the 'str' buffer length */
    miscDynSIZE stringLength = (to - miscDYN_BUF_BEGINNING_POSITION) -
            (from - miscDYN_BUF_BEGINNING_POSITION);

    /* Add an '\0' at the end of the received result */
    str[stringLength + 1] = '\0';

    return mcsSUCCESS;
}

/**
 * Return the comment pattern string used to characterize lines to be skipped
 * when running throughout the Dynamic Buffer line by line.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 *
 * @return a pointer to a Dynamic Buffer comment pattern, or NULL if an error
 * occurred
 */
const char* miscDynBufGetCommentPattern(const miscDYN_BUF *dynBuf)
{
    /* Initialize the received Dynamic Buffer if it is not */
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return ((const char *) NULL);
    }

    /* Return the Dynamic Buffer buffer address */
    return dynBuf->commentPattern;
}

/**
 * Define the comment pattern used to characterize lines to be skipped when
 * running throughout the Dynamic Buffer line by line.
 *
 * If a NULL value is specified, no line will be skipped while using
 * miscDynBufGetNextLine().
 *
 * @remark Comment pattern doesn't have to be defined explicitly with this
 * function if miscDynBufLoadFile() is used (as the comment pattern can be
 * specified directly by one of this function parameter).\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param commentPattern a null-terminated string defining the comment pattern,
 * or a NULL value to reset it
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufSetCommentPattern(miscDYN_BUF *dynBuf,
                                          const char  *commentPattern)
{
    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /* If the commentPattern parameter is undefined */
    if (commentPattern == NULL)
    {
        dynBuf->commentPattern[0] = '\0';
    }
    else
    {
        /* Store the commentPattern in the Dynamic Buffer */
        strncpy(dynBuf->commentPattern,
                commentPattern,
                sizeof (dynBuf->commentPattern));
        dynBuf->commentPattern[sizeof (dynBuf->commentPattern) - 1] = '\0';
    }

    return mcsSUCCESS;
}

/**
 * Return the next line of a Dynamic Buffer.
 *
 * Retrieves the next line following the given @em currentPos position in the
 * Dynamic Buffer, and copies its content (untill '\\n') into the @em nextLine
 * buffer. If there is no new line (no '\\n'), it copies everything left in the
 * @em nextLine buffer.
 *
 * If the given position is a NULL pointer, the search starts from the beginning
 * of the buffer.
 *
 * If @em skipCommentFlag is set to mcsTRUE, comment lines (lines starting with
 * the pattern defined either when loading the file with miscDynBufLoadFile() or
 * by using miscDynBufSetCommentPattern()) are skipped.
 *
 * @warning The returned next line could appear truncated if it is longer than
 * @em maxLineLength bytes.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param currentPos position from which the next line will be searched, or NULL
 * to begin on the first line of the buffer.
 * @param nextLine address of the receiving, already allocated extern buffer in
 * which the next line will be stored.
 * @param maxLineLength maximum extern buffer capacity.
 * @param skipCommentFlag boolean specifying whether the line beginning by the
 * Dynamic Buffer comment pattern should be skipped or not
 *
 * @return a pointer to the new buffer position to be used to get the next line,
 * or NULL whether an error occurred or the end of the buffer has been reached.
 *
 * \n
 * @ex
 * @code
 * miscDYN_BUF dynBuf;
 *
 * /# Load file, where comment lines start with hash sign #/
 * if (miscDynBufLoadFile(&dynBuf, "myFile", "#") == mcsFAILURE)
 * {
 *     /# Handle error #/
 *     return mcsFAILURE;
 * }
 *
 * /# Get all (from the beginning) the lines, skipping the comment lines #/
 * char *currPtr = NULL;
 * mcsSTRING1024 line;
 * while ((currPtr = miscDynBufGetNextLine(&dynBuf, currPtr, line,
 *                                         sizeof(line), mcsTRUE) !=
 *                                         NULL))
 * {
 *     /# Print out line content #/
 *     printf("%s\n", line);
 * }
 * @endcode
 */
const char* miscDynBufGetNextLine(const miscDYN_BUF *dynBuf,
                                  const char        *currentPos,
                                  char              *nextLine,
                                  const mcsUINT32    maxLineLength,
                                  const mcsLOGICAL   skipCommentFlag)
{
    /* Initialize the received Dynamic Buffer if it is not */
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        errAdd(miscERR_DYN_BUF_NOT_INITIALIZED);
        return NULL;
    }

    /* Get the current Dynamic Buffer internal buffer pointer */
    char* bufferStart = miscDynBufGetBuffer(dynBuf);
    if (bufferStart == NULL)
    {
        errAdd(miscERR_DYN_BUF_IS_EMPTY);
        return NULL;
    }

    /* Get the current Dynamic Buffer internal buffer length */
    miscDynSIZE length;
    if (miscDynBufGetNbStoredBytes(dynBuf, &length) == mcsFAILURE)
    {
        return NULL;
    }
    char *bufferEnd = bufferStart + length;

    /* If buffer is empty */
    if (length == 0)
    {
        return NULL;
    }

    /* If the given current Line Pointer is outside of the Dynamic Buffer */
    if ((currentPos != NULL) &&
            ((currentPos < bufferStart) || (currentPos > bufferEnd)))
    {
        return NULL;
    }

    /* Gets the next '\n' occurence after currentPos */
    mcsLOGICAL nextLineFound = mcsFALSE;
    do
    {
        /* Get next line in buffer */
        if (currentPos != NULL)
        {
            /* If there is no more line, return */
            currentPos = strchr(currentPos, '\n');
            if ((currentPos == NULL) || ((currentPos + 1) == bufferEnd))
            {
                return NULL;
            }

            /* Else skip CR character */
            currentPos++;
        }
        else
        {
            /* Restart from beginning of buffer */
            currentPos = bufferStart;
        }

        /* If it is a comment line and it should be skipped, skip it */
        if ((skipCommentFlag == mcsFALSE) ||
                (miscIsCommentLine(currentPos, miscDynBufGetCommentPattern(dynBuf))
                == mcsFALSE))
        {
            nextLineFound = mcsTRUE;
        }
    }
    while (nextLineFound == mcsFALSE);

    /* Copy next line into buffer */
    miscDynSIZE i       = 0;
    miscDynSIZE bufLen  = bufferEnd - currentPos;
    miscDynSIZE lineLen = maxLineLength - 1;

    while ((i < bufLen) &&
            (i < lineLen) &&
            (currentPos[i] != '\n'))
    {
        /* Copy current character */
        nextLine[i] = currentPos[i];

        /* Go to the next one */
        i++;
    }
    nextLine[i] = '\0';

    return currentPos;
}

/**
 * Return the next comment line of a Dynamic Buffer.
 *
 * This function works the same way as miscDynBufGetNextLine(), but for comment
 * lines.
 *
 * @param dynBuf the address of a Dynamic Buffer structure
 * @param currentPos the  position from which the next comment line will be
 * searched, or NULL pointer to begin at the first line of the buffer.
 * @param nextCommentLine address of the receiving, already allocated extern
 * buffer in which the next comment line will be stored.
 * @param maxCommentLineLength maximum extern buffer capacity.
 *
 * @return a pointer to the new buffer position used to get the comment next
 * line, or NULL either if an error occurred or end of the buffer is reached.
 *
 * \n
 * @sa miscDynBufGetNextLine().
 */
const char* miscDynBufGetNextCommentLine(const miscDYN_BUF *dynBuf,
                                         const char        *currentPos,
                                         char              *nextCommentLine,
                                         const mcsUINT32    maxCommentLineLength)
{
    /* Skip lines, until it reaches a comment one (or the end of the buffer) */
    do
    {
        currentPos = miscDynBufGetNextLine(dynBuf, currentPos, nextCommentLine,
                                           maxCommentLineLength, mcsFALSE);
    }
    while ((currentPos != NULL) &&
            (miscIsCommentLine(currentPos, miscDynBufGetCommentPattern(dynBuf))
            == mcsFALSE));

    return currentPos;
}

/**
 * Run the given shell command and store its STDOUT into a Dynamic Buffer.
 *
 * @warning
 * - The given Dynamic Buffer content (if any) will be @em destroyed by this
 * function call.
 *
 * @param dynBuf address of a Dynamic Buffer structure in which STDOUT will be put as a null-terminated string.
 * @param command the shell command that should be performed.
 *
 * @return 0 on successful completion. Otherwise the return code as 8-bits integer is returned.
 */
mcsINT8 miscDynBufExecuteCommand(miscDYN_BUF *dynBuf,
                                 const char  *command)
{
    /* Reset the received Dynamic Buffer first */
    if (miscDynBufReset(dynBuf) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Executing the command */
    FILE* process = popen(command, "r");
    if (process == NULL)
    {
        errAdd(miscERR_COMMAND_EXEC, command);
        return mcsFAILURE;
    }

    /* Keep reading command result, until an error occurs */
    mcsSTRING1024 tempBuffer;
    miscDynSIZE tempBufferLength = sizeof (tempBuffer);
    miscDynSIZE totalReadSize = 0;
    mcsCOMPL_STAT completionStatus = mcsSUCCESS;
    while (feof(process) == 0)
    {
        /* Put the command result in the temp buffer */
        totalReadSize = fread(tempBuffer, 1, tempBufferLength, process);

        /* Put temp buffer content in the true output buffer */
        if (miscDynBufAppendBytes(dynBuf, tempBuffer, totalReadSize) == mcsFAILURE)
        {
            completionStatus = mcsFAILURE;
            break;
        }
    }

    if (completionStatus == mcsSUCCESS)
    {
        /* Add trailing '\0' in order to be able to read output as a string */
        completionStatus = miscDynBufAppendBytes(dynBuf, "\0", 1);
    }

    /* pclose() status check */
    int pcloseStatus = pclose(process);
    if (pcloseStatus == -1)
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_FUNC_CALL, "pclose", mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }

    /* Command execution status check */
    int commandStatus = WEXITSTATUS(pcloseStatus);
    if (commandStatus != 0)
    {
        errAdd(miscERR_COMMAND_STATUS, command, commandStatus);
        return (mcsINT8) commandStatus;
    }

    return completionStatus;
}

/**
 * Load the content of a specified text file into a Dynamic Buffer.
 *
 * A comment pattern can be defined directly through this function call. It then
 * allows to handle comment lines specifically with miscDynBufGetNextLine() and
 * miscDynBufGetNextCommentLine(), without explicitly calling
 * miscDynBufSetCommentPattern() function before.
 *
 * @warning
 * - The given Dynamic Buffer content (if any) will be @em destroyed by this
 * function call.
 * - The given file path must have been @em resolved before this function call.
 * See miscResolvePath() documentation for more information.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param fileName path specifying the file to be loaded in the Dynamic Buffer
 * @param commentPattern a null-terminated string defining the comment pattern,
 * or a NULL value to leave it blank
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufLoadFile(miscDYN_BUF *dynBuf,
                                 const char  *fileName,
                                 const char  *commentPattern)
{
    /* Reset the received Dynamic Buffer first */
    if (miscDynBufReset(dynBuf) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Get the file size */
    struct stat fileStats;
    if (stat(fileName, &fileStats) == -1)
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_DYN_BUF_COULD_NOT_READ_FILE, fileName, mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }
    size_t fileSize = fileStats.st_size;

    /* Allocate some memory to store the file content */
    if (miscDynBufReserve(dynBuf, fileSize + 1) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Open the specified text file */
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_DYN_BUF_COULD_NOT_READ_FILE, fileName, mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }

    /* Get all the content of the specified text file */
    size_t readSize = fread((void*) dynBuf->dynBuf, sizeof (char),
                            fileSize, file);

    /* Test if the file seems to be loaded correctly */
    if ((readSize != fileSize) || (dynBuf->dynBuf == NULL))
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_DYN_BUF_COULD_NOT_READ_FILE, fileName, mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }

    /* Close the text file */
    fclose(file);

    /* Update the Dynamic Buffer internal counters */
    dynBuf->dynBuf[fileSize] = '\0';
    dynBuf->storedBytes = fileSize + 1;

    /* Set the Dynamic Buffer comment pattern */
    return (miscDynBufSetCommentPattern(dynBuf, commentPattern));
}

/**
 * Save the first n bytes of a Dynamic Buffer content in a specified file.
 *
 * @warning
 * - The given file will be over-written on each call.
 * - The given file path must have been @em resolved before this function call.
 * See miscResolvePath() documentation for more information.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param length the number of leading bytes to be saved in file
 * @param fileName path specifying the file to be over-written with the Dynamic
 * Buffer content
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufSavePartInFile(const miscDYN_BUF *dynBuf,
                                       const miscDynSIZE length,
                                       const char        *fileName)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        return mcsFAILURE;
    }

    /* Get the number of bytes stored in the Dynamic Buffer */
    miscDynSIZE dynBufSize = 0;
    if (miscDynBufGetNbStoredBytes(dynBuf, &dynBufSize) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Cap the given length value to the number of stored bytes  */
    dynBufSize = mcsMIN(length, dynBufSize);

    /* Open (or create)  the specified text file in 'write' mode */
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_DYN_BUF_COULD_NOT_SAVE_FILE, fileName, mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }

    /* Put all the content of the Dynamic Buffer in the text file */
    size_t savedSize = fwrite((void*) miscDynBufGetBuffer(dynBuf), sizeof (char),
                              dynBufSize, file);

    /* Test if the Dynamic Buffer has been saved correctly */
    if (savedSize != dynBufSize)
    {
        mcsSTRING1024 errorMsg;
        errAdd(miscERR_DYN_BUF_COULD_NOT_SAVE_FILE, fileName, mcsStrError(errno, errorMsg));
        return mcsFAILURE;
    }

    /* Close the text file */
    fclose(file);

    return mcsSUCCESS;
}

/**
 * Save the whole Dynamic Buffer content in a specified text file.
 *
 * @warning
 * - The given file will be over-written on each call.
 * - The given file path must have been @em resolved before this function call.
 * See miscResolvePath() documentation for more information.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param fileName path specifying the file to be over-written with the Dynamic
 * Buffer content
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufSaveInFile(const miscDYN_BUF *dynBuf,
                                   const char        *fileName)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        return mcsFAILURE;
    }

    /* Get the Dynamic Buffer size to be saved */
    miscDynSIZE dynBufSize;
    if (miscDynBufGetNbStoredBytes(dynBuf, &dynBufSize) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Save the Dynamic Buffer */
    if (miscDynBufSavePartInFile(dynBuf, dynBufSize, fileName) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    return mcsSUCCESS;
}

/**
 * Save the Dynamic Buffer content as an ASCII string in a specified text file.
 *
 * If the given Dynamic Buffer holds a C-string ending with an '\\0' character,
 * all the characters but this '\\0' will be saved in file.
 *
 * @warning
 * - The given file will be over-written on each call.
 * - The given file path must have been @em resolved before this function call.
 * See miscResolvePath() documentation for more information.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param fileName path specifying the file to be over-written with the Dynamic
 * Buffer content
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufSaveInASCIIFile(const miscDYN_BUF *dynBuf,
                                        const char        *fileName)
{
    /* Verify the Dynamic Buffer initialisation state */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        return mcsFAILURE;
    }

    /* Get the Dynamic Buffer size to be saved */
    miscDynSIZE dynBufSize;
    if (miscDynBufGetNbStoredBytes(dynBuf, &dynBufSize) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Retrieve the last character of the Dynamic Buffer */
    char lastCharacter;
    if (miscDynBufGetByteAt(dynBuf, &lastCharacter, dynBufSize) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* If the last character is an '\0' */
    if (lastCharacter == '\0')
    {
        /* Skip it of the file save */
        dynBufSize--;
    }

    /* Save the Dynamic Buffer with or without its last character */
    if (miscDynBufSavePartInFile(dynBuf, dynBufSize, fileName) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    return mcsSUCCESS;
}

/**
 * Replace a Dynamic Buffer byte at a given position.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param byte byte to be written in the Dynamic Buffer
 * @param position position of the Dynamic Buffer byte to be over-written
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufReplaceByteAt(miscDYN_BUF      *dynBuf,
                                      const char        byte,
                                      const miscDynSIZE position)
{
    /* Test the 'dynBuf' and 'position' parameters validity */
    if (miscDynBufChkPositionParam(dynBuf, position) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Overwrite the specified Dynamic Buffer byte with the received one */
    dynBuf->dynBuf[position - miscDYN_BUF_BEGINNING_POSITION] = byte;

    return mcsSUCCESS;
}

/**
 * Replace a Dynamic Buffer bytes range by a given bytes buffer content.
 *
 * The Dynamic Buffer replaced bytes will be over-written. The over-written
 * range can be smaller or bigger than the extern buffer bytes content. If the
 * range is bigger than the extern buffer bytes content, the Dynamic Buffer will
 * be expanded accordinaly.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param bytes address of the extern buffer bytes to be written in the Dynamic
 * Buffer
 * @param length number of extern buffer bytes to be written in the Dynamic
 * Buffer
 * @param from position of the first Dynamic Buffer byte to be substituted
 * @param to position of the last Dynamic Buffer byte to be substituted
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufReplaceBytesFromTo(miscDYN_BUF      *dynBuf,
                                           const char       *bytes,
                                           const miscDynSIZE length,
                                           const miscDynSIZE from,
                                           const miscDynSIZE to)
{
    /* If nothing to replace */
    if (length <= 0)
    {
        /* Return immediately */
        return mcsSUCCESS;
    }

    /* Test the 'bytes' parameter validity */
    if (bytes == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "bytes");
        return mcsFAILURE;
    }

    /* Test the 'dynBuf', 'from' and 'to' parameters validity */
    if (miscDynBufChkFromToParams(dynBuf, from, to) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /*
     * Compute the number of bytes by which the Dynamic Buffer should be
     * expanded and allocate them
     */
    miscDynSIZE bytesToAlloc = length -
            (((to - miscDYN_BUF_BEGINNING_POSITION) -
            (from - miscDYN_BUF_BEGINNING_POSITION)) + 1);
    if (miscDynBufAlloc(dynBuf, bytesToAlloc) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Compute the number of Dynamic Buffer bytes to be backed up */
    miscDynSIZE lengthToBackup = dynBuf->storedBytes -
            ((to - miscDYN_BUF_BEGINNING_POSITION) + 1);

    /* Compute the first 'to be backep up' Dynamic Buffer byte position */
    char *positionToBackup = dynBuf->dynBuf +
            ((to - miscDYN_BUF_BEGINNING_POSITION) + 1);

    /* Compute the first 'to be overwritten' Dynamic Buffer byte position */
    char *positionToWriteIn = dynBuf->dynBuf +
            (from - miscDYN_BUF_BEGINNING_POSITION);

    /* Move the 'not-to-be-overwritten' Dynamic Buffer bytes to their
     * definitive place
     */
    memmove(positionToWriteIn + length, positionToBackup, lengthToBackup);

    /* Copy the extern buffer bytes in the Dynamic Buffer */
    memcpy(positionToWriteIn, bytes, length);

    /* Update the Dynamic Buffer stored length value using the computed
     * signed 'bytesToAlloc' value
     */
    dynBuf->storedBytes += bytesToAlloc;

    return mcsSUCCESS;
}

/**
 * Replace a given range of Dynamic Buffer bytes by a given null-terminated
 * string without its ending '\\0'.
 *
 * This function works the same as miscDynBufReplaceBytesFromTo(), but with
 * null-terminated strings.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param str address of the extern string to be written in the Dynamic Buffer
 * @param from position of the first Dynamic Buffer byte to be substituted
 * @param to the position of the last Dynamic Buffer byte to be substituted
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufReplaceStringFromTo(miscDYN_BUF      *dynBuf,
                                            const char       *str,
                                            const miscDynSIZE from,
                                            const miscDynSIZE to)
{
    /* Test the 'str' parameter validity */
    miscDynSIZE stringLength;
    stringLength = miscDynBufChkStringParam(str);
    if (stringLength == 0)
    {
        return mcsFAILURE;
    }

    /* If the end of the Dynamic Buffer has to be replaced... */
    if (to == dynBuf->storedBytes)
    {
        /*
         * Increment the number of bytes to be copied from the string in order
         * to add the ending '\0' to the Dynamic Buffer
         */
        stringLength++;
    }

    /*
     * Replace Dynamic Buffer specified bytes with the string (with or
     * without its ending '\0')
     */
    return (miscDynBufReplaceBytesFromTo(dynBuf, str, stringLength - 1, from, to));
}

/**
 * Append a given bytes buffer contnent at the end of a Dynamic Buffer.
 *
 * Copy all the extern buffer bytes content at the end of the given Dynamic
 * Buffer.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param bytes address of the extern buffer bytes to be written at the end of
 * the Dynamic Buffer
 * @param length number of extern buffer bytes to be written at the end of the
 * Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufAppendBytes(miscDYN_BUF      *dynBuf,
                                    const char       *bytes,
                                    const miscDynSIZE length)
{
    /* If nothing to append */
    if (length <= 0)
    {
        /* Return immediately */
        return mcsSUCCESS;
    }

    /* Test the 'bytes' parameter validity */
    if (bytes == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "bytes");
        return mcsFAILURE;
    }

    /* Initialize the received Dynamic Buffer if it is not */
    if (miscDynBufIsInitialised(dynBuf) == mcsFALSE)
    {
        if (miscDynBufInit(dynBuf) == mcsFAILURE)
        {
            return mcsFAILURE;
        }
    }

    /* Expand the received Dynamic Buffer size */
    if (miscDynBufReserve(dynBuf, length) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Copy the extern buffer bytes at the end of the Dynamic Buffer */
    memcpy(dynBuf->dynBuf + dynBuf->storedBytes, bytes, length);

    /*
     * Update the Dynamic Buffer stored length value using the number of the
     * extern buffer bytes
     */
    dynBuf->storedBytes += length;

    return mcsSUCCESS;
}

/**
 * Append a given string content at the end of a Dynamic Buffer.
 *
 * Copy a null-terminated extern string content at the end of a Dynamic Buffer,
 * adding an '\\0' at the end of it.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param str address of the extern string content to be written at the end of
 * the Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufAppendString(miscDYN_BUF *dynBuf,
                                     const char  *str)
{
    /* Test the 'str' parameter validity */
    miscDynSIZE stringLength;
    stringLength = miscDynBufChkStringParam(str);
    if (stringLength == 0)
    {
        return mcsFAILURE;
    }

    /* Get the Dynamic Buffer stored bytes number */
    miscDynSIZE storedBytes;
    if (miscDynBufGetNbStoredBytes(dynBuf, &storedBytes) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* If the Dynamic Buffer already contain something... */
    if (storedBytes != 0)
    {
        /* Get the last character of the Dynamic Buffer */
        char lastDynBufChr = '\0';
        if (miscDynBufGetByteAt(dynBuf, &lastDynBufChr, storedBytes) == mcsFAILURE)
        {
            return mcsFAILURE;
        }

        /*
         * If the Dynamic Buffer was already holding a null-terminated string...
         */
        if (lastDynBufChr == '\0')
        {
            /* Remove the ending '\0' from the Dynamic Buffer */
            if (miscDynBufDeleteBytesFromTo(dynBuf, storedBytes, storedBytes) == mcsFAILURE)
            {
                return mcsFAILURE;
            }
        }
    }

    /* Append the string bytes, including its '\0' */
    return (miscDynBufAppendBytes(dynBuf, str, stringLength));
}

/**
 * Append a given line at the end of a Dynamic Buffer.
 *
 * Copy a carriage return ('\\n') followed by an extern null-terminated string
 * at the end of a Dynamic Buffer, adding an '\\0' at the end of it.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param line address of the extern string to be written at the end of a
 * Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufAppendLine(miscDYN_BUF *dynBuf,
                                   const char  *line)
{
    /* Test the 'line' parameter validity */
    miscDynSIZE lineLength;
    lineLength = miscDynBufChkStringParam(line);
    if (lineLength == 0)
    {
        return mcsFAILURE;
    }

    /* Get the Dynamic Buffer stored bytes number */
    miscDynSIZE storedBytes;
    if (miscDynBufGetNbStoredBytes(dynBuf, &storedBytes) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* If the Dynamic Buffer already contain something... */
    if (storedBytes != 0)
    {

        /* Get the last character of the Dynamic Buffer */
        char lastDynBufChr = '\0';
        if (miscDynBufGetByteAt(dynBuf, &lastDynBufChr, storedBytes) == mcsFAILURE)
        {
            return mcsFAILURE;
        }

        /*
         * If the Dynamic Buffer was already holding a null-terminated string...
         */
        if (lastDynBufChr == '\0')
        {
            /* Replace the ending '\0' by an '\n' */
            if (miscDynBufReplaceByteAt(dynBuf, '\n', storedBytes) == mcsFAILURE)
            {
                return mcsFAILURE;
            }
        }
    }

    /* Append the line, with its '\0' */
    return (miscDynBufAppendBytes(dynBuf, line, lineLength));
}

/**
 * Append a comment line at the end of a Dynamic Buffer.
 *
 * Copy a carriage return ('\\n') followed by the Dynamic Buffer @em internal
 * comment pattern and an extern null-terminated string at the end of a Dynamic
 * Buffer, adding an '\\0' at the  end of it.
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param line address of the extern string to be written at the end of a
 * Dynamic Buffer
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 *
 * \n
 * @sa miscDynBufGetCommentPattern() and miscDynBufSetCommentPattern()
 */
mcsCOMPL_STAT miscDynBufAppendCommentLine(miscDYN_BUF *dynBuf,
                                          const char  *line)
{
    /* Test the 'line' parameter validity */
    miscDynSIZE lineLength;
    lineLength = miscDynBufChkStringParam(line);
    if (lineLength == 0)
    {
        return mcsFAILURE;
    }

    /* Append the comment pattern to the Dynamic Buffer */
    if (miscDynBufAppendLine(dynBuf, miscDynBufGetCommentPattern(dynBuf)) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Append the line, with its '\0' */
    return (miscDynBufAppendString(dynBuf, line));
}

/**
 * Insert a given bytes buffer content in a Dynamic Buffer at a given position.
 *
 * The Dynamic Buffer original bytes following the insertion point are not
 * overwritten, but shiffted to make room for the bytes to be inserted.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param bytes pointer to the extern buffer bytes to be inserted
 * @param length number of extern buffer bytes to be inserted
 * @param position position of the first Dynamic Buffer byte to write
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufInsertBytesAt(miscDYN_BUF      *dynBuf,
                                      const char       *bytes,
                                      const miscDynSIZE length,
                                      const miscDynSIZE position)
{
    /* If nothing to insert */
    if (length <= 0)
    {
        /* Return immediately */
        return mcsSUCCESS;
    }

    /* Test the 'bytes' parameter validity */
    if (bytes == NULL)
    {
        errAdd(miscERR_NULL_PARAM, "bytes");
        return mcsFAILURE;
    }

    /* Test the 'dynBuf' and 'position' parameters validity */
    if (miscDynBufChkPositionParam(dynBuf, position) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Expand the received Dynamic Buffer size */
    if (miscDynBufReserve(dynBuf, length) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    /* Compute the number of Dynamic Buffer bytes to be backed up */
    miscDynSIZE lengthToBackup = dynBuf->storedBytes -
            (position - miscDYN_BUF_BEGINNING_POSITION);

    /* Compute the first 'to be overwritten' Dynamic Buffer byte position */
    char *positionToWriteIn = dynBuf->dynBuf +
            (position - miscDYN_BUF_BEGINNING_POSITION);

    /*
     * Move the 'not-to-be-overwritten' Dynamic Buffer bytes to their
     * definitive place
     */
    memmove(positionToWriteIn + length, positionToWriteIn, lengthToBackup);

    /* Copy the extern buffer bytes in the Dynamic Buffer */
    memcpy(positionToWriteIn, bytes, length);

    /*
     * Update the Dynamic Buffer stored length value using the extern buffer
     * bytes number
     */
    dynBuf->storedBytes += length;

    return mcsSUCCESS;
}

/**
 * Insert a given null-terminated string in a Dynamic Buffer at a given
 * position.
 *
 * Removes the given null-terminated string ending '\\0', and then works the
 * same as miscDynBufInsertBytesAt().
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param str pointer to the extern string to be inserted
 * @param position position of the first Dynamic Buffer byte to write
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufInsertStringAt(miscDYN_BUF      *dynBuf,
                                       const char       *str,
                                       const miscDynSIZE position)
{
    /* Test the 'str' parameter validity */
    miscDynSIZE stringLength;
    stringLength = miscDynBufChkStringParam(str);
    if (stringLength == 0)
    {
        return mcsFAILURE;
    }

    /* Insert the string without its ending '\0' in the Dynamic Buffer */
    return (miscDynBufInsertBytesAt(dynBuf, str, stringLength - 1, position));
}

/**
 * Delete a given range of a Dynamic Buffer bytes.
 *
 * @warning The first Dynamic Buffer byte has the position value defined by the
 * miscDYN_BUF_BEGINNING_POSITION macro.\n\n
 *
 * @param dynBuf address of a Dynamic Buffer structure
 * @param from position of the first Dynamic Buffer byte to be deleted
 * @param to position of the last Dynamic Buffer byte to be deleted
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT miscDynBufDeleteBytesFromTo(miscDYN_BUF      *dynBuf,
                                          const miscDynSIZE from,
                                          const miscDynSIZE to)
{
    /* Test the 'dynBuf', 'from' and 'to' parameters validity */
    if (miscDynBufChkFromToParams(dynBuf, from, to) == mcsFAILURE)
    {
        return mcsFAILURE;
    }

    const miscDynSIZE storedBytes = dynBuf->storedBytes;

    /* special case to remove last byte */
    if ((from == to) && (to == storedBytes))
    {
        dynBuf->storedBytes -= 1;
        return mcsSUCCESS;
    }

    /* Compute the number of Dynamic Buffer bytes to be backed up */
    miscDynSIZE lengthToBackup = storedBytes -
            ((to - miscDYN_BUF_BEGINNING_POSITION) + 1);

    /* Compute the first 'to be backep up' Dynamic Buffer byte position */
    char *positionToBackup = dynBuf->dynBuf +
            ((to - miscDYN_BUF_BEGINNING_POSITION) + 1);

    /* Compute the first 'to be deleted' Dynamic Buffer byte position */
    char *positionToWriteIn = dynBuf->dynBuf +
            (from - miscDYN_BUF_BEGINNING_POSITION);

    /*
     * Move the 'not-to-be-deleted' Dynamic Buffer bytes to their
     * definitive place
     */
    memmove(positionToWriteIn, positionToBackup, lengthToBackup);

    /*
     * Update the Dynamic Buffer stored length value using the deleted bytes
     * number
     */
    dynBuf->storedBytes -= ((to - miscDYN_BUF_BEGINNING_POSITION) -
            (from - miscDYN_BUF_BEGINNING_POSITION)) + 1;

    return mcsSUCCESS;
}

/*___oOo___*/
