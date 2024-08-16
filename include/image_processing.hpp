#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <npp.h>

Npp8u* loadPGM(const char* filename, int* width, int* height);
void savePGM(const char* filename, const Npp8u* data, int width, int height);
void applyGaussianBlur(const Npp8u* inputImage, Npp8u* outputImage, int width, int height);

#endif // IMAGE_PROCESSING_H