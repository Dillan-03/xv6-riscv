
#include "kernel/types.h"
#include "user/user.h"


void * _malloc(int size);
void _free(void *ptr);
struct block_data *allocate_head(struct block_data* linked, int size);
struct block_data *request_space(struct block_data* tail, int size);
struct block_data *available_block(struct block_data *data, int size);
