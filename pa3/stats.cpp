#include "stats.h"


#include "stats.h"

/**
   * Initialize the private vectors so that, for each color, entry
   * (x,y) is the sum of that color value in the rectangle from
   * (0,0) to (x,y). Similarly, for each color, the sumSq vector
   * entry (x,y) is the sum of that color squared over all image
   * pixels from (0,0) to (x,y).
   */
stats::stats(PNG & im){
//    std::cout<<"width:";
//    std::cout<<im.width()<<endl;
//    std::cout<<"height:";
//    std::cout<<im.height()<<endl;

    sumRed.resize(im.width());
    sumGreen.resize(im.width());
    sumBlue.resize(im.width());
    sumsqRed.resize(im.width());
    sumsqBlue.resize(im.width());
    sumsqGreen.resize(im.width());
    //std::cout<<"stats 25"<<endl;
    for(unsigned int i=0;i<sumRed.size();i++){
        sumRed[i].resize(im.height());
        sumGreen[i].resize(im.height());
        sumBlue[i].resize(im.height());
        sumsqRed[i].resize(im.height());
        sumsqBlue[i].resize(im.height());
        sumsqGreen[i].resize(im.height());
        for(unsigned int j=0;j<sumRed[i].size();j++){
            sumRed[i][j]=initializeSum('r',im, i, j);
            sumGreen[i][j]=initializeSum('g',im, i, j);
            sumBlue[i][j]=initializeSum('b',im, i, j);
            sumsqRed[i][j]=initializeSumSq('r',im, i, j);
            sumsqGreen[i][j]=initializeSumSq('g',im, i, j);
            sumsqBlue[i][j]=initializeSumSq('b',im, i, j);
        }

        //std::cout<<" (i,j) "<<i<<" "<<endl;
    }


//    std::cout<<"width:";
//    std::cout<<sumsqBlue.size()<<endl;
//    std::cout<<"height:";
//    std::cout<<sumsqBlue[0].size()<<endl;


}

/**
     * helper method for initializing the sum vectors
     * @param channel: r,g,b
     * @param im
     * @param w: the current width
     * @param h: the current height
     * @return sum of that color value in the rectangle from
     *         (0,0) to (x,y) and the sum of that color squared over all image
     *         pixels from (0,0) to (x,y)
     */
