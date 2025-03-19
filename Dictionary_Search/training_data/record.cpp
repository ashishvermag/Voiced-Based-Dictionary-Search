// Record.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#include <direct.h>  // For creating directories
#pragma comment(lib, "winmm.lib")
using namespace std;

#define frame_size 320
#define LENGTH_WAV 16025 * 3
#define MAX_OCCURRENCE 3  // Occurrence limit

short int waveIn[LENGTH_WAV];  // Array where the sound sample will be stored

void PlayRecord() {
    const int NUMPTS = LENGTH_WAV;
    int sampleRate = 16025;

    HWAVEOUT hWaveOut;
    WAVEFORMATEX pFormat;
    pFormat.wFormatTag = WAVE_FORMAT_PCM;
    pFormat.nChannels = 1;
    pFormat.nSamplesPerSec = sampleRate;
    pFormat.nAvgBytesPerSec = sampleRate * 2;
    pFormat.nBlockAlign = 2;
    pFormat.wBitsPerSample = 16;
    pFormat.cbSize = 0;

    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT) != MMSYSERR_NOERROR) {
        printf("Failed to open waveform output device.\n");
        return;
    }

    WAVEHDR WaveOutHdr;
    WaveOutHdr.lpData = (LPSTR)waveIn;
    WaveOutHdr.dwBufferLength = NUMPTS * 2;
    WaveOutHdr.dwBytesRecorded = 0;
    WaveOutHdr.dwUser = 0L;
    WaveOutHdr.dwFlags = 0L;
    WaveOutHdr.dwLoops = 0L;
    waveOutPrepareHeader(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR));

    printf("Playing...\n");
    waveOutWrite(hWaveOut, &WaveOutHdr, sizeof(WaveOutHdr));

    Sleep(3 * 1000);  // Sleep for duration of playback

    waveOutClose(hWaveOut);
}

void StartRecord() {
    const int NUMPTS = LENGTH_WAV;
    int sampleRate = 16025;

    HWAVEIN hWaveIn;
    MMRESULT result;

    WAVEFORMATEX pFormat;
    pFormat.wFormatTag = WAVE_FORMAT_PCM;
    pFormat.nChannels = 1;
    pFormat.nSamplesPerSec = sampleRate;
    pFormat.nAvgBytesPerSec = sampleRate * 2;
    pFormat.nBlockAlign = 2;
    pFormat.wBitsPerSample = 16;
    pFormat.cbSize = 0;

    result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

    if (result != MMSYSERR_NOERROR) {
        printf("Failed to open waveform input device.\n");
        return;
    }

    WAVEHDR WaveInHdr;
    WaveInHdr.lpData = (LPSTR)waveIn;
    WaveInHdr.dwBufferLength = NUMPTS * 2;
    WaveInHdr.dwBytesRecorded = 0;
    WaveInHdr.dwUser = 0L;
    WaveInHdr.dwFlags = 0L;
    WaveInHdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    if (result != MMSYSERR_NOERROR) {
        printf("Failed to add buffer to waveform input device.\n");
        waveInClose(hWaveIn);
        return;
    }

    result = waveInStart(hWaveIn);
    if (result != MMSYSERR_NOERROR) {
        printf("Failed to start waveform input device.\n");
        waveInClose(hWaveIn);
        return;
    }

    printf("Recording for 3 seconds...\n");
    Sleep(3 * 1000);  // Wait until finished recording

    waveInClose(hWaveIn);
	PlayRecord();
}


