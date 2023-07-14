// Generated by imageconverter. Please, do not edit!

#ifndef TOUCHGFX_SVGDATABASE_HPP
#define TOUCHGFX_SVGDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/hal/VGData.hpp>

enum SVGImages
{
    SVG_BADBULBS_ID = 0,
    SVG_BLACKB_ID = 1,
    SVG_BLUEB_ID = 2,
    SVG_BLUETOOTH_ID = 3,
    SVG_DMX_ID = 4,
    SVG_EXCHANGE_FUNDS_FILL_ID = 5,
    SVG_EXP_ID = 6,
    SVG_EXPLODE_ID = 7,
    SVG_FIREWORK_ID = 8,
    SVG_FLASH_ID = 9,
    SVG_LIGHTNING_ID = 10,
    SVG_LINE_CHART_FILL_ID = 11,
    SVG_LOG_ID = 12,
    SVG_PAPARAZZI_ID = 13,
    SVG_PULSE_ID = 14,
    SVG_S_ID = 15,
    SVG_SETTINGS_5_FILL_ID = 16,
    SVG_SOUND_MODULE_FILL_ID = 17,
    SVG_TRANSLATE_ID = 18,
    SVG_TV_ID = 19,
    SVG_WINDY_FILL_ID = 20,
    SVG_XY_ID = 21,
    NUMBER_OF_SVG_IMAGES = 22
};

namespace SVGDatabase
{
const touchgfx::VGObject* getInstance();
uint16_t getInstanceSize();
} // namespace SVGDatabase

#endif // TOUCHGFX_SVGDATABASE_HPP
