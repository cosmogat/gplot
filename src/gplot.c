/* 21-07-2013 */
/* billy */
/* gplot.c */
#include <stdio.h>
#include <stdlib.h>
#include "gplot.h"

void gplot_init(Gplot * gp, char * cad) {
  int punt = 0, tam = strlen(cad), i;
  char * ext;

  ext = malloc(4 * sizeof(char *));
  gp->term = malloc(3 * sizeof(char *));
  gp->name = malloc(100 * sizeof(char *));
  gp->arxiu = popen(GNUPLOT_PATH, "w");
  if (gp->arxiu == NULL) {
    fprintf(stderr, "No s'ha pogut obrir %s\n", GNUPLOT_PATH);
    exit(-1);
  }
  while ((cad[punt] != '.') && (cad[punt] != '\0') && (punt < tam))
    punt++;
  for (i = punt + 1; i < tam; i++)
    ext[i - punt - 1] = cad[i]; 
  ext[3] = '\0';
  if ((strcmp(ext, "svg") == 0) || (strcmp(ext, "pdf") == 0) || (strcmp(ext, "eps") == 0) || (strcmp(ext, "png") == 0)) {
    gplot_printf(gp, "set terminal %s\n", ext);
    strcpy(gp->name, cad);
    gplot_printf(gp, "set output '%s'\n", cad);
    strcpy(gp->term, ext);
  }
  else if (tam == punt && tam != 0) {
    gplot_printf(gp, "set terminal pdf\n");
    strcpy(gp->name, cad);
    strcat(gp->name, ".pdf");
    gplot_printf(gp, "set output '%s.pdf'\n", cad);
    strcpy(gp->term, "pdf");
  }
  else {
    gplot_printf(gp, "set term qt enhanced font 'Verdana,10' persist\n");
    gp->name = "";
    gp->term = "qt";
  }
  gplot_printf(gp, "unset key\n");
  gplot_printf(gp, "unset colorbox\n");
  gp->numPlots = 0;
  gp->numPlots3D = 0;
  gp->numBin = 0;
  for (i = 0; i < _GPLOT_OPC; i++)
    gp->opcions[i] = false;
  strcpy(gp->colors[0], "#0060AD\0");
  strcpy(gp->colors[1], "#60AD00\0");
  strcpy(gp->colors[2], "#AD0B00\0");
  strcpy(gp->colors[3], "#E7E730\0");
  strcpy(gp->colors[4], "#E730E7\0");
  strcpy(gp->colors[5], "#30E7E7\0");
  strcpy(gp->colors[6], "#707070\0");
  strcpy(gp->colors[7], "#FF8E1E\0");
  strcpy(gp->colors[8], "#202020\0");
  strcpy(gp->colors[9], "#F000F0\0"); 
}

void gplot_printf(Gplot * gp, char * text, ...) {
  int debug = 1, ent;
  char * p, * cad;
  va_list pa;
  char car;
  float flo;
  va_start(pa, text);
#ifdef DEBUG
  debug = 0;
  fprintf(stderr, "[DEP][GNUPLOT] ");
#endif
  for (p = text; *p; p++) {
    if (*p != '%') {
      fprintf(gp->arxiu, "%c", *p);
      if (debug == 0)
	fprintf(stderr, "%c", *p);
    }
    else {
      switch (*++p) {
      case 'i':
      case 'd':
	ent = va_arg(pa, int);
	fprintf(gp->arxiu, "%d", ent);
	if (debug == 0)
	  fprintf(stderr, "%d", ent);
	break;
      case 'c':
	car = (char) va_arg(pa, int);
	fprintf(gp->arxiu, "%c", car);
	if (debug == 0)
	  fprintf(stderr, "%c", car);
	break;
      case 's':
	cad = va_arg(pa, char *);
	fprintf(gp->arxiu, "%s", cad);
	if (debug == 0)
	  fprintf(stderr, "%s", cad);
	break;
      case 'f':
	flo = (float) va_arg(pa, double);
	fprintf(gp->arxiu, "%f", flo);
	if (debug == 0)
	  fprintf(stderr, "%f", flo);
	break;
      default:
	fprintf(gp->arxiu, "%c", *p);
	if (debug == 0)
	  fprintf(stderr, "%c", *p);
	break;
      }
    }
  }
  va_end(pa);
}

