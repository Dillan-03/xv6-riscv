#include <stdio.h>

#include "kernel/types.h"
#incldue "user/user.h"

//header file to hold the struct

//Meta information about the block
struct block_data{
	
	//Size of block
	size_t sizeBlock;
	struct block *next;
	int free;



}block;


