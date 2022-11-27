#include "memory_management.h"

void* linked_head = 0;

//Page Size  
int PAGE_SIZE = 4096;


//Meta information about the block
struct block_data{
	
	//Size of the header to be specific
	int sizeBlock;
	//Pointer to the previous block
//	struct block_data *previous; 
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

	//Check if memory can be allocated with appropriate sizeif ((void*)new_block == sbrk(size + sizeof(struct block_data))){
		if (sbrk(size + sizeof(struct block_data)) == (void*) - 1){//failed
				return 0; //sbrk failed
		}
	
		tail->next = new_block;
		new_block->next = 0; //NULL
		new_block->free = 0; 
		new_block->sizeBlock = PAGE_SIZE - sizeof(new_block); //header size
	
	//Append new block to the end of the linked list
//	if (tail == 0){
//		tail->next = *new_block;
	
  	      
	//Assign block and assign meta data
	//new_block->sizeBlock = PAGE_SIZE - sizeof(new_block); //header size 
	//new_block->next = 0;
	//new_block->free = 0; //0 to initialise block has not been freed

	return new_block;
}

// //function which finds available space first through the linked list
struct block_data *available_block(struct block_data *data, int size){

	//create new temp block that holds the block given from the parameter
	struct block_data *find = data;

	//check for memory availability in heap
	//using the first fit approach
	//if memory block is free and size is large enough to be stored
	while (find->free == 0 && find->sizeBlock >= size){
		*data = *find;

		//update block pointer 
		find = find->next;
		
		//break after location to store block is found
		printf("Updated block pointer \n ");
		break;
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
			//0 as the block has not been created
			//4096 of a page size
			linked_head = space_OS(0,4096);

			//assign created block to private block(line 95)
			block = linked_head;

		}
		else{
			//Pool of memory is already created. 
			//We don't know which block is taken or free
			struct block_data* current = linked_head;

			//find available blocks in heap 
			block = available_block(current, size); 
			
			//available space is not found
			//request space from OS
			if (!block){
				block = space_OS(current,size);
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
/**
void _free(void *ptr){
	// printf("block freed\n");
	if (!ptr){ //free failed
		return ;
	}

	//find all addresses that the pointer is going to
//	struct block_data* pointer =  *ptr - 1;

	if ((ptr->free) == 1){//block has not been freed
		// printf("block has not been freed\n");
	}else{
		ptr->free = 1; //block is now freed
	}


} **/



int main(){
	printf("Testing Code: .......");
	printf("\n");


	char *root = _malloc(5);
	//int *test =_malloc(1);
	printf("%d \n", root);
//	_free(root);

	int *testtwo =_malloc(1);
 	printf("%d \n", testtwo);

//	int *testthree =_malloc(1);
//	printf("%d \n", testthree);

//printf("%d, %d\n", test, testtwo);

// 	// _malloc(2);
// 	// // _malloc(3);
// 	// for(int i =0; i < 26; i ++){
// 	// 	root[i] = i + 'A';


	return 0;

} 



