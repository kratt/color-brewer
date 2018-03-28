//Author: Julian Kratt
//Date: 09.07.2015


#include "ColorBrewer.h"
#include <iostream>
#include <algorithm> 
#include <functional> 

ColorBrewer::ColorBrewer()
: m_normalize(true)
{
	initDiverging();
	initQualitative();
	initSequential();
}


ColorBrewer::~ColorBrewer()
{
}

std::vector<float> ColorBrewer::getDiverging(int n, Diverging name, const std::vector<Properties> &props)
{
	auto iterScheme = m_diverging.find(name);
	if (iterScheme == m_diverging.end())
	{
		std::cout << "ColorBrewer::getDiverging(): No color scheme with such name available.";
		return std::vector<float>();
	}

	const ColorScheme &scheme = iterScheme->second;
	auto iterRgb = scheme.rgbs.find(n);
	if (iterRgb == scheme.rgbs.end())
	{
		std::cout << "ColorBrewer::getDiverging(): No color scheme available.";
		return std::vector<float>();
	}

	const auto &schemeProp = scheme.properties;

	for (int i = 0; i < props.size(); ++i)
	{
		Properties curProp = props[i];
		unsigned short val = schemeProp.at(n).at(curProp);
	
		if (val == 0 || val == 2)
			return std::vector<float>();
	}

	std::vector<float> rgb = iterRgb->second;

	if (m_normalize)
		std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

	return rgb;
}

std::vector<float> ColorBrewer::getQualitative(int n, Qualitative name, const std::vector<Properties> &props)
{
	auto iterScheme = m_qualitative.find(name);

	if (iterScheme == m_qualitative.end())
	{
		std::cout << "ColorBrewer::getQualitative(): No color scheme with such name available.";
		return std::vector<float>();
	}

	ColorScheme &scheme = iterScheme->second;
	auto iterRgb = scheme.rgbs.find(n);
	if (iterRgb == scheme.rgbs.end())
	{
		std::cout << "ColorBrewer::getQualitative(): No color scheme available.";
		return std::vector<float>();
	}

	const auto &schemeProp = scheme.properties;
	for (int i = 0; i < props.size(); ++i)
	{
		Properties curProp = props[i];
		unsigned short val = schemeProp.at(n).at(curProp);

		if (val == 0 || val == 2)
			return std::vector<float>();
	}

	std::vector<float> rgb = iterRgb->second;

	if (m_normalize)
		std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

	return rgb;
}

std::vector<float> ColorBrewer::getSequential(int n, Sequential name, const std::vector<Properties> &props)
{
	auto iterScheme = m_sequential.find(name);
	if (iterScheme == m_sequential.end())
	{
		std::cout << "ColorBrewer::getSequential(): No color scheme with such name available.";
		return std::vector<float>();
	}
		

	ColorScheme &scheme = iterScheme->second;
	auto iterRgb = scheme.rgbs.find(n);
	if (iterRgb == scheme.rgbs.end())
	{
		std::cout << "ColorBrewer::getSequential(): No color scheme available.";
		return std::vector<float>();
	}
		

	const auto &schemeProp = scheme.properties;
	for (int i = 0; i < props.size(); ++i)
	{
		Properties curProp = props[i];
		unsigned short val = schemeProp.at(n).at(curProp);

		if (val == 0 || val == 2)
			return std::vector<float>();
	}

	std::vector<float> rgb = iterRgb->second;

	if (m_normalize)
		std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

	return rgb;
}

std::vector< std::vector<float> > ColorBrewer::getDivergings(int n, const std::vector<Properties> &props)
{
	std::vector< std::vector<float> > resRgbs;

	for (auto iterScheme = m_diverging.begin(); iterScheme != m_diverging.end(); ++iterScheme)
	{
		ColorScheme &scheme = iterScheme->second;

		auto iterRgb = scheme.rgbs.find(n);
		if (iterRgb == scheme.rgbs.end())
			continue;

		bool isValid = true;

		const auto &schemeProp = scheme.properties;
		for (int i = 0; i < props.size(); ++i)
		{
			Properties curProp = props[i];
			unsigned short val = schemeProp.at(n).at(curProp);
			
			if (val == 0 || val == 2)
			{
				isValid = false;
				break;
			}
		}

		if (isValid)
		{
			std::vector<float> rgb = iterRgb->second;

			if (m_normalize)
				std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

			resRgbs.push_back(rgb);
		}		
	}	

	return resRgbs;
}

std::vector< std::vector<float> > ColorBrewer::getQualitatives(int n, const std::vector<Properties> &props)
{
	std::vector< std::vector<float> > resRgbs;

	for (auto iterScheme = m_qualitative.begin(); iterScheme != m_qualitative.end(); ++iterScheme)
	{
		ColorScheme &scheme = iterScheme->second;

		auto iterRgb = scheme.rgbs.find(n);
		if (iterRgb == scheme.rgbs.end())
			continue;

		bool isValid = true;

		const auto &schemeProp = scheme.properties;
		for (int i = 0; i < props.size(); ++i)
		{
			Properties curProp = props[i];
			unsigned short val = schemeProp.at(n).at(curProp);

			if (val == 0 || val == 2)
			{
				isValid = false;
				break;
			}
		}

		if (isValid)
		{
			std::vector<float> rgb = iterRgb->second;

			if (m_normalize)
				std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

			resRgbs.push_back(rgb);
		}
	}

	return resRgbs;
}

std::vector< std::vector<float> > ColorBrewer::getSequentials(int n, const std::vector<Properties> &props)
{
	std::vector< std::vector<float> > resRgbs;

	for (auto iterScheme = m_sequential.begin(); iterScheme != m_sequential.end(); ++iterScheme)
	{
		ColorScheme &scheme = iterScheme->second;

		auto iterRgb = scheme.rgbs.find(n);
		if (iterRgb == scheme.rgbs.end())
			continue;

		bool isValid = true;

		const auto &schemeProp = scheme.properties;
		for (int i = 0; i < props.size(); ++i)
		{
			Properties curProp = props[i];
			unsigned short val = schemeProp.at(n).at(curProp);

			if (val == 0 || val == 2)
			{
				isValid = false;
				break;
			}
		}

		if (isValid)
		{
			std::vector<float> rgb = iterRgb->second;

			if (m_normalize)
				std::transform(rgb.begin(), rgb.end(), rgb.begin(), std::bind2nd(std::divides<float>(), 255.0f));

			resRgbs.push_back(rgb);
		}
	}

	return resRgbs;
}

void ColorBrewer::setNormalization(bool norm)
{
	m_normalize = norm;
}

