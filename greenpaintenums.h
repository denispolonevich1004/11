#ifndef GREENPAINTENUMS_H
#define GREENPAINTENUMS_H

/**
 * @brief Enum with instruments names
 *
 */
typedef enum
{
    NONE_INSTRUMENT = 0,
    PEN,
    CURSOR,
    ERASER,
    LINE,
    COLORPICKERPALETTE,
    MAGNIFIER,
    SPRAY,
    FILL,
    RECTANGLE,
    ELLIPSE,
    CURVELINE,
    TEXT,

    // Don't use it. (Used to know count of current instrument)
    INSTRUMENTS_COUNT
} InstrumentsEnum;

/**
 * @brief Enum with effects names
 *
 */
typedef enum
{
    NONE_EFFECT = 0,
    NEGATIVE,
    GRAY,
    BINARIZATION,
    GAUSSIANBLUR,
    GAMMA,
    SHARPEN,
    CUSTOM,

    // Don't use it. (Used to know count of current instrument)
    EFFECTS_COUNT
} EffectsEnum;

#endif // GREENPAINTENUMS_H