void gplot_title(Gplot * gp, char * cad) {
  gplot_printf(gp, "set title '%s'\n", cad);
  gp->opcions[2] = true;
}

void gplot_untitle(Gplot * gp) {
  gplot_printf(gp, "unset title\n");
  gp->opcions[2] = false;
}

void gplot_xrange(Gplot * gp, gpfloat_t x0, gpfloat_t x1) {
  gplot_printf(gp, "set xrange[%f:%f]\n", x0, x1);
}

void gplot_yrange(Gplot * gp, gpfloat_t y0, gpfloat_t y1) {
  gplot_printf(gp, "set yrange[%f:%f]\n", y0, y1);
}

void gplot_zrange(Gplot * gp, gpfloat_t z0, gpfloat_t z1) {
  gplot_printf(gp, "set zrange[%f:%f]\n", z0, z1);
}

void gplot_xlabel(Gplot * gp, char * cad) {
  gplot_printf(gp, "set xlabel '%s'\n", cad);
}

void gplot_ylabel(Gplot * gp, char * cad) {
  gplot_printf(gp, "set ylabel '%s'\n", cad);
}

void gplot_zlabel(Gplot * gp, char * cad) {
  gplot_printf(gp, "set zlabel '%s'\n", cad);
}

void gplot_xtics(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set xtics '%f'\n", num);
}

void gplot_ytics(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set ytics '%f'\n", num);
}

void gplot_ztics(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set ytics '%f'\n", num);
}

void gplot_unxtics(Gplot * gp) {
  gplot_printf(gp, "unset xtics\n");
}

void gplot_unytics(Gplot * gp) {
  gplot_printf(gp, "unset ytics\n");
}

void gplot_unztics(Gplot * gp) {
  gplot_printf(gp, "unset ztics\n");
}

void gplot_logscale(Gplot * gp, char * axis, int base) {
  if (base <= 0)
    gplot_printf(gp, "set logscale %s\n", axis);
  else
    gplot_printf(gp, "set logscale %s %d\n", axis, base);
}

void gplot_unlogscale(Gplot * gp, char * axis) {
  gplot_printf(gp, "unset logscale %s\n", axis);
}

void gplot_lmargin(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set lmargin at screen %f\n", num);
}

void gplot_rmargin(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set rmargin at screen %f\n", num);
} 

void gplot_tmargin(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set tmargin at screen %f\n", num);
}

void gplot_bmargin(Gplot * gp, gpfloat_t num) {
  gplot_printf(gp, "set bmargin at screen %f\n", num);
}

void gplot_text(Gplot * gp, char * text, gpfloat_t x, gpfloat_t y) {
  gplot_printf(gp, "set label '%s' at %f, %f center\n", text, x, y);
}

void gplot_untext(Gplot * gp) {
  gplot_printf(gp, "unset label\n");
}

void gplot_text3D(Gplot * gp, char * text, gpfloat_t x, gpfloat_t y, gpfloat_t z) {
  gplot_printf(gp, "set label '%s' at %f, %f, %f center\n", text, x, y, z);
}

void gplot_untext3D(Gplot * gp) {
  gplot_untext(gp);
}

void gplot_arrow(Gplot * gp, int vec, gpfloat_t x0, gpfloat_t y0, gpfloat_t x1, gpfloat_t y1) {
  gplot_printf(gp, "set arrow from %f, %f to %f, %f %s\n", x0, y0, x1, y1, vec == 0 ? "head" : "nohead");
}

void gplot_unarrow(Gplot * gp) {
  gplot_printf(gp, "unset arrow\n");
}

void gplot_arrow3D(Gplot * gp, int vec, gpfloat_t x0, gpfloat_t y0, gpfloat_t z0, gpfloat_t x1, gpfloat_t y1, gpfloat_t z1) {
  gplot_printf(gp, "set arrow from %f, %f, %f to %f, %f, %f %s\n", x0, y0, z0, x1, y1, z1, vec == 0 ? "head" : "nohead");
}

void gplot_unarrow3D(Gplot * gp) {
  gplot_unarrow(gp);
}

void gplot_grid(Gplot * gp) {
  gplot_printf(gp, "set grid\n");
  gp->opcions[0] = true;
}

void gplot_ungrid(Gplot * gp) {
  gplot_printf(gp, "unset grid\n");
  gp->opcions[0] = false;
}

