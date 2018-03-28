//Author: Julian Kratt
//Date: 09.07.2015

#ifndef COLORBREWER
#define COLORBREWER

#include <map>
#include <vector>

/**
**  Available color schemes:
**	Diverging:   Spectral, RdYlGn, RdBu, PiYG, PRGn, RdYlBu, BrBG, RdGy, PuOr
**  Qualitative: Set2, Accent, Set1, Set3, Dark2, Paired, Pastel2, Pastel1
**  Sequential:  OrRd, PuBu, BuPu, Oranges, BuGn, YlOrBr, YlGn, Reds, RdPu, Greens, YlGnBu, Purples, GnBu, Greys, YlOrRd, PuRd, Blues, PuBuGn
**
**	Properties: blind, print, copy, screen
**
**	Usage:
**  ColorBrewer brewer;
**	std::vector<float> rgb = brewer.getDiverging(9, ColorBrewer::Diverging::BrBG, {});
**  std::vector< std::vector<float> > rgbs = brewer.getDivering(7, {ColorBrewer::Properties::print});
**
**/


class ColorBrewer
{

public:
	enum Diverging
	{
		Spectral, RdYlGn, RdBu, PiYG, PRGn, RdYlBu, BrBG, RdGy, PuOr
	};

	enum Qualitative
	{
		Set2, Accent, Set1, Set3, Dark2, Paired, Pastel2, Pastel1
	};

	enum Sequential
	{
		OrRd, PuBu, BuPu, Oranges, BuGn, YlOrBr, YlGn, Reds, RdPu, Greens, YlGnBu, Purples, GnBu, Greys, YlOrRd, PuRd, Blues, PuBuGn
	};

	enum Properties
	{
		blind, print, copy, screen
	};


	struct ColorScheme
	{
		std::map< unsigned int, std::vector<float> > rgbs;
		std::map< unsigned int, std::map<Properties, unsigned short> > properties;
	};


public:
	ColorBrewer();
	~ColorBrewer();

	void setNormalization(bool norm);

	// get single color scheme
	std::vector<float> getDiverging(int n, Diverging name = Spectral, const std::vector<Properties> &properties = {});
	std::vector<float> getQualitative(int n, Qualitative name = Set2, const std::vector<Properties> &properties = {});
	std::vector<float> getSequential(int n, Sequential name = OrRd, const std::vector<Properties> &properties = {});

	// get multiple color schemes
	std::vector< std::vector<float> > getDivergings(int n, const std::vector<Properties> &properties = { });
	std::vector< std::vector<float> > getQualitatives(int n, const std::vector<Properties> &properties = { });
	std::vector< std::vector<float> > getSequentials(int n, const std::vector<Properties> &properties = { });


private:
	void initDiverging();
	void initQualitative();
	void initSequential();

	std::map<Diverging, ColorScheme>   m_diverging;
	std::map<Qualitative, ColorScheme> m_qualitative;
	std::map<Sequential, ColorScheme>  m_sequential;

	bool m_normalize;
};


#endif
