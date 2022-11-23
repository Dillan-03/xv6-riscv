#include "kernel/types.h"
#include "user/user.h"
#include "memory_management.h"


int main(){
	printf("Testing Code: .......");
	return 0;
}
// global variable head for our linked list
void *linked_head = NULL;

//malloc function
void *malloc(size_t size){
	
	//Create struct
	struct block* block_meta;

	if (size<= 0){
		printf("Malloc failed: unable to allocate memory");
	}

	//No linked list
	if (linked_head == NULL){
		new_block = request_space(NULL,size);
	} 
	linked_head = block_meta;

	//Need to find suitable free block in linked list
}



//Parameter are the new created block, and the size of the space that is required to store the block
void request_space(struct block* tail, size_t size){
	
	struct block* new_block;
	
	//request space
	new_block = sbrk(0);
	
	//Check if memory can be allocated
	if ((void*)block == sbrk(size + sizeof(struct block)) == 0){ //failed
		printf("cannot request space from OS");
		return 0;
	}
	

	if (tail == NULL){ //linked list has not been created 
		tail->next = block;
	}
	
	//Create block and assign meta data
	new_block->size = size;
	new_block->next = NULL;
	new_block->free = 0; //0 to initialise block has not been freed
}	return new_block;
