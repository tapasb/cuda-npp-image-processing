#include <iostream>
#include "image_processing.h"

int main() {
    // Load input image
    int width, height;
    Npp8u* h_inputImage = loadPGM("images/input.pgm", &width, &height);
    if (!h_inputImage) {
        std::cerr << "Error: Could not load input image!" << std::endl;
        return -1;
    }

    // Prepare output image
    Npp8u* h_outputImage = new Npp8u[width * height];

    // Apply Gaussian blur using NPP
    applyGaussianBlur(h_inputImage, h_outputImage, width, height);

    // Save the result
    savePGM("images/output.pgm", h_outputImage, width, height);

    // Clean up
    delete[] h_inputImage;
    delete[] h_outputImage;

    return 0;
}