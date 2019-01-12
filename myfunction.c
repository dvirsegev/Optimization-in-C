// dvir segev - 318651627 - group 06 - ex.5
#include "readBMP.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
// macro function of using calcindex.
#define CALCINDEX(i, j, n) ((i)*(n)+(j))
// macro function of multiply 9
#define Mult9(a) (((a) << 0b011) + (a))
#define SIZE m*n;
// the struct of pixel
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;
// the value of the pixel
typedef struct {
    short red;
    short green;
    short blue;
} pixel_sum;


/**
 * @param src the backup Pic
 * @param dst the new blur Pic
 * since we know for sure that every element in the kernel is 1, the kernel scale is 9
 * and the kernel size is 3 we gave up on passing this arguments to the function and we refer
 * this values as constants. We performed loop unrolling to the whole process so we have one 2 for nested
 * loops, in each iteration we calculate two pixels or one pixel, depends if m is even or odd.
 */
void blurImg(pixel *src, pixel *dst) {
    register int i, j;
    int x = m-2;
    // kernel size is always 3, therefore 3/2 is always 1.
    i =x;
    // calculate m - 1 once instead of every iteration in the head of the for-loop.
    short limit = 0;
    // since the loop unrooling, and the fact that we calculating the value of sum
    // in one command and not accumulating the value of sum with each inner iterations it is
    // enough to define sum and current_pixel, too, once here and give up on initializing sum.
    pixel_sum sum;
    short sumGreen, sumBlue, sumRed;
    unsigned int  index, index1;
    pixel current_pixel;
    pixel p1, p2, p3, p4, p5, p6, p7, p8, p9;
    // i++ was changed to ++i since it's more fast.
    for (; i != 0; --i) {
        j = x;
        index = CALCINDEX(i, j, m);
        index1 = CALCINDEX(i - 1, j - 1, m);
        p1 = src[index1];
        p2 = src[index1 + 1];
        p3 = src[index1 + 2];
        p4 = src[index1 + m];
        p5 = src[index];
        p6 = src[index1 + m + 2];
        p7 = src[index1 + m + m];
        p8 = src[index1 + m + m + 1];
        p9 = src[index1 + m + m + 2];
        for (; j != 0; --j) {
            // if we create a index 1, we need only calculate the left vector of the matrix, all the rest is common
            if (j != x) {
                sum.red -= (((short) p3.red) + ((short) p6.red) + ((short) p9.red));
                sum.green -= (((short) p3.green) + ((short) p6.green) + ((short) p9.green));
                sum.blue -= (((short) p3.blue) + ((short) p6.blue) + ((short) p9.blue));
                p2 = src[index1];
                p3 = src[index1 + 1];
                p5 = src[index1 + m];
                p6 = src[index1 + m + 1];
                p8 = src[index1 + m + m];
                p9 = src[index1 + m + m + 1];
                --index1;
                p1 = src[index1];
                p4 = src[index1 + m];
                p7 = src[index1 + m + m];
                sum.red = sum.red + ((short) p1.red) + ((short) p4.red) + ((short) p7.red);
                sum.green = sum.green + ((short) p1.green) + ((short) p4.green) + ((short) p7.green);
                sum.blue = sum.blue + ((short) p1.blue) + ((short) p4.blue) + ((short) p7.blue);
            }else {
                // calculating first pixel - calculating in each iteration two pixels
                sum.red = ((short) p1.red) + ((short) p2.red) + ((short) p3.red) +
                          ((short) p4.red) + ((short) p5.red) + ((short) p6.red) +
                          ((short) p7.red) + ((short) p8.red) + ((short) p9.red);
            sum.green = ((short) p1.green) + ((short) p2.green) + ((short) p3.green) +
                        ((short) p4.green) + ((short) p5.green) + ((short) p6.green) +
                        ((short) p7.green) + ((short) p8.green) + ((short) p9.green);
            sum.blue = ((short) p1.blue) + ((short) p2.blue) + ((short) p3.blue) +
                       ((short) p4.blue) + ((short) p5.blue) + ((short) p6.blue) +
                       ((short) p7.blue) + ((short) p8.blue) + ((short) p9.blue);
        }
        sumRed = sum.red * 58255 >> 19;
        sumGreen = sum.green *58255 >> 19;
        sumBlue = sum.blue * 58255 >> 19;
        dst[index].red = (unsigned char) sumRed;
        dst[index].blue = (unsigned char) sumBlue;
        dst[index].green = (unsigned char) sumGreen;
        --index;
    }
}
}

