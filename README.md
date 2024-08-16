# CUDA NPP Image Processing

## Overview
This project demonstrates the use of the CUDA NPP library for performing image processing tasks on a GPU. Specifically, it applies a Gaussian blur filter to an input image.

## Requirements
- CUDA Toolkit
- CMake

## Build and Run
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/cuda-npp-image-processing.git
    cd cuda-npp-image-processing
    ```

2. Create a build directory and navigate to it:
    ```sh
    mkdir build
    cd build
    ```

3. Configure the project with CMake:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

5. Run the executable:
    ```sh
    ./main
    ```

6. Check the `images` directory for the output image.

## Notes
- Ensure that you have an NVIDIA GPU and the CUDA Toolkit installed.
- Modify the `input.pgm` file in the `images` directory with your own image for testing.