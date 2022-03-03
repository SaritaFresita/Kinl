#ifndef __IDT_H
#define __IDT_H

#include <sys/kernel.h>

struct idt_desc
{
  u16 offset_1; // Offset bits  0 - 16
  u16 selector; // Selector that's in our GDT
  u8 zero;
  u8 type_attribute; // Descriptor type attribute
  u16 offset_2;      // Offset bits 16-31
} __attribute__ ((packed));

struct idtr_desc
{
  u16 limit; // Size of descriptor tabe
  u32 base;  // Base address of the start of the interrupt table
} __attribute__ ((packed));

void idt_init ();
void idt_set (int interrupt_no, void *address);

#endif