long stats::initializeSum(char channel,PNG & im, unsigned int w, unsigned int h){
    long sum=0;
//    for(unsigned int i=0;i<=w;i++){
//        for(unsigned int j=0;j<=h;j++) {
//            if(channel=='r'){
//                sum+=im.getPixel(i,j)->r;
//            }else if(channel=='g'){
//                sum+=im.getPixel(i,j)->g;
//            }else if(channel=='b'){
//                sum+=im.getPixel(i,j)->b;
//            }else{
//                std::cout<<"error check constructor"<<endl;
//            }
//        }
//    }
    if(w==0 && h==0){
        if(channel=='r'){
               sum=im.getPixel(w,h)->r;
        }else if(channel=='g'){
                sum=im.getPixel(w,h)->g;
        }else if(channel=='b'){
                sum=im.getPixel(w,h)->b;
        }
    }else if(h==0){
        if(channel=='r'){
            sum=sumRed[w-1][h]+im.getPixel(w,h)->r;
        }else if(channel=='g'){
            sum=sumGreen[w-1][h]+im.getPixel(w,h)->g;
        }else if(channel=='b'){
            sum=sumBlue[w-1][h]+im.getPixel(w,h)->b;
        }
    }else if(w==0){
        if(channel=='r'){
            sum=sumRed[w][h-1]+im.getPixel(w,h)->r;

        }else if(channel=='g'){
            sum=sumGreen[w][h-1]+im.getPixel(w,h)->g;
        }else if(channel=='b'){
            sum=sumBlue[w][h-1]+im.getPixel(w,h)->b;
        }
    } else{
        if(channel=='r'){
            sum=sumRed[w-1][h]+sumRed[w][h-1]-sumRed[w-1][h-1]+im.getPixel(w,h)->r;
        }else if(channel=='g'){
            sum=sumGreen[w-1][h]+sumGreen[w][h-1]-sumGreen[w-1][h-1]+im.getPixel(w,h)->g;
        }else if(channel=='b'){
            sum=sumBlue[w-1][h]+sumBlue[w][h-1]-sumBlue[w-1][h-1]+im.getPixel(w,h)->b;
        }
    }

    //std::cout<<"pixel 99: (w,h)"<<w<<","<<h<<"  "<<sum<<endl;


    return sum;
}
long stats::initializeSumSq(char channel,PNG & im, unsigned int w, unsigned int h){
    long sum=0;
//    for(unsigned int i=0;i<=w;i++){
//        for(unsigned int j=0;j<=h;j++) {
//            if(channel=='r'){
//                sum=sum+(im.getPixel(i,j)->r)*(im.getPixel(i,j)->r);
//            }
//            else if(channel=='b'){
//                sum=sum+(im.getPixel(i,j)->b)*(im.getPixel(i,j)->b);
//            }
//            else if(channel=='g'){
//                sum=sum+(im.getPixel(i,j)->g)*(im.getPixel(i,j)->g);
//            }
//        }
//    }
    if(w==0 && h==0){
        if(channel=='r'){
            sum=(im.getPixel(w,h)->r)*(im.getPixel(w,h)->r);
        }else if(channel=='g'){
            sum=(im.getPixel(w,h)->g)*(im.getPixel(w,h)->g);
        }else if(channel=='b'){
            sum=(im.getPixel(w,h)->b)*(im.getPixel(w,h)->b);
        }
    }else if(h==0){
        if(channel=='r'){
            sum=sumsqRed[w-1][h]+(im.getPixel(w,h)->r)*(im.getPixel(w,h)->r);
        }else if(channel=='g'){
            sum=sumsqGreen[w-1][h]+(im.getPixel(w,h)->g)*(im.getPixel(w,h)->g);
        }else if(channel=='b'){
            sum=sumsqBlue[w-1][h]+(im.getPixel(w,h)->b)*(im.getPixel(w,h)->b);
        }
    }else if(w==0){
        if(channel=='r'){
            sum=sumsqRed[w][h-1]+(im.getPixel(w,h)->r)*(im.getPixel(w,h)->r);
        }else if(channel=='g'){
            sum=sumsqGreen[w][h-1]+(im.getPixel(w,h)->g)*(im.getPixel(w,h)->g);
        }else if(channel=='b'){
            sum=sumsqBlue[w][h-1]+(im.getPixel(w,h)->b)*(im.getPixel(w,h)->b);
        }
    } else{
        if(channel=='r'){
            sum=sumsqRed[w-1][h]+sumsqRed[w][h-1]-sumsqRed[w-1][h-1]+(im.getPixel(w,h)->r)*(im.getPixel(w,h)->r);
        }else if(channel=='g'){
            sum=sumsqGreen[w-1][h]+sumsqGreen[w][h-1]-sumsqGreen[w-1][h-1]+(im.getPixel(w,h)->g)*(im.getPixel(w,h)->g);
        }else if(channel=='b'){
            sum=sumsqBlue[w-1][h]+sumsqBlue[w][h-1]-sumsqBlue[w-1][h-1]+(im.getPixel(w,h)->b)*(im.getPixel(w,h)->b);
        }
    }
    //std::cout<<"pixel 167: (w,h)"<<w<<","<<h<<"  "<<sum<<endl;




    return sum;
}




/**
   * Returns the sums of all pixel values in one color channel.
   * Useful in computing the average color of a rectangle.
   * @param channel is one of r, g, or b
   * @param ul is (x,y) of the upper left corner of the rectangle
   * @param w,h are the width and height of the rectangle
   */
