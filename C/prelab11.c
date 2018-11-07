#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string.h>
#define NUM_CHANNELS 2
#define BITS_PER_SAMPLE 32
#define SAMPLE_RATE 192000
#define BYTE_RATE ((SAMPLE_RATE) * (NUM_CHANNELS) * (BITS_PER_SAMPLE) / 8)
#define BLOCK_ALIGN ((NUM_CHANNELS) * (BITS_PER_SAMPLE) / 8)
#define BASE_SIZE 36
const unsigned long long MAX_SAMPLE_VALUE = (unsigned long long)pow(2, BITS_PER_SAMPLE) - 1;
#define REST_FACTOR 25

/* Typedef a sample value depending on BITS_PER_SAMPLE */
#if (BITS_PER_SAMPLE == 16)
typedef int16_t wav_sample_value;
#elif (BITS_PER_SAMPLE == 32)
typedef int32_t wav_sample_value;
#else
#error Unsupported bits per sample.
#endif


/* The format "subchunk" */
struct wav_format_header {
	char chunk_id[4];
	uint32_t chunk_size;
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;
};

struct wav_sample {
	wav_sample_value values[NUM_CHANNELS];
};

/* The data "subchunk" */
struct wav_data {
	char chunk_id[4];
	uint32_t chunk_size;
	struct wav_sample * samples;
	//TODO: add another data member called samples, which is
	//a pointer to a wav_sample struct. We will malloc some
	//space later to store the samples, and this is where we'll
	//store the pointer that's returned by malloc.
};

/* The overall "chunk" */
struct wav_file {
	char chunk_id[4];
	uint32_t chunk_size;
	char format[4];
	struct wav_format_header fmt_hdr;
	struct wav_data data;
};

/*****************************************************/
/* Function prototypes */

void init_wav_format_header(struct wav_format_header * wfh);
void init_wav_data(struct wav_data * wd);
void init_wav_file(struct wav_file * wf);
void free_samples(struct wav_file * wf);
long long allocate_samples(struct wav_file * wf, unsigned long num_new_samples);
int add_tone(struct wav_file * wf, double freq, unsigned long long dur);
void write_wav_file(struct wav_file * wf, FILE * output_file);
double get_freq_from_str(char str[]);

