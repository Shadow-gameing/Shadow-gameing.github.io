#include "drv/arcdrv.h"
#include <string.h>

//.bss
static arcObj work[4];




//void* arcOpen(char* filename, )


//BOOL arcDataCheck()

void arcInit(void) {
	int i;

	for (i = 0; i < 4; i++) {
		memset(&work[i], 0, sizeof(arcObj));
	}
}

void* arcOpen(char* filename, void** addr, u32* length) {
	ARCFileInfo info;
	void* startAddr;
	int i;

	for (i = 0; i < 4; i++) {
		if ((work[i].flags & 1) && ARCOpen(&work[i].handle, filename, &info)) {
			startAddr = ARCGetStartAddrInMem(&info);
			if (addr) {
				*addr = startAddr;
			}
			if (length) {
				*length = ARCGetLength(&info);
			}
			ARCClose();
			return startAddr;
		}
	}
	if (addr) {
		*addr = NULL;
	}
	if (length) {
		*length = 0;
	}
	return NULL;
}