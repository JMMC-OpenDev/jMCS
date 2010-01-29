/*
 * ImageViewer.java
 *
 * Created on 5 avril 2007, 21:35
 */
package fr.jmmc.mcs.image;

import java.util.Observable;
import java.util.Observer;

/**
 *
 * @author  mella
 */
public class ImageViewer extends javax.swing.JFrame implements Observer {

  /** default serial UID for Serializable interface */
  private static final long serialVersionUID = 1;
  /**
   * DOCUMENT ME!
   */
  private ImageCanvas imageCanvas;
  // Variables declaration - do not modify//GEN-BEGIN:variables
  private javax.swing.JComboBox colorModelComboBox;
  private javax.swing.JTextField imageInfoTextField;
  private javax.swing.JLabel jLabel1;
  private javax.swing.JPanel jPanel1;
  // End of variables declaration//GEN-END:variables

  /** Creates new form ImageViewer */
  public ImageViewer() {
    init();
  }

  /**
   * DOCUMENT ME!
   */
  protected void init() {
    initComponents();
    // add image canvas
    imageCanvas = new ImageCanvas();

    imageCanvas.addObserver(this);
    getContentPane().add(imageCanvas, java.awt.BorderLayout.CENTER);
    // set items for colormodels
    colorModelComboBox.setModel(new javax.swing.DefaultComboBoxModel(
            ColorModels.colorModelNames));
  }

  public ImageCanvas getImageCanvas() {
    return imageCanvas;
  }

  /**
   * DOCUMENT ME!
   *
   * @param observable DOCUMENT ME!
   * @param object DOCUMENT ME!
   */
  public void update(Observable observable, Object object) {
    final float value = imageCanvas.mousePixel_ / imageCanvas.normalisePixelCoefficient_ + imageCanvas.minValue_;

    String info = imageCanvas.getImageDimension().height + "x" +
            imageCanvas.getImageDimension().width + " Image " +
            imageCanvas.getCanvasDimension().height + "x" + imageCanvas.getCanvasDimension().width +
            " pixels [" + imageCanvas.mouseX_ + "," + imageCanvas.mouseY_ + " : " +
            imageCanvas.mousePixel_ + "] = " + value;
    imageInfoTextField.setText(info);
    imageInfoTextField.validate();
  }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the Form Editor.
   */
  // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
  private void initComponents() {
    java.awt.GridBagConstraints gridBagConstraints;

    jPanel1 = new javax.swing.JPanel();
    jLabel1 = new javax.swing.JLabel();
    colorModelComboBox = new javax.swing.JComboBox();
    imageInfoTextField = new javax.swing.JTextField();

    setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

    jPanel1.setLayout(new java.awt.GridBagLayout());

    jLabel1.setText("Color model:"); // NOI18N
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
    gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
    jPanel1.add(jLabel1, gridBagConstraints);

    colorModelComboBox.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(java.awt.event.ActionEvent evt) {
        colorModelComboBoxActionPerformed(evt);
      }
    });
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
    gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
    jPanel1.add(colorModelComboBox, gridBagConstraints);

    imageInfoTextField.setBorder(null);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.weightx = 1.0;
    gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
    jPanel1.add(imageInfoTextField, gridBagConstraints);

    getContentPane().add(jPanel1, java.awt.BorderLayout.SOUTH);

    pack();
  }// </editor-fold>//GEN-END:initComponents

    /**
     * DOCUMENT ME!
     *
     * @param evt DOCUMENT ME!
     */
    private void colorModelComboBoxActionPerformed(java.awt.event.ActionEvent evt)
    {//GEN-FIRST:event_colorModelComboBoxActionPerformed
        imageCanvas.setColorModel(ColorModels.colorModels[colorModelComboBox.getSelectedIndex()]);
    }//GEN-LAST:event_colorModelComboBoxActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        java.awt.EventQueue.invokeLater(new Runnable()
            {
                public void run()
                {
                        final ImageViewer viewer = new ImageViewer();

                        int     w   = 32;
                        int     h   = 32;
                        float[] img = new float[w * h];

                        for (int i = 0, size = img.length; i < size; i++)
                        {
                            img[i] = i;
                        }

                        viewer.getImageCanvas().initImage(w, h, img);

                        viewer.pack();
                        viewer.setVisible(true);
                }
            });
    }
}
