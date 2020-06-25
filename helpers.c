#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    int average = 0;
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            pixel = image[h][w];
            average = round(((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue)/3.0));
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;

    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            pixel = image[h][w];
            sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

            if(sepiaRed > 255) {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255) {
                sepiaBlue = 255;
            }

            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int currentPixelRed;
    int currentPixelGreen;
    int currentPixelBlue;

    int oppositePixelRed;
    int oppositePixelGreen;
    int oppositePixelBlue;
    int oppositePixelWidthIndex = 0;

    RGBTRIPLE(*originalImage)[width] = image;

    int middleOfImage = round(width/2);

    for(int h = 0; h < height; h++) {
        for(int w = 0; w < middleOfImage; w++) {
            oppositePixelWidthIndex = abs(w - (width - 1));

            currentPixelRed = image[h][w].rgbtRed;
            currentPixelGreen = image[h][w].rgbtGreen;
            currentPixelBlue = image[h][w].rgbtBlue;

            oppositePixelRed = image[h][oppositePixelWidthIndex].rgbtRed;
            oppositePixelGreen = image[h][oppositePixelWidthIndex].rgbtGreen;
            oppositePixelBlue = image[h][oppositePixelWidthIndex].rgbtBlue;

            image[h][oppositePixelWidthIndex].rgbtRed = currentPixelRed;
            image[h][oppositePixelWidthIndex].rgbtGreen = currentPixelGreen;
            image[h][oppositePixelWidthIndex].rgbtBlue = currentPixelBlue;

            image[h][w].rgbtRed = oppositePixelRed;
            image[h][w].rgbtGreen = oppositePixelGreen;
            image[h][w].rgbtBlue = oppositePixelBlue;

        }
    }
}

bool isInsideImageBoundary(int currentRow, int currentColumn, int height, int width) {
    return (currentRow >= 0 && currentRow < height) && (currentColumn >= 0 && currentColumn < width);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float pixelsInBlurBox = 0.0;
    int blurBoxTotalRedPixel = 0;
    int blurBoxTotalGreenPixel = 0;
    int blurBoxTotalBluePixel = 0;

    int currentRow = 0;
    int currentColumn = 0;

    RGBTRIPLE originalImage[height][width];
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            originalImage[h][w] = image[h][w];;
        }
    }

    RGBTRIPLE pixel;
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            for(int row = -1; row < 2; row++) {
                for(int column = -1; column < 2; column++) {
                    currentRow = h + row;
                    currentColumn = w + column;

                    if(isInsideImageBoundary(currentRow,currentColumn,height,width) == true)
                    {
                        pixel = originalImage[currentRow][currentColumn];
                        blurBoxTotalRedPixel += pixel.rgbtRed;
                        blurBoxTotalGreenPixel += pixel.rgbtGreen;
                        blurBoxTotalBluePixel += pixel.rgbtBlue;

                        pixelsInBlurBox++;
                        //printf("In boundary: (%d,%d) \t",currentRow,currentColumn);
                    } else {
                        //printf("Out boundary:(%d,%d) \t",currentRow,currentColumn);
                    }
                }
                //printf("\n");
            }
            image[h][w].rgbtRed = round(blurBoxTotalRedPixel / pixelsInBlurBox);
            image[h][w].rgbtGreen = round(blurBoxTotalGreenPixel / pixelsInBlurBox);
            image[h][w].rgbtBlue = round(blurBoxTotalBluePixel / pixelsInBlurBox);

            pixelsInBlurBox = 0.0;
            blurBoxTotalRedPixel = 0;
            blurBoxTotalGreenPixel = 0;
            blurBoxTotalBluePixel = 0;
            //printf("-------------------------------------\n");
        }
    }
}