long stats::getSum(char channel, pair<int,int> ul, int w, int h){
     long sum=0;
    if(channel=='r'){
        if(ul.first==0 && ul.second==0){
            return sumRed[w-1][h-1];
        }
        if(ul.first==0){
            return sumRed[w-1][ul.second+h-1]-sumRed[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumRed[ul.first+w-1][h-1]-sumRed[ul.first-1][h-1];
        }
        sum= sumRed[ul.first+w-1][ul.second+h-1]-sumRed[ul.first+w-1][ul.second-1]-sumRed[ul.first-1][ul.second+h-1]+sumRed[ul.first-1][ul.second-1];
    }
    else if(channel=='g'){
        if(ul.first==0 && ul.second==0){
            return sumGreen[w-1][h-1];
        }
        if(ul.first==0){
            return sumGreen[w-1][ul.second+h-1]-sumGreen[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumGreen[ul.first+w-1][h-1]-sumGreen[ul.first-1][h-1];
        }
        sum= sumGreen[ul.first+w-1][ul.second+h-1]-sumGreen[ul.first+w-1][ul.second-1]-sumGreen[ul.first-1][ul.second+h-1]+sumGreen[ul.first-1][ul.second-1];
    }
    else if(channel=='b'){
        if(ul.first==0 && ul.second==0){
            return sumBlue[w-1][h-1];
        }
        if(ul.first==0){
            return sumBlue[w-1][ul.second+h-1]-sumBlue[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumBlue[ul.first+w-1][h-1]-sumBlue[ul.first-1][h-1];
        }
        sum= sumBlue[ul.first+w-1][ul.second+h-1]-sumBlue[ul.first+w-1][ul.second-1]-sumBlue[ul.first-1][ul.second+h-1]+sumBlue[ul.first-1][ul.second-1];
    }

    return sum;
}

/**
   * Returns the sums of squares of all pixel values in one color
   * channel.
   * Useful in computing the variance of a rectangle
   * @param channel is one of r, g, or b
   * @param ul is (x,y) of the upper left corner of the rectangle
   * @param w,h are the width and height of the rectangle
   */
long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    long sum=0;
    if(channel=='r'){
        if(ul.first==0 && ul.second==0){
            return sumsqRed[w-1][h-1];
        }
        if(ul.first==0){
            return sumsqRed[w-1][ul.second+h-1]-sumsqRed[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumsqRed[ul.first+w-1][h-1]-sumsqRed[ul.first-1][h-1];
        }
        sum= sumsqRed[ul.first+w-1][ul.second+h-1]-sumsqRed[ul.first+w-1][ul.second-1]-sumsqRed[ul.first-1][ul.second+h-1]+sumsqRed[ul.first-1][ul.second-1];
    }
    else if(channel=='g'){
        if(ul.first==0 && ul.second==0){
            return sumsqGreen[w-1][h-1];
        }
        if(ul.first==0){
            return sumsqGreen[w-1][ul.second+h-1]-sumsqGreen[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumsqGreen[ul.first+w-1][h-1]-sumsqGreen[ul.first-1][h-1];
        }
        sum= sumsqGreen[ul.first+w-1][ul.second+h-1]-sumsqGreen[ul.first+w-1][ul.second-1]-sumsqGreen[ul.first-1][ul.second+h-1]+sumsqGreen[ul.first-1][ul.second-1];
    }
    else if(channel=='b'){
        if(ul.first==0 && ul.second==0){
            return sumsqBlue[w-1][h-1];
        }
        if(ul.first==0){
            return sumsqBlue[w-1][ul.second+h-1]-sumsqBlue[w-1][ul.second-1];
        }
        if(ul.second==0){
            return sumsqBlue[ul.first+w-1][h-1]-sumsqBlue[ul.first-1][h-1];
        }
        sum= sumsqBlue[ul.first+w-1][ul.second+h-1]-sumsqBlue[ul.first+w-1][ul.second-1]-sumsqBlue[ul.first-1][ul.second+h-1]+sumsqBlue[ul.first-1][ul.second-1];
    }

    return sum;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
/**
   * Given a rectangle, compute its sum of squared deviations from avg,
   * over all pixels and all color channels.
   * @param ul is (x, y) of the upper left corner of the rectangle
   * @param w,h are the width and height of the rectangle
   */
double stats::getVar(pair<int,int> ul, int w, int h){
    long r_sq = getSumSq('r',ul,w,h);
    long g_sq = getSumSq('g',ul,w,h);
    long b_sq = getSumSq('b',ul,w,h);
    long r=getSum('r',ul,w,h);
    long g=getSum('g',ul,w,h);
    long b=getSum('b',ul,w,h);
    return ((double)r_sq-(double)(r*r)/(double)(w*h))+ ((double)(g_sq)-(double)(g*g)/(double)(w*h))+ ((double)b_sq-(double)(b*b)/(double)(w*h));

}

/**
   * Given a rectangle, return the average color value over the rectangle
   * as a pixel.
   * Each color component of the pixel is the average value of that
   * component over the rectangle.
   * @param ul is (x,y) of the upper left corner of the rectangle
   * @param w,h are the width and height of the rectangle
   */
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){

     int r=(int)getSum('r',ul,w,h)/(w*h);
     int g=(int)getSum('g',ul,w,h)/(w*h);
     int b=(int)getSum('b',ul,w,h)/(w*h);
     RGBAPixel pix(r,g,b);

     return pix;
}