/*****************************************************/
/* Main function */
int main() {
	FILE * f;
	char input_file_name[] = "mary_had_a_little_lamb.txt";
	char output_file_name[] = "test.wav";
	double freq;
	unsigned long long duration;
	char input[10];

	struct wav_file my_wav;
	//TODO: call init_wav_file, passing my_wav by pointer
	init_wav_file(&my_wav);
	//TODO: open the input file for reading
	f =

	/*The input file is composed of lines with two
		values on them, the name of a musical note (which
		corresponds with a frequency), and the duration for
		the note. We'll use two calls to fscanf() to
		read these values.*/
	//TODO: loop while this fscanf doesn't return EOF
	while(fscanf(f, "%s", input) != ) {
		/* Interpret the musical note name as a frequency */
		freq = get_freq_from_str(input);
		//TODO: use fscanf to read the next value into duration
		//as an unsigned long long
		fscanf(
		printf("Freq: %lf, duration: %llu\n", freq, duration);

	//TODO: close the output file

	/* Free the memory allocated for samples */
	free_samples(&my_wav);
}

/*****************************************************/
/* Generates a sine wave tone. Freq in Hz, dur in ms */
int add_tone(struct wav_file * wf, double freq, unsigned long long dur) {
	double samples_per_period = 0.0;
	unsigned long num_rest_samples = 0;

	/* We'll need to allocate memory for more samples. The number
			of new samples depends on the sample rate for our WAV. */
	unsigned long num_new_samples = wf->fmt_hdr.sample_rate * dur / 1000;
	//TODO: call allocate_samples, passing in wf and num_new_samples,
	//and assign the return value to old_num_samples
	unsigned long old_num_samples =

	printf("Adding %lu new samples (had %lu)\n", num_new_samples, old_num_samples);

	/* If allocate_samples returned a negative number, it failed */
	if(old_num_samples < 0) {
		return 0;
	}

	/* Calculate the number of samples in a period of a sine wave
			with frequency freq */
	samples_per_period = wf->fmt_hdr.sample_rate / freq;
	printf("Samples per period: %lf\n", samples_per_period);

	/* Calculate the number of new samples that will be "rests", i.e.
			no tone. */
	num_rest_samples = num_new_samples / REST_FACTOR;

	/* For each new sample that isn't a rest, populate it with a
			sine wave sample. */
	for(int i = old_num_samples;
			i < old_num_samples + num_new_samples - num_rest_samples;
			i++) {
		/* Each sample is composed of multiple channels. We'll write
				the same value to each channel. */
		for(int c = 0; c < wf->fmt_hdr.num_channels; c++) {
			/* Get number of periods that have passed */
			double num_periods = i / samples_per_period;
			/* Find position of i in the period */
			double period_frac = num_periods - (int)num_periods;
			/* Get the sine value */
			double sin_val = sin(period_frac * 2 * M_PI);
			/* Get the amplitude of the sine wave */
			unsigned long long val = sin_val * MAX_SAMPLE_VALUE;
			/* Center the wave on zero */
			wf->data.samples[i].values[c] = val - MAX_SAMPLE_VALUE / 2;
		}
	}

	/* For each "rest" sample, populate it with zero */
	for(int i = old_num_samples + num_new_samples - num_rest_samples;
			i < old_num_samples + num_new_samples;
			i++) {
		for(int c = 0; c < wf->fmt_hdr.num_channels; c++) {
			wf->data.samples[i].values[c] = 0;
		}
	}

	printf("Done adding samples.\n");
	return 1;
}

/*****************************************************/
/* Allocates some samples using malloc() or realloc(). */
long long allocate_samples(struct wav_file * wf, unsigned long num_new_samples) {
	/* Old size of the allocated memory, in bytes */
	unsigned long old_size = wf->data.chunk_size;
	/* New size that we're going to ask for, in bytes */
	unsigned long new_size = old_size + num_new_samples * sizeof(struct wav_sample);

	printf("Allocating samples. Old size: %lu, new size: %lu\n", old_size, new_size);

	/* We only call malloc() the first time; otherwise, we
		call realloc to increase the size of our memory block. If
		we haven't called malloc yet, wf->data.samples will be NULL. */

	//TODO: check if wf->data.samples is NULL
	if(wf->data.samples == ) {
		printf("Calling malloc\n");
		//TODO: call malloc, asking for new_size bytes of memory.
		//Cast the pointer that is returned as a pointer to a
		//struct wav_sample and store it in wf->data.samples.
		wf->data.samples = ;
	} else {
		printf("Calling realloc\n");
		//TODO: call realloc to increase the size of the memory
		//block pointed at by wf->data.samples. Ask for new_size bytes.
		//Cast the pointer that is returned as a pointer to a
		//struct wav_sample.
		wf->data.samples = ;
	}

	/* If the pointer was NULL, we failed. */
	if(wf->data.samples == NULL) {
		wf->data.chunk_size = 0;
		return -1;
	}

	/* Update the sizes in the WAV metadata. */
	wf->data.chunk_size = new_size;
	wf->chunk_size = BASE_SIZE + new_size;

	/* We return the previous number of samples. This tells
			the calling function where to start writing the new
			sample data. */
	return old_size / sizeof(struct wav_sample);
}

/*****************************************************/
/* Free the memory allocated for the samples. */
void free_samples(struct wav_file * wf) {
	//TODO: Call free(). The argument
	//to free is the pointer to the block of memory allocated
	//by malloc, which is the the "samples" data member of the
	//"data" data member of wf. To access it, first use the
	//arrow operator (->) to get "data" from wf. Then add the
	//dot operator (.) to get "samples" from the result.

}

/*****************************************************/
/* Declare constants for the frequencies of musical notes. */
const double C4 = 261.63;
const double D4 = 293.66;
const double E4 = 329.63;
const double F4 = 349.23;
const double G4 = 392.00;
const double A4 = 440;
const double B4 = 493.88;
const double C5 = 523.25;

/* Convert a musical note name string into a frequency. */
double get_freq_from_str(char str[]) {
	printf("Freq string: %s\n", str);
	if(strcmp(str, "C4") == 0)
		return C4;
	else if(strcmp(str, "D4") == 0)
		return D4;
	else if(strcmp(str, "E4") == 0)
		return E4;
	else if(strcmp(str, "F4") == 0)
		return F4;
	else if(strcmp(str, "G4") == 0)
		return G4;
	else if(strcmp(str, "A4") == 0)
		return A4;
	else if(strcmp(str, "B4") == 0)
		return B4;
	else if(strcmp(str, "C5") == 0)
		return C5;
	else
		return 0;
}

/*****************************************************/
/* Write a struct wav_format_header to a file. This cheats
		and assumes no struct padding, which should be true for us. */
void write_wav_format_header(struct wav_format_header * wfh, FILE * output_file) {
	for(int i = 0; i < sizeof(struct wav_format_header); i++) {
		/* Interpret the struct as a series of bytes */
		fputc(((unsigned char *)(wfh))[i], output_file);
	}
}

/*****************************************************/
/* Write a struct wav_data to a file, including the samples. */
void write_wav_data(struct wav_data * wd, FILE * output_file) {
	unsigned long data_size = wd->chunk_size;
	for(int i = 0; i < 8; i++) {
		/* Interpret the struct as a series of bytes */
		fputc(((unsigned char *)(wd))[i], output_file);
	}
	printf("Writing data, length %ld bytes\n", data_size);
	for(int i = 0; i < data_size; i++) {
		/* Interpret the sample data as a series of bytes */
		fputc(((unsigned char *)(wd->samples))[i], output_file);
	}
}

/*****************************************************/
/* Write the wav_file struct to a file. */
void write_wav_file(struct wav_file * wf, FILE * output_file) {
	for(int i = 0; i < 12; i++) {
		/* Interpret the struct as a series of bytes */
		fputc(((unsigned char *)(wf))[i], output_file);
	}
	write_wav_format_header(&wf->fmt_hdr, output_file);
	write_wav_data(&wf->data, output_file);

	printf("Size field in file was %d with base size %d\n", wf->chunk_size, BASE_SIZE);
}

/*****************************************************/
/* Initialize a wav_format_header struct */
void init_wav_format_header(struct wav_format_header * wfh) {
	wfh->chunk_id[0] = 'f';
	wfh->chunk_id[1] = 'm';
	wfh->chunk_id[2] = 't';
	wfh->chunk_id[3] = ' ';
	wfh->chunk_size = 16;
	wfh->audio_format = 1; //PCM
	wfh->num_channels = NUM_CHANNELS;
	wfh->sample_rate = SAMPLE_RATE;
	wfh->byte_rate = BYTE_RATE;
}

/*****************************************************/
/* Initialize a wav_format_header struct */
void init_wav_format_header(struct wav_format_header * wfh) {
	wfh->chunk_id[0] = 'f';
	wfh->chunk_id[1] = 'm';
	wfh->chunk_id[2] = 't';
	wfh->chunk_id[3] = ' ';
	wfh->chunk_size = 16;
	wfh->audio_format = 1; //PCM
	wfh->num_channels = NUM_CHANNELS;
	wfh->sample_rate = SAMPLE_RATE;
	wfh->byte_rate = BYTE_RATE;
	wfh->block_align = BLOCK_ALIGN;
	wfh->bits_per_sample = BITS_PER_SAMPLE;
}

/*****************************************************/
/* Initialize a wav_data struct */
void init_wav_data(struct wav_data * wd) {
	wd->chunk_id[0] = 'd';
	wd->chunk_id[1] = 'a';
	wd->chunk_id[2] = 't';
	wd->chunk_id[3] = 'a';
	wd->chunk_size = 0;
	wd->samples = NULL;
}

/*****************************************************/
/* Initialize a wav_file struct */
void init_wav_file(struct wav_file * wf) {
	wf->chunk_id[0] = 'R';
	wf->chunk_id[1] = 'I';
	wf->chunk_id[2] = 'F';
	wf->chunk_id[3] = 'F';
	wf->chunk_size = BASE_SIZE;
	wf->format[0] = 'W';
	wf->format[1] = 'A';
	wf->format[2] = 'V';
	wf->format[3] = 'E';
	init_wav_format_header(&wf->fmt_hdr);
	init_wav_data(&wf->data);
}

/*****************************************************/

