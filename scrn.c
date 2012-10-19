#include <system.h>

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

/* Scrools the screen */
void scroll(void) {
	unsigned blank, temp;
