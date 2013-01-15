/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui.task;

/**
 * This class describes the jMCS tasks associated with SwingWorker(s).
 * 
 * @author Guillaume MELLA, Laurent BOURGES.
 */
public final class JmcsTaskRegistry extends TaskRegistry {

    /** task registry singleton */
    private final static JmcsTaskRegistry _instance;

    /* JMCS tasks */
    /** feedback Report task */
    public final static Task TASK_FEEDBACK_REPORT;

    /**
     * Static initializer to define tasks and their child tasks
     */
    static {
        // create the task registry singleton :
        _instance = new JmcsTaskRegistry();

        // create tasks :
        TASK_FEEDBACK_REPORT = new Task("FeedbackReport");

        // register tasks :
        _instance.addTask(TASK_FEEDBACK_REPORT);
    }

    /**
     * Singleton pattern for the registry itself
     * @return registry instance
     */
    public static TaskRegistry getInstance() {
        return _instance;
    }

    /**
     * Protected constructor
     */
    protected JmcsTaskRegistry() {
        super();
    }
}
