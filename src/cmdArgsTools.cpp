#include "cmdArgsTools.hpp"

int getArgPosition(std::string arg, char** argv, int argc) {
    for(int i=0; i<argc; i++) {
        if (arg.compare(argv[i]) == 0) return i; 
    }
    return -1;
} 

int getModeFromArgs(char** argv, int argc) { 
    int m1TokPos = getArgPosition("-m1", argv, argc);
    int m2TokPos = getArgPosition("-m2", argv, argc);
    if ( ((m1TokPos !=-1) && (m2TokPos !=-1)) || ((m1TokPos ==-1) && (m2TokPos ==-1)) ){
        std::cout << "Se debe incluir solo un modo -m1/-m2" << std::endl;
        return -1;
    }
    
    else if ( m1TokPos !=-1 ) {
        std::cout << "Modo 1" << std::endl;
        return 1;
    }
    
    else {
        std::cout << "Modo 2" << std::endl;
        return 2;
    }
}

bool isAValidPath(char* path) {
    std::cout << "Checking path..." << std::endl;
    if ( FILE *file = fopen(path, "r") ){
        fclose(file);
        return true;
    }

    else {
        return false;
    }   
}

double getGammaFromArgs(bool workingWithImg, int tokenPos, char** argv, int argc){
    int gammaPosition = tokenPos + 1;
    if (workingWithImg) gammaPosition++;
    std::stringstream gammaBuffer;
    gammaBuffer << argv[gammaPosition];
    double gamma;
    gammaBuffer >> gamma;
    const double minGamma = 0.001;
    if(gamma <= minGamma ){
        gamma = 1;
        std::cout << "Invalid gamma value. Gamma correction deactivated" << std::endl;
    } 
    return gamma;
}

int setBorderFromArgs(int border[], int imageWidth, int imageHeight, char** argv, int argc) {
    int frameTokenPosition = getArgPosition("-f", argv, argc);
    std::cout << "Getting area data..." << std::endl;
    if (frameTokenPosition != -1){
        for (int idx=0; idx<4; idx++) 
            border[idx] = atoi(argv[frameTokenPosition+idx+1]);

        const bool EDGE_EXCEED_WIDTH = (border[0]+border[2] > imageWidth);
        if (EDGE_EXCEED_WIDTH)
            border[2] = imageWidth - border[0];
        const bool EDGE_EXCEED_HEIGHT = (border[1]+border[3] > imageHeight);
        if (EDGE_EXCEED_HEIGHT)
            border[3] = imageHeight - border[1];
    
        return 0;
    }
    else{
        return -1;
    }
}

int setBorderColorFromArgs(int frameColorRGB[], char** argv, int argc) {
    int colorTokenPosition = getArgPosition("-c", argv, argc);
    std::cout << "Getting color data..." << std::endl;

    if (colorTokenPosition != -1) {
        for (int idx=0; idx<3; idx++)
            frameColorRGB[idx] = atoi(argv[colorTokenPosition+idx+1]);
        return 0;
    }
    else{
        return -1;
    }
}

