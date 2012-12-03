/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui.action;

import fr.jmmc.jmcs.collection.FixedSizeLinkedHashMap;
import fr.jmmc.jmcs.data.preference.FileChooserPreferences;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JSeparator;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * RecentFilesManager singleton class.
 * 
 * RecentFilesManager.addFile() must be called by application to feed the Recent File menu entry.
 * 
 * @author Sylvain LAFRASSE, Laurent BOURGES, Guillaume MELLA.
 */
public final class RecentFilesManager {

    /** Logger */
    private static final Logger _logger = LoggerFactory.getLogger(RecentFilesManager.class.getName());
    /** Maximum number of recent files by MIME type */
    private static final int MAXIMUM_HISTORY_ENTRIES = 10;
    /** Singleton instance */
    private static volatile RecentFilesManager _instance = null;
    // Members
    /** Action registrar reference */
    private final ActionRegistrar _registrar;
    /** Hook to the "Open Recent" sub-menu */
    final JMenu _menu;
    /** thread safe recent file repository */
    private final Map<String, String> _repository = Collections.synchronizedMap(new FixedSizeLinkedHashMap<String, String>(MAXIMUM_HISTORY_ENTRIES));

    /**
     * Return the singleton instance
     * @return singleton instance
     */
    static synchronized RecentFilesManager getInstance() {
        // DO NOT MODIFY !!!
        if (_instance == null) {
            _instance = new RecentFilesManager();
        }

        return _instance;
        // DO NOT MODIFY !!!
    }

    /**
     * Hidden constructor
     */
    protected RecentFilesManager() {
        _registrar = ActionRegistrar.getInstance();
        _menu = new JMenu("Open Recent");
        populateMenuFromPreferences();
    }

    /**
     * Link RecentFilesManager menu to the "Open Recent" sub-menu
     * @return "Open Recent" sub-menu container
     */
    public static JMenu getMenu() {
        return getInstance()._menu;
    }

    /**
     * Add the given recent file for MIME type.
     * @param file file object or null
     */
    public static void addFile(final File file) {
        if (file != null) {
            final RecentFilesManager rfm = getInstance();

            if (!rfm.storeFile(file)) {
                return;
            }

            rfm.refreshMenu();
            rfm.flushRecentFileListToPrefrences();
        }
    }

    /**
     * Store the given file in the recent file repository.
     * @param file file to be added in the file repository
     * @return  true if operation succedeed else false.
     */
    private boolean storeFile(final File file) {
        // Check parameter validity
        if (file == null || !file.canRead()) {
            _logger.warn("Could not read file '{}'", file);
            return false;
        }

        // Check file path
        String path;
        try {
            path = file.getCanonicalPath();
        } catch (IOException ex) {
            _logger.warn("Could not resolve file path of file '{}'", file, ex);
            return false;
        }

        if ((path == null) || (path.length() == 0)) {
            _logger.warn("Could not resolve empty file path of file '{}'", file);
            return false;
        }

        // Check file name
        String name = file.getName();
        if ((name == null) || (name.length() == 0)) { // If no name found
            name = path; // Use path instead
        }

        // Store file
        _repository.put(path, name);
        return true;
    }

    /**
     * Refresh content of "Open Recent" File menu entry.
     */
    private void refreshMenu() {

        // Clean, then re-fill sub-menu
        _menu.removeAll();
        _menu.setEnabled(false);

        // For each registered files
        for (final String currentPath : _repository.keySet()) {

            // Create an action to open it
            final String currentName = _repository.get(currentPath);
            final AbstractAction currentAction = new AbstractAction(currentName) {
                /** default serial UID for Serializable interface */
                private static final long serialVersionUID = 1;

                @Override
                public void actionPerformed(ActionEvent ae) {
                    _registrar.getOpenAction().actionPerformed(new ActionEvent(_registrar, 0, currentPath));
                }
            };
            _menu.add(new JMenuItem(currentAction));
        }

        if (_menu.getItemCount() > 0) {
            addCleanAction();
            _menu.setEnabled(true);
        }
    }

    /**
     * Add a "Clear" item at end below a separator
     */
    private void addCleanAction() {

        final AbstractAction cleanAction = new AbstractAction("Clear History") {
            /** default serial UID for Serializable interface */
            private static final long serialVersionUID = 1;

            @Override
            public void actionPerformed(ActionEvent ae) {
                _repository.clear();
                _menu.removeAll();
                _menu.setEnabled(false);
                // TODO : clean pref too !!!
            }
        };

        _menu.add(new JSeparator());
        _menu.add(new JMenuItem(cleanAction));
    }

    /**
     * Grab recent files from shared preference.
     */
    private void populateMenuFromPreferences() {

        final List<String> recentFilePaths = FileChooserPreferences.getRecentFilePaths();
        if (recentFilePaths == null) {
            _logger.warn("No recent file path found.");
            return;
        }

        for (String path : recentFilePaths) {
            storeFile(new File(path));
        }

        refreshMenu();
    }

    /**
     * Flush file list to shared preference.
     */
    private void flushRecentFileListToPrefrences() {
        // Create list of paths
        if ((_repository == null) || (_repository.isEmpty())) {
            _logger.debug("Could not get recent file paths.");
            return;
        }
        final List<String> pathsList = new ArrayList<String>(_repository.keySet());

        // Put this to prefs
        FileChooserPreferences.setRecentFilePaths(pathsList);
    }
}