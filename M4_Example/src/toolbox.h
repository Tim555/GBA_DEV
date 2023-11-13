// toolbox.h:
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can
//   be found in tonclib, and might not represent the
//   final forms.


#ifndef TOOLBOX_H
#define TOOLBOX_H

// === (from tonc_types.h) ============================================
/*
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32, uint;

typedef u16 COLOR;

#define REG_VCOUNT *(u16*)0x04000006




#define INLINE static inline

// === (from tonc_memmap.h) ===========================================

#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000

#define REG_DISPCNT     *((volatile u32*)(MEM_IO+0x0000))



// === (from tonc_memdef.h) ===========================================

// --- REG_DISPCNT defines ---
#define DCNT_MODE0     0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000


// === (from tonc_video.h) ============================================

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160
#define M3_WIDTH       240
#define M3_SIZE        76796

#define vid_mem     ((u16*)MEM_VRAM)

#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF


INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }


// Functions
void bmp16_line(int x1, int y1, int x2, int y2, u32 clr, void *dstBase, uint dstPitch);

void bmp16_rect(int left, int top, int right, int bottom, u32 clr, void *dstBase, uint dstPitch);

void bmp16_frame(int left, int top, int right, int bottom, u32 clr, void *dstBase, uint dstPitch);

void m3_fill(COLOR clr);

//INLINE
//! Plot a single \a clr colored pixel in mode 3 at (\a x, \a y).
INLINE void m3_plot(int x, int y, COLOR clr)
{
    vid_mem[y*M3_WIDTH+x]= clr;
}

//! Draw a colored line in mode 3 from (x1, y1) to (x2, y2).
INLINE void m3_line(int x1, int y1, int x2, int y2, COLOR clr)
{
    bmp16_line(x1, y1, x2, y2, clr, vid_mem, M3_WIDTH*2);
}

//! Draw a \a clr colored rectangle in mode 3.
INLINE void m3_rect(int left, int top, int right, int bottom, COLOR clr)
{
    bmp16_rect(left, top, right, bottom, clr, vid_mem, M3_WIDTH*2);
}

//! Draw a \a clr colored frame in mode 3.
INLINE void m3_frame(int left, int top, int right, int bottom, COLOR clr)
{
    bmp16_frame(left, top, right, bottom, clr, vid_mem, M3_WIDTH*2);
}

*/


#endif // TOOLBOX_H