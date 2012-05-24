/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.util;

import org.ivoa.util.runner.EmptyJobListener;
import org.ivoa.util.runner.JobListener;
import org.ivoa.util.runner.LocalLauncher;
import org.ivoa.util.runner.RootContext;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Wrapper on http://code.google.com/p/vo-urp/ task runner.
 * 
 * @author Sylvain LAFRASSE, Laurent BOURGES
 */
public final class JnlpStarter {

    /** Class logger */
    private static final Logger _logger = LoggerFactory.getLogger(JnlpStarter.class.getName());
    /** application identifier for LocalLauncher */
    public final static String APP_NAME = "JnlpStarter";
    /** user for LocalLauncher */
    public final static String USER_NAME = "JMMC";
    /** task identifier for LocalLauncher */
    public final static String TASK_NAME = "JavaWebStart";
    /** javaws command */
    public final static String JAVAWS_CMD = "javaws";
//    public final static String JAVAWS_CMD = "/usr/lib/jvm/java-1.6.0-openjdk-1.6.0.0.x86_64/bin/javaws";
    /** flag to execute javaws with -verbose option */
    private static boolean JNLP_VERBOSE = false;

    /** Forbidden constructor */
    private JnlpStarter() {
    }

    /**
     * Launch the given Java WebStart application in background.
     * 
     * @param jnlpUrl jnlp url to launch the Jnlp application
     * @return the job context identifier
     * @throws IllegalStateException if the job can not be submitted to the job queue
     */
    public static Long launch(final String jnlpUrl) throws IllegalStateException {
        return launch(jnlpUrl, new EmptyJobListener());
    }

    /**
     * Launch the given Java WebStart application in background.
     * 
     * @param jnlpUrl jnlp url to launch the Jnlp application
     * @param jobListener job event listener (not null)
     * @return the job context identifier
     * @throws IllegalStateException if the job can not be submitted to the job queue
     */
    public static Long launch(final String jnlpUrl, final JobListener jobListener) throws IllegalStateException {

        if (jnlpUrl == null || jnlpUrl.length() == 0) {
            throw new IllegalArgumentException("empty JNLP url !");
        }
        if (jobListener == null) {
            throw new IllegalArgumentException("undefined job listener !");
        }

        _logger.info("launch: {}", jnlpUrl);

        // create the execution context without log file:
        final RootContext jobContext = LocalLauncher.prepareMainJob(APP_NAME, USER_NAME, FileUtils.getTempDirPath(), null);

        // command line: 'javaws -Xnosplash <jnlpUrl>'
        final String[] cmd;
        if (JNLP_VERBOSE) {
            cmd = new String[]{JAVAWS_CMD, "-verbose", "-Xnosplash", jnlpUrl};
        } else {
            cmd = new String[]{JAVAWS_CMD, "-Xnosplash", jnlpUrl};
        }

        LocalLauncher.prepareChildJob(jobContext, TASK_NAME, cmd);

        // puts the job in the job queue :
        // can throw IllegalStateException if job not queued :
        LocalLauncher.startJob(jobContext, jobListener);

        return jobContext.getId();
    }

    /** Start Java WebStart viewer */
    public static void launchJavaWebStartViewer() {

        _logger.info("launch 'javaws -viewer'");

        // create the execution context without log file:
        final RootContext jobContext = LocalLauncher.prepareMainJob(APP_NAME, USER_NAME, FileUtils.getTempDirPath(), null);

        // command line: 'javaws -viewer'
        LocalLauncher.prepareChildJob(jobContext, TASK_NAME, new String[]{JAVAWS_CMD, "-viewer"});

        // puts the job in the job queue :
        // can throw IllegalStateException if job not queued :
        LocalLauncher.startJob(jobContext, new EmptyJobListener());
    }

    /**
     * Return the flag to execute javaws with -verbose option
     * @return flag to execute javaws with -verbose option
     */
    public static boolean isJavaWebStartVerbose() {
        return JNLP_VERBOSE;
    }

    /**
     * Define the flag to execute javaws with -verbose option
     * @param verbose flag to execute javaws with -verbose option
     */
    public static void setJavaWebStartVerbose(final boolean verbose) {
        JNLP_VERBOSE = verbose;
    }
}
