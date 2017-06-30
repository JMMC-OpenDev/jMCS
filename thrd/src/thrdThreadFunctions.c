/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * @file
 * pthread-based thread library.
 *
 * This library is simple. It allows you to:
 * @li launch a new thread,
 * @li wait for its termination.
 *
 * @n
 * @ex
 * A C program using a Dynamic Buffer.
 * @code
 * #include "thrdThread.h"
 *
 * thrdFCT_RET myThreadFunction(thrdFCT_ARG param)
 * {
 *     int i;
 *     for (i=0; i<=100; i++)
 *     {
 *         printf("%s - %d\n", (char*)param, i);
 *     }
 *
 *     return NULL;
 * }
 *
 * int main (int argc, char *argv[])
 * {
 *  /# Thread creation #/
 *  thrdTHREAD_STRUCT           myThread;
 *  myThread.function  = myThreadFunction;
 *  myThread.parameter = "Thread 1";
 *  thrdThreadCreate(&myThread);
 *
 *  /# Launch a function in parallel execution #/
 *  myThreadFunction("Thread 2");
 *
 *  /# Wait for the thread end #/
 *  thrdThreadWait(&myThread);
 *
 *  exit();
 * }
 * @endcode
 *
 * @sa pthread
 */




/*
 * System Headers
 */
#include <stdio.h>
#include <errno.h>


/*
 * MCS Headers
 */
#include "mcs.h"
#include "log.h"
#include "err.h"


/*
 * Local Headers
 */
#include "thrdThreadFunctions.h"
#include "thrdPrivate.h"
#include "thrdErrors.h"


/*
 * Public functions definition
 */

/**
 * Launch the given thread execution.
 *
 * Please note that the value passed to the thread must have been stored in the
 * 'parameter' field of the given thrdThred structure.
 *
 * @warning The given thrdThread structure must have been fully initialized
 * before.
 *
 * @param thread the thread to be launched
 *
 * @sa pthread_create
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT thrdThreadCreate (thrdTHREAD_STRUCT  *thread)
{
    /* Verify parameter validity */
    if (thread == NULL)
    {
        errAdd(thrdERR_NULL_PARAM, "thread");
        return mcsFAILURE;
    }

    /* Try to launch the given thread function */
    if (pthread_create(&thread->id, NULL, thread->function, thread->parameter)
            != 0)
    {
        /* If an eror occurred, raise the corresponding error */
        switch (errno)
        {
            case EAGAIN:
                /*There is no system resources left to create a new thread */
                errAdd(thrdERR_THREAD_NUMBER);
                return mcsFAILURE;
                break;

            default:
                errAdd(thrdERR_ASSERT_FAILED);
                return mcsFAILURE;
        }
    }

    return mcsSUCCESS;
}

/**
 * Wait for termination of the given thread.
 *
 * Please note that the value returned by the thread will be stored in the
 * 'result' field of the given thrdThred structure after termination.
 *
 * @warning The given thrdThread structure must have been fully initialized
 * before.
 *
 * @param thread the thread to wait
 *
 * @sa pthread_join
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT thrdThreadWait (thrdTHREAD_STRUCT  *thread)
{
    /* Verify parameter validity */
    if (thread == NULL)
    {
        errAdd(thrdERR_NULL_PARAM, "thread");
        return mcsFAILURE;
    }

    /* Wait until the given thread function ends */
    if (pthread_join(thread->id, &thread->result) != 0)
    {
        /* If an eror occurred, raise the corresponding error */
        switch (errno)
        {
            case ESRCH:
                /* No thread could be found with the specified id */
                errAdd(thrdERR_THREAD_NOT_FOUND, thread->id);
                return mcsFAILURE;
                break;

            case EINVAL:
                /*
                 * The given thread has been detached, or another thread is
                 * already waiting on its termination
                 */
                errAdd(thrdERR_THREAD_DETACHED, thread->id);
                return mcsFAILURE;
                break;

            case EDEADLK:
                /* The given thread refers to itself, leading to a dead lock */
                errAdd(thrdERR_THREAD_DEADLOCK, thread->id);
                return mcsFAILURE;
                break;

            default:
                errAdd(thrdERR_ASSERT_FAILED);
                return mcsFAILURE;
        }
    }

    return mcsSUCCESS;
}

/**
 * Kill the given thread.
 *
 * @warning The given thrdThread structure must have been fully initialized
 * before.
 *
 * @param thread the thread to kill
 *
 * @sa pthread_join
 *
 * @return mcsSUCCESS on successful completion. Otherwise mcsFAILURE is
 * returned.
 */
mcsCOMPL_STAT thrdThreadKill (thrdTHREAD_STRUCT  *thread)
{
    /* Verify parameter validity */
    if (thread == NULL)
    {
        errAdd(thrdERR_NULL_PARAM, "thread");
        return mcsFAILURE;
    }

    /* Wait until the given thread function ends */
    if (pthread_cancel(thread->id) != 0)
    {
        /* If an eror occurred, raise the corresponding error */
        switch (errno)
        {
            case ESRCH:
                /* No thread could be found with the specified id */
                errAdd(thrdERR_THREAD_NOT_FOUND, thread->id);
                return mcsFAILURE;
                break;

            default:
                errAdd(thrdERR_ASSERT_FAILED);
                return mcsFAILURE;
        }
    }

    return mcsSUCCESS;
}



/*___oOo___*/