/*
void PlayRecord()
{
	 const int NUMPTS = 16025 * 3;   // 3 seconds
	 int sampleRate = 16025;  
	 // 'short int' is a 16-bit type; I request 16-bit samples below
		// for 8-bit capture, you'd    use 'unsigned char' or 'BYTE' 8-bit types
	 HWAVEIN  hWaveIn;
	 WAVEFORMATEX pFormat;
	 pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
	 pFormat.nChannels=1;                    //  1=mono, 2=stereo
	 pFormat.nSamplesPerSec=sampleRate;      // 44100
	 pFormat.nAvgBytesPerSec=sampleRate*2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
	 pFormat.nBlockAlign=2;                  // = n.Channels * wBitsPerSample/8
	 pFormat.wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
	 pFormat.cbSize=0;
	 // Specify recording parameters
	 waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
	 WAVEHDR      WaveInHdr;
	 // Set up and prepare header for input
	 WaveInHdr.lpData = (LPSTR)waveIn;
	 WaveInHdr.dwBufferLength = NUMPTS*2;
	 WaveInHdr.dwBytesRecorded=0;
	 WaveInHdr.dwUser = 0L;
	 WaveInHdr.dwFlags = 0L;
	 WaveInHdr.dwLoops = 0L;
	 waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	 HWAVEOUT hWaveOut;
	 cout<<"playing..." <<endl;
	 waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0, 0, WAVE_FORMAT_DIRECT);
	 waveOutWrite(hWaveOut, &WaveInHdr, sizeof(WaveInHdr)); // Playing the data
	 Sleep(3 * 1000); //Sleep for as long as there was recorded
	 waveInClose(hWaveIn);
	 waveOutClose(hWaveOut);
} 
void StartRecord()
{
	const int NUMPTS = 16025 * 3;   // 3 seconds
	int sampleRate = 16025;  
	// 'short int' is a 16-bit type; I request 16-bit samples below
	// for 8-bit capture, you'd use 'unsigned char' or 'BYTE' 8-bit types
	HWAVEIN hWaveIn;
	MMRESULT result;
	WAVEFORMATEX pFormat;
	pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
	pFormat.nChannels=1;                    //  1=mono, 2=stereo
	pFormat.nSamplesPerSec=sampleRate;      // 8.0 kHz, 11.025 kHz, 22.05 kHz, and 44.1 kHz
	pFormat.nAvgBytesPerSec=sampleRate*2;   // =  nSamplesPerSec × nBlockAlign
	pFormat.nBlockAlign=2;                  // = (nChannels × wBitsPerSample) / 8
	pFormat.wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
	pFormat.cbSize=0;
	// Specify recording parameters
	result = waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
	WAVEHDR      WaveInHdr;
	// Set up and prepare header for input
	WaveInHdr.lpData = (LPSTR)waveIn;
	WaveInHdr.dwBufferLength = NUMPTS*2;
	WaveInHdr.dwBytesRecorded=0;
	WaveInHdr.dwUser = 0L;
	WaveInHdr.dwFlags = 0L;
	WaveInHdr.dwLoops = 0L;
	waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	// Insert a wave input buffer
	result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	// Commence sampling input
	result = waveInStart(hWaveIn);
	cout << "recording for 3 seconds..." << endl;
	Sleep(3 * 1000);
	// Wait until finished recording
	waveInClose(hWaveIn);
	PlayRecord();
}
*/
void save_data(int digit, int occurrence) {
    char filepath[1000];
    sprintf(filepath, "english/txt/244101007_%d_%d.txt", digit, occurrence);  // File path for text file

    FILE* file = fopen(filepath, "w+");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < LENGTH_WAV; i++) {
        fprintf(file, "%d\n", waveIn[i]);
    }

    fclose(file);
    printf("Saved as %s\n", filepath);
}

void save_to_wav(int digit, int occurrence) {
    char filepath[1000];
    sprintf(filepath, "english/wav/244101007_%d_%d.wav", digit, occurrence);  // File path for wav file

    FILE* wav_file = fopen(filepath, "wb");
    if (!wav_file) {
        printf("Error opening wav file\n");
        return;
    }

    int sampleRate = 16025;
    int dataSize = LENGTH_WAV * 3;

    fwrite("RIFF", 1, 4, wav_file);
    int chunkSize = 36 + dataSize;
    fwrite(&chunkSize, 4, 1, wav_file);
    fwrite("WAVE", 1, 4, wav_file);
    fwrite("fmt ", 1, 4, wav_file);
    int subchunk1Size = 16;
    fwrite(&subchunk1Size, 4, 1, wav_file);
    short audioFormat = 1;
    fwrite(&audioFormat, 2, 1, wav_file);
    short numChannels = 1;
    fwrite(&numChannels, 2, 1, wav_file);
    fwrite(&sampleRate, 4, 1, wav_file);
    int byteRate = sampleRate * 2;
    fwrite(&byteRate, 4, 1, wav_file);
    short blockAlign = 2;
    fwrite(&blockAlign, 2, 1, wav_file);
    short bitsPerSample = 16;
    fwrite(&bitsPerSample, 2, 1, wav_file);
    fwrite("data", 1, 4, wav_file);
    fwrite(&dataSize, 4, 1, wav_file);
    fwrite(waveIn, 2, LENGTH_WAV, wav_file);

    fclose(wav_file);
    printf("Saved as %s\n", filepath);
}

int main() {
    int occurrences[10] = {0};  // Array to store occurrences for digits 0-9
    int digit;

    // Create directory structure: 'english', 'english/wav', 'english/txt'
    _mkdir("English");
    _mkdir("English/wav");
    _mkdir("English/txt");

    printf("Enter a digit (0-9): ");
    scanf("%d", &digit);

    if (digit < 0 || digit > 9) {
        printf("Invalid input! Please enter a digit between 0 and 9.\n");
        return 1;
    }

    for (int i = 1; i <= 40; i++) {
        StartRecord();
		//PlayRecord();
        save_data(digit, i);
        save_to_wav(digit, i);
        printf("Recorded and saved occurrence %d for digit %d\n", i, digit);
    }

    printf("All 40 occurrences for digit %d have been recorded and saved.\n", digit);

    return 0;
}