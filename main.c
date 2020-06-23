#include<stdio.h>
#include<stdlib.h>
#include"conversion.h"

int main() {
	printf("wpcb with %d pages per block\n", PAGES_PER_BLOCK);
	bt = fopen("C:\\Users\\DB-LAB\\source\\repos\\dataset\\bt_output\\bt_sequ_output.txt", "r");
	wpc = fopen("C:\\Users\\DB-LAB\\source\\repos\\dataset\\wpcb_out\\wpcb_out_sequ.txt", "w");
	int node_num = read_from_file();;
	open();
	while (node_num != -1) {
		/*
		printf("-------\n");
		
		printf("node_num: %d\n", node_num);
		*/
		write(node_num);
		node_num = read_from_file();
		
	}
	fprintf(wpc, "%d\n", -1);
	fclose(bt);
	fclose(wpc);
	printf("write: %d  read: %d erase: %d\n", write_count, read_count, erase_count);
	double time = calculate_time(write_count, erase_count, read_count);
	printf("time: %.2f\n", time);
	system("pause");
}

double calculate_time(int write_count, int erase_count, int read_count) {
	double time = read_count * 0.02 + write_count * 0.2 + erase_count * 2.0;
	return time;
}