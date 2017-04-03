//
//  main.cpp
//  Akshar
//
//  Created by CoRo on 02/04/17.
//  Copyright © 2017 CoRo. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

#define FILE_PATH_BEE "/Users/bee.wav"
#define FILE_PATH_BLOP "/Users/blop.wav"

struct AudioData{
    
    Uint8* pos;
    Uint32 length;
    
};

void MyAudioCallback(void* userdata, Uint8* stream, int streamLength){
    
    AudioData* audio = (AudioData*)userdata;
    
    if (audio -> length == 0) {
        return;
    }
    
    Uint32 length = (Uint32) streamLength;
    length = (length > audio -> length ? audio->length : length);
    
    SDL_memcpy(stream, audio -> pos, length);
    
    audio -> pos += length;
    audio -> length -= length;
}

int main(int argc, const char * argv[]) {

    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_AudioSpec wavSpec; //describing the frequency of the wavfile and other details
    
    Uint8* wavStart;  //locating the start of the wav file in the memory
    
    Uint32 wavLength; // length of the wav file
    
     int a = 1;
    
    if (a == 1) {
        if (SDL_LoadWAV(FILE_PATH_BEE, &wavSpec, &wavStart, &wavLength) == NULL) {
            
            std::cerr << "Error:" << FILE_PATH_BEE << "Audio file couldn't be found" << std::endl;
            return 1;
        }
    }
    else{
        if (SDL_LoadWAV(FILE_PATH_BLOP, &wavSpec, &wavStart, &wavLength) == NULL) {
            
            std::cerr << "Error:" << FILE_PATH_BLOP << "Audio file couldn't be found" << std::endl;
            return 1;
        }
    }
    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;
    
    wavSpec.callback = MyAudioCallback;
    wavSpec.userdata = &audio;
    
    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
    
    if(device == 0){
        std::cerr << "Error:" << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_PauseAudioDevice(device, 0);
    
    while (audio.length > 0) {
        SDL_Delay(1000);
    }
    
    
    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(wavStart);
    SDL_Quit();
    return 0;
}


