#include<stdio.h>
#include<stdlib.h>
#include"conversion.h"

void open() {
	int i = 0;

	/*
	 reset write buffer mapping table
	 */
	for (i; i < BUFFER_BLOCKS; i++) {
		wbt.BufferBlockNum[i].offset = 0;
		for (int j = 0; j < PAGES_PER_BLOCK; j++) {
			wbt.BufferBlockNum[i].LPN_of_node[j] = -1;
		}
	}

	/*
	 reset ram space
	*/
	for (i = 0; i < TOTAL_PAGES_IN_BUFFER_BLK; i++) {
		ram_lpn[i].lpn = -1;
	}
	write_count = 0;
	read_count = 0;
	erase_count = 0;

}

void write(int node_num) {
	int lbn = node_num / PAGES_PER_BLOCK;
	int wbbn = lbn % BUFFER_BLOCKS;
	int* poffset = &wbt.BufferBlockNum[wbbn].offset;
	if (*poffset == PAGES_PER_BLOCK) {
		commit(wbbn);
		reset(wbbn);
		// write new node_num
		write_count++;
		wbt.BufferBlockNum[wbbn].LPN_of_node[0] = node_num;
		wbt.BufferBlockNum[wbbn].offset = 1;

	}
	else if (*poffset < PAGES_PER_BLOCK) {
		// write to write buffer table
		
		wbt.BufferBlockNum[wbbn].LPN_of_node[*poffset] = node_num;
		(*poffset)++;
		write_count++;
	}
	
//	print_lpn(wbbn);
//	printf("\n");
}

int read_from_file() {
	int key, node_num, op;
	fscanf(bt, "%d %d %d", &key, &node_num, &op);
	return node_num;
}

void reset(int wbbn) {
	wbt.BufferBlockNum[wbbn].offset = 0;
	for (int i = 0; i < PAGES_PER_BLOCK; i++) {
		wbt.BufferBlockNum[wbbn].LPN_of_node[i] = -1;
	}
	erase_count++;
}

void commit(int wbbn) {
	//write converter
//	print_lpn(wbbn);
	int tem[PAGES_PER_BLOCK];
	for (int i = 0; i < PAGES_PER_BLOCK; i++) {
		tem[i] = -1;
	}
	
	for (int wbbi = PAGES_PER_BLOCK-1; wbbi >=0; wbbi--) {
		read_count++;
		for (int temi = 0; temi < PAGES_PER_BLOCK; temi++) {
			if (tem[temi] == -1) {
				tem[temi] = wbt.BufferBlockNum[wbbn].LPN_of_node[wbbi];
				break;
			}
			else if (tem[temi] == wbt.BufferBlockNum[wbbn].LPN_of_node[wbbi])
				break;

		}
	}
	//commit
//	printf("commit\n");
	for (int i = 0; i < PAGES_PER_BLOCK; i++) {
		if (tem[i] == -1) break;
		else {
			fprintf(wpc, "%d\n", tem[i]);
//			printf("%d\n", tem[i]);
		}
	}
}

void print_lpn(wbbn) {
	for (int i = 0; i < PAGES_PER_BLOCK; i++) {
		printf("%d ", wbt.BufferBlockNum[wbbn].LPN_of_node[i]);
	}
}


