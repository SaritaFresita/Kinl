#include <sys/kernel.h>

#include <drivers/vesa/vesa.h>

#include <sys/idt/idt.h>
#include <sys/io/io.h>

void
kmain ()
{
  terminal_print ("Welcome to the Kinl operating system!\n");

  // Initialise the IDT
  terminal_print_pending ("Initialise IDT");
  idt_init ();
  terminal_print_done ("Initialised IDT");
}
