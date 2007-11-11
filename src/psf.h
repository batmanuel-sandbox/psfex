 /*
 				psf.h

*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*	Part of:	PSFEx
*
*	Author:		E.BERTIN (IAP)
*
*	Contents:	Include for psf.c.
*
*	Last modify:	11/11/2007
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifndef _POLY_H_
#include "poly.h"
#endif

#ifndef _SAMPLE_H_
#include "sample.h"
#endif

#ifndef _PSF_H_
#define _PSF_H_

/*----------------------------- Internal constants --------------------------*/

#define	PSF_FREEDFACTOR	1.0	/* Margin against overfitting */
#define	PSF_NMASKDIM	3	/* Number of dimensions for PSF data */
#define	PSF_MAXSHIFT	3.0	/* Max shift from initial guess (pixels)*/
#define	PSF_MINSHIFT	1e-4	/* Min shift from previous guess (pixels)*/
#define PSF_NITER	40	/* Maximum number of iterations in fit */
#define	PSF_NSNAPMAX	16	/* Maximum number of PSF snapshots/dimension */
#define	GAUSS_LAG_OSAMP	3	/* Gauss-Laguerre oversampling factor */

/*----------------------------- Type definitions --------------------------*/
typedef enum {BASIS_NONE, BASIS_PIXEL, BASIS_GAUSS_LAGUERRE, BASIS_FILE}
        basistypenum;
/*--------------------------- structure definitions -------------------------*/

typedef struct code
  {
  float		*pc;
  float		**param;
  int		*parammod;
  int		ncode;
  int		nparam;
  }     codestruct;

typedef struct moffat
  {
  double	context[POLY_MAXDIM];	/* Context coordinates */
  double	amplitude;	/* Central amplitude */
  double	xc[2];		/* Center coordinates */
  double	fwhm_min;	/* FWHM along the minor axis */
  double	fwhm_max;	/* FWHM along the major axis */
  double	theta;		/* Position angle of the major axis / NAXIS1 */
  double	beta;		/* Moffat beta parameter */
  double	residuals;	/* Normalized residuals */
  double	symresiduals;	/* Normalized symmetry residuals */
  }	moffatstruct;

typedef struct psf
  {
  int		dim;		/* Dimensionality of the tabulated data */
  int		*size;		/* PSF  dimensions */
  int		npix;		/* Total number of involved PSF pixels */
  float		*comp; 		/* Complete pix. data (principal components) */
  float		*loc;		/* Local PSF */
  float		*resi;		/* Map of residuals */
  char		**contextname;	/* Array of context key-names */
  double	*contextoffset;	/* Offset to apply to context data */
  double	*contextscale;	/* Scaling to apply to context data */
  struct poly	*poly;		/* Polynom describing the PSF variations */
  float		pixstep;	/* Mask oversampling (pixel). */
  int		samples_loaded;	/* Number of detections loaded */
  int		samples_accepted;/* Number of detections accepted */
  double	chi2;		/* chi2/d.o.f. */
  float		fwhm;		/* Initial guess of the FWHM */
  int		*pixmask;	/* Pixel mask for local bases */
  float		*basis;		/* Basis vectors */
  int		nbasis;		/* Number of basis vectors */
  int		ndata;		/* Size of the design matrix along data axis */
  moffatstruct	*moffat;	/* Array of Moffat fits to PSF */
  double	moffat_fwhm_min;
  double	moffat_fwhm;	/* Central Moffat FWHM */
  double	moffat_fwhm_max;
  double	moffat_elongation_min;
  double	moffat_elongation;/* Central Moffat elongation */
  double	moffat_elongation_max;
  double	moffat_beta_min;
  double	moffat_beta;	/* Central Moffat beta */
  double	moffat_beta_max;
  double	moffat_residuals_min;
  double	moffat_residuals;/* Central Moffat residuals */
  double	moffat_residuals_max;
  double	moffat_symresiduals_min;
  double	moffat_symresiduals;/* Symmetry residuals */
  double	moffat_symresiduals_max;
  }	psfstruct;


typedef struct pc
  {
  char		name[MAXCHAR];	/* PC filename */
  int		npc;		/* Number of Principal Components */
  int		dim;		/* Dimensionality of the tabulated data */
  int		*size;		/* PC  dimensions */
  int		npix;		/* Total number of involved PC pixels */
  float		*comp; 		/* Complete pix. data (principal components) */
  double	*mx2,*my2,*mxy;	/* 2nd order moments for each component */
  double	*flux;		/* Flux of each component */
  double	*bt;		/* B/T for each component */
  codestruct	*code;
  }	pcstruct;


/*---------------------------------- protos --------------------------------*/
extern void	psf_build(psfstruct *psf, double *pos),
		psf_end(psfstruct *psf),
		psf_make(psfstruct *psf, setstruct *set),
		psf_makebasis(psfstruct *psf, setstruct *set,
			basistypenum basis_type,  int nvec),
		psf_makeresi(psfstruct *psf, setstruct *set, int centflag,
			float psf_extraccu),
		psf_makemask(psfstruct *psf, setstruct *set, double chithresh),
		psf_refine(psfstruct *psf, setstruct *set,
			basistypenum basis_type, int nvec),
		psf_save(psfstruct *psf, pcstruct *pcc, pcstruct *pc,
			char *filename, int ext, int next);

extern int	psf_pshapelet(float **shape, int w, int h, int nmax,
			double beta),
		psf_readbasis(psfstruct *psf, char *filename, int ext);

extern double	psf_chi2(psfstruct *psf, setstruct *set),
		psf_clean(psfstruct *psf, setstruct *set);

extern psfstruct	*psf_init(char **names, int *group, int ndim,
				int *dim, int ngroup,
				int wpsf, int hpsf, float psfstep,int nsample),
			*psf_load(char *filename);


extern void	matinv(double *mat, int nmat),
		pc_end(pcstruct *pc),
		psf_clip(psfstruct *psf);

extern pcstruct	*pc_convolve(pcstruct *pc, psfstruct *psf),
		*pc_load(char *filename),
		*pc_orthogon(pcstruct *pc2, pcstruct *pc, float pixstep);

#endif

