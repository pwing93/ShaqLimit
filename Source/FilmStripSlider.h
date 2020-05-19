/*
  ==============================================================================

    FilmStripSlider.h
    Created: 19 May 2020 4:32:58pm
    Author:  Peter Wing

  ==============================================================================
*/


#include <JuceHeader.h>
#pragma once

class FilmStripSlider
{
    public:
        FilmStripSlider (Image *_knobStrip);
        void drawFrame (Graphics &g, int x, int y, int width, int height, Slider &slider);

    private:
        Image *knobStrip;
        int frameCount;
        int frameSize;
        bool isVerticalStrip;
};
