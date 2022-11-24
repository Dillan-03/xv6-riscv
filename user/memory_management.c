
#include "memory_management.h"



//malloc function
void* _malloc(int size){
	// void *value = sbrk(0);
	// void *data = sbrk(size);
	// if (data == (void*) - 1){
	// 	return 0;
	// } else{
	// 	return value;
	// }
	
	//Create struct
	struct block_data* block_meta;
	void *result = sbrk(0);
	if (size<= 0){
	//	printf("Malloc failed: unable to allocate memory");
		return 0;
	}

	//No linked list
	if (linked_head == 0){
		block_meta = request_space(0,size); 
	 
		linked_head = block_meta;//create new linked list 
	}
	else{
	//linked list is already created -> check for free memory
		struct block_data *head = linked_head;
		block_meta = available_block(&head, size);

		//unable to find available free blocks in linked list
		if (block_meta == 0){
			//printf("Unable to find available free block");
			//request space -> sbrk 
			block_meta = request_space(head, size);
			if (!block_meta){
				return 0;
			}
		}
		//found free block to store data
		else{
			//initalise free as taken
			//free = 0; memory is taken 
			//free = 1: memory is avaiable
			block_meta->free = 0;

		}
		
	}

	return result+1;
}


//free function which clears memory and remove the block from the linked list
//takes in pointer of block that needs to be freed
void _free(void *ptr){
	return ;

	
}




int main(){
	printf("Testing Code: .......");
	char *root = _malloc(5);
	// _malloc(1);
	// _malloc(2);
	// _malloc(3);
	for(int i =0; i < 26; i ++){
		root[i] = i + 'A';
	}

	return 0;

}



