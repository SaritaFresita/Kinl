#include "vesa.h"

#include "fonts/fonts.h"

#include <sys/kernel.h>
#include <sys/string/string.h>

#define TERMINAL_DEFAULT_FONT font_vga

u16 _row = 0;
u16 _col = 0;

static void
terminal_putchar (char c, u32 col)
{
  if (c == '\n')
    {
      _row += 1;
      _col = 0;
      return;
    }

  vesa_putchar (TERMINAL_DEFAULT_FONT, FONT_VGA_WIDTH, FONT_VGA_HEIGHT, c,
                _col * (FONT_VGA_WIDTH / 1.5), _row * FONT_VGA_HEIGHT, col);

  _col += 1;
  if (_col * (FONT_VGA_WIDTH / 1.5) >= vesa_get_width ())
    {
      _col = 0;
      _row += 1;
    }
}

void
terminal_print (const char *str)
{
  int len = strlen (str);
  for (int i = 0; i < len; i++)
    {
      terminal_putchar (str[i], vesa_make_colour (255, 255, 255));
    }
}

void
terminal_print_ext (const char *str, u32 col)
{
  int len = strlen (str);

  for (int i = 0; i < len; i++)
    {
      terminal_putchar (str[i], col);
    }
}

// This is a function that will write "* PENDING `task'" to the screen
void
terminal_print_pending (const char *task)
{
  terminal_print_ext ("\n*", vesa_make_colour (255, 105, 147));
  terminal_print_ext (" PENDING ", vesa_make_colour (255, 20, 147));
  terminal_print (task);
}

// This is a function that will write "* DONE `task'" to the screen
void
terminal_print_done (const char *task)
{
  terminal_print_ext ("\n*", vesa_make_colour (0, 255, 0));
  terminal_print_ext (" DONE ", vesa_make_colour (34, 139, 34));
  terminal_print (task);
}
