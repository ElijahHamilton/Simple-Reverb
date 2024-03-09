/*
THIS VERSION PROPERLY SPACES OUT THE DELAY TIMES, AND USES A FASTER METHOD TO
CALCULATE THE EXPONENTIAL DECAY AMPLITUDES.
V3 INCLUDES AN AMPLITUDE "CUT-OFF", TO PREVENT AN EXTREMELY HIGH NUMBER OF DELAYS.
THIS FAST VERSION DIRECTLY OPPERATES ON SHORTS, REDUCING BOTH PROCESSING TIME AND QUALITY.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fs 48000		//sample rate (hertz)
#define length 10		//audio length in seconds
#define num_delays 100		//number of delays per second of audio
#define decay 0.99		//amplitude decay factor (linear, 0-1)
#define thresh 0.1		//reverb cut-off threshold (linear, 0-1)
#define outamp 0.1		//output volume (linear, 0-1)

int main() {
	int j, p;
	int n = fs*length;	//input file length in seconds
	int step = fs/num_delays;
	short *inbuf = malloc(2*n);
	short *outbuf = malloc(2*n);
	double amp = 1;

	FILE *fin = fopen("input.raw", "rb");	//input filename
	FILE *fout = fopen("output.raw", "wb");	//output filename
	fread(inbuf, 2, n, fin);

	srand(5);	//"random" seed

	p = 0;
	while(amp > thresh) {
		j = (rand()%step)+p;

		for(int i=j; i<(n-j); i++) {
			outbuf[i+j] += inbuf[i]*amp*outamp;
		}
		amp *= decay;
		p += step;
	}

	fwrite(outbuf, 2, n, fout);
	printf("output written to output.raw\n");

	fclose(fin);
	fclose(fout);
	free(inbuf);
	free(outbuf);

	return 0;
}
