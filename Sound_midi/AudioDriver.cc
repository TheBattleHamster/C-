

#include "AudioDriver.h"
#include <iostream>

static void audio_callback(void * userdata, Uint8 * stream, int len)
{
	short * buffer = reinterpret_cast<short*>(stream);
	int samples = len / sizeof(short);
	AudioDriver * ad = reinterpret_cast<AudioDriver *>(userdata);
	ad->callback(buffer, samples);
}

AudioDriver::AudioDriver()
{
	_spec.channels = 1;
	_spec.format = AUDIO_S16;
	_spec.freq = AUDIO_SAMPLING_FREQUENCY;
	_spec.callback = audio_callback;
	_spec.userdata = this;
	//SDL_AudioInit("directsound");

	_id = SDL_OpenAudioDevice(nullptr, 0, &_spec, &_obtained_spec, 0);
	if (_id == 0) {
		//system("pause");
	   std::cout << "Failed to open audio:" << SDL_GetError() << std::endl;
	}
	else std::cout << "Successfully opened audio device!" << std::endl;

	for (int i = 0; i < SDL_GetNumAudioDrivers(); ++i) {
				const char* driver_name = SDL_GetAudioDriver(i);
				printf("[%d] %s\n", i, driver_name);
		}
}

AudioDriver::~AudioDriver()
{
	pause();
	SDL_CloseAudioDevice(_id);
}

void AudioDriver::callback(short * buffer, int samples)
{
	for (int i = 0; i < samples; i++)
	{
		buffer[i] = short(_source ->next_sample() * _master_volume);
//		std::cout <<"Это в буфере:"<< buffer[i]<< std::endl;
//		std::cout.flush();
	}
}