/**
 *
 * @param src the back up picture
 * @param dst the new picture sharper
 * since we know for sure that every element in the kernel is -1, except kernel[1][1] = 9, the kernel scale is 1
 * and the kernel size is 3 we gave up on passing this arguments to the function and we refer
 * this values as constants. We performed loop unrolling to the whole process so we have one 2 for nested
 * loops, in each iteration we calculate one pixel.
 */

void sharpImg(pixel *src, pixel *dst) {
    register int i,j;
    // kernel size is always 3, therefore 3/2 is always 1.
    i = m - 2;
    unsigned int index, index1 ;

    // since the loop unrooling, and the fact that we calculating the value of sum
    // in one command and not accumulating the value of sum with each inner iterations.
    pixel_sum sum;
    pixel current_pixel;
    pixel p1, p2, p3, p4, p5, p6, p7, p8, p9;
    int x = m-2;
    // change the loop from up to down because is more quick.
    for (; i != 0; --i) {
        j = x;
        // register on the variables because is more quick.
        register index = CALCINDEX(i, j, m);
        register index1 = CALCINDEX(i - 1, j - 1, m);
        p1 = src[index1];
        p2 = src[index1 + 1];
        p3 = src[index1 + 2];
        p4 = src[index1 + m];
        p5 = src[index1 + m + 1];
        p6 = src[index1 + m + 2];
        p7 = src[index1 + m + m];
        p8 = src[index1 + m + m + 1];
        p9 = src[index1 + m + m + 2];
        for (; j != 0; --j) {
            pixel p1 = src[index1];
            // if we already calculate the sum's, just change the location.
            if (j != x) {
                sum.red = sum.red - (((short) p3.red) + ((short) p6.red) + ((short) p9.red));
                sum.green = sum.green - (((short) p3.green) + ((short) p6.green) + ((short) p9.green));
                sum.blue = sum.blue - (((short) p3.blue) + ((short) p6.blue) + ((short) p9.blue));
                p2 = src[index1];
                p3 = src[index1 + 1];
                p5 = src[index1 + m];
                p6 = src[index1 + m + 1];
                p8 = src[index1 + m + m];
                p9 = src[index1 + m + m + 1];
                --index1;
                p1 = src[index1];
                p4 = src[index1 + m];
                p7 = src[index1 + m + m];
            }
            sum.red = -(((short) p1.red) + ((short) p2.red) + ((short) p3.red) +
                        ((short) p4.red) + ((short) p6.red) +
                        ((short) p7.red) + ((short) p8.red) + ((short) p9.red)) + Mult9(((short) p5.red));
            sum.green = -(((short) p1.green) + ((short) p2.green) + ((short) p3.green) +
                          ((short) p4.green) + ((short) p6.green) +
                          ((short) p7.green) + ((short) p8.green) + ((short) p9.green)) + Mult9(((short) p5.green));
            sum.blue = -(((short) p1.blue) + ((short) p2.blue) + ((short) p3.blue) +
                         ((short) p4.blue) + ((short) p6.blue) +
                         ((short) p7.blue) + ((short) p8.blue) + ((short) p9.blue)) + Mult9(((short) p5.blue));

            // assign kernel's result to pixel at [i,j]
            // kernel scale in this case is 1 so there is no need to divide the sum by 1
            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            // put it into the imagePic
            dst[index] = current_pixel;
            --index;
        }
    }
}


/**
 *
 * @param image the picture
 * @param srcImgpName the new image in the end of every iteration(blur or sharp)
 * @param blurRsltImgName the blur pic
 * @param sharpRsltImgName the sharp pic
 */
void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName) {
    unsigned int size = SIZE;
    unsigned int sizePixel = size + size + size;
//   pixel* pixelsImg = malloc(m*n*sizeof(pixel) * 3);
    pixel *backupOrg = calloc(1, sizePixel);

    pixel *pixelsImg = calloc(1, sizePixel);
    memcpy(pixelsImg, image->data, sizePixel);
    //copyPixels(pixelsImg, backupOrg);
    memcpy(backupOrg, pixelsImg, sizePixel);
    blurImg(backupOrg, pixelsImg);
    memcpy(image->data, pixelsImg, sizePixel);


    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);
    // moving the size of bytes from image->data to pixelsImg (replace the charsToPixels(image, pixelsImg));
    memcpy(pixelsImg, image->data, sizePixel);
    memcpy(backupOrg, pixelsImg, sizePixel);
    //copyPixels(pixelsImg, backupOrg);
    sharpImg(backupOrg, pixelsImg);
    // moving the size of bytes from pixelsImg to image->data (replace the PixelsToChars(image, pixelsImg));
    memcpy(image->data, pixelsImg, sizePixel);
    writeBMP(image, srcImgpName, sharpRsltImgName);
    // free the memory.
    free(pixelsImg);
    free(backupOrg);
}
