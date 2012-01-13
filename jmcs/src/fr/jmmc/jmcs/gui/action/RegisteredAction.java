/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui.action;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import javax.swing.Action;
import javax.swing.KeyStroke;

/**
 * Action class customized to auto-register in ActionRegistrar when created.
 * 
 * @author Sylvain LAFRASSE, Laurent BOURGES.
 */
public abstract class RegisteredAction extends MCSAction {

    /** default serial UID for Serializable interface */
    private static final long serialVersionUID = 1;
    /** Logger */
    private static final Logger _logger = LoggerFactory.getLogger(RegisteredAction.class.getName());
    /** Action Registrar */
    private static final ActionRegistrar _registrar = ActionRegistrar.getInstance();

    /**
     * Constructor, that automatically register the action in RegisteredAction.
     * Action name, icon, accelerator and description is first initiated using
     * fieldName to build a MCSAction.
     * @param classPath the path of the class containing the field pointing to
     * the action, in the form returned by 'getClass().getName();'.
     * @param fieldName the name of the field pointing to the action.
     */
    public RegisteredAction(final String classPath, final String fieldName) {
        super(fieldName);

        _registrar.put(classPath, fieldName, this);
    }

    /**
     * Constructor, that automatically register the action in RegisteredAction.
     * Action name, icon, accelerator and description is first initiated using
     * fieldName to build a MCSAction.
     * @param classPath the path of the class containing the field pointing to
     * the action, in the form returned by 'getClass().getName();'.
     * @param fieldName the name of the field pointing to the action.
     * @param deferedInitialization true indicates to perform deferred initialization i.e. after application startup
     */
    public RegisteredAction(final String classPath, final String fieldName, final boolean deferedInitialization) {
        super(fieldName);

        _registrar.put(classPath, fieldName, this);

        _registrar.flagAsDeferedInitAction(classPath, fieldName);
    }

    /**
     * Perform deferred initialization i.e. executed after the application startup.
     * This method must be overridden in sub classes
     */
    protected void performDeferedInitialization() {
        // not implemented
    }

    /**
     * Constructor, that automatically register the action in RegisteredAction,
     * and assign it a name.
     * Action name, icon, accelerator and description is first initiated following MCSAction.
     * Then actionName set or overwrite action name.
     * @param classPath the path of the class containing the field pointing to
     * the action, in the form returned by 'getClass().getName();'.
     * @param fieldName the name of the field pointing to the action.
     * @param actionName the name of the action.
     */
    public RegisteredAction(final String classPath, final String fieldName, final String actionName) {
        this(classPath, fieldName);

        // Define action name and accelerator
        putValue(Action.NAME, actionName);
    }

    /**
     * Constructor, that automatically register the action in RegisteredAction,
     * and assign it a name and an accelerator.
     * Action name, icon, accelerator and description is first initiated following MCSAction.
     * Then actionName and actionAccelerator set or overwrite action name and action accelerator.
     *
     * @param classPath the path of the class containing the field pointing to
     * the action, in the form returned by 'getClass().getName();'.
     * @param fieldName the name of the field pointing to the action.
     * @param actionName the name of the action.
     * @param actionAccelerator the accelerator of the action, like "ctrl Q".
     */
    public RegisteredAction(final String classPath, final String fieldName,
            final String actionName, final String actionAccelerator) {
        this(classPath, fieldName, actionName);

        // Define action name and accelerator
        putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke(actionAccelerator));
    }

    /**
     * Flag the action as the one dedicated to handle Preference panel display.
     */
    public void flagAsPreferenceAction() {
        // Force the preference action name
        putValue(Action.NAME, "Preferences...");

        _registrar.putPreferenceAction(this);
    }

    /**
     * Flag the action as the one dedicated to file opening sequence.
     */
    public void flagAsOpenAction() {
        // Force the 'open' action name
        putValue(Action.NAME, "Open");

        // Force the 'open' keyboard shortcut
        putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke("ctrl O"));

        _registrar.putOpenAction(this);
    }

    /**
     * Flag the action as the one dedicated to handle Quit sequence.
     */
    public void flagAsQuitAction() {
        // Force the 'quit' action name
        putValue(Action.NAME, "Quit");

        // Force the 'quit' keyboard shortcut
        putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke("ctrl Q"));

        _registrar.putQuitAction(this);
    }
}
/*___oOo___*/