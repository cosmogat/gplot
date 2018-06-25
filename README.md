# gplot
Graphing library for C based in gnuplot
## Dependences
You need gnuplot to use this library, in Debian GNU/Linux you can do this:
```
apt install gnuplot
```
This library tested in gnuplot 5.0 patchlevel rc2.
## Using

### Using with installation
### Using without installation
You can use this library like a normal library in C, including the header file and compile *.c file. For example, if you have a c file called test.c with the next include:
```
#include "gplot.h"
```
You can compile with:
```
gcc test.c gplot.c -o test
```
If gplot.c, gplot.h and test.c  are in the same directory. If you want to test with the test file called *prova_gplot.c* you can do this in the command line:
```
cp src/gplot.{c,h} test/
cd test
gcc prova_gplot.c gplot.c -lm -o test
rm gplot.{c,h}
./test
```


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
