//
// Created by Tim Leys on 13/10/2023.
//

#include "toolbox.h"

void bmp16_line(int x1, int y1, int x2, int y2, u32 clr, void *dstBase, uint dstPitch)
{
    int ii, dx, dy, xstep, ystep, dd;

    u16 *dst = (u16*)(dstBase + y1*dstPitch + x1*2);
    dstPitch /=2;

    // Normalize
    if(x1 > x2) {
        xstep = -1; dx = x1 - x2;
    } else {
        xstep =  1; dx = x2 - x1;
    }

    if(y1 > y2){
        ystep = -dstPitch; dy = y1-y2;
    } else {
        ystep = +dstPitch; dy = y2-y1;
    }

    // DRAWING
    // horizontal line
    if (dy == 0){
        for(ii=0;ii<=dx;ii++){
            dst[ii*xstep]=clr;
        }
    }
    // vertical line
    else if(dx==0){
        for(ii=0;ii<=dy;ii++){
            dst[ii*ystep]=clr;
        }
    }
    // Diagonal, slope <= 1
    else if(dx>=dy)
    {
        dd= 2*dy - dx;

        for(ii=0; ii<=dx; ii++)
        {
            *dst= clr;
            if(dd >= 0)
            {   dd -= 2*dx; dst += ystep;  }

            dd += 2*dy;
            dst += xstep;
        }
    }
    // Diagonal, slope > 1
    else
    {
        dd= 2*dx - dy;
        for(ii=0; ii<=dy; ii++)
        {
            *dst= clr;
            if(dd >= 0)
            {   dd -= 2*dy; dst += xstep;  }

            dd += 2*dx;
            dst += ystep;
        }
    }
}

//! Draw a rectangle on a 16bpp canvas
void bmp16_rect(int left, int top, int right, int bottom, u32 clr,
                void *dstBase, uint dstPitch)
{
    int ix, iy;

    uint width= right-left, height= bottom-top;
    u16 *dst= (u16*)(dstBase+top*dstPitch + left*2);
    dstPitch /= 2;

    // --- Draw ---
    for(iy=0; iy<height; iy++)
        for(ix=0; ix<width; ix++)
            dst[iy*dstPitch + ix]= clr;
}

//! Draw a frame on a 16bpp canvas
void bmp16_frame(int left, int top, int right, int bottom, u32 clr,
                 void *dstBase, uint dstPitch)
{
    // Frame is RB exclusive
    right--;
    bottom--;

    bmp16_line(left,  top,   right,  top,    clr, dstBase, dstPitch);
    bmp16_line(left,  bottom, right, bottom, clr, dstBase, dstPitch);

    bmp16_line(left,  top,   left,   bottom, clr, dstBase, dstPitch);
    bmp16_line(right, top,   right,  bottom, clr, dstBase, dstPitch);
}

void m3_fill(COLOR clr){
    //int m3_size = 240*160*2 - 4;
    int ii;
    u32 *dst= (u32*)vid_mem;
    u32 wd= (clr<<16) | clr;

    for(ii=0; ii<M3_SIZE/4; ii++)
        *dst++= wd;
        *dst++= wd;
}

