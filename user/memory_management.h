
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



// struct block_data* linked_head = 0;

// global variable head for our linked list

// void *linked_head = 0;
// struct block_data* linked_head;

//Page 
int PAGE_SIZE = 4096;

//header file to hold the struct

//Meta information about the block
 struct block_data{
	
	//Size of block
	int sizeBlock;
	//Pointer to the next block
	struct block_data *next;

	//is data free
	//free = 0 unavailable
	int free;


};
struct block_data *allocate_head(struct block_data* linked, int size){
	linked = (struct block_data*) sbrk(4096);

	//NULL next block
	linked->next = 0;
	linked->free = 1;

	linked->sizeBlock = PAGE_SIZE - sizeof(linked);

	return linked;
}
//Parameter are the new created block, and the size of the space that is required to store the block
struct block_data *request_space(struct block_data* tail, int size){

        //request space
		struct block_data *new_block;
        new_block = (struct block_data*)sbrk(size);

        //Check if memory can be allocated
    
        if ((void*)new_block == sbrk(size + sizeof(struct block_data))){
			if (sbrk(size + sizeof(struct block_data)) == (void*) - 1){//failed

			//     printf("cannot request space from OS");
					return 0; //sbrk failed
			}
		}

		// if (tail == 0){
			// tail->next = new_block;
		// }
        
        //Create block and assign meta data
        new_block->sizeBlock = PAGE_SIZE - sizeof(new_block);
        new_block->next = 0;
        new_block->free = 0; //0 to initialise block has not been freed
		// linked_head-> free = 1;
		// linked_head -> next = new_block;

        return new_block;
}

// //function which finds available space first through the linked list
struct block_data *available_block(struct block_data **data, int size){
	//create new temp block that holds the head of the linked list
	struct block_data *find = *data;
	while (find && !(find->free == 0 && find->sizeBlock >= size)){
		*data = find;
		find = find->next;
	}
	return find; //return updated head of linked list 

}

//Function which find the address of the struct in multiple places 
struct block_data *get_blocks(void* ptr){
	return (struct block_data*)ptr - 1;
}