void gplot_key(Gplot * gp, char * title, int box, int ins, int ver, int pos) {
  char posi[9][12] = {"right\0", "center left\0", "cent\0", "cent right\0", "bottom left\0", "bot center\0", "bot right\0", "left top\0", "center top\0"};
  if ((pos < 0) || (pos > 8))
    pos = 0;
  if (strlen(title) != 0)
    gplot_printf(gp, "set key title '%s'\n", title);
  if (box == 0)
    gplot_printf(gp, "set key box\n");
  else
    gplot_printf(gp, "set key nobox\n");
  if (ins == 0)
    gplot_printf(gp, "set key ins\n");
  else
    gplot_printf(gp, "set key out\n");
  if (ver == 0)
    gplot_printf(gp, "set key vert\n");
  else
    gplot_printf(gp, "set key horiz\n");
  gplot_printf(gp, "set key %s\n", posi[pos]);
  gp->opcions[6] = true;
}

void gplot_unkey(Gplot * gp) {
  gplot_printf(gp, "unset key\n");
  gp->opcions[6] = false;
}

void gplot_colorbox(Gplot * gp) {
  gplot_printf(gp, "set colorbox\n");
  gp->opcions[3] = true;
}

void gplot_uncolorbox(Gplot * gp) {
  gplot_printf(gp, "unset colorbox\n");
  gp->opcions[3] = false;
}

void gplot_palette(Gplot * gp, int r, int g, int b) {
  if ((r > 36) || (r < -36))
    r = r % 37;
  if ((g > 36) || (g < -36))
    g = g % 37;
  if ((b > 36) || (b < -36))
    b = b % 37;
  gplot_printf(gp, "set palette rgb %d, %d, %d\n", r, g, b);
  gp->opcions[4] = true;
}

void gplot_unpalette(Gplot * gp) {
  gp->opcions[4] = false;
}

void gplot_multiplot(Gplot * gp, gpfloat_t orig_x, gpfloat_t orig_y, gpfloat_t size_x, gpfloat_t size_y) {
  if (gp->opcions[1] == false) {
    gplot_printf(gp, "set multiplot\n");
    gp->opcions[1] = true;
  }
  gplot_printf(gp, "set origin %f, %f\n", orig_x, orig_y);
  gplot_printf(gp, "set size %f, %f\n", size_x, size_y);
  gp->numPlots = gp->numPlots3D = 0;
}

void gplot_unmultiplot(Gplot * gp) {
  gplot_printf(gp, "unset multiplot\n");
  gp->opcions[1] = false;
}

void gplot_view(Gplot * gp, int rot_x, int rot_z, int scale_x, int scale_z) {
  gplot_printf(gp, "set view %d, %d, %d, %d\n", rot_x % 180, rot_z % 360, scale_x > 0 ? scale_x : 1, scale_z > 0 ? scale_z : 1);
}

void gplot_unview(Gplot * gp) {
  gplot_printf(gp, "set view 60, 30, 1, 1\n");
}

void gplot_levels(Gplot * gp, gpfloat_t * vec, int tam) {
  int i = 0;
  gp->levels = malloc(tam * sizeof(gpfloat_t));
  for (i = 0; i < tam; i++)
    gp->levels[i] = vec[i];
  gp->opcions[5] = true;
  gp->num_levels = tam;
}

void gplot_unlevels(Gplot * gp) {
  gp->opcions[5] = false;
  gp->num_levels = 0;
}

void gplot_colors(Gplot * gp, char cad[10][10]) {
  int i;
  for (i = 0; i < 10; i++)
    strcpy(gp->colors[i], cad[i]);
}

void gplot_samples(Gplot * gp, int samples) {
  gplot_printf(gp, "set samples %d\n", samples);
}

void gplot_fillTransparent(Gplot * gp, gpfloat_t trans) {
  gplot_printf(gp, "set style fill transparent solid %f noborder\n", trans);
}

void gplot_plot(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "lines", color, 0);
}

void gplot_plotFilled(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, gpfloat_t y_begin, char * title, char * color) {
  char filled[35];
  sprintf(filled, "filledcurves y1=%f", y_begin);
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, filled, color, 0);
}

void gplot_plotDots(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "dots", color, 0);
}

void gplot_plotPoints(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "points", color, 0);
}

void gplot_plotLinesPoints(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "linespoints", color, 0);
}

