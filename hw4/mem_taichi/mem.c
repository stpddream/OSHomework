
int Mem_Init(int sizeOfRegion);

void *Mem_Alloc(int size);

int Mem_Free(void *ptr, int coalesce);

void Mem_Dump();
