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

/* Special pointer which includes the limit:
 * The max bytes taken up by the GDT, minus 1.
 * Again, this NEEDS to be packed*/
struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT
 * pointer */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/*This will be a function in start.asm. We use this to properly
 * reload the new segment registers */
extern void gdt_flush();

/* Setup a descriptor in the Global Descriptor table */
void 
gdt_set_gate(int number, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits*/
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