void gplot_plotImpulses(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "impulses", color, 0);
}

void gplot_plotSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "steps", color, 0);
}

void gplot_plotFSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "fsteps", color, 0);
}

void gplot_plotHiSteps(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "histeps", color, 0);
}

void gplot_plotBoxes(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam, char * title, char * color) {
  gplot_writeBin2D(gp, vec_x, vec_y, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "boxes", color, 0);
}

void gplot_plotXError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, int tam, char * title, char * color) {
  gplot_writeBin2DError(gp, vec_xx, vec_yy, vec_ex, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "xerrorbars", color, 0);
}

void gplot_plotYError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ey, int tam, char * title, char * color) {
  gplot_writeBin2DError(gp, vec_xx, vec_yy, vec_ey, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "yerrorbars", color, 0);
}

void gplot_plotXYError(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam, char * title, char * color) {
  gplot_writeBin2DErrors(gp, vec_xx, vec_yy, vec_ex, vec_ey, tam);
  gplot_plotPriv(gp, gp->fitBin[gp->numBin - 1], title, "xyerrorbars", color, 0);
}

void gplot_plotFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "lines", color, 1);
}

void gplot_plotFilledFile(Gplot * gp, char * arxiu, gpfloat_t y_begin, char * title, char * color) {
  char filled[35];
  sprintf(filled, "filledcurves y1=%f", y_begin);
  gplot_plotPriv(gp, arxiu, title, filled, color, 1);
}

void gplot_plotDotsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "dots", color, 1);
}

void gplot_plotPointsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "points", color, 1);
}

void gplot_plotLinesPointsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "linespoints", color, 1);
}

void gplot_plotImpulsesFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "impulses", color, 1);
}

void gplot_plotStepsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "steps", color, 1);
}

void gplot_plotFStepsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "fsteps", color, 1);
}

void gplot_plotHiStepsFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "histeps", color, 1);
}

void gplot_plotBoxesFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "boxes", color, 1);
}

void gplot_plotXErrorFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "xerrorbars", color, 1);
}

void gplot_plotYErrorFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "yerrorbars", color, 1);
}

void gplot_plotXYErrorFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plotPriv(gp, arxiu, title, "xyerrorbars", color, 1);
}

void gplot_plotEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "lines", color, 2);
}

void gplot_plotFilledEquation(Gplot * gp, char * eq, gpfloat_t y_begin, char * title, char * color) {
  char filled[35];
  sprintf(filled, "filledcurves y1=%f", y_begin);
  gplot_plotPriv(gp, eq, title, filled, color, 2);
}

void gplot_plotDotsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "dots", color, 2);
}

void gplot_plotPointsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "points", color, 2);
}

void gplot_plotLinesPointsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "linespoints", color, 2);
}

void gplot_plotImpulsesEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "impulses", color, 2);
}

void gplot_plotStepsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "steps", color, 2);
}

void gplot_plotFStepsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "fsteps", color, 2);
}

void gplot_plotHiStepsEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "histeps", color, 2);
}

void gplot_plotBoxesEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plotPriv(gp, eq, title, "boxes", color, 2);
}

void gplot_plotPriv(Gplot * gp, char * cad, char * title, char * with, char * color, int mode) {
  char * plot = "replot";
  char * amb = gplot_with(gp, with, 0, color);

  if (gp->numPlots == 0)
    plot = "plot";
  if (mode == 0)
    gplot_printf(gp, "%s '%s' binary record=(-1, -1) %s title '%s'\n", plot, cad, amb, title);
  else if (mode == 1)
    gplot_printf(gp, "%s '%s' %s title '%s'\n", plot, cad, amb, title);
  else if (mode == 2)
    gplot_printf(gp, "%s %s %s title '%s'\n", plot, cad, amb, title);
  else
    exit(-1);
  gp->numPlots = gp->numPlots + 1;
}

void gplot_plot3DColor(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 0, 0, 0);
}

void gplot_plot3DSurface(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 1, 0, 0);
}

void gplot_plot3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, char * title, char * color) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, color, 0, 2, 0, 0);
}

void gplot_plot3DContourSurface(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title, char * color) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, color, 0, 2, 1, num_lin);
}

void gplot_plot3DContour(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 2, 2, num_lin);
}

void gplot_contour(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 0, 3, num_lin);
}

void gplot_calorMap(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 1, 3, num_lin);
}

