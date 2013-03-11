package org.ivoa.util.runner;

import fr.jmmc.jmcs.util.CollectionUtils;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.Future;

/**
 * Generic Job state (id, state, dates, duration).
 *
 * Sub classes will extend this class to add specific attributes ...
 *
 * @author laurent bourges (voparis)
 */
public final class RootContext extends RunContext implements Iterator<RunContext> {
    //~ Constants --------------------------------------------------------------------------------------------------------

    /**
     * serial UID for Serializable interface
     */
    private static final long serialVersionUID = 1L;
    //~ Members ----------------------------------------------------------------------------------------------------------
    /** future used to be able to cancel the job */
    private transient Future<?> future = null;
    /**
     * The user who owns this run (login)
     */
    private String owner;
    /**
     * Process working directory
     */
    private String workingDir;
    /**
     * Relative path to results of the job in either runner or archive
     */
    private String relativePath;
    /**
     * Child contexts (No cascade at all to have unary operation)
     */
    private final List<RunContext> childContexts = new ArrayList<RunContext>(2);
    /**
     * Current executed task position in the Child contexts
     */
    private int currentTask = 0;

    /**
     * Creates a new RunContext object for JPA
     */
    public RootContext() {
        super();
    }

    /**
     * Creates a new RunContext object
     *
     * @param applicationName application identifier
     * @param id job identifier
     * @param workingDir user's temporary working directory
     */
    public RootContext(final String applicationName, final Long id,
            final String workingDir) {
        super(null, applicationName, id);
        this.workingDir = workingDir;
    }

    /**
     * This method can be used to release resources
     */
    @Override
    public void close() {
        // clean up code :
    }

    /**
     * Simple toString representation : "job[id][state] duration ms."
     *
     * @return "job[id][state] duration ms."
     */
    @Override
    public String toString() {
        return super.toString() + ((getChildContexts() != null)
                ? (CollectionUtils.toString(getChildContexts())) : "");
    }

    /**
     * Return the future associated with this root context
     * @return future associated with this root context
     */
    public Future<?> getFuture() {
        return future;
    }

    /**
     * Define the future associated to the execution of this root context
     * @param pFuture future instance
     */
    public void setFuture(final Future<?> pFuture) {
        this.future = pFuture;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(final String owner) {
        this.owner = owner;
    }

    /**
     * Returns the process working directory
     *
     * @return process working directory
     */
    @Override
    public String getWorkingDir() {
        return workingDir;
    }

    public String getRelativePath() {
        return relativePath;
    }

    public void setRelativePath(final String relativePath) {
        this.relativePath = relativePath;
    }

    public List<RunContext> getChildContexts() {
        return childContexts;
    }

    public RunContext getCurrentChildContext() {
        if (currentTask < this.childContexts.size()) {
            return this.childContexts.get(currentTask);
        }
        return null;
    }

    public void addChild(final RunContext childContext) {
        this.childContexts.add(childContext);
    }

    @Override
    public boolean hasNext() {
        return currentTask < this.childContexts.size();
    }

    @Override
    public RunContext next() {
        return this.childContexts.get(currentTask);
    }

    public void goNext() {
        currentTask++;
    }

    @Override
    public void remove() {
        /* no-op */
    }
}