void ColorBrewer::initDiverging()
{
	ColorScheme scheme;
	std::vector<float> rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8, rgb_9, rgb_10, rgb_11;
	std::map<Properties, unsigned short> prop_3, prop_4, prop_5, prop_6, prop_7, prop_8, prop_9, prop_10, prop_11;

	
	// spectral
	rgb_3 = std::vector<float>({ 252.0f, 141.0f, 89.0f, 255.0f, 255.0f, 191.0f, 153.0f, 213.0f, 148.0f });
	rgb_4 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 171.0f, 221.0f, 164.0f, 43.0f, 131.0f, 186.0f });
	rgb_5 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 255.0f, 255.0f, 191.0f, 171.0f, 221.0f, 164.0f, 43.0f, 131.0f, 186.0f });
	rgb_6 = std::vector<float>({ 213.0f, 62.0f, 79.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 139.0f, 230.0f, 245.0f, 152.0f, 153.0f, 213.0f, 148.0f, 50.0f, 136.0f, 189.0f });
	rgb_7 = std::vector<float>({ 213.0f, 62.0f, 79.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 230.0f, 245.0f, 152.0f, 153.0f, 213.0f, 148.0f, 50.0f, 136.0f, 189.0f });
	rgb_8 = std::vector<float>({ 213.0f, 62.0f, 79.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 230.0f, 245.0f, 152.0f, 171.0f, 221.0f, 164.0f, 102.0f, 194.0f, 165.0f, 50.0f, 136.0f, 189.0f });
	rgb_9 = std::vector<float>({ 213.0f, 62.0f, 79.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 230.0f, 245.0f, 152.0f, 171.0f, 221.0f, 164.0f, 102.0f, 194.0f, 165.0f, 50.0f, 136.0f, 189.0f });
	rgb_10 = std::vector<float>({ 158.0f, 1.0f, 66.0f, 213.0f, 62.0f, 79.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 230.0f, 245.0f, 152.0f, 171.0f, 221.0f, 164.0f, 102.0f, 194.0f, 165.0f, 50.0f, 136.0f, 189.0f, 94.0f, 79.0f, 162.0f });
	rgb_11 = std::vector<float>({ 158.0f, 1.0f, 66.0f, 213.0f, 62.0f, 79.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 230.0f, 245.0f, 152.0f, 171.0f, 221.0f, 164.0f, 102.0f, 194.0f, 165.0f, 50.0f, 136.0f, 189.0f, 94.0f, 79.0f, 162.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });


	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::Spectral, scheme));


	// RdYlGn
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 252.0f, 141.0f, 89.0f, 255.0f, 255.0f, 191.0f, 145.0f, 207.0f, 96.0f });
	rgb_4 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 166.0f, 217.0f, 106.0f, 26.0f, 150.0f, 65.0f });
	rgb_5 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 255.0f, 255.0f, 191.0f, 166.0f, 217.0f, 106.0f, 26.0f, 150.0f, 65.0f });
	rgb_6 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 139.0f, 217.0f, 239.0f, 139.0f, 145.0f, 207.0f, 96.0f, 26.0f, 152.0f, 80.0f });
	rgb_7 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 217.0f, 239.0f, 139.0f, 145.0f, 207.0f, 96.0f, 26.0f, 152.0f, 80.0f });
	rgb_8 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 217.0f, 239.0f, 139.0f, 166.0f, 217.0f, 106.0f, 102.0f, 189.0f, 99.0f, 26.0f, 152.0f, 80.0f });
	rgb_9 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 217.0f, 239.0f, 139.0f, 166.0f, 217.0f, 106.0f, 102.0f, 189.0f, 99.0f, 26.0f, 152.0f, 80.0f });
	rgb_10 = std::vector<float>({ 165.0f, 0.0f, 38.0f, 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 217.0f, 239.0f, 139.0f, 166.0f, 217.0f, 106.0f, 102.0f, 189.0f, 99.0f, 26.0f, 152.0f, 80.0f, 0.0f, 104.0f, 55.0f });
	rgb_11 = std::vector<float>({ 165.0f, 0.0f, 38.0f, 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 139.0f, 255.0f, 255.0f, 191.0f, 217.0f, 239.0f, 139.0f, 166.0f, 217.0f, 106.0f, 102.0f, 189.0f, 99.0f, 26.0f, 152.0f, 80.0f, 0.0f, 104.0f, 55.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });


	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::RdYlGn, scheme));


	// RdBu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 239.0f, 138.0f, 98.0f, 247.0f, 247.0f, 247.0f, 103.0f, 169.0f, 207.0f });
	rgb_4 = std::vector<float>({ 202.0f, 0.0f, 32.0f, 244.0f, 165.0f, 130.0f, 146.0f, 197.0f, 222.0f, 5.0f, 113.0f, 176.0f });
	rgb_5 = std::vector<float>({ 202.0f, 0.0f, 32.0f, 244.0f, 165.0f, 130.0f, 247.0f, 247.0f, 247.0f, 146.0f, 197.0f, 222.0f, 5.0f, 113.0f, 176.0f });
	rgb_6 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 239.0f, 138.0f, 98.0f, 253.0f, 219.0f, 199.0f, 209.0f, 229.0f, 240.0f, 103.0f, 169.0f, 207.0f, 33.0f, 102.0f, 172.0f });
	rgb_7 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 239.0f, 138.0f, 98.0f, 253.0f, 219.0f, 199.0f, 247.0f, 247.0f, 247.0f, 209.0f, 229.0f, 240.0f, 103.0f, 169.0f, 207.0f, 33.0f, 102.0f, 172.0f });
	rgb_8 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 209.0f, 229.0f, 240.0f, 146.0f, 197.0f, 222.0f, 67.0f, 147.0f, 195.0f, 33.0f, 102.0f, 172.0f });
	rgb_9 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 247.0f, 247.0f, 247.0f, 209.0f, 229.0f, 240.0f, 146.0f, 197.0f, 222.0f, 67.0f, 147.0f, 195.0f, 33.0f, 102.0f, 172.0f });
	rgb_10 = std::vector<float>({ 103.0f, 0.0f, 31.0f, 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 209.0f, 229.0f, 240.0f, 146.0f, 197.0f, 222.0f, 67.0f, 147.0f, 195.0f, 33.0f, 102.0f, 172.0f, 5.0f, 48.0f, 97.0f });
	rgb_11 = std::vector<float>({ 103.0f, 0.0f, 31.0f, 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 247.0f, 247.0f, 247.0f, 209.0f, 229.0f, 240.0f, 146.0f, 197.0f, 222.0f, 67.0f, 147.0f, 195.0f, 33.0f, 102.0f, 172.0f, 5.0f, 48.0f, 97.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::RdBu, scheme));

	// PiYG
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 233.0f, 163.0f, 201.0f, 247.0f, 247.0f, 247.0f, 161.0f, 215.0f, 106.0f });
	rgb_4 = std::vector<float>({ 208.0f, 28.0f, 139.0f, 241.0f, 182.0f, 218.0f, 184.0f, 225.0f, 134.0f, 77.0f, 172.0f, 38.0f });
	rgb_5 = std::vector<float>({ 208.0f, 28.0f, 139.0f, 241.0f, 182.0f, 218.0f, 247.0f, 247.0f, 247.0f, 184.0f, 225.0f, 134.0f, 77.0f, 172.0f, 38.0f });
	rgb_6 = std::vector<float>({ 197.0f, 27.0f, 125.0f, 233.0f, 163.0f, 201.0f, 253.0f, 224.0f, 239.0f, 230.0f, 245.0f, 208.0f, 161.0f, 215.0f, 106.0f, 77.0f, 146.0f, 33.0f });
	rgb_7 = std::vector<float>({ 197.0f, 27.0f, 125.0f, 233.0f, 163.0f, 201.0f, 253.0f, 224.0f, 239.0f, 247.0f, 247.0f, 247.0f, 230.0f, 245.0f, 208.0f, 161.0f, 215.0f, 106.0f, 77.0f, 146.0f, 33.0f });
	rgb_8 = std::vector<float>({ 197.0f, 27.0f, 125.0f, 222.0f, 119.0f, 174.0f, 241.0f, 182.0f, 218.0f, 253.0f, 224.0f, 239.0f, 230.0f, 245.0f, 208.0f, 184.0f, 225.0f, 134.0f, 127.0f, 188.0f, 65.0f, 77.0f, 146.0f, 33.0f });
	rgb_9 = std::vector<float>({ 197.0f, 27.0f, 125.0f, 222.0f, 119.0f, 174.0f, 241.0f, 182.0f, 218.0f, 253.0f, 224.0f, 239.0f, 247.0f, 247.0f, 247.0f, 230.0f, 245.0f, 208.0f, 184.0f, 225.0f, 134.0f, 127.0f, 188.0f, 65.0f, 77.0f, 146.0f, 33.0f });
	rgb_10 = std::vector<float>({ 142.0f, 1.0f, 82.0f, 197.0f, 27.0f, 125.0f, 222.0f, 119.0f, 174.0f, 241.0f, 182.0f, 218.0f, 253.0f, 224.0f, 239.0f, 230.0f, 245.0f, 208.0f, 184.0f, 225.0f, 134.0f, 127.0f, 188.0f, 65.0f, 77.0f, 146.0f, 33.0f, 39.0f, 100.0f, 25.0f });
	rgb_11 = std::vector<float>({ 142.0f, 1.0f, 82.0f, 197.0f, 27.0f, 125.0f, 222.0f, 119.0f, 174.0f, 241.0f, 182.0f, 218.0f, 253.0f, 224.0f, 239.0f, 247.0f, 247.0f, 247.0f, 230.0f, 245.0f, 208.0f, 184.0f, 225.0f, 134.0f, 127.0f, 188.0f, 65.0f, 77.0f, 146.0f, 33.0f, 39.0f, 100.0f, 25.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::PiYG, scheme));

	// PRGn
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 175.0f, 141.0f, 195.0f, 247.0f, 247.0f, 247.0f, 127.0f, 191.0f, 123.0f });
	rgb_4 = std::vector<float>({ 123.0f, 50.0f, 148.0f, 194.0f, 165.0f, 207.0f, 166.0f, 219.0f, 160.0f, 0.0f, 136.0f, 55.0f });
	rgb_5 = std::vector<float>({ 123.0f, 50.0f, 148.0f, 194.0f, 165.0f, 207.0f, 247.0f, 247.0f, 247.0f, 166.0f, 219.0f, 160.0f, 0.0f, 136.0f, 55.0f });
	rgb_6 = std::vector<float>({ 118.0f, 42.0f, 131.0f, 175.0f, 141.0f, 195.0f, 231.0f, 212.0f, 232.0f, 217.0f, 240.0f, 211.0f, 127.0f, 191.0f, 123.0f, 27.0f, 120.0f, 55.0f });
	rgb_7 = std::vector<float>({ 118.0f, 42.0f, 131.0f, 175.0f, 141.0f, 195.0f, 231.0f, 212.0f, 232.0f, 247.0f, 247.0f, 247.0f, 217.0f, 240.0f, 211.0f, 127.0f, 191.0f, 123.0f, 27.0f, 120.0f, 55.0f });
	rgb_8 = std::vector<float>({ 118.0f, 42.0f, 131.0f, 153.0f, 112.0f, 171.0f, 194.0f, 165.0f, 207.0f, 231.0f, 212.0f, 232.0f, 217.0f, 240.0f, 211.0f, 166.0f, 219.0f, 160.0f, 90.0f, 174.0f, 97.0f, 27.0f, 120.0f, 55.0f });
	rgb_9 = std::vector<float>({ 118.0f, 42.0f, 131.0f, 153.0f, 112.0f, 171.0f, 194.0f, 165.0f, 207.0f, 231.0f, 212.0f, 232.0f, 247.0f, 247.0f, 247.0f, 217.0f, 240.0f, 211.0f, 166.0f, 219.0f, 160.0f, 90.0f, 174.0f, 97.0f, 27.0f, 120.0f, 55.0f });
	rgb_10 = std::vector<float>({ 64.0f, 0.0f, 75.0f, 118.0f, 42.0f, 131.0f, 153.0f, 112.0f, 171.0f, 194.0f, 165.0f, 207.0f, 231.0f, 212.0f, 232.0f, 217.0f, 240.0f, 211.0f, 166.0f, 219.0f, 160.0f, 90.0f, 174.0f, 97.0f, 27.0f, 120.0f, 55.0f, 0.0f, 68.0f, 27.0f });
	rgb_11 = std::vector<float>({ 64.0f, 0.0f, 75.0f, 118.0f, 42.0f, 131.0f, 153.0f, 112.0f, 171.0f, 194.0f, 165.0f, 207.0f, 231.0f, 212.0f, 232.0f, 247.0f, 247.0f, 247.0f, 217.0f, 240.0f, 211.0f, 166.0f, 219.0f, 160.0f, 90.0f, 174.0f, 97.0f, 27.0f, 120.0f, 55.0f, 0.0f, 68.0f, 27.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::PRGn, scheme));

	// RdYlBu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 252.0f, 141.0f, 89.0f, 255.0f, 255.0f, 191.0f, 145.0f, 191.0f, 219.0f });
	rgb_4 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 171.0f, 217.0f, 233.0f, 44.0f, 123.0f, 182.0f });
	rgb_5 = std::vector<float>({ 215.0f, 25.0f, 28.0f, 253.0f, 174.0f, 97.0f, 255.0f, 255.0f, 191.0f, 171.0f, 217.0f, 233.0f, 44.0f, 123.0f, 182.0f });
	rgb_6 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 144.0f, 224.0f, 243.0f, 248.0f, 145.0f, 191.0f, 219.0f, 69.0f, 117.0f, 180.0f });
	rgb_7 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 252.0f, 141.0f, 89.0f, 254.0f, 224.0f, 144.0f, 255.0f, 255.0f, 191.0f, 224.0f, 243.0f, 248.0f, 145.0f, 191.0f, 219.0f, 69.0f, 117.0f, 180.0f });
	rgb_8 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 144.0f, 224.0f, 243.0f, 248.0f, 171.0f, 217.0f, 233.0f, 116.0f, 173.0f, 209.0f, 69.0f, 117.0f, 180.0f });
	rgb_9 = std::vector<float>({ 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 144.0f, 255.0f, 255.0f, 191.0f, 224.0f, 243.0f, 248.0f, 171.0f, 217.0f, 233.0f, 116.0f, 173.0f, 209.0f, 69.0f, 117.0f, 180.0f });
	rgb_10 = std::vector<float>({ 165.0f, 0.0f, 38.0f, 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 144.0f, 224.0f, 243.0f, 248.0f, 171.0f, 217.0f, 233.0f, 116.0f, 173.0f, 209.0f, 69.0f, 117.0f, 180.0f, 49.0f, 54.0f, 149.0f });
	rgb_11 = std::vector<float>({ 165.0f, 0.0f, 38.0f, 215.0f, 48.0f, 39.0f, 244.0f, 109.0f, 67.0f, 253.0f, 174.0f, 97.0f, 254.0f, 224.0f, 144.0f, 255.0f, 255.0f, 191.0f, 224.0f, 243.0f, 248.0f, 171.0f, 217.0f, 233.0f, 116.0f, 173.0f, 209.0f, 69.0f, 117.0f, 180.0f, 49.0f, 54.0f, 149.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::RdYlBu, scheme));

	// BrBG
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 216.0f, 179.0f, 101.0f, 245.0f, 245.0f, 245.0f, 90.0f, 180.0f, 172.0f });
	rgb_4 = std::vector<float>({ 166.0f, 97.0f, 26.0f, 223.0f, 194.0f, 125.0f, 128.0f, 205.0f, 193.0f, 1.0f, 133.0f, 113.0f });
	rgb_5 = std::vector<float>({ 166.0f, 97.0f, 26.0f, 223.0f, 194.0f, 125.0f, 245.0f, 245.0f, 245.0f, 128.0f, 205.0f, 193.0f, 1.0f, 133.0f, 113.0f });
	rgb_6 = std::vector<float>({ 140.0f, 81.0f, 10.0f, 216.0f, 179.0f, 101.0f, 246.0f, 232.0f, 195.0f, 199.0f, 234.0f, 229.0f, 90.0f, 180.0f, 172.0f, 1.0f, 102.0f, 94.0f });
	rgb_7 = std::vector<float>({ 140.0f, 81.0f, 10.0f, 216.0f, 179.0f, 101.0f, 246.0f, 232.0f, 195.0f, 245.0f, 245.0f, 245.0f, 199.0f, 234.0f, 229.0f, 90.0f, 180.0f, 172.0f, 1.0f, 102.0f, 94.0f });
	rgb_8 = std::vector<float>({ 140.0f, 81.0f, 10.0f, 191.0f, 129.0f, 45.0f, 223.0f, 194.0f, 125.0f, 246.0f, 232.0f, 195.0f, 199.0f, 234.0f, 229.0f, 128.0f, 205.0f, 193.0f, 53.0f, 151.0f, 143.0f, 1.0f, 102.0f, 94.0f });
	rgb_9 = std::vector<float>({ 140.0f, 81.0f, 10.0f, 191.0f, 129.0f, 45.0f, 223.0f, 194.0f, 125.0f, 246.0f, 232.0f, 195.0f, 245.0f, 245.0f, 245.0f, 199.0f, 234.0f, 229.0f, 128.0f, 205.0f, 193.0f, 53.0f, 151.0f, 143.0f, 1.0f, 102.0f, 94.0f });
	rgb_10 = std::vector<float>({ 84.0f, 48.0f, 5.0f, 140.0f, 81.0f, 10.0f, 191.0f, 129.0f, 45.0f, 223.0f, 194.0f, 125.0f, 246.0f, 232.0f, 195.0f, 199.0f, 234.0f, 229.0f, 128.0f, 205.0f, 193.0f, 53.0f, 151.0f, 143.0f, 1.0f, 102.0f, 94.0f, 0.0f, 60.0f, 48.0f });
	rgb_11 = std::vector<float>({ 84.0f, 48.0f, 5.0f, 140.0f, 81.0f, 10.0f, 191.0f, 129.0f, 45.0f, 223.0f, 194.0f, 125.0f, 246.0f, 232.0f, 195.0f, 245.0f, 245.0f, 245.0f, 199.0f, 234.0f, 229.0f, 128.0f, 205.0f, 193.0f, 53.0f, 151.0f, 143.0f, 1.0f, 102.0f, 94.0f, 0.0f, 60.0f, 48.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::BrBG, scheme));

	// RdGy
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 239.0f, 138.0f, 98.0f, 255.0f, 255.0f, 255.0f, 153.0f, 153.0f, 153.0f });
	rgb_4 = std::vector<float>({ 202.0f, 0.0f, 32.0f, 244.0f, 165.0f, 130.0f, 186.0f, 186.0f, 186.0f, 64.0f, 64.0f, 64.0f });
	rgb_5 = std::vector<float>({ 202.0f, 0.0f, 32.0f, 244.0f, 165.0f, 130.0f, 255.0f, 255.0f, 255.0f, 186.0f, 186.0f, 186.0f, 64.0f, 64.0f, 64.0f });
	rgb_6 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 239.0f, 138.0f, 98.0f, 253.0f, 219.0f, 199.0f, 224.0f, 224.0f, 224.0f, 153.0f, 153.0f, 153.0f, 77.0f, 77.0f, 77.0f });
	rgb_7 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 239.0f, 138.0f, 98.0f, 253.0f, 219.0f, 199.0f, 255.0f, 255.0f, 255.0f, 224.0f, 224.0f, 224.0f, 153.0f, 153.0f, 153.0f, 77.0f, 77.0f, 77.0f });
	rgb_8 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 224.0f, 224.0f, 224.0f, 186.0f, 186.0f, 186.0f, 135.0f, 135.0f, 135.0f, 77.0f, 77.0f, 77.0f });
	rgb_9 = std::vector<float>({ 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 255.0f, 255.0f, 255.0f, 224.0f, 224.0f, 224.0f, 186.0f, 186.0f, 186.0f, 135.0f, 135.0f, 135.0f, 77.0f, 77.0f, 77.0f });
	rgb_10 = std::vector<float>({ 103.0f, 0.0f, 31.0f, 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 224.0f, 224.0f, 224.0f, 186.0f, 186.0f, 186.0f, 135.0f, 135.0f, 135.0f, 77.0f, 77.0f, 77.0f, 26.0f, 26.0f, 26.0f });
	rgb_11 = std::vector<float>({ 103.0f, 0.0f, 31.0f, 178.0f, 24.0f, 43.0f, 214.0f, 96.0f, 77.0f, 244.0f, 165.0f, 130.0f, 253.0f, 219.0f, 199.0f, 255.0f, 255.0f, 255.0f, 224.0f, 224.0f, 224.0f, 186.0f, 186.0f, 186.0f, 135.0f, 135.0f, 135.0f, 77.0f, 77.0f, 77.0f, 26.0f, 26.0f, 26.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::RdGy, scheme));

	// PuOr
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 241.0f, 163.0f, 64.0f, 247.0f, 247.0f, 247.0f, 153.0f, 142.0f, 195.0f });
	rgb_4 = std::vector<float>({ 230.0f, 97.0f, 1.0f, 253.0f, 184.0f, 99.0f, 178.0f, 171.0f, 210.0f, 94.0f, 60.0f, 153.0f });
	rgb_5 = std::vector<float>({ 230.0f, 97.0f, 1.0f, 253.0f, 184.0f, 99.0f, 247.0f, 247.0f, 247.0f, 178.0f, 171.0f, 210.0f, 94.0f, 60.0f, 153.0f });
	rgb_6 = std::vector<float>({ 179.0f, 88.0f, 6.0f, 241.0f, 163.0f, 64.0f, 254.0f, 224.0f, 182.0f, 216.0f, 218.0f, 235.0f, 153.0f, 142.0f, 195.0f, 84.0f, 39.0f, 136.0f });
	rgb_7 = std::vector<float>({ 179.0f, 88.0f, 6.0f, 241.0f, 163.0f, 64.0f, 254.0f, 224.0f, 182.0f, 247.0f, 247.0f, 247.0f, 216.0f, 218.0f, 235.0f, 153.0f, 142.0f, 195.0f, 84.0f, 39.0f, 136.0f });
	rgb_8 = std::vector<float>({ 179.0f, 88.0f, 6.0f, 224.0f, 130.0f, 20.0f, 253.0f, 184.0f, 99.0f, 254.0f, 224.0f, 182.0f, 216.0f, 218.0f, 235.0f, 178.0f, 171.0f, 210.0f, 128.0f, 115.0f, 172.0f, 84.0f, 39.0f, 136.0f });
	rgb_9 = std::vector<float>({ 179.0f, 88.0f, 6.0f, 224.0f, 130.0f, 20.0f, 253.0f, 184.0f, 99.0f, 254.0f, 224.0f, 182.0f, 247.0f, 247.0f, 247.0f, 216.0f, 218.0f, 235.0f, 178.0f, 171.0f, 210.0f, 128.0f, 115.0f, 172.0f, 84.0f, 39.0f, 136.0f });
	rgb_10 = std::vector<float>({ 127.0f, 59.0f, 8.0f, 179.0f, 88.0f, 6.0f, 224.0f, 130.0f, 20.0f, 253.0f, 184.0f, 99.0f, 254.0f, 224.0f, 182.0f, 216.0f, 218.0f, 235.0f, 178.0f, 171.0f, 210.0f, 128.0f, 115.0f, 172.0f, 84.0f, 39.0f, 136.0f, 45.0f, 0.0f, 75.0f });
	rgb_11 = std::vector<float>({ 127.0f, 59.0f, 8.0f, 179.0f, 88.0f, 6.0f, 224.0f, 130.0f, 20.0f, 253.0f, 184.0f, 99.0f, 254.0f, 224.0f, 182.0f, 247.0f, 247.0f, 247.0f, 216.0f, 218.0f, 235.0f, 178.0f, 171.0f, 210.0f, 128.0f, 115.0f, 172.0f, 84.0f, 39.0f, 136.0f, 45.0f, 0.0f, 75.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));

	m_diverging.insert(std::make_pair(Diverging::PuOr, scheme));
}

