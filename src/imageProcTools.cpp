#include "imageProcTools.hpp"

// GAMMA -----------------------------------------------------------------------------
int gammaPow(int srcLum, double gamma){ 
    double normSrcLum = ((double) srcLum) / 255;
    double normDstLum = pow(normSrcLum, gamma);
    int dstLum = normDstLum * 255; 
    return dstLum;
}

void setGammaArray(int gammaArray[], double gamma){
    for (int i = 0; i < MAX_BYTE; i++){
        double gammaNorm = ((double) i ) / (MAX_BYTE-1);
        gammaArray[i] = (int) (pow(gammaNorm, gamma)*(MAX_BYTE-1));
    }
}

// GAMMA CORRECTION ------------------------------------------------------------------

cv::Mat processFrame(int border[], int mode, const cv::Mat& oriFrame, double gamma, int gammaArray[], int edgeColorBGR[]){
    cv::Mat HLSImage;
    cvtColor(oriFrame, HLSImage, cv::COLOR_BGR2HLS);

    cv::Mat roi( HLSImage, cv::Rect(border[0], border[1], border[2], border[3]) );
    cv::MatIterator_<cv::Vec3b> it, end;
    if (mode ==  1){
        // tabla precalculada
        for (it = roi.begin<cv::Vec3b>(), end = roi.end<cv::Vec3b>(); it != end; it++) {
            (*it)[1] = gammaArray[(*it)[1]];
        }
    }else{ // (mode == 2)
        // cálculo pixel a pixel
        for (it = roi.begin<cv::Vec3b>(), end = roi.end<cv::Vec3b>(); it != end; it++) {
            (*it)[1] = gammaPow((*it)[1], 0.5);
        }
    }
    cv::Mat resultImage;
    cvtColor(HLSImage, resultImage, cv::COLOR_HLS2BGR);
    colorEdge(resultImage, border, edgeColorBGR);

    return resultImage;
}

// COLOR FRAME -----------------------------------------------------------------------
void colorRect(cv::Mat& rect, int edgeColorBGR[]){

    cv::MatIterator_<cv::Vec3b> it, end;
    for (it = rect.begin<cv::Vec3b>(), end = rect.end<cv::Vec3b>(); it != end; it++) {
        (*it)[0] = edgeColorBGR[0];
        (*it)[1] = edgeColorBGR[1];
        (*it)[2] = edgeColorBGR[2];
    }
}

void colorEdge(cv::Mat& resultImage, int border[], int edgeColorBGR[]){
    int leftBoxWidth = border[0];
    int rightBoxWidth = resultImage.size().width - border[0] - border[2];
    int topBoxHeight = border[1];
    int botBoxHeight = resultImage.size().height - (border[3] + border[1]);
    
    cv::Mat   roniUp(   resultImage,
                        cv::Rect(0, 0, resultImage.cols, topBoxHeight) );
    cv::Mat roniDown(   resultImage,
                        cv::Rect(0, (topBoxHeight + border[3]), resultImage.cols, botBoxHeight ));
    cv::Mat roniLeft(   resultImage,
                        cv::Rect(0, 0, leftBoxWidth, resultImage.rows) );
    cv::Mat roniRight(  resultImage, 
                        cv::Rect((leftBoxWidth + border[2]), 0, rightBoxWidth, resultImage.rows) );

    std::vector<cv::Mat> edge;
    edge.push_back(roniUp); edge.push_back(roniDown);
    edge.push_back(roniLeft); edge.push_back(roniRight);

    for(int i=0; i<4; i++){
        colorRect(edge[i],    edgeColorBGR);
    }
}