#pragma once

#ifndef LAYER_INDICATOR_H
#define LAYER_INDICATOR_H

#include "ILI9341_t3.h"
#include "fonts/font_Quattrocento-Bold.h"

#define INDICATOR_WIDTH 56
#define INDICATOR_HEIGHT 46

void setLayerIndicator(uint8_t activeLayer);
void drawLayerInfo(int16_t x, int16_t y);

#endif // !LAYER_INDICATOR_H
