#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fs 48000		//sample rate (hertz)
#define length 10		//audio length in seconds
#define num_delays 100	//number of delays per second of audio
#define maxlen 3		//max delay length in seconds
#define minamp 0.001	//amplitude at max delay length

int main() {
	int n = fs*length;	//input file length in seconds
	int j;
	short *inbuf2 = malloc(2*n);
	double *inbuf = malloc(8*n);
	double amp;

	FILE *fin = fopen("input.raw", "rb");	//input filename
	FILE *fout = fopen("output.raw", "wb");	//output filename
	fread(inbuf2, 2, n, fin);

	srand(5);	//"random" seed

	for(int i=0; i<n; i++) {
		inbuf[i] = inbuf2[i];
	}

	free(inbuf2);
	double *outbuf = malloc(8*n);

	for(int p=0; p<num_delays*maxlen; p++) {
		j = rand() % (int)(fs*maxlen);	//max delay length (4 seconds);
		amp = (j/maxlen)/(double)fs;
		amp = pow(minamp, amp);	//volume at max delay time

		for(int i=j; i<(n-j); i++) {
			outbuf[i+j] += inbuf[i]*amp;
		}

		printf("percent complete: %f\r", 100*(double)p/(num_delays*maxlen));
		fflush(stdout);
	}

	short *outbuf2 = malloc(2*n);
	for(int i=0; i<n; i++) {
		outbuf2[i] = outbuf[i]*0.1;	//output volume (0-1)
	}

	fwrite(outbuf2, 2, n, fout);
	fclose(fin);
	fclose(fout);

	free(inbuf);
	free(outbuf);
	free(outbuf2);

	return 0;
}
