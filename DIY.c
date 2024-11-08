#include <stdio.h>
#include <ctype.h>
int main(void){
	FILE *read,*write;
	char fname[] = "data.txt";
	read = fopen("data.txt","r");
	write = fopen("count.txt","w");
	fprintf(write,"aiueo");



	fclose(read);
	fclose(write);

}



