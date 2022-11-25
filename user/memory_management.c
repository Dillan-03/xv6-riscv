
#include "memory_management.h"

struct block_data* linked_head = 0;

// struct block_data* linked_head = 0;


//malloc function
void* _malloc(int size){

	// void *space = sbrk(4096);

	//check for linked list being created
	if (size <= 0){
		return 0;
	}else{
		if (linked_head == 0){ //failed 

			//create new block
			linked_head = (struct block_data*) sbrk(4096);

			//NULL next block
			linked_head->next = 0;
			linked_head->free = 1;


			linked_head->sizeBlock = PAGE_SIZE - sizeof(linked_head);
			// printf("%d\n",linked_head);
			printf("created linked_head = ");

		}
		else{
			//Pool of memory is already created. 
			//We don't which block is taken or free
			struct block_data *block = linked_head;

			//find available blocks in heap 
			block = available_block(&block, size); 
			
			//available space is not found
			//request space from OS
			if (!block){
				block = request_space(block,4096);
				// linked_head ->next = block;
				printf("free block available at loc: ");
				// return linked_head->next;
			}else{
				// linked_head->next = block;
				block->free = 0 ;
				block->sizeBlock = PAGE_SIZE - sizeof(block); 
			}

			// linked_head->free = 0;
			
			// block->next = 0;
			// block->free = 1;
			// block->sizeBlock = PAGE_SIZE - sizeof(block);
			//assign pointer to next blocksize
	// } else{
	// 	return value;
	// }
	
// 	//Create struct
// 	struct block_data* block_meta;
// 	void *result = sbrk(0);
// 	if (size<= 0){
// 	//	printf("Malloc failed: unable to allocate memory");
// 		return 0;
// 	}

// 	//No linked list
// 	if (linked_head == 0){
// 		block_meta = request_space(0,size); 
	 
// 		linked_head = block_meta;//create new linked list 
// 	}
// 	else{
// 	//linked list is already created -> check for free memory
// 		struct block_data *head = linked_head;
// 		block_meta = available_block(&head, size);

// 		//unable to find available free blocks in linked list
// 		if (block_meta == 0){
// 			//printf("Unable to find available free block");
// 			//request space -> sbrk 
// 			block_meta = request_space(head, size);
// 			if (!block_meta){
// 				return 0;
// 			}
// 		}
// 		//found free block to store data
// 		else{
// 			//initalise free as taken
// 			//free = 0; memory is taken 
// 			//free = 1: memory is avaiable
// 			block_meta->free = 0;

// 		}
		
	}
	return linked_head+1;
	// printf(space,"/n");
	// return linked_head;
}


//free function which clears memory and remove the block from the linked list
//takes in pointer of block that needs to be freed
void _free(void *ptr){
	return ;

	
}




int main(){
	printf("Testing Code: .......");
	printf("\n");


	// char *root = _malloc(5);
	int *test =_malloc(1);
	printf("%d \n", test);

	int *testtwo =_malloc(1);
	printf("%d \n", testtwo);

	int *testthree =_malloc(1);
	printf("%d \n", testthree);

	// printf("%d, %d\n", test, testtwo);

	// _malloc(2);
	// // _malloc(3);
	// for(int i =0; i < 26; i ++){
	// 	root[i] = i + 'A';
	// }

	return 0;

}



