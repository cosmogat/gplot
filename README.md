# gplot
Graphing library for C based in gnuplot
## Dependences
You need gnuplot to use this library, in Debian GNU/Linux you can do this:
```
apt install gnuplot
```
This library tested in gnuplot 5.0 patchlevel rc2.
## Example
```
...
#include "gplot.h"
...
Gplot graf;
...
gplot_init(&graf, ""); 
gplot_fillTransparent(&graf, 0.5); 
gplot_xrange(&graf, 0.1, 3); 
gplot_yrange(&graf, -0.6, 0.6); 
gplot_key(&graf, "Sinus", 1, 0, 1, 5); 
xxx[0] = 0;
gplot_logscale(&graf, "x", 10); 
gplot_unlogscale(&graf, "x");
dif_x = 3.0 / 1000.0; 
for (i = 1; i < 1000; i++)
  xxx[i] = xxx[i - 1] + dif_x;
for (i = 2; i < 10; i++) { */
  for (j = 0; j < 1000; j++)
    sinus[j] = sin(xxx[j] * i) / i;
  sprintf(cad, "sin(%d·x)/%d", i, i);
  gplot_plotFilled(&graf, xxx, sinus, quants, 0.0, cad, "");
   } 
gplot_exit(&graf);
```
You can see more examples in [prova_gplot.c](./prova_gplot.c)
## Autors
* **Cosmo Cat**  [cosmogat](https://github.com/cosmogat)
## License
See the [LICENSE](LICENSE)
