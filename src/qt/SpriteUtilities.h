#ifndef PTXN_Q_SPRITE_UTILITIES_H
#define PTXN_Q_SPRITE_UTILITIES_H

#include <QImage>

class MultipaletteSprite;

QImage spriteToQImage(const MultipaletteSprite&, unsigned paletteId = 0);
QImage fitToMargins(const QImage&, int width, int height);

#endif
