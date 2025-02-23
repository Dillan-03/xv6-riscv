
#include "memory_management.h"


void* linked_head = 0;


//Meta information about the block
struct block_data{

	//Size of block
	int sizeBlock;

	//is data free
	//free = 0 unavailable
	//free = 1 available
	int free;

	//Pointer to the next block
	struct block_data *next;


};

//Create the head of the linked list since list has not been created
struct block_data *allocate_head(struct block_data* linked, int size){

	//Create a page of 4096 bytes (i.e one page)
	linked = (struct block_data*)sbrk(4096);

	//NULL next block
	linked->next = 0;

	//assign the header to be free
	linked->free = 1;

	//Assign the header size of the block
	linked->sizeBlock = 4096 - sizeof(struct block_data);


	// printf("Size of the header block is %d \n", linked->sizeBlock);
	return linked;
}

//Parameter are the new created block, and the size of the space that is required to store the block
struct block_data *request_space(struct block_data* tail, int size){

    //request space
	struct block_data *new_block;

	//Call sbrk to request a new memory space from the OS
    new_block = (struct block_data*)sbrk(size+sizeof(struct block_data));

	//Check if memory can be allocated
	if ((void*)new_block == sbrk(size)){
		if (sbrk(size) == (void*) - 1){//failed
		//printf("cannot request space from OS");
			return 0; //sbrk failed
		}
	}

	//Create block and assign meta data
	new_block->sizeBlock = 4096 - sizeof(struct block_data);

	// 4096 - (size + sizeof(struct block_data));
	new_block->next = 0;
	new_block->free = 0; //0 to initialise block has not been freed

	return new_block;
}

//function which finds available space first through the linked list
struct block_data *blocks_availability(struct block_data **data, int size){

	//create new temp block that holds the head of the linked list
	struct block_data* find = *data;

	//loop through heap to find free memory which is large enough to store the block
	while (find == 0){

		if (find->free == 1 && find->sizeBlock >= size){

			*data = find;
			//Update next pointer
			find = find->next;

		}
		// break;
		else{ //no block is free
			continue;
		}
		break; // break after block is found
	}

	return find; //return updated head of linked list
}


//malloc function
void * _malloc(int size){
	struct block_data *block = 0;

	//check for linked list being created
	if (size <= 0 ){
		return 0;
	}else{
	// 	//linked list has not been created
		if (linked_head == 0){ //failed

			//create new block
			linked_head = allocate_head(0,4096);
			//current block points to the head of the linked list
			block = linked_head;
			// printf("linked head allocat ");
		}

			//Pool of memory is already created.
			//We don't know which block is taken or free
			struct block_data *previous = linked_head;

			//find available blocks in heap
			block = blocks_availability(&previous, size);

			//available space is not found
			//request space from OS
			if (block == 0){

				block = request_space(previous,size);

				if (block == 0){ //sbrk failed
					return 0;
				}
			}else{
				//found free block to be used
				block->free = 0;
				block->sizeBlock = 4096 - sizeof(struct block_data);//header size
			}
		}
		//return updated address of the block
		return block+1 ;

}


//free function which clears memory and remove the block from the linked list
//takes in pointer of block that needs to be freed
void _free(void *ptr){
	// printf("block freed\n");
	if (ptr == 0 || (void*)sbrk(0)){
		//cannot free memory
		return ; //failed
	}

	//Merging block once blocks have been splitted
	struct block_data* pointer = (struct block_data*)ptr - 1;
	if (pointer->free == 0){//block needs to be freed
		pointer->free = 1;
	}
}


int main(){
	// printf("Testing Code: .......");
	printf("\n");


	// char *root = _malloc(5);
	int *test =(int*)_malloc(100);
	printf("malloc 100 : %p \n", test);
	// _free(test);

	int *testtwo =(int*)_malloc(100);
	printf("malloc 500 : %p \n", testtwo);

	// int *testthree =_malloc(100);
	// printf("malloc 100 : %d \n", testthree);

	// printf("%d, %d\n", test, testtwo);

	// _malloc(2);
	// // _malloc(3);
	// for(int i =0; i < 26; i ++){
	// 	root[i] = i + 'A';
	// }

	return 0;

}
