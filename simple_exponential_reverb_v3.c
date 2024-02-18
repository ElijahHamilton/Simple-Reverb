/*
THIS VERSION PROPERLY SPACES OUT THE DELAY TIMES, AND USES A FASTER METHOD TO
CALCULATE THE EXPONENTIAL DECAY AMPLITUDES.
V3 INCLUDES AN AMPLITUDE "CUT-OFF", TO PREVENT AN EXTREMELY HIGH NUMBER OF DELAYS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fs 48000		//sample rate (hertz)
#define length 10		//audio length in seconds
#define num_delays 100	//number of delays per second of audio
#define decay 0.99		//amplitude decay factor (linear, 0-1)
#define thresh 0.1		//reverb cut-off threshold (linear, 0-1)

int main() {
	int j, p;
	int n = fs*length;	//input file length in seconds
	int step = fs/num_delays;
	short *inbuf2 = malloc(2*n);
	double *inbuf = malloc(8*n);
	double amp = 1;

	FILE *fin = fopen("input.raw", "rb");	//input filename
	FILE *fout = fopen("output.raw", "wb");	//output filename
	fread(inbuf2, 2, n, fin);

	srand(5);	//"random" seed

	for(int i=0; i<n; i++) {
		inbuf[i] = inbuf2[i];
	}

	free(inbuf2);
	double *outbuf = malloc(8*n);

	p = 0;
	while(amp > thresh) {
		j = (rand()%step)+p;

		for(int i=j; i<(n-j); i++) {
			outbuf[i+j] += inbuf[i]*amp;
		}
		amp *= decay;
		p += step;
	}

	short *outbuf2 = malloc(2*n);
	for(int i=0; i<n; i++) {
		outbuf2[i] = outbuf[i]*0.1;	//output volume (0-1)
	}
	fwrite(outbuf2, 2, n, fout);
	printf("output written to output.raw\n");

	fclose(fin);
	fclose(fout);
	free(inbuf);
	free(outbuf);
	free(outbuf2);

	return 0;
}
