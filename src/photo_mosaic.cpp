#include "photo_mosaic.h"
#include "rgb_image.h"
#include <limits>
#include <cmath>
#include <iostream>

// Constructor
PhotoMosaic::PhotoMosaic() {}

PhotoMosaic::PhotoMosaic(Image* image) {
    TImage = image;
}

// Destructor
PhotoMosaic::~PhotoMosaic() {}

// Read sub-images
void PhotoMosaic::readSubImage(const string& imgName, vector<string>& Mnist_Folder) {
    subImage.List_Name_Directory(imgName, Mnist_Folder);
    for (const auto& name : Mnist_Folder) {
        subImage.LoadImage(name);
        sub_image.push_back(subImage);
        int*** _pixel = subImage.get_3D_pixels();
        sub_avg.push_back(CalculateAverage(_pixel, subImage.get_width(), subImage.get_height()));
    }
}

// Calculate the average color of an image
array<int, 3> PhotoMosaic::CalculateAverage(int*** pixels, int width, int height) {
    long sumR = 0, sumG = 0, sumB = 0;
    int count = width * height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sumR += pixels[y][x][0];
            sumG += pixels[y][x][1];
            sumB += pixels[y][x][2];
        }
    }

    return { static_cast<int>(sumR / count), static_cast<int>(sumG / count), static_cast<int>(sumB / count) };
}

// Find the best match index based on the average color
int PhotoMosaic::getBestMatchIndex(const array<int, 3>& tarAvg) {
    int bestIndex = 0;
    double minDist = std::numeric_limits<double>::max();

    for (size_t i = 0; i < sub_avg.size(); ++i) {
        double dist = pow(tarAvg[0] - sub_avg[i][0], 2) + 
                      pow(tarAvg[1] - sub_avg[i][1], 2) + 
                      pow(tarAvg[2] - sub_avg[i][2], 2);
        if (dist < minDist) {
            minDist = dist;
            bestIndex = i;
        }
    }
    return bestIndex;
}

// Split the image into sub-images
vector<int***> PhotoMosaic::splitImage(int*** pixels, int subWidth, int subHeight, int width, int height) {
    vector<int***> subImages;
    for (int y = 0; y < height / subHeight; ++y) {
        for (int x = 0; x < width / subWidth; ++x) {
            int*** subImage = new int**[subHeight];
            for (int i = 0; i < subHeight; ++i) {
                subImage[i] = new int*[subWidth];
                for (int j = 0; j < subWidth; ++j) {
                    subImage[i][j] = new int[3];
                    subImage[i][j][0] = pixels[y * subHeight + i][x * subWidth + j][0];
                    subImage[i][j][1] = pixels[y * subHeight + i][x * subWidth + j][1];
                    subImage[i][j][2] = pixels[y * subHeight + i][x * subWidth + j][2];
                }
            }
            subImages[y][x] = subImage;
        }
    }
    return subImages;
}

// Create the image grid
int*** PhotoMosaic::createImageGrid(const vector<int***>& sub_images_pixel, int subWidth, int subHeight, int width, int height) {
    int*** grid = new int**[height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            grid[i][j] = new int[3];
        }
    }
    cout << "Start Grid success\n";
    for (int y = 0; y < height / subHeight; ++y) {
        for (int x = 0; x < width / subWidth; ++x) {
            for (int i = 0; i < subHeight; ++i) {
                for (int j = 0; j < subWidth; ++j) {
                    grid[y * subHeight + i][x * subWidth + j][0] = sub_images_pixel[y * (width / subWidth) + x][i][j][0];
                    grid[y * subHeight + i][x * subWidth + j][1] = sub_images_pixel[y * (width / subWidth) + x][i][j][1];
                    grid[y * subHeight + i][x * subWidth + j][2] = sub_images_pixel[y * (width / subWidth) + x][i][j][2];
                }
            }
        }
    }
    return grid;
}

// Generate the mosaic image
void PhotoMosaic::Generate_Mosaic(const string& path) {
    cout << "enter Generate_MOsaic\n";
    int subHeight = sub_image[0].get_height(), subWidth = sub_image[0].get_width();
    cout << "get subheight success\n";
    int height = TImage->get_height(), width = TImage->get_width();
    cout << "get Imageheight success\n";
    vector<string> subName;
    cout << "Set up Generate_Mosaic success\n";
    readSubImage(path, subName);
    cout << "Read subImage success\n";

    int*** m_pixels = TImage->get_3D_pixels();
    vector<int***> splitedImage = splitImage(m_pixels, subWidth, subHeight, width, height);
    cout << "Split Image success\n";
    vector<int***> Grid_v;
    cout << "Ready to Generate_mosaic success\n";
    for (int y = 0; y < height / subHeight; y++) {
    for (int x = 0; x < width / subWidth; x++) {
        CalculateAverage(splitImage[y * (width / subWidth) + x]); // Calculate the average of the y+xth splited photo
        BestMatchIndex = getBestMatchIndex(splited_image[y * (width / subWidth) + x], sub_avg);
        Grid_v.push_back(sub_image[BestMatchIndex].get_3D_pixels());
    }
}

    // Clean up previously allocated memory
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         delete[] m_pixels[i][j];
    //     }
    //     delete[] m_pixels[i];
    // }
    // delete[] m_pixels;

    // Assign the new grid
    m_pixels = createImageGrid(Grid_v, subWidth, subHeight, width, height);
}

// Load image

Image *PhotoMosaic::get_TImage(){
    return TImage;
}
