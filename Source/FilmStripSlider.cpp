/*
  ==============================================================================

    FilmStripSlider.cpp
    Created: 19 May 2020 4:32:58pm
    Author:  Peter Wing

  ==============================================================================
*/

#include "FilmStripSlider.h"

FilmStripSlider::FilmStripSlider (Image *_knobStrip) : knobStrip(_knobStrip)
{
    if (knobStrip->getWidth() > knobStrip->getHeight())
    {
        frameCount        = knobStrip->getWidth() / knobStrip->getHeight();
        frameSize        = knobStrip->getHeight();
        isVerticalStrip    = false;
    }
    else
    {
        frameCount        = knobStrip->getHeight() / knobStrip->getWidth();
        frameSize        = knobStrip->getWidth();
        isVerticalStrip    = true;
    }
}

void FilmStripSlider::drawFrame (Graphics &g, int x, int y, int width, int height, Slider &slider)
{
    const double div    = slider.getMaximum() / frameCount;
    double pos            = (int)(slider.getValue() / div);

    if (pos > 0)
        pos = pos - 1;

    if (width != height) /* scale */
    {
        x        = (width / 2) - (height / 2);
        width    = height;
    }

    if (isVerticalStrip)
    {
        g.drawImage(*knobStrip, x, y, width, height, 0, (int)(pos*frameSize), frameSize, frameSize, false);
        
    }
    else
    {
        g.drawImage(*knobStrip, x, y, width, height, (int)(pos*frameSize), 0, frameSize, frameSize, false);
    }
}
