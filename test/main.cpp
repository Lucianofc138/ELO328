#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/opencv.hpp>

#include "imageProcTools.hpp"

std::vector<cv::Mat> loadSamples();
double getImageProcessTime(const cv::Mat& image, int mode);
double getAverage(const std::vector<double>& samples);

int main(int argc, char** argv){ //------------------------------------------------------------------

    if ( argc > 1 ){
        printf("Este programa no acepta argumentos\n");
    }
    
    std::vector<cv::Mat> samples = loadSamples();
    
    
    std::vector<double> timesTable;
    std::vector<double> timesPixByPix;

    std::vector<cv::Mat>::iterator it;
    int counter = 0;
    for (it = samples.begin(); it < samples.end(); ++it) {
        timesTable.push_back(
            getImageProcessTime(samples[counter], 1)
        );

        timesPixByPix.push_back(
            getImageProcessTime(samples[counter], 2)
        );
        counter++;
    }

    std::cout << "Tiempo tabla / tiempo pixel a pixel" << std::endl;

    for (int i = 0; i < samples.size(); ++i) {
        std::cout << timesTable[i] << " / ";
        std::cout << timesPixByPix[i] << " [s]" << std::endl << std::endl;
    }

    std::cout << "Tiempo promedio tabla: " << getAverage(timesTable) << std::endl;
    std::cout << "Tiempo promedio pixel a pixel: " << getAverage(timesPixByPix) << std::endl;

    return 0;
} 
 
std::vector<cv::Mat> loadSamples() {
    std::string currentSample;
    int sampleCounter = 0;
    std::vector<cv::Mat> samples;

    while (true) {
        currentSample = "./samples/sample" + std::to_string(sampleCounter) + ".jpg";
        cv::Mat tempSample;
        
        tempSample = cv::imread(currentSample, cv::IMREAD_COLOR);

        if (tempSample.empty())
        {
            break;
        }

        samples.push_back(tempSample);
        currentSample.clear();
        sampleCounter++;
    }


    return samples;
}

double getImageProcessTime(const cv::Mat& image, int mode) {
    int gammaArray[256] = {0};
    int edgeColorBGR[3] = {0};
    double gamma = 0.5;

    int border[4] = {0, 0, image.size().width, image.size().height};
    
    if (mode == 1) 
        setGammaArray(gammaArray, gamma);

    double initialTick = (double)cv::getTickCount(); 
    processFrame(border, mode, image, 0.5, gammaArray, edgeColorBGR);
    double finalTick = (double)cv::getTickCount();
    
    return (finalTick - initialTick) / cv::getTickFrequency();
}

double getAverage(const std::vector<double>& samples) {
    double cumSum = 0;
    for (int i = 0; i < samples.size(); ++i) {
        cumSum += samples[i];
    }
    return cumSum / samples.size();
}