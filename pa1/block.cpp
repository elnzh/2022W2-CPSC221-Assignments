#include "block.h"
#include <cmath>
#include <iostream>

/**
 * Return the height of the current block.
 * */
int Block::height() const {

    return data[0].size();
  
}
/**
 * Return the width of the current block.
 * */
int Block::width() const {

    return data.size();
}

/**
 * Draw the current block at position (x,0) in im.
 * */
void Block::render(PNG &im, int x) const {

    for( unsigned int i=(unsigned)x;i<((unsigned)x+(unsigned)width());i++) {
        for (unsigned int j = 0; j < (unsigned)im.height(); j++) {
           *(im.getPixel(i, j)) = data[i-(unsigned)x][j];
        }
    }

}
/**
 * From the PNG image im, grab the vertical, 
 * rectangular strip of pixels whose upper left corner is at position (x,0),
 *  and whose dimensions are width by height of the image im.
 * */
void Block::build(PNG &im, int x, int width) {

    for(unsigned int i=x;i<(unsigned)x+(unsigned)width;i++){
        vector<HSLAPixel> temp;
        for(unsigned int j =0; j<(unsigned)im.height();j++){
            HSLAPixel * p = im.getPixel(i,j);
            temp.push_back(*p);
        }
        data.push_back(temp);

    }


}
