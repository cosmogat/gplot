# gplot
Graphing library for C based in gnuplot
## Dependences
You need gnuplot to use this library, in Debian GNU/Linux you can do this:
```
apt install gnuplot
```
This library tested in gnuplot 5.0 patchlevel rc2.
## Using
For download the code you can write this on your shell:
```
git clone https://github.com/cosmogat/gplot.git
```
You can use this library installing in your operative system or use like a normal c library. If you want some examples for use this library you can see *prova_gplot.c* file.

### Using with installation
There is an installation script, that installs this library in */usr/local* tree. You can install this library with:
```
sudo ./install.sh
```
After, you can use the library like the next example. Imagine that you have a C file called "file.c" that contents:
```
#include <stdio.h>
#include <stdlib.h>
#include <gplot.h>
#define N 100
int main () {
  Gplot graph;
  int i = 0;
  float x[N], y1[N], y2[N], y3[N], y4[N], y5[N];
  for (i = 0; i < N; i++) {
    x[i] = (((float) i) * 0.01);
    y1[i] = x[i];
    y2[i] = y1[i] * x[i];
    y3[i] = y2[i] * x[i];
    y4[i] = y3[i] * x[i];
    y5[i] = y4[i] * x[i];
  }
  gplot_init(&graph, "ex1.png");
  gplot_title(&graph, "Graph title");
  gplot_key(&graph, "", 1, 0, 0, 7);
  gplot_xlabel(&graph, "x");
  gplot_ylabel(&graph, "y");
  gplot_plot(&graph, x, y1, N, "  x", "");
  gplot_plot(&graph, x, y2, N, "x^2", "");
  gplot_plot(&graph, x, y3, N, "x^3", "");
  gplot_plot(&graph, x, y4, N, "x^4", "");
  gplot_plot(&graph, x, y5, N, "x^5", "");
  gplot_exit(&graph);
  return 0;
}
```
And you can compile this with:
```
gcc -lgplot file.c -o output
```
Then you execute the ouput file and you obtain this png file:

### Using without installation
You can use this library like a normal library in C, including the header file and compile *.c file. For example, if you have a c file called test.c with the next include:
```
#include "gplot.h"
```
You can compile with:
```
gcc test.c gplot.c -o test
```
If gplot.c, gplot.h and test.c are in the same directory. If you want to test with the test file called *prova_gplot.c* you can do this in the command line:
```
cp src/gplot.{c,h} test/
cd test
gcc prova_gplot.c gplot.c -lm -o test
rm gplot.{c,h}
./test
```
## Autors
* **Cosmo Cat**  [cosmogat](https://github.com/cosmogat)
## License
See the [LICENSE](LICENSE)
