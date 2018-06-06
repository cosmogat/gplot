/* 21-07-2013 */
/* billy */
/* gplot.h */
/* Funciona amb la versió 5.0 patchlevel rc2 de gnuplot */
#ifndef _GPLOT_H
#define _GPLOT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define GNUPLOT_PATH "/usr/bin/gnuplot"
#define _GPLOT_QUANTS 100
#define _GPLOT_OPC 7
#define _GPLOT_MAXBIN 50

typedef float gpfloat_t;
typedef enum {false, true} _GplotBool;
typedef struct _Gplot {
  FILE * arxiu;
  char * name;
  int numPlots;
  int numPlots3D;
  _GplotBool opcions[_GPLOT_OPC];
  char * term;
  gpfloat_t * levels;
  int num_levels;
  char fitBin[_GPLOT_MAXBIN][20];
  int numBin;
  char colors[10][10];
} Gplot;

/* opcions:                */
/* opcions[0] <- grid      */
/* opcions[1] <- multiplot */
/* opcions[2] <- title     */
/* opcions[3] <- colorbox  */
/* opcions[4] <- palette   */
/* opcions[5] <- cntrparam */
/* opcions[6] <- keys      */

void gplot_init(Gplot * gp, char * cad);
void gplot_printf(Gplot * gp, char * text, ...);
void gplot_title(Gplot * gp, char * cad);
void gplot_untitle(Gplot * gp);
void gplot_xrange(Gplot * gp, gpfloat_t x0, gpfloat_t x1);
void gplot_yrange(Gplot * gp, gpfloat_t y0, gpfloat_t y1);
void gplot_zrange(Gplot * gp, gpfloat_t z0, gpfloat_t z1);
void gplot_xlabel(Gplot * gp, char * cad);
void gplot_ylabel(Gplot * gp, char * cad);
void gplot_zlabel(Gplot * gp, char * cad);
void gplot_xtics(Gplot * gp, gpfloat_t num);
void gplot_ytics(Gplot * gp, gpfloat_t num);
void gplot_ztics(Gplot * gp, gpfloat_t num);
void gplot_unxtics(Gplot * gp);
void gplot_unytics(Gplot * gp);
void gplot_unztics(Gplot * gp);
void gplot_logscale(Gplot * gp, char * axis, int base);
void gplot_unlogscale(Gplot * gp, char * axis);
void gplot_lmargin(Gplot * gp, gpfloat_t num);
void gplot_rmargin(Gplot * gp, gpfloat_t num);
void gplot_tmargin(Gplot * gp, gpfloat_t num);
void gplot_bmargin(Gplot * gp, gpfloat_t num);
void gplot_text(Gplot * gp, char * text, gpfloat_t x, gpfloat_t y);
void gplot_untext(Gplot * gp);
void gplot_text3D(Gplot * gp, char * text, gpfloat_t x, gpfloat_t y, gpfloat_t z);
void gplot_untext3D(Gplot * gp);
void gplot_arrow(Gplot * gp, int vec, gpfloat_t x0, gpfloat_t y0, gpfloat_t x1, gpfloat_t y1);
void gplot_unarrow(Gplot * gp);
void gplot_arrow3D(Gplot * gp, int vec, gpfloat_t x0, gpfloat_t y0, gpfloat_t z0, gpfloat_t x1, gpfloat_t y1, gpfloat_t z1);
void gplot_unarrow3D(Gplot * gp);
void gplot_grid(Gplot * gp);
void gplot_ungrid(Gplot * gp);
void gplot_key(Gplot * gp, char * title, int box, int ins, int ver, int pos);
void gplot_unkey(Gplot * gp);
void gplot_colorbox(Gplot * gp);
void gplot_uncolorbox(Gplot * gp);
void gplot_palette(Gplot * gp, int r, int g, int b);
void gplot_unpalette(Gplot * gp);
void gplot_multiplot(Gplot * gp, gpfloat_t orig_x, gpfloat_t orig_y, gpfloat_t size_x, gpfloat_t size_y);
void gplot_unmultiplot(Gplot * gp);
void gplot_view(Gplot * gp, int rot_x, int rot_z, int scale_x, int scale_z);
void gplot_unview(Gplot * gp);
void gplot_levels(Gplot * gp, gpfloat_t * vec, int tam);
void gplot_samples(Gplot * gp, int samples);
void gplot_fillTransparent(Gplot * gp, gpfloat_t trans);

