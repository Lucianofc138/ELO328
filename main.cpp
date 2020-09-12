#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

#include "cmdArgsTools.hpp"
#include "imageProcTools.hpp"

int imageProgramRoutine(int argc, char** argv, int imageTokenPosition); 
int videoProgramRoutine(int argc, char** argv, int vidTokenPos);

int main(int argc, char** argv){ //------------------------------------------------------------------

    if ( argc < 4 ){
        printf("Se necesitan como mínimo 4 argumentos para video o 5 para foto\n");
        printf("./GAMMA [-m1 / -m2] [-v / -i <IMG_PATH>] gamma {-f x y w h} {-c r g b]} \n");
        printf("[]: opciones entre las cuales se debe elegir una.\n{}: argumentos opcionales. \n\n");
        return -1;
    }

    int imgTokenPos = getArgPosition("-i", argv, argc);
    int vidTokenPos = getArgPosition("-v", argv, argc);

    const bool ERROR_TOKENS = 
        (imgTokenPos==-1 && vidTokenPos==-1) || (imgTokenPos!=-1 && vidTokenPos!=-1);
    const bool IMAGE_TOKEN = 
        (imgTokenPos!=-1) && (vidTokenPos == -1);

    if ( ERROR_TOKENS ){
        std::cout << 
            "Choose JUST ONE between -v and -i" 
            << std::endl;
        return -1;
    } 
    
    else if ( IMAGE_TOKEN ){
        return imageProgramRoutine(argc, argv, imgTokenPos);
    } 
    
    else {
        std::cout << "VIDEO" << std::endl << std::endl;
        return videoProgramRoutine(argc, argv, vidTokenPos);
    }

    return 0;

} 

int imageProgramRoutine(int argc, char** argv, int imageTokenPosition) {//-------------------------
    char* imagePath = argv[imageTokenPosition+1];

    if (isAValidPath( imagePath )){
        cv::Mat image;
        image = cv::imread( argv[3], cv::IMREAD_COLOR);

        if ( !image.data ){ // cuchitril: 
            std::cerr << "No image data" << std::endl;
            return 1;
        }
        std::stringstream gammaBuffer;
        gammaBuffer << argv[imageTokenPosition + 2];

        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE );
        cv::imshow("Original", image);



        int border[4] = {0, 0, image.cols, image.rows};
        int edgeColorBGR[3] = {200, 100, 200};
        int gammaArray[MAX_BYTE];
        int mode = getModeFromArgs(argv, argc);
        double gamma = getGammaFromArgs(true, imageTokenPosition, argv, argc);

        setBorderFromArgs(border, image.size().width, image.size().height, argv, argc);
        setBorderColorFromArgs(edgeColorBGR, argv, argc);
        setGammaArray(gammaArray, gamma);
    
        cv::Mat resultImage = processFrame(
            border, mode, image, gamma, gammaArray, edgeColorBGR);

        cv::namedWindow("Result", cv::WINDOW_AUTOSIZE );
        cv::imshow("Result", resultImage);
        
        cv::waitKey(0);
        return 0;
    } 
    
    else {
        std::cout << "Path invalido. No coincide con una imagen." << std::endl;
        return -1;
    }
}

int videoProgramRoutine(int argc, char** argv, int videoTokenPosition) {//-------------------------
    std::string videoDevice("/dev/video0");
    std::stringstream gammaBuffer;
    cv::VideoCapture webCam;

    gammaBuffer << argv[videoTokenPosition + 1];

    webCam.open(videoDevice);

    if (!webCam.isOpened()) {
        std::cerr << "Unable to open video device!" << std::endl;
        return 1;
    }
    
    cv::Mat currentImage;
    cv::Mat resultImage;
    webCam >> currentImage;

    // Default Values
    int border[4] = {0, 0, currentImage.cols, currentImage.rows};
    int edgeColorBGR[3] = {200, 100, 200};
    int gammaArray[MAX_BYTE];
    int mode = getModeFromArgs(argv, argc);
    int delay =  30; // ms 
    double gamma = getGammaFromArgs(false, videoTokenPosition, argv, argc);

    setBorderFromArgs(border, currentImage.size().width, currentImage.size().height, argv, argc);
    setBorderColorFromArgs(edgeColorBGR, argv, argc);
    setGammaArray(gammaArray, gamma);

    

    bool RESOLUTION_EXCEEDED = false;
    while(true) {
        webCam >> currentImage;
        
        try {
            resultImage = processFrame(
                border, mode, currentImage, gamma, gammaArray, edgeColorBGR);
        }
        catch(cv::Exception) {
            std::cerr << "Error loading processed image." << std::endl;
            return 1;
            RESOLUTION_EXCEEDED = true;
        }
        
        cv::imshow("Live Feed", resultImage);
        
        if ( (cv::waitKey(delay) != -1) || (RESOLUTION_EXCEEDED)) {
            break;
        }
    }
    
    webCam.release();
    return 0;
}