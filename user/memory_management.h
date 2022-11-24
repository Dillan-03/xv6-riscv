
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// global variable head for our linked list

void *linked_head = 0;

//header file to hold the struct

//Meta information about the block
struct block_data{
	
	//Size of block
	int sizeBlock;
	struct block_data *next;
	int free;


};

//Parameter are the new created block, and the size of the space that is required to store the block
struct block_data *request_space(struct block_data* tail, int size){

        struct block_data *new_block;

        //request space
        new_block = (struct block_data*)sbrk(0);

        //Check if memory can be allocated
    
        if ((void*)new_block == sbrk(size + sizeof(struct block_data))){
			if (sbrk(size + sizeof(struct block_data)) == (void*) - 1){//failed

			//     printf("cannot request space from OS");
					return 0; //sbrk failed
			}
		}


        if (tail == 0){ //linked list has not been created 
                tail->next = new_block;
        }

        //Create block and assign meta data
        new_block->sizeBlock = size;
        new_block->next = 0;
        new_block->free = 0; //0 to initialise block has not been freed
        return new_block;
}

//function which finds available space first through the linked list
struct block_data *available_block(struct block_data **data, int size){
	//create new temp block that holds the head of the linked list
	struct block_data *find = linked_head;
	while (find && !(find->free == 0 && find->sizeBlock >= size)){
		*data = find;
		find = find->next;
	}
	return find; //return updated head of linked list 

}
