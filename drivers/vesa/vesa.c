#include "vesa.h"

struct vbe_info *info = (struct vbe_info *)VBE_INFO_ADDR;

u32
vesa_make_colour (u8 r, u8 g, u8 b)
{
  return r << info->red_position | g << info->green_position
         | b << info->blue_position;
}

void
vesa_putpixel (u16 x, u16 y, u32 col)
{
  void *framebuffer = (void *)(unsigned long)info->framebuffer;

  switch (info->bpp)
    {
    case 8:
      {
        u8 *pixel = framebuffer + info->pitch * y + x;
        *pixel = col;
      }
      break;

    case 15:
    case 16:
      {
        u16 *pixel = framebuffer + info->pitch * y + 2 * x;
        *pixel = col;
      }
      break;

    case 24:
      {
        u32 *pixel = framebuffer + info->pitch * y + 3 * x;
        *pixel = (col & 0xffffff) | (*pixel & 0xff000000);
      }
      break;

    case 32:
      {
        u32 *pixel = framebuffer + info->pitch * y + 4 * x;
        *pixel = col;
      }
      break;
    }
}

void
vesa_cls (u32 col)
{
  for (u16 y = 0; y < info->height; y++)
    {
      for (u16 x = 0; x < info->width; x++)
        {
          vesa_putpixel (x, y, col);
        }
    }
}

void
vesa_draw_rect (u16 x, u16 y, u16 w, u16 h, u32 col)
{
  for (u16 j = y; j < (y + h); j++)
    {
      for (u16 i = x; i < (x + w); i++)
        {
          vesa_putpixel (i, j, col);
        }
    }
}

u16
vesa_get_width ()
{
  return info->width;
}

u16
vesa_get_height ()
{
  return info->height;
}

void
vesa_putchar (int (*font) (int, int), u8 font_width, u8 font_height, char c,
              u16 x, u16 y, u32 col)
{
  for (u8 j = 0; j < font_height; j++)
    {
      u32 row = (*font) ((i32)c, j);
      i32 shift = font_width - 1;
      i32 bit_val = 0;

      for (u8 i = 0; i < font_width; i++)
        {
          bit_val = (row >> shift) & 1;
          if (bit_val)
            vesa_putpixel (x + i, y + j, col);

          shift -= 1;
        }
    }
}
