/*
 * pnmhide/src/hide.c --
 */

#include "hide.h"

int set_bit(unsigned char byte,int pos, int val){
    int bit = (byte>>pos)%2;
    if (bit!=val){
        val = 1<<pos;
        byte^=val;
    }
    return byte;
}

int get_bit(unsigned char byte, int pos){
    return (byte >> pos)%2;
}

void sign(image_t *im)
{
    int row = (im->rows)-1;
    for (int i = 0; i<(im->cols);i++){
        unsigned char r,g,b;
        r =  PPM_GETR(im->xels[row][i]); 
        g =  PPM_GETG(im->xels[row][i]);            
        b =  PPM_GETB(im->xels[row][i]); 
        int bit = 0;
        if (i==0 || i == (im->cols)-1){
            bit = 1;
        }
        r = set_bit(r,0,bit);
        r = set_bit(r,1,bit);
        g = set_bit(g,0,bit);
        g = set_bit(g,1,bit);
        b = set_bit(r,0,bit);
        b = set_bit(r,1,bit);
        PNM_ASSIGN(im->xels[row][i], r, g, b);
    }
}
int verifySign(image_t *im)
{
    int row = (im->rows)-1;
    for (int i = 0; i<(im->cols);i++){
        unsigned char r,g,b;
        r =  PPM_GETR(im->xels[row][i]); 
        g =  PPM_GETG(im->xels[row][i]);            
        b =  PPM_GETB(im->xels[row][i]); 
        int bits[6];

        bits[0] = get_bit(r,0);
        bits[1] = get_bit(r,1);
        bits[2] = get_bit(g,0);
        bits[3] = get_bit(g,1);
        bits[4] = get_bit(r,0);
        bits[5] = get_bit(r,1);
        
        if (i==0 || i == (im->cols)-1){
            int resbit=1;
            for (int j = 0; j<6;j++)
            {
                resbit&=bits[j];
            }
            if (resbit==0){
                return 0;
            }
        }
        else{
            int resbit=0;
            for (int j = 0; j<6;j++)
            {
                resbit|=bits[j];
            }
            if (resbit == 1){
                return 0;
            }
        }
    }   
    return 1;
}

int
im_encode(image_t *im, char *msg)
{
    //add signature (in last row all last 2 bits are all 0s, corner ones are all 1s)
    sign(im);
    int counter_let = 0;
    char c = msg[0];
    int flag = 0;
    for (int i =0;i<im->rows-1;i++)
    {
        for (int j =0;j<(im->cols)-1;j+=2)
        {
            unsigned char r,g,b,r2,g2,b2;
            r =  PPM_GETR(im->xels[i][j]); 
            g =  PPM_GETG(im->xels[i][j]);            
            b =  PPM_GETB(im->xels[i][j]);            
            r2 = PPM_GETR(im->xels[i][j+1]);
            g2 = PPM_GETG(im->xels[i][j+1]);
            b2 = PPM_GETB(im->xels[i][j+1]);
            
            int bit[8];
            for (int q=0;q<=7;q++){
                bit[7-q] = ((c>>q)%2)&1;                
            }

            r = set_bit(r,1,bit[0]);
            r = set_bit(r,0,bit[1]);
            g = set_bit(g,1,bit[2]);
            g = set_bit(g,0,bit[3]);
            b = set_bit(b,1,bit[4]);
            b = set_bit(b,0,bit[5]);
            r2 = set_bit(r2,1,bit[6]);
            r2 = set_bit(r2,0,bit[7]);

            PNM_ASSIGN(im->xels[i][j], r, g, b);
            PNM_ASSIGN(im->xels[i][j+1], r2, g2, b2);

            counter_let++;
            c = msg[counter_let];
            if (flag == 1){
                return counter_let-1;
            }
            if (c == NULL){
                c = 0;
                flag = 1;
            }

        }
    }
    return counter_let;
}

int
im_decode(image_t *im,volatile char *buffer, size_t size)
{
    if (!verifySign(im)){
        return -1;
    }
    int counter_let = 0;
    unsigned char c = 0;
    int bit = 0;
    for (int i =0;i<im->rows-1;i++)
    {
        for (int j =0;j<(im->cols)-1;j+=2)
        {
            unsigned char r,g,b,r2,g2,b2;
            r =  PPM_GETR(im->xels[i][j]); 
            g =  PPM_GETG(im->xels[i][j]);            
            b =  PPM_GETB(im->xels[i][j]);            
            r2 = PPM_GETR(im->xels[i][j+1]);
            g2 = PPM_GETG(im->xels[i][j+1]);
            b2 = PPM_GETB(im->xels[i][j+1]);
            
            int bit[8];
            bit[0] = get_bit(r,1);
            bit[1] = get_bit(r,0);
            bit[2] = get_bit(g,1);
            bit[3] = get_bit(g,0);
            bit[4] = get_bit(b,1);
            bit[5] = get_bit(b,0);
            bit[6] = get_bit(r2,1);
            bit[7] = get_bit(r2,0);

            for (int q = 0;q<8;q++){
                c|= (bit[q]<<(7-q));
            }
            buffer[counter_let]=c;
            if (c == 0){
                return counter_let;
            }
            counter_let++;
            c = 0;
        }
    }
    return counter_let;
}
