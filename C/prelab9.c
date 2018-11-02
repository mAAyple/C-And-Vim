#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define IMG_ROWS 900
#define IMG_COLS 900

char input_file_name[] = "cy.bmp";
char output_file_name[] = "cy2.bmp";

uint16_t bpp;
uint32_t pixel_arr_loc;
unsigned int r_in[IMG_ROWS][IMG_COLS];
unsigned int g_in[IMG_ROWS][IMG_COLS];
unsigned int b_in[IMG_ROWS][IMG_COLS];
unsigned int a_in[IMG_ROWS][IMG_COLS];
unsigned int r_out[IMG_ROWS][IMG_COLS];
unsigned int g_out[IMG_ROWS][IMG_COLS];
unsigned int b_out[IMG_ROWS][IMG_COLS];
unsigned int a_out[IMG_ROWS][IMG_COLS];

int load_image(FILE *fp) {
	unsigned char signature[2];
	uint32_t file_size;
	uint32_t dib_size;
	uint16_t comp_method;

	if(fp == NULL) {
		printf("Unable to open file.\n");
		return 1;
	}

	fread(signature, 1, 2, fp);
	printf("sig %c %c\n", signature[0], signature[1]);
	if(signature[0] != 'B' || signature[1] != 'M') {
		printf("Not a valid BMP file.\n");
		return 1;
	}

	fseek(fp, 2, SEEK_SET);
	fread(&file_size, 4, 1, fp);
	printf("file size %u\n", file_size);

	fseek(fp, 10, SEEK_SET);
	fread(&pixel_arr_loc, 4, 1, fp);
	printf("pixel array location %u\n", pixel_arr_loc);

	fseek(fp, 14, SEEK_SET);
	fread(&dib_size, 4, 1, fp);
	printf("dib size %u\n", dib_size);
	if(dib_size != 40) {
		printf("BMP version not supported.\n");
		return 1;
	}

	fseek(fp, 28, SEEK_SET);
	fread(&bpp, 2, 1, fp);
	printf("bits per pixel %u\n", bpp);
	if(bpp != 32) {
		printf("Bits per pixel not supported.\n");
		return 1;
	}

	fseek(fp, 30, SEEK_SET);
	fread(&comp_method, 2, 1, fp);
	printf("compression method %u\n", comp_method);
	if(comp_method != 0) {
		printf("Compression method not supported.\n");
		return 1;
	}

	int bytes_per_row = IMG_COLS * bpp / 8;
	int padding = 0;
	if(bytes_per_row % 4 != 0) {
		padding = 4 - bytes_per_row % 4;
	}
	printf("input padding %u\n", padding);
	fseek(fp, pixel_arr_loc, SEEK_SET);
	for(int row = IMG_ROWS - 1; row >= 0; row--) {
		for(int col = 0; col < IMG_COLS; col++) {
			fread(&b_in[row][col], 1, 1, fp);
			fread(&g_in[row][col], 1, 1, fp);
			fread(&r_in[row][col], 1, 1, fp);
			fread(&a_in[row][col], 1, 1, fp);
			b_out[row][col] = b_in[row][col];
			g_out[row][col] = g_in[row][col];
			r_out[row][col] = r_in[row][col];
			a_out[row][col] = a_in[row][col];
			fseek(fp, padding, SEEK_CUR);
		}
	}
	return 0;
}

int write_image(FILE *out, FILE *in) {
	int c;

	rewind(out);
	rewind(in);

	c = fgetc(in);
	while(c != EOF) {
		fputc(c, out);
		c = fgetc(in);
	}

	int bytes_per_row = IMG_COLS * bpp / 8;
	int padding = 0;
	if(bytes_per_row % 4 != 0) {
		padding = 4 - bytes_per_row % 4;
	}
	printf("output padding %u\n", padding);
	fseek(out, pixel_arr_loc, SEEK_SET);
	for(int row = IMG_ROWS - 1; row >= 0; row--) {
		for(int col = 0; col < IMG_COLS; col++) {
			fwrite(&b_out[row][col], 1, 1, out);
			fwrite(&g_out[row][col], 1, 1, out);
			fwrite(&r_out[row][col], 1, 1, out);
			fwrite(&a_out[row][col], 1, 1, out);
			fseek(out, padding, SEEK_CUR);
		}
	 }
	return 0;
}

int main() {
	int r_max,r_min;
	FILE *in = fopen(input_file_name, "rb");
	FILE *out = fopen(output_file_name, "wb");
	load_image(in);

	/*------------Start of filter code-------------*/
	void grey(int, int);
	printf("What should the max grey color be? \n\n");
	printf("Enter a number between 1 and 100:\n\n");
	scanf("%d", &r_max);
	printf("What should the min grey color be? \n\n");
	printf("Enter a number between 1 and 100:\n\n");
	scanf("%d", &r_min);
	grey(r_max, r_min);
	/*------------End of filter code-------------*/

	write_image(out, in);
	fclose(in);
	fclose(out);
}


void grey(int max,int min){
	int i,j,tmp;
	char inp;
	printf("Enter either (x)max or (n)min for your grayscale: \n\n");
	scanf("%s", &inp);
	if(inp == 'x')
	{
	for(i = 0; i < 900; i++){

		for(j = 0; j < 900; j++) {
			r_out[i][j] = (r_in[i][j] / (32) * max);
			g_out[i][j] = (g_in[i][j] / (32) * max);
			b_out[i][j] = (b_in[i][j] / (32) * max);
			if(r_out[i][j] <= g_out[i][j]){
				tmp = g_out[i][j];
				r_out[i][j] = tmp;
			}

			if(b_out[i][j] <= g_out[i][j]){
				tmp = g_out[i][j];
				b_out[i][j] = tmp;
			}

			if(g_out[i][j] <= r_out[i][j]){
				tmp = r_out[i][j];
				g_out[i][j] = tmp;
			}

			if(b_out[i][j] <= r_out[i][j]){
				tmp = r_out[i][j];
				b_out[i][j] = tmp;
			}

			if(r_out[i][j] <= b_out[i][j]){
				tmp = b_out[i][j];
				r_out[i][j] = tmp;
			}

			if(g_out[i][j] <= b_out[i][j]){
				tmp = b_out[i][j];
				g_out[i][j] = tmp;
			}
		}
	}
	}
	else if(inp == 'n')
	{
	for(i = 0; i < 900; i++){
		for(j = 0; j < 900; j++) {
			r_out[i][j] = (r_in[i][j] / (32) * min);
			g_out[i][j] = (g_in[i][j] / (32) * min);
			b_out[i][j] = (b_in[i][j] / (32) * min);
			if(r_out[i][j] <= g_out[i][j]){
				tmp = g_out[i][j];
				r_out[i][j] = tmp;
			}
			if(b_out[i][j] <= g_out[i][j]){
				tmp = g_out[i][j];
				b_out[i][j] = tmp;
			}
			if(g_out[i][j] <= r_out[i][j]){
				tmp = r_out[i][j];
				g_out[i][j] = tmp;
			}
			if(b_out[i][j] <= r_out[i][j]){
				tmp = r_out[i][j];
				b_out[i][j] = tmp;
			}
			if(r_out[i][j] <= b_out[i][j]){
				tmp = b_out[i][j];
				r_out[i][j] = tmp;
			}
			if(g_out[i][j] <= b_out[i][j]){
				tmp = b_out[i][j];
				g_out[i][j] = tmp;
			}
		}
	}

	}
}

