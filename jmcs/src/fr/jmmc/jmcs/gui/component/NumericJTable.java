/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui.component;

import fr.jmmc.jmcs.gui.util.SwingUtils;
import java.awt.Color;
import java.awt.Component;
import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.table.TableCellEditor;
import javax.swing.text.JTextComponent;

/**
 * Extends the swing jtable and fixes the default behaviour
 * to provide ergonomic scientific softwares.
 * Most tables should use this class as custom creation code.
 * 
 * @author Guillaume MELLA, Laurent BOURGES.
 */
public class NumericJTable extends javax.swing.JTable {

    /** default serial UID for Serializable interface */
    private static final long serialVersionUID = 1;

    /**
     * Overriden constructor to change default behaviour (default editor, single selection)
     */
    public NumericJTable() {
        super();

        // use custom double editor to fix focus problems:
        final DoubleEditor editor = new DoubleEditor();

        // set one click edition on following table and show all decimals in numerical values
        editor.setClickCountToStart(1);

        setDefaultEditor(Double.class, editor);

        // single table selection :
        getSelectionModel().setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        // Fix lost focus issues on JTable :
        putClientProperty("terminateEditOnFocusLost", Boolean.TRUE);
    }

    @Override
    public Component prepareEditor(TableCellEditor editor, int row, int column) {
        final Component c = super.prepareEditor(editor, row, column);

        if (c instanceof JTextComponent) {
            /* use invokeLater because of mouse events default behavior (caret ...) */
            SwingUtils.invokeLaterEDT(new Runnable() {

                @Override
                public void run() {
                    ((JTextComponent) c).selectAll();
                }
            });
        }
        return c;
    }

    /**
     * Custom Number editor fixing focus lost problems on empty cell
     */
    static class DoubleEditor extends DefaultCellEditor {

        private Double value;

        public DoubleEditor() {
            super(new JTextField());
            ((JTextField) getComponent()).setHorizontalAlignment(JTextField.RIGHT);
        }

        @Override
        public Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected,
                int row, int column) {
            this.value = null;

            ((JComponent) getComponent()).setBorder(new LineBorder(Color.black));

            return super.getTableCellEditorComponent(table, value, isSelected, row, column);
        }

        @Override
        public Object getCellEditorValue() {
            return value;
        }

        @Override
        public boolean stopCellEditing() {
            final String s = (String) super.getCellEditorValue();
            // Here we are dealing with the case where a user
            // has deleted the string value in a cell, possibly
            // after a failed validation. Return null, so that
            // they have the option to replace the value with
            // null or use escape to restore the original.
            // For Strings, return "" for backward compatibility.
            if ("".equals(s)) {
                // Fix focus lost problem:
                value = null;
                return super.stopCellEditing();
            }

            try {
                value = new Double(s);
            } catch (Exception e) {
                ((JComponent) getComponent()).setBorder(new LineBorder(Color.red));
                return false;
            }
            return super.stopCellEditing();
        }
    }
}