void ColorBrewer::initQualitative()
{
	ColorScheme scheme;
	std::vector<float> rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8, rgb_9, rgb_10, rgb_11, rgb_12;
	std::map<Properties, unsigned short> prop_3, prop_4, prop_5, prop_6, prop_7, prop_8, prop_9, prop_10, prop_11, prop_12;

	// Set2
	rgb_3 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f });
	rgb_4 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f, 231.0f, 138.0f, 195.0f });
	rgb_5 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f, 231.0f, 138.0f, 195.0f, 166.0f, 216.0f, 84.0f });
	rgb_6 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f, 231.0f, 138.0f, 195.0f, 166.0f, 216.0f, 84.0f, 255.0f, 217.0f, 47.0f });
	rgb_7 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f, 231.0f, 138.0f, 195.0f, 166.0f, 216.0f, 84.0f, 255.0f, 217.0f, 47.0f, 229.0f, 196.0f, 148.0f });
	rgb_8 = std::vector<float>({ 102.0f, 194.0f, 165.0f, 252.0f, 141.0f, 98.0f, 141.0f, 160.0f, 203.0f, 231.0f, 138.0f, 195.0f, 166.0f, 216.0f, 84.0f, 255.0f, 217.0f, 47.0f, 229.0f, 196.0f, 148.0f, 179.0f, 179.0f, 179.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));

	m_qualitative.insert(std::make_pair(Qualitative::Set2, scheme));

	// Accent
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f });
	rgb_4 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f, 255.0f, 255.0f, 153.0f });
	rgb_5 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f, 255.0f, 255.0f, 153.0f, 56.0f, 108.0f, 176.0f });
	rgb_6 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f, 255.0f, 255.0f, 153.0f, 56.0f, 108.0f, 176.0f, 240.0f, 2.0f, 127.0f });
	rgb_7 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f, 255.0f, 255.0f, 153.0f, 56.0f, 108.0f, 176.0f, 240.0f, 2.0f, 127.0f, 191.0f, 91.0f, 23.0f });
	rgb_8 = std::vector<float>({ 127.0f, 201.0f, 127.0f, 190.0f, 174.0f, 212.0f, 253.0f, 192.0f, 134.0f, 255.0f, 255.0f, 153.0f, 56.0f, 108.0f, 176.0f, 240.0f, 2.0f, 127.0f, 191.0f, 91.0f, 23.0f, 102.0f, 102.0f, 102.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));

	m_qualitative.insert(std::make_pair(Qualitative::Accent, scheme));

	// Set1
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f });
	rgb_4 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f });
	rgb_5 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f, 255.0f, 127.0f, 0.0f });
	rgb_6 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f, 255.0f, 127.0f, 0.0f, 255.0f, 255.0f, 51.0f });
	rgb_7 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f, 255.0f, 127.0f, 0.0f, 255.0f, 255.0f, 51.0f, 166.0f, 86.0f, 40.0f });
	rgb_8 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f, 255.0f, 127.0f, 0.0f, 255.0f, 255.0f, 51.0f, 166.0f, 86.0f, 40.0f, 247.0f, 129.0f, 191.0f });
	rgb_9 = std::vector<float>({ 228.0f, 26.0f, 28.0f, 55.0f, 126.0f, 184.0f, 77.0f, 175.0f, 74.0f, 152.0f, 78.0f, 163.0f, 255.0f, 127.0f, 0.0f, 255.0f, 255.0f, 51.0f, 166.0f, 86.0f, 40.0f, 247.0f, 129.0f, 191.0f, 153.0f, 153.0f, 153.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_qualitative.insert(std::make_pair(Qualitative::Set1, scheme));

	// Set3
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f });
	rgb_4 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f });
	rgb_5 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f });
	rgb_6 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f });
	rgb_7 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f });
	rgb_8 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f, 252.0f, 205.0f, 229.0f });
	rgb_9 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f, 252.0f, 205.0f, 229.0f, 217.0f, 217.0f, 217.0f });
	rgb_10 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f, 252.0f, 205.0f, 229.0f, 217.0f, 217.0f, 217.0f, 188.0f, 128.0f, 189.0f });
	rgb_11 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f, 252.0f, 205.0f, 229.0f, 217.0f, 217.0f, 217.0f, 188.0f, 128.0f, 189.0f, 204.0f, 235.0f, 197.0f });
	rgb_12 = std::vector<float>({ 141.0f, 211.0f, 199.0f, 255.0f, 255.0f, 179.0f, 190.0f, 186.0f, 218.0f, 251.0f, 128.0f, 114.0f, 128.0f, 177.0f, 211.0f, 253.0f, 180.0f, 98.0f, 179.0f, 222.0f, 105.0f, 252.0f, 205.0f, 229.0f, 217.0f, 217.0f, 217.0f, 188.0f, 128.0f, 189.0f, 204.0f, 235.0f, 197.0f, 255.0f, 237.0f, 111.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 0) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_12 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));
	scheme.properties.insert(std::make_pair(12, prop_12));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));
	scheme.rgbs.insert(std::make_pair(12, rgb_12));

	m_qualitative.insert(std::make_pair(Qualitative::Set3, scheme));

	// Dark2
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f });
	rgb_4 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f, 231.0f, 41.0f, 138.0f });
	rgb_5 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f, 231.0f, 41.0f, 138.0f, 102.0f, 166.0f, 30.0f });
	rgb_6 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f, 231.0f, 41.0f, 138.0f, 102.0f, 166.0f, 30.0f, 230.0f, 171.0f, 2.0f });
	rgb_7 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f, 231.0f, 41.0f, 138.0f, 102.0f, 166.0f, 30.0f, 230.0f, 171.0f, 2.0f, 166.0f, 118.0f, 29.0f });
	rgb_8 = std::vector<float>({ 27.0f, 158.0f, 119.0f, 217.0f, 95.0f, 2.0f, 117.0f, 112.0f, 179.0f, 231.0f, 41.0f, 138.0f, 102.0f, 166.0f, 30.0f, 230.0f, 171.0f, 2.0f, 166.0f, 118.0f, 29.0f, 102.0f, 102.0f, 102.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));

	m_qualitative.insert(std::make_pair(Qualitative::Dark2, scheme));


	// Paired
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f });
	rgb_4 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f });
	rgb_5 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f });
	rgb_6 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f });
	rgb_7 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f });
	rgb_8 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f, 255.0f, 127.0f, 0.0f });
	rgb_9 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f, 255.0f, 127.0f, 0.0f, 202.0f, 178.0f, 214.0f });
	rgb_10 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f, 255.0f, 127.0f, 0.0f, 202.0f, 178.0f, 214.0f, 106.0f, 61.0f, 154.0f });
	rgb_11 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f, 255.0f, 127.0f, 0.0f, 202.0f, 178.0f, 214.0f, 106.0f, 61.0f, 154.0f, 255.0f, 255.0f, 153.0f });
	rgb_12 = std::vector<float>({ 166.0f, 206.0f, 227.0f, 31.0f, 120.0f, 180.0f, 178.0f, 223.0f, 138.0f, 51.0f, 160.0f, 44.0f, 251.0f, 154.0f, 153.0f, 227.0f, 26.0f, 28.0f, 253.0f, 191.0f, 111.0f, 255.0f, 127.0f, 0.0f, 202.0f, 178.0f, 214.0f, 106.0f, 61.0f, 154.0f, 255.0f, 255.0f, 153.0f, 177.0f, 89.0f, 40.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_10 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_11 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_12 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));
	scheme.properties.insert(std::make_pair(10, prop_10));
	scheme.properties.insert(std::make_pair(11, prop_11));
	scheme.properties.insert(std::make_pair(12, prop_12));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));
	scheme.rgbs.insert(std::make_pair(10, rgb_10));
	scheme.rgbs.insert(std::make_pair(11, rgb_11));
	scheme.rgbs.insert(std::make_pair(12, rgb_12));

	m_qualitative.insert(std::make_pair(Qualitative::Paired, scheme));


	// Pastel2
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f });
	rgb_4 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f, 244.0f, 202.0f, 228.0f });
	rgb_5 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f, 244.0f, 202.0f, 228.0f, 230.0f, 245.0f, 201.0f });
	rgb_6 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f, 244.0f, 202.0f, 228.0f, 230.0f, 245.0f, 201.0f, 255.0f, 242.0f, 174.0f });
	rgb_7 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f, 244.0f, 202.0f, 228.0f, 230.0f, 245.0f, 201.0f, 255.0f, 242.0f, 174.0f, 241.0f, 226.0f, 204.0f });
	rgb_8 = std::vector<float>({ 179.0f, 226.0f, 205.0f, 253.0f, 205.0f, 172.0f, 203.0f, 213.0f, 232.0f, 244.0f, 202.0f, 228.0f, 230.0f, 245.0f, 201.0f, 255.0f, 242.0f, 174.0f, 241.0f, 226.0f, 204.0f, 204.0f, 204.0f, 204.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));

	m_qualitative.insert(std::make_pair(Qualitative::Pastel2, scheme));

	// Pastel1
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f });
	rgb_4 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f });
	rgb_5 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f, 254.0f, 217.0f, 166.0f });
	rgb_6 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f, 254.0f, 217.0f, 166.0f, 255.0f, 255.0f, 204.0f });
	rgb_7 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f, 254.0f, 217.0f, 166.0f, 255.0f, 255.0f, 204.0f, 229.0f, 216.0f, 189.0f });
	rgb_8 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f, 254.0f, 217.0f, 166.0f, 255.0f, 255.0f, 204.0f, 229.0f, 216.0f, 189.0f, 253.0f, 218.0f, 236.0f });
	rgb_9 = std::vector<float>({ 251.0f, 180.0f, 174.0f, 179.0f, 205.0f, 227.0f, 204.0f, 235.0f, 197.0f, 222.0f, 203.0f, 228.0f, 254.0f, 217.0f, 166.0f, 255.0f, 255.0f, 204.0f, 229.0f, 216.0f, 189.0f, 253.0f, 218.0f, 236.0f, 242.0f, 242.0f, 242.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 2), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 0), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_qualitative.insert(std::make_pair(Qualitative::Pastel1, scheme));
}