void gplot_contour3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 0, 2, num_lin);
}

void gplot_contour3DMap(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY, int num_lin, char * title) {
  gplot_writeBin3D(gp, vec_x, vec_y, mat, tamX, tamY);
  gplot_plot3DPriv(gp, gp->fitBin[gp->numBin - 1], title, "", 0, 1, 2, num_lin);
}

void gplot_plot3DColorFile(Gplot * gp, char * arxiu, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 0, 0, 0);
}

void gplot_plot3DSurfaceFile(Gplot * gp, char * arxiu, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 1, 0, 0);
}

void gplot_plot3DFile(Gplot * gp, char * arxiu, char * title, char * color) {
  gplot_plot3DPriv(gp, arxiu, title, color, 1, 2, 0, 0);
}

void gplot_plot3DContourSurfaceFile(Gplot * gp, char * arxiu, int num_lin, char * title, char * color) {
  gplot_plot3DPriv(gp, arxiu, title, color, 1, 2, 1, num_lin);
}

void gplot_plot3DContourFile(Gplot * gp, char * arxiu, int num_lin, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 2, 2, num_lin);
}

void gplot_contourFile(Gplot * gp, char * arxiu, int num_lin, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 0, 3, num_lin);
}

void gplot_calorMapFile(Gplot * gp, char * arxiu, int num_lin, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 1, 3, num_lin);
}

void gplot_contour3DFile(Gplot * gp, char * arxiu, int num_lin, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 0, 2, num_lin);
}

void gplot_contour3DMapFile(Gplot * gp, char * arxiu, int num_lin, char * title) {
  gplot_plot3DPriv(gp, arxiu, title, "", 1, 1, 2, num_lin);
}

void gplot_plot3DColorEquation(Gplot * gp, char * eq, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 0, 0, 0);
}

void gplot_plot3DSurfaceEquation(Gplot * gp, char * eq, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 1, 0, 0);
}

void gplot_plot3DEquation(Gplot * gp, char * eq, char * title, char * color) {
  gplot_plot3DPriv(gp, eq, title, color, 2, 2, 0, 0);
}

void gplot_plot3DContourSurfaceEquation(Gplot * gp, char * eq, int num_lin, char * title, char * color) {
  gplot_plot3DPriv(gp, eq, title, color, 2, 2, 1, num_lin);
}

void gplot_plot3DContourEquation(Gplot * gp, char * eq, int num_lin, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 2, 2, num_lin);
}

void gplot_contourEquation(Gplot * gp, char * eq, int num_lin, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 0, 3, num_lin);
}

void gplot_calorMapEquation(Gplot * gp, char * eq, int num_lin, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 1, 3, num_lin);
}

void gplot_contour3DEquation(Gplot * gp, char * eq, int num_lin, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 0, 2, num_lin);
}

void gplot_contour3DMapEquation(Gplot * gp, char * eq, int num_lin, char * title) {
  gplot_plot3DPriv(gp, eq, title, "", 2, 1, 2, num_lin);
}

