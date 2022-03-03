#ifndef __IO_H
#define __IO_H

#include <sys/kernel.h>

u8 insb (u16 port);
u16 insw (u16 port);

void outb (u16 port, u8 val);
void outw (u16 port, u16 val);

#endif