void ColorBrewer::initSequential()
{
	ColorScheme scheme;
	std::vector<float> rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8, rgb_9;
	std::map<Properties, unsigned short> prop_3, prop_4, prop_5, prop_6, prop_7, prop_8, prop_9;

	// OrRd
	rgb_3 = std::vector<float>({ 254.0f, 232.0f, 200.0f, 253.0f, 187.0f, 132.0f, 227.0f, 74.0f, 51.0f });
	rgb_4 = std::vector<float>({ 254.0f, 240.0f, 217.0f, 253.0f, 204.0f, 138.0f, 252.0f, 141.0f, 89.0f, 215.0f, 48.0f, 31.0f });
	rgb_5 = std::vector<float>({ 254.0f, 240.0f, 217.0f, 253.0f, 204.0f, 138.0f, 252.0f, 141.0f, 89.0f, 227.0f, 74.0f, 51.0f, 179.0f, 0.0f, 0.0f });
	rgb_6 = std::vector<float>({ 254.0f, 240.0f, 217.0f, 253.0f, 212.0f, 158.0f, 253.0f, 187.0f, 132.0f, 252.0f, 141.0f, 89.0f, 227.0f, 74.0f, 51.0f, 179.0f, 0.0f, 0.0f });
	rgb_7 = std::vector<float>({ 254.0f, 240.0f, 217.0f, 253.0f, 212.0f, 158.0f, 253.0f, 187.0f, 132.0f, 252.0f, 141.0f, 89.0f, 239.0f, 101.0f, 72.0f, 215.0f, 48.0f, 31.0f, 153.0f, 0.0f, 0.0f });
	rgb_8 = std::vector<float>({ 255.0f, 247.0f, 236.0f, 254.0f, 232.0f, 200.0f, 253.0f, 212.0f, 158.0f, 253.0f, 187.0f, 132.0f, 252.0f, 141.0f, 89.0f, 239.0f, 101.0f, 72.0f, 215.0f, 48.0f, 31.0f, 153.0f, 0.0f, 0.0f });
	rgb_9 = std::vector<float>({ 255.0f, 247.0f, 236.0f, 254.0f, 232.0f, 200.0f, 253.0f, 212.0f, 158.0f, 253.0f, 187.0f, 132.0f, 252.0f, 141.0f, 89.0f, 239.0f, 101.0f, 72.0f, 215.0f, 48.0f, 31.0f, 179.0f, 0.0f, 0.0f, 127.0f, 0.0f, 0.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::OrRd, scheme));

	// PuBu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 236.0f, 231.0f, 242.0f, 166.0f, 189.0f, 219.0f, 43.0f, 140.0f, 190.0f });
	rgb_4 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 189.0f, 201.0f, 225.0f, 116.0f, 169.0f, 207.0f, 5.0f, 112.0f, 176.0f });
	rgb_5 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 189.0f, 201.0f, 225.0f, 116.0f, 169.0f, 207.0f, 43.0f, 140.0f, 190.0f, 4.0f, 90.0f, 141.0f });
	rgb_6 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 116.0f, 169.0f, 207.0f, 43.0f, 140.0f, 190.0f, 4.0f, 90.0f, 141.0f });
	rgb_7 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 116.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 5.0f, 112.0f, 176.0f, 3.0f, 78.0f, 123.0f });
	rgb_8 = std::vector<float>({ 255.0f, 247.0f, 251.0f, 236.0f, 231.0f, 242.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 116.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 5.0f, 112.0f, 176.0f, 3.0f, 78.0f, 123.0f });
	rgb_9 = std::vector<float>({ 255.0f, 247.0f, 251.0f, 236.0f, 231.0f, 242.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 116.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 5.0f, 112.0f, 176.0f, 4.0f, 90.0f, 141.0f, 2.0f, 56.0f, 88.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));


	m_sequential.insert(std::make_pair(Sequential::PuBu, scheme));

	// BuPu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 224.0f, 236.0f, 244.0f, 158.0f, 188.0f, 218.0f, 136.0f, 86.0f, 167.0f });
	rgb_4 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 179.0f, 205.0f, 227.0f, 140.0f, 150.0f, 198.0f, 136.0f, 65.0f, 157.0f });
	rgb_5 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 179.0f, 205.0f, 227.0f, 140.0f, 150.0f, 198.0f, 136.0f, 86.0f, 167.0f, 129.0f, 15.0f, 124.0f });
	rgb_6 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 191.0f, 211.0f, 230.0f, 158.0f, 188.0f, 218.0f, 140.0f, 150.0f, 198.0f, 136.0f, 86.0f, 167.0f, 129.0f, 15.0f, 124.0f });
	rgb_7 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 191.0f, 211.0f, 230.0f, 158.0f, 188.0f, 218.0f, 140.0f, 150.0f, 198.0f, 140.0f, 107.0f, 177.0f, 136.0f, 65.0f, 157.0f, 110.0f, 1.0f, 107.0f });
	rgb_8 = std::vector<float>({ 247.0f, 252.0f, 253.0f, 224.0f, 236.0f, 244.0f, 191.0f, 211.0f, 230.0f, 158.0f, 188.0f, 218.0f, 140.0f, 150.0f, 198.0f, 140.0f, 107.0f, 177.0f, 136.0f, 65.0f, 157.0f, 110.0f, 1.0f, 107.0f });
	rgb_9 = std::vector<float>({ 247.0f, 252.0f, 253.0f, 224.0f, 236.0f, 244.0f, 191.0f, 211.0f, 230.0f, 158.0f, 188.0f, 218.0f, 140.0f, 150.0f, 198.0f, 140.0f, 107.0f, 177.0f, 136.0f, 65.0f, 157.0f, 129.0f, 15.0f, 124.0f, 77.0f, 0.0f, 75.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::BuPu, scheme));

	// Oranges
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 254.0f, 230.0f, 206.0f, 253.0f, 174.0f, 107.0f, 230.0f, 85.0f, 13.0f });
	rgb_4 = std::vector<float>({ 254.0f, 237.0f, 222.0f, 253.0f, 190.0f, 133.0f, 253.0f, 141.0f, 60.0f, 217.0f, 71.0f, 1.0f });
	rgb_5 = std::vector<float>({ 254.0f, 237.0f, 222.0f, 253.0f, 190.0f, 133.0f, 253.0f, 141.0f, 60.0f, 230.0f, 85.0f, 13.0f, 166.0f, 54.0f, 3.0f });
	rgb_6 = std::vector<float>({ 254.0f, 237.0f, 222.0f, 253.0f, 208.0f, 162.0f, 253.0f, 174.0f, 107.0f, 253.0f, 141.0f, 60.0f, 230.0f, 85.0f, 13.0f, 166.0f, 54.0f, 3.0f });
	rgb_7 = std::vector<float>({ 254.0f, 237.0f, 222.0f, 253.0f, 208.0f, 162.0f, 253.0f, 174.0f, 107.0f, 253.0f, 141.0f, 60.0f, 241.0f, 105.0f, 19.0f, 217.0f, 72.0f, 1.0f, 140.0f, 45.0f, 4.0f });
	rgb_8 = std::vector<float>({ 255.0f, 245.0f, 235.0f, 254.0f, 230.0f, 206.0f, 253.0f, 208.0f, 162.0f, 253.0f, 174.0f, 107.0f, 253.0f, 141.0f, 60.0f, 241.0f, 105.0f, 19.0f, 217.0f, 72.0f, 1.0f, 140.0f, 45.0f, 4.0f });
	rgb_9 = std::vector<float>({ 255.0f, 245.0f, 235.0f, 254.0f, 230.0f, 206.0f, 253.0f, 208.0f, 162.0f, 253.0f, 174.0f, 107.0f, 253.0f, 141.0f, 60.0f, 241.0f, 105.0f, 19.0f, 217.0f, 72.0f, 1.0f, 166.0f, 54.0f, 3.0f, 127.0f, 39.0f, 4.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Oranges, scheme));

	// BuGn
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 229.0f, 245.0f, 249.0f, 153.0f, 216.0f, 201.0f, 44.0f, 162.0f, 95.0f });
	rgb_4 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 178.0f, 226.0f, 226.0f, 102.0f, 194.0f, 164.0f, 35.0f, 139.0f, 69.0f });
	rgb_5 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 178.0f, 226.0f, 226.0f, 102.0f, 194.0f, 164.0f, 44.0f, 162.0f, 95.0f, 0.0f, 109.0f, 44.0f });
	rgb_6 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 204.0f, 236.0f, 230.0f, 153.0f, 216.0f, 201.0f, 102.0f, 194.0f, 164.0f, 44.0f, 162.0f, 95.0f, 0.0f, 109.0f, 44.0f });
	rgb_7 = std::vector<float>({ 237.0f, 248.0f, 251.0f, 204.0f, 236.0f, 230.0f, 153.0f, 216.0f, 201.0f, 102.0f, 194.0f, 164.0f, 65.0f, 174.0f, 118.0f, 35.0f, 139.0f, 69.0f, 0.0f, 88.0f, 36.0f });
	rgb_8 = std::vector<float>({ 247.0f, 252.0f, 253.0f, 229.0f, 245.0f, 249.0f, 204.0f, 236.0f, 230.0f, 153.0f, 216.0f, 201.0f, 102.0f, 194.0f, 164.0f, 65.0f, 174.0f, 118.0f, 35.0f, 139.0f, 69.0f, 0.0f, 88.0f, 36.0f });
	rgb_9 = std::vector<float>({ 247.0f, 252.0f, 253.0f, 229.0f, 245.0f, 249.0f, 204.0f, 236.0f, 230.0f, 153.0f, 216.0f, 201.0f, 102.0f, 194.0f, 164.0f, 65.0f, 174.0f, 118.0f, 35.0f, 139.0f, 69.0f, 0.0f, 109.0f, 44.0f, 0.0f, 68.0f, 27.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::BuGn, scheme));

	// YlOrBr
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 255.0f, 247.0f, 188.0f, 254.0f, 196.0f, 79.0f, 217.0f, 95.0f, 14.0f });
	rgb_4 = std::vector<float>({ 255.0f, 255.0f, 212.0f, 254.0f, 217.0f, 142.0f, 254.0f, 153.0f, 41.0f, 204.0f, 76.0f, 2.0f });
	rgb_5 = std::vector<float>({ 255.0f, 255.0f, 212.0f, 254.0f, 217.0f, 142.0f, 254.0f, 153.0f, 41.0f, 217.0f, 95.0f, 14.0f, 153.0f, 52.0f, 4.0f });
	rgb_6 = std::vector<float>({ 255.0f, 255.0f, 212.0f, 254.0f, 227.0f, 145.0f, 254.0f, 196.0f, 79.0f, 254.0f, 153.0f, 41.0f, 217.0f, 95.0f, 14.0f, 153.0f, 52.0f, 4.0f });
	rgb_7 = std::vector<float>({ 255.0f, 255.0f, 212.0f, 254.0f, 227.0f, 145.0f, 254.0f, 196.0f, 79.0f, 254.0f, 153.0f, 41.0f, 236.0f, 112.0f, 20.0f, 204.0f, 76.0f, 2.0f, 140.0f, 45.0f, 4.0f });
	rgb_8 = std::vector<float>({ 255.0f, 255.0f, 229.0f, 255.0f, 247.0f, 188.0f, 254.0f, 227.0f, 145.0f, 254.0f, 196.0f, 79.0f, 254.0f, 153.0f, 41.0f, 236.0f, 112.0f, 20.0f, 204.0f, 76.0f, 2.0f, 140.0f, 45.0f, 4.0f });
	rgb_9 = std::vector<float>({ 255.0f, 255.0f, 229.0f, 255.0f, 247.0f, 188.0f, 254.0f, 227.0f, 145.0f, 254.0f, 196.0f, 79.0f, 254.0f, 153.0f, 41.0f, 236.0f, 112.0f, 20.0f, 204.0f, 76.0f, 2.0f, 153.0f, 52.0f, 4.0f, 102.0f, 37.0f, 6.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::YlOrBr, scheme));


	// YlGn
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 247.0f, 252.0f, 185.0f, 173.0f, 221.0f, 142.0f, 49.0f, 163.0f, 84.0f });
	rgb_4 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 194.0f, 230.0f, 153.0f, 120.0f, 198.0f, 121.0f, 35.0f, 132.0f, 67.0f });
	rgb_5 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 194.0f, 230.0f, 153.0f, 120.0f, 198.0f, 121.0f, 49.0f, 163.0f, 84.0f, 0.0f, 104.0f, 55.0f });
	rgb_6 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 217.0f, 240.0f, 163.0f, 173.0f, 221.0f, 142.0f, 120.0f, 198.0f, 121.0f, 49.0f, 163.0f, 84.0f, 0.0f, 104.0f, 55.0f });
	rgb_7 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 217.0f, 240.0f, 163.0f, 173.0f, 221.0f, 142.0f, 120.0f, 198.0f, 121.0f, 65.0f, 171.0f, 93.0f, 35.0f, 132.0f, 67.0f, 0.0f, 90.0f, 50.0f });
	rgb_8 = std::vector<float>({ 255.0f, 255.0f, 229.0f, 247.0f, 252.0f, 185.0f, 217.0f, 240.0f, 163.0f, 173.0f, 221.0f, 142.0f, 120.0f, 198.0f, 121.0f, 65.0f, 171.0f, 93.0f, 35.0f, 132.0f, 67.0f, 0.0f, 90.0f, 50.0f });
	rgb_9 = std::vector<float>({ 255.0f, 255.0f, 229.0f, 247.0f, 252.0f, 185.0f, 217.0f, 240.0f, 163.0f, 173.0f, 221.0f, 142.0f, 120.0f, 198.0f, 121.0f, 65.0f, 171.0f, 93.0f, 35.0f, 132.0f, 67.0f, 0.0f, 104.0f, 55.0f, 0.0f, 69.0f, 41.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::YlGn, scheme));

	// Reds
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 254.0f, 224.0f, 210.0f, 252.0f, 146.0f, 114.0f, 222.0f, 45.0f, 38.0f });
	rgb_4 = std::vector<float>({ 254.0f, 229.0f, 217.0f, 252.0f, 174.0f, 145.0f, 251.0f, 106.0f, 74.0f, 203.0f, 24.0f, 29.0f });
	rgb_5 = std::vector<float>({ 254.0f, 229.0f, 217.0f, 252.0f, 174.0f, 145.0f, 251.0f, 106.0f, 74.0f, 222.0f, 45.0f, 38.0f, 165.0f, 15.0f, 21.0f });
	rgb_6 = std::vector<float>({ 254.0f, 229.0f, 217.0f, 252.0f, 187.0f, 161.0f, 252.0f, 146.0f, 114.0f, 251.0f, 106.0f, 74.0f, 222.0f, 45.0f, 38.0f, 165.0f, 15.0f, 21.0f });
	rgb_7 = std::vector<float>({ 254.0f, 229.0f, 217.0f, 252.0f, 187.0f, 161.0f, 252.0f, 146.0f, 114.0f, 251.0f, 106.0f, 74.0f, 239.0f, 59.0f, 44.0f, 203.0f, 24.0f, 29.0f, 153.0f, 0.0f, 13.0f });
	rgb_8 = std::vector<float>({ 255.0f, 245.0f, 240.0f, 254.0f, 224.0f, 210.0f, 252.0f, 187.0f, 161.0f, 252.0f, 146.0f, 114.0f, 251.0f, 106.0f, 74.0f, 239.0f, 59.0f, 44.0f, 203.0f, 24.0f, 29.0f, 153.0f, 0.0f, 13.0f });
	rgb_9 = std::vector<float>({ 255.0f, 245.0f, 240.0f, 254.0f, 224.0f, 210.0f, 252.0f, 187.0f, 161.0f, 252.0f, 146.0f, 114.0f, 251.0f, 106.0f, 74.0f, 239.0f, 59.0f, 44.0f, 203.0f, 24.0f, 29.0f, 165.0f, 15.0f, 21.0f, 103.0f, 0.0f, 13.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Reds, scheme));

	// RdPu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 253.0f, 224.0f, 221.0f, 250.0f, 159.0f, 181.0f, 197.0f, 27.0f, 138.0f });
	rgb_4 = std::vector<float>({ 254.0f, 235.0f, 226.0f, 251.0f, 180.0f, 185.0f, 247.0f, 104.0f, 161.0f, 174.0f, 1.0f, 126.0f });
	rgb_5 = std::vector<float>({ 254.0f, 235.0f, 226.0f, 251.0f, 180.0f, 185.0f, 247.0f, 104.0f, 161.0f, 197.0f, 27.0f, 138.0f, 122.0f, 1.0f, 119.0f });
	rgb_6 = std::vector<float>({ 254.0f, 235.0f, 226.0f, 252.0f, 197.0f, 192.0f, 250.0f, 159.0f, 181.0f, 247.0f, 104.0f, 161.0f, 197.0f, 27.0f, 138.0f, 122.0f, 1.0f, 119.0f });
	rgb_7 = std::vector<float>({ 254.0f, 235.0f, 226.0f, 252.0f, 197.0f, 192.0f, 250.0f, 159.0f, 181.0f, 247.0f, 104.0f, 161.0f, 221.0f, 52.0f, 151.0f, 174.0f, 1.0f, 126.0f, 122.0f, 1.0f, 119.0f });
	rgb_8 = std::vector<float>({ 255.0f, 247.0f, 243.0f, 253.0f, 224.0f, 221.0f, 252.0f, 197.0f, 192.0f, 250.0f, 159.0f, 181.0f, 247.0f, 104.0f, 161.0f, 221.0f, 52.0f, 151.0f, 174.0f, 1.0f, 126.0f, 122.0f, 1.0f, 119.0f });
	rgb_9 = std::vector<float>({ 255.0f, 247.0f, 243.0f, 253.0f, 224.0f, 221.0f, 252.0f, 197.0f, 192.0f, 250.0f, 159.0f, 181.0f, 247.0f, 104.0f, 161.0f, 221.0f, 52.0f, 151.0f, 174.0f, 1.0f, 126.0f, 122.0f, 1.0f, 119.0f, 73.0f, 0.0f, 106.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::RdPu, scheme));

	// Greens
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 229.0f, 245.0f, 224.0f, 161.0f, 217.0f, 155.0f, 49.0f, 163.0f, 84.0f });
	rgb_4 = std::vector<float>({ 237.0f, 248.0f, 233.0f, 186.0f, 228.0f, 179.0f, 116.0f, 196.0f, 118.0f, 35.0f, 139.0f, 69.0f });
	rgb_5 = std::vector<float>({ 237.0f, 248.0f, 233.0f, 186.0f, 228.0f, 179.0f, 116.0f, 196.0f, 118.0f, 49.0f, 163.0f, 84.0f, 0.0f, 109.0f, 44.0f });
	rgb_6 = std::vector<float>({ 237.0f, 248.0f, 233.0f, 199.0f, 233.0f, 192.0f, 161.0f, 217.0f, 155.0f, 116.0f, 196.0f, 118.0f, 49.0f, 163.0f, 84.0f, 0.0f, 109.0f, 44.0f });
	rgb_7 = std::vector<float>({ 237.0f, 248.0f, 233.0f, 199.0f, 233.0f, 192.0f, 161.0f, 217.0f, 155.0f, 116.0f, 196.0f, 118.0f, 65.0f, 171.0f, 93.0f, 35.0f, 139.0f, 69.0f, 0.0f, 90.0f, 50.0f });
	rgb_8 = std::vector<float>({ 247.0f, 252.0f, 245.0f, 229.0f, 245.0f, 224.0f, 199.0f, 233.0f, 192.0f, 161.0f, 217.0f, 155.0f, 116.0f, 196.0f, 118.0f, 65.0f, 171.0f, 93.0f, 35.0f, 139.0f, 69.0f, 0.0f, 90.0f, 50.0f });
	rgb_9 = std::vector<float>({ 247.0f, 252.0f, 245.0f, 229.0f, 245.0f, 224.0f, 199.0f, 233.0f, 192.0f, 161.0f, 217.0f, 155.0f, 116.0f, 196.0f, 118.0f, 65.0f, 171.0f, 93.0f, 35.0f, 139.0f, 69.0f, 0.0f, 109.0f, 44.0f, 0.0f, 68.0f, 27.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Greens, scheme));


	// YlGnBu
	scheme.rgbs.clear();
	scheme.properties.clear();
	
	rgb_3 = std::vector<float>({ 237.0f, 248.0f, 177.0f, 127.0f, 205.0f, 187.0f, 44.0f, 127.0f, 184.0f });
	rgb_4 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 161.0f, 218.0f, 180.0f, 65.0f, 182.0f, 196.0f, 34.0f, 94.0f, 168.0f });
	rgb_5 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 161.0f, 218.0f, 180.0f, 65.0f, 182.0f, 196.0f, 44.0f, 127.0f, 184.0f, 37.0f, 52.0f, 148.0f });
	rgb_6 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 199.0f, 233.0f, 180.0f, 127.0f, 205.0f, 187.0f, 65.0f, 182.0f, 196.0f, 44.0f, 127.0f, 184.0f, 37.0f, 52.0f, 148.0f });
	rgb_7 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 199.0f, 233.0f, 180.0f, 127.0f, 205.0f, 187.0f, 65.0f, 182.0f, 196.0f, 29.0f, 145.0f, 192.0f, 34.0f, 94.0f, 168.0f, 12.0f, 44.0f, 132.0f });
	rgb_8 = std::vector<float>({ 255.0f, 255.0f, 217.0f, 237.0f, 248.0f, 177.0f, 199.0f, 233.0f, 180.0f, 127.0f, 205.0f, 187.0f, 65.0f, 182.0f, 196.0f, 29.0f, 145.0f, 192.0f, 34.0f, 94.0f, 168.0f, 12.0f, 44.0f, 132.0f });
	rgb_9 = std::vector<float>({ 255.0f, 255.0f, 217.0f, 237.0f, 248.0f, 177.0f, 199.0f, 233.0f, 180.0f, 127.0f, 205.0f, 187.0f, 65.0f, 182.0f, 196.0f, 29.0f, 145.0f, 192.0f, 34.0f, 94.0f, 168.0f, 37.0f, 52.0f, 148.0f, 8.0f, 29.0f, 88.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::YlGnBu, scheme));


	// Purples
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 239.0f, 237.0f, 245.0f, 188.0f, 189.0f, 220.0f, 117.0f, 107.0f, 177.0f });
	rgb_4 = std::vector<float>({ 242.0f, 240.0f, 247.0f, 203.0f, 201.0f, 226.0f, 158.0f, 154.0f, 200.0f, 106.0f, 81.0f, 163.0f });
	rgb_5 = std::vector<float>({ 242.0f, 240.0f, 247.0f, 203.0f, 201.0f, 226.0f, 158.0f, 154.0f, 200.0f, 117.0f, 107.0f, 177.0f, 84.0f, 39.0f, 143.0f });
	rgb_6 = std::vector<float>({ 242.0f, 240.0f, 247.0f, 218.0f, 218.0f, 235.0f, 188.0f, 189.0f, 220.0f, 158.0f, 154.0f, 200.0f, 117.0f, 107.0f, 177.0f, 84.0f, 39.0f, 143.0f });
	rgb_7 = std::vector<float>({ 242.0f, 240.0f, 247.0f, 218.0f, 218.0f, 235.0f, 188.0f, 189.0f, 220.0f, 158.0f, 154.0f, 200.0f, 128.0f, 125.0f, 186.0f, 106.0f, 81.0f, 163.0f, 74.0f, 20.0f, 134.0f });
	rgb_8 = std::vector<float>({ 252.0f, 251.0f, 253.0f, 239.0f, 237.0f, 245.0f, 218.0f, 218.0f, 235.0f, 188.0f, 189.0f, 220.0f, 158.0f, 154.0f, 200.0f, 128.0f, 125.0f, 186.0f, 106.0f, 81.0f, 163.0f, 74.0f, 20.0f, 134.0f });
	rgb_9 = std::vector<float>({ 252.0f, 251.0f, 253.0f, 239.0f, 237.0f, 245.0f, 218.0f, 218.0f, 235.0f, 188.0f, 189.0f, 220.0f, 158.0f, 154.0f, 200.0f, 128.0f, 125.0f, 186.0f, 106.0f, 81.0f, 163.0f, 84.0f, 39.0f, 143.0f, 63.0f, 0.0f, 125.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 0) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Purples, scheme));


	// GnBu
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 224.0f, 243.0f, 219.0f, 168.0f, 221.0f, 181.0f, 67.0f, 162.0f, 202.0f });
	rgb_4 = std::vector<float>({ 240.0f, 249.0f, 232.0f, 186.0f, 228.0f, 188.0f, 123.0f, 204.0f, 196.0f, 43.0f, 140.0f, 190.0f });
	rgb_5 = std::vector<float>({ 240.0f, 249.0f, 232.0f, 186.0f, 228.0f, 188.0f, 123.0f, 204.0f, 196.0f, 67.0f, 162.0f, 202.0f, 8.0f, 104.0f, 172.0f });
	rgb_6 = std::vector<float>({ 240.0f, 249.0f, 232.0f, 204.0f, 235.0f, 197.0f, 168.0f, 221.0f, 181.0f, 123.0f, 204.0f, 196.0f, 67.0f, 162.0f, 202.0f, 8.0f, 104.0f, 172.0f });
	rgb_7 = std::vector<float>({ 240.0f, 249.0f, 232.0f, 204.0f, 235.0f, 197.0f, 168.0f, 221.0f, 181.0f, 123.0f, 204.0f, 196.0f, 78.0f, 179.0f, 211.0f, 43.0f, 140.0f, 190.0f, 8.0f, 88.0f, 158.0f });
	rgb_8 = std::vector<float>({ 247.0f, 252.0f, 240.0f, 224.0f, 243.0f, 219.0f, 204.0f, 235.0f, 197.0f, 168.0f, 221.0f, 181.0f, 123.0f, 204.0f, 196.0f, 78.0f, 179.0f, 211.0f, 43.0f, 140.0f, 190.0f, 8.0f, 88.0f, 158.0f });
	rgb_9 = std::vector<float>({ 247.0f, 252.0f, 240.0f, 224.0f, 243.0f, 219.0f, 204.0f, 235.0f, 197.0f, 168.0f, 221.0f, 181.0f, 123.0f, 204.0f, 196.0f, 78.0f, 179.0f, 211.0f, 43.0f, 140.0f, 190.0f, 8.0f, 104.0f, 172.0f, 8.0f, 64.0f, 129.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::GnBu, scheme));

	
	// Greys
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 240.0f, 240.0f, 240.0f, 189.0f, 189.0f, 189.0f, 99.0f, 99.0f, 99.0f });
	rgb_4 = std::vector<float>({ 247.0f, 247.0f, 247.0f, 204.0f, 204.0f, 204.0f, 150.0f, 150.0f, 150.0f, 82.0f, 82.0f, 82.0f });
	rgb_5 = std::vector<float>({ 247.0f, 247.0f, 247.0f, 204.0f, 204.0f, 204.0f, 150.0f, 150.0f, 150.0f, 99.0f, 99.0f, 99.0f, 37.0f, 37.0f, 37.0f });
	rgb_6 = std::vector<float>({ 247.0f, 247.0f, 247.0f, 217.0f, 217.0f, 217.0f, 189.0f, 189.0f, 189.0f, 150.0f, 150.0f, 150.0f, 99.0f, 99.0f, 99.0f, 37.0f, 37.0f, 37.0f });
	rgb_7 = std::vector<float>({ 247.0f, 247.0f, 247.0f, 217.0f, 217.0f, 217.0f, 189.0f, 189.0f, 189.0f, 150.0f, 150.0f, 150.0f, 115.0f, 115.0f, 115.0f, 82.0f, 82.0f, 82.0f, 37.0f, 37.0f, 37.0f });
	rgb_8 = std::vector<float>({ 255.0f, 255.0f, 255.0f, 240.0f, 240.0f, 240.0f, 217.0f, 217.0f, 217.0f, 189.0f, 189.0f, 189.0f, 150.0f, 150.0f, 150.0f, 115.0f, 115.0f, 115.0f, 82.0f, 82.0f, 82.0f, 37.0f, 37.0f, 37.0f });
	rgb_9 = std::vector<float>({ 255.0f, 255.0f, 255.0f, 240.0f, 240.0f, 240.0f, 217.0f, 217.0f, 217.0f, 189.0f, 189.0f, 189.0f, 150.0f, 150.0f, 150.0f, 115.0f, 115.0f, 115.0f, 82.0f, 82.0f, 82.0f, 37.0f, 37.0f, 37.0f, 0.0f, 0.0f, 0.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Greys, scheme));


	// YlOrRd
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 255.0f, 237.0f, 160.0f, 254.0f, 178.0f, 76.0f, 240.0f, 59.0f, 32.0f });
	rgb_4 = std::vector<float>({ 255.0f, 255.0f, 178.0f, 254.0f, 204.0f, 92.0f, 253.0f, 141.0f, 60.0f, 227.0f, 26.0f, 28.0f });
	rgb_5 = std::vector<float>({ 255.0f, 255.0f, 178.0f, 254.0f, 204.0f, 92.0f, 253.0f, 141.0f, 60.0f, 240.0f, 59.0f, 32.0f, 189.0f, 0.0f, 38.0f });
	rgb_6 = std::vector<float>({ 255.0f, 255.0f, 178.0f, 254.0f, 217.0f, 118.0f, 254.0f, 178.0f, 76.0f, 253.0f, 141.0f, 60.0f, 240.0f, 59.0f, 32.0f, 189.0f, 0.0f, 38.0f });
	rgb_7 = std::vector<float>({ 255.0f, 255.0f, 178.0f, 254.0f, 217.0f, 118.0f, 254.0f, 178.0f, 76.0f, 253.0f, 141.0f, 60.0f, 252.0f, 78.0f, 42.0f, 227.0f, 26.0f, 28.0f, 177.0f, 0.0f, 38.0f });
	rgb_8 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 255.0f, 237.0f, 160.0f, 254.0f, 217.0f, 118.0f, 254.0f, 178.0f, 76.0f, 253.0f, 141.0f, 60.0f, 252.0f, 78.0f, 42.0f, 227.0f, 26.0f, 28.0f, 177.0f, 0.0f, 38.0f });
	rgb_9 = std::vector<float>({ 255.0f, 255.0f, 204.0f, 255.0f, 237.0f, 160.0f, 254.0f, 217.0f, 118.0f, 254.0f, 178.0f, 76.0f, 253.0f, 141.0f, 60.0f, 252.0f, 78.0f, 42.0f, 227.0f, 26.0f, 28.0f, 189.0f, 0.0f, 38.0f, 128.0f, 0.0f, 38.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::YlOrRd, scheme));


	// PuRd
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 231.0f, 225.0f, 239.0f, 201.0f, 148.0f, 199.0f, 221.0f, 28.0f, 119.0f });
	rgb_4 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 215.0f, 181.0f, 216.0f, 223.0f, 101.0f, 176.0f, 206.0f, 18.0f, 86.0f });
	rgb_5 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 215.0f, 181.0f, 216.0f, 223.0f, 101.0f, 176.0f, 221.0f, 28.0f, 119.0f, 152.0f, 0.0f, 67.0f });
	rgb_6 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 212.0f, 185.0f, 218.0f, 201.0f, 148.0f, 199.0f, 223.0f, 101.0f, 176.0f, 221.0f, 28.0f, 119.0f, 152.0f, 0.0f, 67.0f });
	rgb_7 = std::vector<float>({ 241.0f, 238.0f, 246.0f, 212.0f, 185.0f, 218.0f, 201.0f, 148.0f, 199.0f, 223.0f, 101.0f, 176.0f, 231.0f, 41.0f, 138.0f, 206.0f, 18.0f, 86.0f, 145.0f, 0.0f, 63.0f });
	rgb_8 = std::vector<float>({ 247.0f, 244.0f, 249.0f, 231.0f, 225.0f, 239.0f, 212.0f, 185.0f, 218.0f, 201.0f, 148.0f, 199.0f, 223.0f, 101.0f, 176.0f, 231.0f, 41.0f, 138.0f, 206.0f, 18.0f, 86.0f, 145.0f, 0.0f, 63.0f });
	rgb_9 = std::vector<float>({ 247.0f, 244.0f, 249.0f, 231.0f, 225.0f, 239.0f, 212.0f, 185.0f, 218.0f, 201.0f, 148.0f, 199.0f, 223.0f, 101.0f, 176.0f, 231.0f, 41.0f, 138.0f, 206.0f, 18.0f, 86.0f, 152.0f, 0.0f, 67.0f, 103.0f, 0.0f, 31.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 1) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::PuRd, scheme));


	// Blues
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 222.0f, 235.0f, 247.0f, 158.0f, 202.0f, 225.0f, 49.0f, 130.0f, 189.0f });
	rgb_4 = std::vector<float>({ 239.0f, 243.0f, 255.0f, 189.0f, 215.0f, 231.0f, 107.0f, 174.0f, 214.0f, 33.0f, 113.0f, 181.0f });
	rgb_5 = std::vector<float>({ 239.0f, 243.0f, 255.0f, 189.0f, 215.0f, 231.0f, 107.0f, 174.0f, 214.0f, 49.0f, 130.0f, 189.0f, 8.0f, 81.0f, 156.0f });
	rgb_6 = std::vector<float>({ 239.0f, 243.0f, 255.0f, 198.0f, 219.0f, 239.0f, 158.0f, 202.0f, 225.0f, 107.0f, 174.0f, 214.0f, 49.0f, 130.0f, 189.0f, 8.0f, 81.0f, 156.0f });
	rgb_7 = std::vector<float>({ 239.0f, 243.0f, 255.0f, 198.0f, 219.0f, 239.0f, 158.0f, 202.0f, 225.0f, 107.0f, 174.0f, 214.0f, 66.0f, 146.0f, 198.0f, 33.0f, 113.0f, 181.0f, 8.0f, 69.0f, 148.0f });
	rgb_8 = std::vector<float>({ 247.0f, 251.0f, 255.0f, 222.0f, 235.0f, 247.0f, 198.0f, 219.0f, 239.0f, 158.0f, 202.0f, 225.0f, 107.0f, 174.0f, 214.0f, 66.0f, 146.0f, 198.0f, 33.0f, 113.0f, 181.0f, 8.0f, 69.0f, 148.0f });
	rgb_9 = std::vector<float>({ 247.0f, 251.0f, 255.0f, 222.0f, 235.0f, 247.0f, 198.0f, 219.0f, 239.0f, 158.0f, 202.0f, 225.0f, 107.0f, 174.0f, 214.0f, 66.0f, 146.0f, 198.0f, 33.0f, 113.0f, 181.0f, 8.0f, 81.0f, 156.0f, 8.0f, 48.0f, 107.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::Blues, scheme));


	// PuBuGn
	scheme.rgbs.clear();
	scheme.properties.clear();

	rgb_3 = std::vector<float>({ 236.0f, 226.0f, 240.0f, 166.0f, 189.0f, 219.0f, 28.0f, 144.0f, 153.0f });
	rgb_4 = std::vector<float>({ 246.0f, 239.0f, 247.0f, 189.0f, 201.0f, 225.0f, 103.0f, 169.0f, 207.0f, 2.0f, 129.0f, 138.0f });
	rgb_5 = std::vector<float>({ 246.0f, 239.0f, 247.0f, 189.0f, 201.0f, 225.0f, 103.0f, 169.0f, 207.0f, 28.0f, 144.0f, 153.0f, 1.0f, 108.0f, 89.0f });
	rgb_6 = std::vector<float>({ 246.0f, 239.0f, 247.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 103.0f, 169.0f, 207.0f, 28.0f, 144.0f, 153.0f, 1.0f, 108.0f, 89.0f });
	rgb_7 = std::vector<float>({ 246.0f, 239.0f, 247.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 103.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 2.0f, 129.0f, 138.0f, 1.0f, 100.0f, 80.0f });
	rgb_8 = std::vector<float>({ 255.0f, 247.0f, 251.0f, 236.0f, 226.0f, 240.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 103.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 2.0f, 129.0f, 138.0f, 1.0f, 100.0f, 80.0f });
	rgb_9 = std::vector<float>({ 255.0f, 247.0f, 251.0f, 236.0f, 226.0f, 240.0f, 208.0f, 209.0f, 230.0f, 166.0f, 189.0f, 219.0f, 103.0f, 169.0f, 207.0f, 54.0f, 144.0f, 192.0f, 2.0f, 129.0f, 138.0f, 1.0f, 108.0f, 89.0f, 1.0f, 70.0f, 54.0f });

	prop_3 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 1), std::make_pair(Properties::copy, 1), std::make_pair(Properties::screen, 1) });
	prop_4 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 2), std::make_pair(Properties::screen, 1) });
	prop_5 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 2), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 2) });
	prop_6 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_7 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_8 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });
	prop_9 = std::map<Properties, unsigned short>({ std::make_pair(Properties::blind, 1), std::make_pair(Properties::print, 0), std::make_pair(Properties::copy, 0), std::make_pair(Properties::screen, 0) });

	scheme.properties.insert(std::make_pair(3, prop_3));
	scheme.properties.insert(std::make_pair(4, prop_4));
	scheme.properties.insert(std::make_pair(5, prop_5));
	scheme.properties.insert(std::make_pair(6, prop_6));
	scheme.properties.insert(std::make_pair(7, prop_7));
	scheme.properties.insert(std::make_pair(8, prop_8));
	scheme.properties.insert(std::make_pair(9, prop_9));

	scheme.rgbs.insert(std::make_pair(3, rgb_3));
	scheme.rgbs.insert(std::make_pair(4, rgb_4));
	scheme.rgbs.insert(std::make_pair(5, rgb_5));
	scheme.rgbs.insert(std::make_pair(6, rgb_6));
	scheme.rgbs.insert(std::make_pair(7, rgb_7));
	scheme.rgbs.insert(std::make_pair(8, rgb_8));
	scheme.rgbs.insert(std::make_pair(9, rgb_9));

	m_sequential.insert(std::make_pair(Sequential::PuBuGn, scheme));
}