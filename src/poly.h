 /*
 				poly.h

*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*	Part of:	A program using polynomial fits
*
*	Author:		E.BERTIN (IAP) 
*
*	Contents:	Include for poly.c
*
*	Last modify:	04/11/2008
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifndef _POLY_H_
#define _POLY_H_

/*--------------------------------- constants -------------------------------*/

#define	POLY_MAXDIM		4	/* Max dimensionality of polynom */
#define POLY_MAXDEGREE		10	/* Max degree of the polynom */
#define	POLY_TINY		1e-30	/* A tiny number */

/*---------------------------------- macros ---------------------------------*/

/*--------------------------- structure definitions -------------------------*/

typedef struct poly
  {
  double	*basis;		/* Current values of the basis functions */
  double	*orthobasis;	/* Curr orthonormalized basis function values */
  double	*coeff;		/* Polynom coefficients */
  int		ncoeff;		/* Number of coefficients */
  int		*group;		/* Groups */
  int		ndim;		/* dimensionality of the polynom */
  int		*degree;	/* Degree in each group */
  int		ngroup;		/* Number of different groups */
  double	*orthomat;	/* Orthonormalization matrix */
  double	*deorthomat;	/* "Deorthonormalization" matrix */
  }	polystruct;

/*---------------------------------- protos --------------------------------*/

extern polystruct	*poly_copy(polystruct *poly),
			*poly_init(int *group,int ndim,int *degree,int ngroup);

extern double		*poly_deortho(polystruct *poly, double *datain,
				double *dataout),
			poly_func(polystruct *poly, double *pos),
			*poly_ortho(polystruct *poly, double *datain,
				double *dataout);

extern int		cholsolve(double *a, double *b, int n),
			*poly_powers(polystruct *poly);

extern void		poly_addcste(polystruct *poly, double *cste),
			poly_end(polystruct *poly),
			poly_fit(polystruct *poly, double *x, double *y,
				double *w, int ndata, double *extbasis),
			poly_initortho(polystruct *poly, double *data,
				int ndata),
			poly_solve(double *a, double *b, int n),
			svdsolve(double *a, double *b, int m, int n,
				double *vmat, double *wmat);

#endif

