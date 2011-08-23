/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.mcs.model.function.math;

/**
 * This class computes the Fourier transform at frequencies (UFREQ,VFREQ) of a gaussian object.
 * 
 * @author Laurent BOURGES.
 */
public class GaussianFunction extends DiskFunction {

  /**
   * Public constructor
   */
  public GaussianFunction() {
    super();
  }

  /**
   * Compute the Fourier transform at frequencies (UFREQ,VFREQ) of this object
   * @param ufreq U frequency in rad-1
   * @param vfreq V frequency in rad-1
   * @return Fourier transform value
   */
  @Override
  public double computeWeight(final double ufreq, final double vfreq) {
    if (axisRatio != 1d) {
      // transform UV coordinates :
      final double t_ufreq = Functions.transformU(ufreq, vfreq, axisRatio, positionAngle);
      final double t_vfreq = Functions.transformV(ufreq, vfreq, positionAngle);

      return Functions.computeGaussian(t_ufreq, t_vfreq, flux_weight, diameter);
    }
    return Functions.computeGaussian(ufreq, vfreq, flux_weight, diameter);
  }
}