void gplot_plot3DPriv(Gplot * gp, char * cad, char * title, char * color, int mode, int plot_mode, int contour_mode, int contour_levels) {
  int i;
  char * amb;
  char * plot = "replot";

  if (gp->numPlots3D == 0)
    plot = "splot";
  if (plot_mode < 0)
    exit(-1);
  else if (plot_mode < 2)
    amb = gplot_with(gp, "", 1, "");
  else
    amb = gplot_with(gp, "", 0, color);
  if (contour_mode > 0) {
    if (contour_mode == 1) {
      gplot_printf(gp, "set contour surface\n");
    }
    else if (contour_mode == 2) {
      gplot_printf(gp, "set contour base\n");
     }
    else if (contour_mode == 3) {
      gplot_printf(gp, "set contour base\n");
      gplot_printf(gp, "unset surface\n");
      gplot_printf(gp, "set view map\n");
    }
    if (gp->opcions[5] == true) {
      gplot_printf(gp, "set cntrparam levels discrete ");
      for (i = 0; i < (gp->num_levels); i++)
	gplot_printf(gp, " %f, ", gp->levels[i]);
      gplot_printf(gp, "%f\n", gp->levels[gp->num_levels - 1]);
    }
    else
      gplot_printf(gp, "set cntrparam levels %d\n", contour_levels);
  }
  if ((gp->opcions[4] == false))
    gplot_printf(gp, "set palette defined (0 '#000090', 1 '#000FFF', 2 '#0090FF', 3 '#0FFFEE', 4 '#90FF70', 5 '#FFEE00', 6 '#FF7000', 7 '#EE0000', 8 '#7F0000')\n");
  if (plot_mode == 1) {
    gplot_printf(gp, "set pm3d\n");
    gplot_printf(gp, "set hidden3d\n");
  }
  if (mode == 0)
    gplot_printf(gp, "%s '%s' binary matrix %s title '%s' %s\n", plot, cad, plot_mode < 2 ? "ls 1 palette" : "", title, amb);
  else if (mode == 1)
    gplot_printf(gp, "%s '%s' %s title '%s' %s\n", plot, cad, plot_mode < 2 ? "ls 1 palette" : "", title, amb);
  else if (mode == 2)
    gplot_printf(gp, "%s %s %s title '%s' %s\n", plot, cad, plot_mode < 2 ? "ls 1 palette" : "", title, amb);
  if (plot_mode == 1) {
    gplot_printf(gp, "unset pm3d\n");
    gplot_printf(gp, "unset hidden3d\n");
  }
  if (contour_mode > 0)
    gplot_printf(gp, "unset contour\n");
  gp->numPlots3D = gp->numPlots3D + 1;
}

void gplot_export2D(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam) {
  int i;
  FILE * exp;
  if (strlen(arxiu) == 0)
    arxiu = "data2D.dat";
  exp = fopen(arxiu, "w");
  for (i = 0; i < tam; i++)
    fprintf(exp, "%.18e %.18e\n", vec_x[i], vec_y[i]);
  fclose(exp);
}

void gplot_export2DError(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t * vec_e, int tam) {
  int i;
  FILE * exp;
  if (strlen(arxiu) == 0)
    arxiu = "data2DError.dat";
  exp = fopen(arxiu, "w");
  for (i = 0; i < tam; i++)
    fprintf(exp, "%.18e %.18e %.18e\n", vec_x[i], vec_y[i], vec_e[i]);
  fclose(exp);
}

void gplot_export2DErrors(char * arxiu, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam) {
  int i;
  FILE * exp;
  if (strlen(arxiu) == 0)
    arxiu = "data2DErrors.dat";
  exp = fopen(arxiu, "w");
  for (i = 0; i < tam; i++)
    fprintf(exp, "%.18e %.18e %.18e %.18e\n", vec_xx[i], vec_yy[i], vec_ex[i], vec_ey[i]);
  fclose(exp);
}

void gplot_export3D(char * arxiu, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY) {
  int i, j;
  FILE * exp;
  if (strlen(arxiu) == 0)
    arxiu = "data3D.dat";
  exp = fopen(arxiu, "w");
  for (i = 0; i < tamX; i++)
    for (j = 0; j < tamY; j++)
      fprintf(exp, "%.18e %.18e %.18e\n", vec_x[i], vec_y[j], mat[i][j]);
  fclose(exp);
}

void gplot_writeBin2D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, int tam) {
  int i;
  FILE * tmp_f;

  gplot_newBin(gp);
  tmp_f = fopen(gp->fitBin[gp->numBin - 1], "wb");
  for (i = 0; i < tam; i++) {
    fwrite(&vec_x[i], sizeof(vec_x[0]), 1, tmp_f);
    fwrite(&vec_y[i], sizeof(vec_y[0]), 1, tmp_f);
  }
  fclose(tmp_f);
}

void gplot_writeBin2DError(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t * vec_e, int tam) {
  int i;
  FILE * tmp_f;

  gplot_newBin(gp);
  tmp_f = fopen(gp->fitBin[gp->numBin - 1], "wb");
  for (i = 0; i < tam; i++) {
    fwrite(&vec_x[i], sizeof(vec_x[0]), 1, tmp_f);
    fwrite(&vec_y[i], sizeof(vec_y[0]), 1, tmp_f);
    fwrite(&vec_e[i], sizeof(vec_e[0]), 1, tmp_f);
  }
  fclose(tmp_f);
}

