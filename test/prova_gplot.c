/* 15-07-2013 */
/* alejandro */
/* prova_gplot.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <math.h>
#include "gplot.h"

double temps();

int main () {
  int quants = 100;
  float x0 = -20.0, x1 = 20.0, p0 = -10.0, p1 = 10.0, m = 1.0;
  int i, j;
  float x[quants], V[quants], p[quants], X[quants], Y[quants], xxx[quants], sinus[quants], dif_x, dif_p;
  float nivells[13] = {-9.99, -9.0, -5.32, -3.0, 4.5, 10.0, 15.0, 20.0, 30.0, 41.3, 56.0, 50.66, 59.99};
  float xx[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 , 8.0, 9.0, 10.0};
  float yy[10] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0};
  float ex[10] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
  float ey[10] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
  Gplot graf;
  char cad[20];
  float ** Z0, ** Z1, ** E;
  Z0 = (float **) malloc(quants * sizeof(float *));
  for (i = 0; i < quants; i++)
    Z0[i] = (float *) malloc(quants * sizeof(float));
  Z1 = (float **) malloc(quants * sizeof(float *));
  for (i = 0; i < quants; i++)
    Z1[i] = (float *) malloc(quants * sizeof(float));
  E = (float **) malloc(quants * sizeof(float *));
  for (i = 0; i < quants; i++)
    E[i] = (float *) malloc(quants * sizeof(float));
  
  /* Calculs */
  dif_x = (x1 - x0) / quants;
  dif_p = (p1 - p0) / quants;
  x[0] = x0;
  p[0] = p0;
  V[0] = 100 * x[0] / (25 + (x[0] * x[0]));
  for (i = 1; i < quants; i++) {
    x[i] = x[i - 1] + dif_x;
    p[i] = p[i - 1] + dif_p;
    V[i] = 100 * x[i] / (25 + (x[i] * x[i]));
  }
  for (i = 0; i < quants; i++)
    for (j = 0; j < quants; j++)
       E[i][j] = (((p[i] * p[i]) / (2 * m)) + V[j]);
  X[0] = Y[0] = p0;
  for (i = 1; i < quants; i++)
    X[i] = Y[i] = X[i - 1] + dif_p;
  for (i = 0; i < quants; i++)
    for (j = 0; j < quants; j++) {
      Z0[i][j] = sin(X[i]) * sin(Y[j]);
      Z1[i][j] = cos(X[i]) * cos(Y[j]);
    }

  /* /\* Gràfiques transparents *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_fillTransparent(&graf, 0.5); */
  /* gplot_xrange(&graf, 0.1, 3); */
  /* gplot_yrange(&graf, -0.6, 0.6); */
  /* gplot_key(&graf, "Sinus", 1, 0, 1, 5); */
  /* xxx[0] = 0; */
  /* gplot_logscale(&graf, "x", 10); */
  /* gplot_unlogscale(&graf, "x"); */
  /* dif_x = 3.0 / quants; */
  /* for (i = 1; i < quants; i++) */
  /*   xxx[i] = xxx[i - 1] + dif_x; */
  /* for (i = 2; i < 10; i++) { */
  /*   for (j = 0; j < quants; j++) */
  /*     sinus[j] = sin(xxx[j] * i) / i; */
  /*   sprintf(cad, "sin(%d·x)/%d", i, i); */
  /*   gplot_plotFilled(&graf, xxx, sinus, quants, 0.0, cad, ""); */
  /* } */
  /* gplot_exit(&graf); */

  /* /\* Gràfica d'errors *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_plot(&graf, xx, yy, 10, "", ""); */
  /* gplot_plotXYError(&graf, xx, yy, ex, ey, 10, "", ""); */
  /* gplot_exit(&graf); */

  /* /\* Gràfica d'una equació *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_title(&graf, "Gràfiques"); */
  /* gplot_yrange(&graf, -10, 10); */
  /* gplot_key(&graf, "", 0, 0, 0, 0); */
  /* gplot_samples(&graf, 1000); */
  /* gplot_plotEquation(&graf, "sin(x)", "sinus", "#000000"); */
  /* gplot_plotDotsEquation(&graf, "cos(x)", "cosinus", "#FF0000"); */
  /* gplot_plotPointsEquation(&graf, "tan(x)", "tangent", "#00FF00"); */
  /* gplot_plotLinesPointsEquation(&graf, "log(x)", "logaritme", "#0000FF"); */
  /* gplot_plotImpulsesEquation(&graf, "sqrt(x)", "arrel", "#FFFF00"); */
  /* gplot_plotStepsEquation(&graf, "sinh(x)", "sinus hiperbolic", "#00FFFF"); */
  /* gplot_plotFStepsEquation(&graf, "cosh(x)", "cosinus hiperbolic", "#FF00FF"); */
  /* gplot_plotHiStepsEquation(&graf, "0.1*x", "0.1x", "#FFF000"); */
  /* gplot_plotBoxesEquation(&graf, "-sqrt(x)", "-arrel", "#000FFF"); */
  /* gplot_exit(&graf); */

  /* /\* Gràfica 2D *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_title(&graf, "Potencials"); */
  /* gplot_xlabel(&graf, "x"); */
  /* gplot_ylabel(&graf, "V(x)"); */
  /* gplot_xrange(&graf, x0, x1); */
  /* gplot_yrange(&graf, p0, p1); */
  /* gplot_plot(&graf, x, V, quants, "", ""); */
  /* gplot_plotEquation(&graf, "(x*x) - 10", "", ""); */
  /* gplot_exit(&graf); */

  /* /\* Gràfica 2D d'un fitxer *\/ */
  /* gplot_export2D("pot.dat", x, V, quants); */
  /* gplot_init(&graf, ""); */
  /* gplot_title(&graf, "Potencial des de fitxer"); */
  /* gplot_plotFile(&graf, "pot.dat", "", ""); */
  /* gplot_exit(&graf); */

  /* Contorn */
  gplot_init(&graf, "");
  gplot_title(&graf, "Espai de fases");
  gplot_xlabel(&graf, "x");
  gplot_ylabel(&graf, "p");
  gplot_levels(&graf, nivells, 13);
  gplot_palette(&graf, 23, 28, 3);
  gplot_contour(&graf, p, x, E, quants, quants, 15, "");
  gplot_exit(&graf);

  /* Varies gràfiques: gràfica 2D i contorn */
  gplot_init(&graf, "");
  gplot_title(&graf, "Potencial i espai de fases");
  gplot_grid(&graf);
  gplot_xrange(&graf, x0, x1);
  gplot_yrange(&graf, p0, p1);
  gplot_xlabel(&graf, "x");
  gplot_ylabel(&graf, "V(x)");
  gplot_xtics(&graf, 5.0);
  gplot_ytics(&graf, 5.0);
  gplot_lmargin(&graf, 0.09);
  gplot_rmargin(&graf, 0.93);
  gplot_multiplot(&graf, 0.0, 0.5, 1.0, 0.5);
  gplot_plot(&graf, x, V, quants, "", "");
  gplot_multiplot(&graf, 0.0, 0.0, 1.0, 0.6);
  gplot_untitle(&graf);
  gplot_ylabel(&graf, "p");
  gplot_levels(&graf, nivells, 13);
  gplot_contour(&graf, p, x, E, quants, quants, 15, "");
  gplot_exit(&graf);

  /* /\* Varies gràfiques 2D *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_multiplot(&graf, 0.0, 0.5, 0.5, 0.5); */
  /* gplot_plotEquation(&graf, "sin(x)", "", ""); */
  /* gplot_multiplot(&graf, 0.0, 0.0, 0.5, 0.5); */
  /* gplot_plotEquation(&graf, "cos(x)", "", ""); */
  /* gplot_multiplot(&graf, 0.5, 0.0, 0.5, 0.5); */
  /* gplot_plotEquation(&graf, "sin(x)*cos(x)", "", ""); */
  /* gplot_multiplot(&graf, 0.5, 0.5, 0.5, 0.5); */
  /* gplot_plotEquation(&graf, "sin(x)*sin(x)", "", ""); */
  /* gplot_exit(&graf); */

  /* /\* Gràfiques 3D *\/ */
  /* gplot_init(&graf, ""); */
  /* gplot_key(&graf, "", 0, 0, 0, 0); */
  /* gplot_xrange(&graf, -10, 10); */
  /* gplot_yrange(&graf, -10, 10); */
  /* gplot_zrange(&graf, -1, 1); */
  /* gplot_text3D(&graf, "Màxims", -10, 10, 1.6); */
  /* for (i = 1; i < 8; i += 4) */
  /*   for (j = 1; j < 8; j += 4) */
  /*     gplot_arrow3D(&graf, 1, -10, 10, 1.5, (i * 3.1416) / 2, (j * 3.1416) / 2, 1); */
  /* gplot_plot3D(&graf, X, Y, Z0, quants, quants, "Sinus 3D", ""); */
  /* gplot_plot3D(&graf, X, Y, Z1, quants, quants, "Cosinus 3D", ""); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_plot3DColor(&graf, X, Y, Z0, quants, quants, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_plot3DSurface(&graf, X, Y, Z0, quants, quants, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_plot3DContourSurface(&graf, X, Y, Z0, quants, quants, 15,  "Sinus 3D", ""); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_contour(&graf, X, Y, Z0, quants, quants, 15, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_calorMap(&graf, X, Y, Z0, quants, quants, 15, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_contour3D(&graf, X, Y, Z0, quants, quants, 15, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  /* gplot_init(&graf, ""); */
  /* gplot_contour3DMap(&graf, X, Y, Z0, quants, quants, 15, "Sinus 3D"); */
  /* gplot_exit(&graf); */

  return 0;
}

double temps() {
  clock_t ct;
  struct tms t;
  
  ct = times(&t);
  if ( ct == (clock_t) - 1 )
    return 0.0; 
  else
    return (((double) t.tms_utime ) / ((double) sysconf(_SC_CLK_TCK)));
}
