#include "image_processing.h"
#include <iostream>
#include <fstream>
#include <npp.h>
#include <cuda_runtime.h>

Npp8u* loadPGM(const char* filename, int* width, int* height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return nullptr;
    }

    std::string header;
    file >> header;
    if (header != "P5") {
        std::cerr << "Error: Invalid PGM file" << std::endl;
        return nullptr;
    }

    file >> *width >> *height;
    int maxVal;
    file >> maxVal;
    file.ignore(256, '\n');

    Npp8u* data = new Npp8u[*width * *height];
    file.read(reinterpret_cast<char*>(data), *width * *height);

    file.close();
    return data;
}

void savePGM(const char* filename, const Npp8u* data, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << "P5\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(data), width * height);

    file.close();
}

void applyGaussianBlur(const Npp8u* inputImage, Npp8u* outputImage, int width, int height) {
    // Initialize CUDA device
    cudaSetDevice(0);

    // Allocate memory on the GPU
    Npp8u *d_src, *d_dst;
    int srcStep = width * sizeof(Npp8u);
    int dstStep = width * sizeof(Npp8u);
    NppiSize roiSize = {width, height};

    cudaMalloc((void**)&d_src, width * height * sizeof(Npp8u));
    cudaMalloc((void**)&d_dst, width * height * sizeof(Npp8u));

    // Copy data from host to device
    cudaMemcpy(d_src, inputImage, width * height * sizeof(Npp8u), cudaMemcpyHostToDevice);

    // Define Gaussian kernel
    Npp32f kernel[5 * 5] = {
        1,  4,  7,  4, 1,
        4, 16, 26, 16, 4,
        7, 26, 41, 26, 7,
        4, 16, 26, 16, 4,
        1,  4,  7,  4, 1
    };
    NppiSize kernelSize = {5, 5};
    NppiPoint anchor = {2, 2};

    // Apply Gaussian blur
    nppiFilter_8u_C1R(d_src, srcStep, d_dst, dstStep, roiSize, kernel, kernelSize, anchor);

    // Copy result back to host
    cudaMemcpy(outputImage, d_dst, width * height * sizeof(Npp8u), cudaMemcpyDeviceToHost);

    // Free GPU memory
    cudaFree(d_src);
    cudaFree(d_dst);
}