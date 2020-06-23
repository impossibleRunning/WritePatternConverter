#pragma once
#ifndef _CONVERSION_H_
#define _CONVERSION_H_


#define PAGES_PER_BLOCK 4
#define BUFFER_BLOCKS 16
#define TOTAL_PAGES_IN_BUFFER_BLK (PAGES_PER_BLOCK*BUFFER_BLOCKS)

typedef struct {
	int offset;
	int LPN_of_node[PAGES_PER_BLOCK];
}WriteBufferTable;

typedef struct  {
	WriteBufferTable BufferBlockNum[BUFFER_BLOCKS];
}WriteBufferTableEntry;

typedef struct {
	int lpn;
}RAM;

RAM ram_lpn[TOTAL_PAGES_IN_BUFFER_BLK];
WriteBufferTableEntry wbt;

FILE* wpc;
FILE* bt;


void reset(int wbbn);
int read_from_file();
void write(int node_num);
void open();
void commit(int wbbn);
void print_lpn(wbbn);
double calculate_time(int write_count, int erase_count, int read_count);

int write_count;
int read_count;
int erase_count;
#endif