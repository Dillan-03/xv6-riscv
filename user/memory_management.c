#include "memory_management.h"

void* linked_head = 0;

//Page Size  
int PAGE_SIZE = 4096;


//Meta information about the block
struct block_data{
	
	//Size of block
	int sizeBlock;
	//Pointer to the next block
	struct block_data *next;

	//is data free
	//free = 0 unavailable
	//free = 1 available
	int free;

};


//Default starting method which will create a starting block
//Will be called once
//parameters: created block, size entered
struct block_data *allocate_head(struct block_data* linked, int size){
	
	//create a pool of memory to store the linked list
	//one page table is of 4KB
	linked = (struct block_data*) sbrk(4096);

	//NULL next block
	linked->next = 0;
	linked->free = 1;


	linked->sizeBlock = PAGE_SIZE - sizeof(linked);

	return linked;
}

//Function which request memory space from the OS using sbrk
//Parameter are the new created block, and the size of the space that is required to store the block
struct block_data *space_OS(struct block_data* tail, int size){

	struct block_data *new_block;
        
	//hold pool of memory to new_block
	new_block = (struct block_data*)sbrk(size);

	//Check if memory can be allocated with appropriate size
	if ((void*)new_block == sbrk(size + sizeof(struct block_data))){
		if (sbrk(size + sizeof(struct block_data)) == (void*) - 1){//failed
				return 0; //sbrk failed
		}
	}
	
	//Append new block to the end of the linked list
	if (tail == 0){
		tail->next = new_block;
	}
        
	//Assign block and assign meta data
	new_block->sizeBlock = PAGE_SIZE - sizeof(new_block);
	new_block->next = 0;
	new_block->free = 0; //0 to initialise block has not been freed

	return new_block;
}

// //function which finds available space first through the linked list
struct block_data *available_block(struct block_data **data, int size){

	//create new temp block that holds the block given from the parameter
	struct block_data *find = *data;

	//check for memory availability in heap
	//if memory block is free and size is large enough to be stored
	while (find && !(find->free == 0 && find->sizeBlock >= size)){
		*data = find;

		//update block pointer
		find = find->next;
	}
	return find; //return updated head of linked list 

}

//Function which find the address of the struct in multiple places 
struct block_data *get_blocks(void* ptr){
	return (struct block_data*)ptr - 1;
}


//malloc function
void * _malloc(int size){
	struct block_data *block;
	// void *space = sbrk(4096);

	//check for size is valid
	//size is 0
	if (size <= 0){
		return 0;
	}else{

		if (linked_head == 0){ //failed 

			//create new block
			linked_head = space_OS(0,4096);

			//assign created block to private block(line 95)
			block = linked_head;

		}
		else{
			//Pool of memory is already created. 
			//We don't which block is taken or free
			struct block_data *previous = linked_head;

			//find available blocks in heap 
			block = available_block(&previous, size); 
			
			//available space is not found
			//request space from OS
			if (!block){
				block = space_OS(previous,size);
				// linked_head ->next = block;
				if (!block){
					return 0;
				}
				// printf("free block available at loc: ");
				// return linked_head->next;
			}else{
				//found free block to be used
				// linked_head->next = block;
				block->free = 0 ;
				block->sizeBlock = PAGE_SIZE - sizeof(block); 
			}
		}
	}

	//Increment the address of the block that is returned
	return block+1;
}

//free function which clears memory and remove the block from the linked list
//takes in pointer of block that needs to be freed
void _free(void *ptr){
	// printf("block freed\n");
	if (!ptr){
		return ;
	}

	//find all addresses that the pointer it going to
	struct block_data* pointer =  (struct block_data*)ptr - 1;

	if ((pointer->free) == 1){//block has not been freed
		// printf("block has not been freed\n");
	}else{
		pointer->free = 1;
	}


}



int main(){
	printf("Testing Code: .......");
	printf("\n");


	char *root = _malloc(5);
	//int *test =_malloc(1);
	printf("%d \n", root);
	_free(root);

	int *testtwo =_malloc(1);
 	printf("%d \n", testtwo);

	int *testthree =_malloc(1);
	printf("%d \n", testthree);

//printf("%d, %d\n", test, testtwo);

// 	// _malloc(2);
// 	// // _malloc(3);
// 	// for(int i =0; i < 26; i ++){
// 	// 	root[i] = i + 'A';


	return 0;

} 



