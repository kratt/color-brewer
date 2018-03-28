# Color Brewer

Class-based implementation of [Color Brewer](http://colorbrewer2.org).


#### Available color schemes:<br>
* Diverging:   Spectral, RdYlGn, RdBu, PiYG, PRGn, RdYlBu, BrBG, RdGy, PuOr<br>
* Qualitative: Set2, Accent, Set1, Set3, Dark2, Paired, Pastel2, Pastel1<br>
* Sequential:  OrRd, PuBu, BuPu, Oranges, BuGn, YlOrBr, YlGn, Reds, RdPu, Greens, YlGnBu, Purples, GnBu, Greys, YlOrRd, PuRd, Blues, PuBuGn<br>

#### Properties: <br>
blind, print, copy, screen

#### Usage:<br>
ColorBrewer brewer;<br>
std::vector<float> rgb = brewer.getDiverging(9, ColorBrewer::Diverging::BrBG, {});<br>
std::vector< std::vector<float> > rgbs = brewer.getDivering(7, {ColorBrewer::Properties::print});
