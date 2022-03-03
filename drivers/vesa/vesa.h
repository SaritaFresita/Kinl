#ifndef __VESA_H
#define __VESA_H

#include <sys/kernel.h>

#define VBE_INFO_ADDR 0x500

struct vbe_info
{
  u16 attributes;
  u8 window_a;
  u8 window_b;
  u16 granularity;
  u16 window_size;
  u16 segment_a;
  u16 segment_b;
  u32 win_func_ptr;
  u16 pitch;
  u16 width;
  u16 height;
  u8 w_char;
  u8 y_char;
  u8 planes;
  u8 bpp;
  u8 banks;
  u8 memory_model;
  u8 bank_size;
  u8 image_pages;
  u8 reserved0;

  u8 red_mask;
  u8 red_position;
  u8 green_mask;
  u8 green_position;
  u8 blue_mask;
  u8 blue_position;
  u8 reserved_mask;
  u8 reserved_position;
  u8 direct_colour_attributes;

  u32 framebuffer;

  u32 off_screen_mem_off;
  u16 off_screen_mem_size;

  u8 reserved1[206];
} __attribute__ ((packed));

u32 vesa_make_colour (u8 r, u8 g, u8 b);
void vesa_putpixel (u16 x, u16 y, u32 col);
void vesa_cls (u32 col);
void vesa_draw_rect (u16 x, u16 y, u16 w, u16 h, u32 col);
void vesa_putchar (int (*font) (int, int), u8 font_width, u8 font_height,
                   char c, u16 x, u16 y, u32 col);

// "terminal"
void terminal_print (const char *str);
void terminal_print_ext (const char *str, u32 col);

void terminal_print_pending (const char *task);
void terminal_print_done (const char *task);

u16 vesa_get_width ();
u16 vesa_get_height ();

#endif