void gplot_writeBin2DErrors(Gplot * gp, gpfloat_t * vec_xx, gpfloat_t * vec_yy, gpfloat_t * vec_ex, gpfloat_t * vec_ey, int tam) {
  int i;
  FILE * tmp_f;

  gplot_newBin(gp);
  tmp_f = fopen(gp->fitBin[gp->numBin - 1], "wb");
  for (i = 0; i < tam; i++) {
    fwrite(&vec_xx[i], sizeof(vec_xx[0]), 1, tmp_f);
    fwrite(&vec_yy[i], sizeof(vec_yy[0]), 1, tmp_f);
    fwrite(&vec_ex[i], sizeof(vec_ex[0]), 1, tmp_f);
    fwrite(&vec_ey[i], sizeof(vec_ey[0]), 1, tmp_f);
  }
  fclose(tmp_f);
}

void gplot_writeBin3D(Gplot * gp, gpfloat_t * vec_x, gpfloat_t * vec_y, gpfloat_t ** mat, int tamX, int tamY) {
  int i, j;
  gpfloat_t aux = (gpfloat_t) (tamY);
  FILE * tmp_f;
  gplot_newBin(gp);
  tmp_f = fopen(gp->fitBin[gp->numBin - 1], "wb");
  fwrite(&aux, sizeof(gpfloat_t), 1, tmp_f);
  fwrite(vec_y, sizeof(gpfloat_t), tamY, tmp_f);
  for (i = 0; i < tamX; i++) {
    fwrite(&vec_x[i], sizeof(gpfloat_t), 1, tmp_f);
    for (j = 0; j < tamY; j++)
      fwrite(&mat[i][j], sizeof(mat[0][0]), 1, tmp_f);
  }
  fclose(tmp_f);
}

_GplotBool colorValid(char * color) {
  unsigned int i;
  if (strlen(color) != 7)
    return false;
  if (color[0] != '#')
    return false;
  for (i = 1; i < strlen(color); i++)
    if (!isxdigit(color[i]))
      return false;
  return true;
}

char * gplot_with(Gplot * gp, char * cad, int colors, char * color) {
  int pos = (gp->numPlots + gp->numPlots3D) % 10;
  char * ret;
  char * aux1 = "with ";
  char * aux2 = " lc rgb ";
  char * lin = "lines";
  char * com = "'";
  ret = malloc(50 * sizeof(char));
  strcpy(ret, aux1);
  if ((strcmp(cad, "dots") == 0) || (strcmp(cad, "points") == 0) || (strcmp(cad, "linespoints") == 0) || (strcmp(cad, "impulses") == 0) || (strcmp(cad, "steps") == 0) || (strcmp(cad, "fsteps") == 0) || (strcmp(cad, "histeps") == 0) || (strcmp(cad, "boxes") == 0)|| (strcmp(cad, "xerrorbars") == 0)|| (strcmp(cad, "yerrorbars") == 0) || (strcmp(cad, "xyerrorbars") == 0) || (strncmp(cad, "filledcurves", 12) == 0))
    strcat(ret, cad);
  else
    strcat(ret, lin);
  if (colors == 0) {
    strcat(ret, aux2);
    strcat(ret, com);
    if (colorValid(color) == true)
      strcat(ret, color);
    else
      strcat(ret, gp->colors[pos]);
    strcat(ret, com);
  }
  return ret;
}

void gplot_reset(Gplot * gp, char * cad) {
  gplot_exit(gp);
  gplot_init(gp, cad);
}

void gplot_exit(Gplot * gp) {
  if (strcmp(gp->term, "qt") != 0) {
    gplot_printf(gp, "set output '%s'\n", gp->name);
    gplot_printf(gp, "replot\n");
  }
  gplot_printf(gp, "exit\n");
  fflush(gp->arxiu);
  pclose(gp->arxiu);
  gp->term = "";
  gplot_delBin(gp);
}

void gplot_newBin(Gplot * gp) {
  if (gp->numBin >= _GPLOT_MAXBIN)
    gplot_delBin(gp);
  /* tmpnam(gp->fitBin[gp->numBin]); */
  strcpy(gp->fitBin[gp->numBin], P_tmpdir);
  strcat(gp->fitBin[gp->numBin], "/gplotXXXXXX");
  mkstemp(gp->fitBin[gp->numBin]);
  gp->numBin = gp->numBin + 1;
}

void gplot_delBin(Gplot * gp) {
  int i;
  for (i = 0; i < gp->numBin; i++)
    unlink(gp->fitBin[i]);
  gp->numBin = 0;
}
