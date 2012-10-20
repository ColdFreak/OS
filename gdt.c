#include <system.h>

/* Defines a GDT entry. We say packed, because it 
 * prevents the compiler from doing things it thinks
 * is best: Prevent compiler "optimization" by packing*/
struct gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
}__attribute__((packed));