void gplot_plot(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotFilled(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, gpfloat_t y_begin, char * title, char * color);
void gplot_plotDots(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotPoints(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotLinesPoints(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotImpulses(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotFSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotHiSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotBoxes(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color);
void gplot_plotXError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, int tam, char * title, char * color);
void gplot_plotYError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ey, int tam, char * title, char * color);
void gplot_plotXYError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam, char * title, char * color);
void gplot_plotFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotFilledFile(Gplot * gp, char * arxiu, gpfloat_t y_begin, char * title, char * color);
void gplot_plotDotsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotPointsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotLinesPointsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotImpulsesFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotStepsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotFStepsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotHiStepsFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotBoxesFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotXErrorFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotYErrorFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotXYErrorFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plotEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotFilledEquation(Gplot * gp, char * arxiu, gpfloat_t y_begin, char * title, char * color);
void gplot_plotDotsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotPointsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotLinesPointsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotImpulsesEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotStepsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotFStepsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotHiStepsEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotBoxesEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plotPriv(Gplot * gp, char * cad, char * title, char * with, char * color, int mode);

void gplot_plot3DColor(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title);
void gplot_plot3DSurface(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title);
void gplot_plot3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title, char * color);
void gplot_plot3DContourSurface(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title, char * color);
void gplot_plot3DContour(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title);
void gplot_contour(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title);
void gplot_calorMap(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title);
void gplot_contour3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title);
void gplot_contour3DMap(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title);
void gplot_plot3DColorFile(Gplot * gp, char * arxiu, char * title);
void gplot_plot3DSurfaceFile(Gplot * gp, char * arxiu, char * title);
void gplot_plot3DFile(Gplot * gp, char * arxiu, char * title, char * color);
void gplot_plot3DContourSurfaceFile(Gplot * gp, char * arxiu, int num_lin, char * title, char * color);
void gplot_plot3DContourFile(Gplot * gp, char * arxiu, int num_lin, char * title);
void gplot_contourFile(Gplot * gp, char * arxiu, int num_lin, char * title);
void gplot_calorMapFile(Gplot * gp, char * arxiu, int num_lin, char * title);
void gplot_contour3DFile(Gplot * gp, char * arxiu, int num_lin, char * title);
void gplot_contour3DMapFile(Gplot * gp, char * arxiu, int num_lin, char * title);
void gplot_plot3DColorEquation(Gplot * gp, char * eq, char * title);
void gplot_plot3DSurfaceEquation(Gplot * gp, char * eq, char * title);
void gplot_plot3DEquation(Gplot * gp, char * eq, char * title, char * color);
void gplot_plot3DContourSurfaceEquation(Gplot * gp, char * eq, int num_lin, char * title, char * color);
void gplot_plot3DContourEquation(Gplot * gp, char * eq, int num_lin, char * title);
void gplot_contourEquation(Gplot * gp, char * eq, int num_lin, char * title);
void gplot_calorMapEquation(Gplot * gp, char * eq, int num_lin, char * title);
void gplot_contour3DEquation(Gplot * gp, char * eq, int num_lin, char * title);
void gplot_contour3DMapEquation(Gplot * gp, char * eq, int num_lin, char * title);
void gplot_plot3DPriv(Gplot * gp, char * cad, char * title, char * color, int mode, int plot_mode, int contour_mode, int contour_levels);

void gplot_export2D(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam);
void gplot_export2DError(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t * vec_e, int tam);
void gplot_export2DErrors(char * arxiu, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam);
void gplot_export3D(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY);
void gplot_writeBin2D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam);
void gplot_writeBin2DError(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t * vec_e, int tam);
void gplot_writeBin2DErrors(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam);
void gplot_writeBin3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY);
_GplotBool colorValid(char * color);
char * gplot_with(Gplot * gp, char * cad, int colors, char * color);

void gplot_reset(Gplot * gp, char * cad);
void gplot_exit(Gplot * gp);
void gplot_newBin(Gplot * gp);
void gplot_delBin(Gplot * gp);
#endif
