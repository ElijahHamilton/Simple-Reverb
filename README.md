# Simple-Reverb
Simplistic programs for simulating reverberation.
These programs operate on raw (signed 16-bit, mono, 48khz) audio files. Of course, the sample rate can easily be changed within the code.

This project was made to simulate "outdoor" reveberation, where there is no "room size".
The program simply picks a random number of samples to delay the signal by, multiplies it by a computed amplitude, and sums it with the output signal (100+ times or more).
Only 100 delays per second seem to produce good results.

# Compiling
`gcc -O3 simple_exponential_reverb.c`
