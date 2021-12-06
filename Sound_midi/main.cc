

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "AudioDriver.h"
#include "SoundSource.h"
#include "WaveGenerator.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

#ifdef __WIN32__
#include <winsock.h>
#else
#include <netinet/in.h>
#endif
#include <vector>

int main(int, char**)
{
	static const double s_freq_table[] = {
			32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00,
			 51.91, 55.00, 58.27, 61.74, 65.41, 69.30, 73.42, 77.78,
			 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47,
			 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00,
			 207.65, 220.00, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13,
			 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
			 523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99,
			 830.61, 880.00, 932.33, 987.77, 1046.50, 1108.73, 1174.66, 1244.51,
			 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53,
			 2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96,
			 3322.44, 3520.00, 3729.31, 3951.07, 4186.01, 4434.92, 4698.64, 4978.03,
			 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13,
			 8372.02, 8869.84, 9397.27, 9956.06, 10548.08, 11175.30, 11839.82, 12543.85,
			 13289.75, 14080.00, 14917.24, 15804.27, 16744.04, 17739.69, 18794.55, 19912.13,
			 21096.16, 22350.61, 23679.64, 25087.71, 26579.50, 28160.00, 29834.48, 31608.53,
			 33488.07, 35479.38, 37589.09, 39824.25, 42192.33, 44701.21, 47359.29, 50175.42
};

	SDL_setenv("SDL_AUDIODRIVER", "directsound", true);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_setenv("SDL_AUDIODRIVER", "directsound", true);


	AudioDriver drv;
	drv.unpause();

	auto src = std::make_shared<SoundSource>();
	auto wg = std::make_shared<SquareWaveGenerator>();
	auto eg = std::make_shared<ConstantEnvelopeGenerator>(1.);
	auto fg = std::make_shared<FMWaveGenerator>();

	FMInstrument f;
	f.al = 7;
	f.fb = 0;
	f.op[0] = {0.001, 1., 0.95, 0.01, 1., 0.};
	f.op[1] = {0.001, 1., 0.95, 0.01, 1., 0.};
	f.op[2] = {0.001, 1., 0.95, 0.01, 1., 0.};
	f.op[3] = {0.001, 1., 0.95, 0.01, 1., 0.};
	f.be[0] = 1.; f.be[1] = 1.; f.be[2] = 1.; f.be[3] = 1.;
	f.multi[0] = 1.; f.multi[1] = 1.; f.multi[2] = 1.; f.multi[3] = 1.;

	fg->set_freq(440.);
	fg->setup(f);
	src->set_envelope_generator(eg);
	src->set_wave_generator(fg);

	drv.set_sound_source(src);
	drv.set_master_volume(4000);

	std::vector<std::vector<char>> track;

			std::fstream file;

			file.open("PINBALL.MID", std::ios::in | std::ios::binary);
			//file.open("gimn_rossii.mid", std::ios::in | std::ios::binary);


			int chunk_type;
			int MThd_length;
			short MThd_format;
			short MThd_tracks;
			short MThd_division;


			// Читаем заголовок
			file.read(reinterpret_cast<char*>(&chunk_type), sizeof(chunk_type));
			if (chunk_type == (
					'M'*0x00000001 +
					'T'*0x00000100 +
					'h'*0x00010000 +
					'd'*0x01000000))
				std::cout << "О, это заголовок!" << std::endl;

			file.read(reinterpret_cast<char*>(&MThd_length), sizeof(MThd_length));
			MThd_length = ntohl(MThd_length);
			std::cout << "MThd length: " << MThd_length << std::endl;

			file.read(reinterpret_cast<char*>(&MThd_format), sizeof(MThd_format));
			MThd_format = ntohs(MThd_format);
			std::cout << "MThd format: " << MThd_format << std::endl;

			file.read(reinterpret_cast<char*>(&MThd_tracks), sizeof(MThd_tracks));
			MThd_tracks = ntohs(MThd_tracks);
			std::cout << "MThd tracks: " << MThd_tracks << std::endl;

			file.read(reinterpret_cast<char*>(&MThd_division), sizeof(MThd_division));
			MThd_division = ntohs(MThd_division);
			std::cout << "MThd division: " << MThd_division << std::endl;
			if (MThd_division & 0x8000) {
				std::cout << "Единица измерения - SMPTE" << std::endl;
			} else {
				std::cout << "Единица измерения - TPQN" << std::endl;
			}

			track.resize(MThd_tracks);

			for (int i = 0; i < MThd_tracks; i++) {
				file.read(reinterpret_cast<char*>(&chunk_type), sizeof(chunk_type));
				if (chunk_type == (
						'M'*0x00000001 +
						'T'*0x00000100 +
						'r'*0x00010000 +
						'k'*0x01000000)) {
					std::cout << "О, а это дорожка " << i << std::endl;

				} else {
					std::cout << "Ой, это не дорожка :(" << std::endl;
					break;
				}
				int trk_length;
				file.read(reinterpret_cast<char*>(&trk_length), sizeof(int));
				trk_length = ntohl(trk_length);
				std::cout << "  Длина: " << trk_length <<std::endl;
				track[i].resize(trk_length);
				file.read(&track[i][0], trk_length);
			}

			size_t trk = 1;

			std::cout << "Для демонстрации будем работать только с дорожкой " << trk << std::endl;
			size_t p = 0;
			while (p < track[trk].size()) {
				int delta = 0;
				int delta_v;
				do {
					delta_v = track[trk][p++];
					delta *= 256;
					delta += delta_v;
				} while (delta_v > 0);


				std::cout << std::setw(10) << delta << ": ";

				int event_type = track[trk][p++];
				int note;
				int velocity;
				int metatype;

				switch(event_type & 0xff) {
				case 0xff:
					metatype = track[trk][p++] & 0xff;
					  std::cout << "Это метасобытие " << metatype << std::endl;
					  switch (metatype) {
					  case 3:
					  {
					      int len = track[trk][p++] & 0xff;
					      std::vector<char> str(len+1);
					      for (int i = 0; i < len; i++)
					        str[i] = track[trk][p++] & 0xff;
					      str[len] = 0;
					      std::cout << "Имя дорожки: " << (&str[0]) << std::endl;
					    }
					    break;
					  }

					break;
				case 0x00 ... 0x7b:
					 p++;
					 break;
				case 0x80 ... 0x8f:
				{
					note = track[trk][p++];
					velocity = track[trk][p++];
					fg->set_freq(s_freq_table[note]);
					fg->set_volume(velocity/127.);
					fg->key_off();
				}
				  break;
				case 0x90 ... 0x9f:
				{
					note = track[trk][p++];
					velocity = track[trk][p++];
					fg->set_freq(s_freq_table[note]);
					fg->set_volume(velocity/127.);
					std::cout << "note: " << note << std::endl;
					std::cout.flush();
					fg->key_on();
				}
				  break;
				case 0xA0 ... 0xAf:

					break;
				case 0xB0 ... 0xBf:

					break;
				case 0xC0 ... 0xCf:
				{

				}
					break;
				case 0xD0 ... 0xDf:

					break;
				case 0xE0 ... 0xEf:

					break;


				default:
					std::cout << "ААААА, я события " << (event_type & 0xff) << " не знаю!" << std::endl;
					return 1;
				}
			}



			file.close();


	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow("", 50, 50, 800, 600, SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	SDL_Event ev;
	for (;;) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) goto the_exit;
		}

		SDL_Delay(10);
	}





the_exit:


	return 0;
}
