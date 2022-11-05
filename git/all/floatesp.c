#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BITS 8
#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 2


uint8_t bits[BITS] = { 	0x1,
			0x2,
			0x4,
 			0x8,
 			0x10,
 			0x20,
 			0x40,
 			0x80};

int getEndianess();
void getBits(uint8_t arr[32], float val, int endianess);
void printArr(uint8_t arr[], int size);

int main(){
	float x = 0.2;
	uint8_t bit_arr[32];
	int endianess = getEndianess();
	
	getBits(bit_arr, x, endianess);
	
	printf("Endianess: ");
	if(endianess == LITTLE_ENDIAN) printf("Little endian");
	else printf("Big endian");
	printf("\nWhole IEEE conversion: ");
	printArr(bit_arr, 32);
	printf("\nEsponent: ");
	printArr(bit_arr+1, 8);
	printf("\n");
}


int getEndianess(){
	int temp = 1;
	uint8_t* p = (uint8_t*) &temp;
	
	if(*p == 0)
		return BIG_ENDIAN;
	return LITTLE_ENDIAN;
}

void getBits(uint8_t arr[32], float val, int endianess) {
	
	uint8_t* bytepointer = (void*) &val;
	uint8_t i_arr = endianess == LITTLE_ENDIAN? 31:0;
	
	if(endianess == BIG_ENDIAN)
		for(int i = 0; i < sizeof(float); i++) {
			for(int j = BITS-1; j >= 0; j--) {
				arr[i_arr++] = (bits[j] & *bytepointer) > 0;
			}
			bytepointer++;
		}
	else 
		for(int i = sizeof(float)-1; i >= 0; i--) {
			for(int j = 0; j < BITS; j++) {
				arr[i_arr--] = (bits[j] & *bytepointer) > 0;
			}
			bytepointer++;
		}
}

void printArr(uint8_t arr[], int size) {
	for(int i = 0; i < size; i++)
		printf("%d", (int) arr[i]);
}
