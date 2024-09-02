#include "daisy_pod.h"
#include "daisysp.h"

// Uncomment to enable semihosted logging to the STLink console
// #define LOG_STLINK 1

daisy::DaisyPod hw;


void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
}

int main(void)
{

	#ifdef LOG_STLINK
	auto logger = daisy::Logger<daisy::LOGGER_SEMIHOST>();
	logger.StartLog(false);
	logger.PrintLine("Seimohosted logging activated!");
	#endif

	hw.Init();
	hw.seed.StartLog(false);
	hw.SetAudioBlockSize(32); // number of samples handled per callback
	hw.SetAudioSampleRate(daisy::SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	

	bool led_state = true;
	while(1) {
		hw.seed.PrintLine("Led state:%s", led_state? "on" : "off");
		hw.seed.SetLed(led_state);
		hw.DelayMs(1000);
		led_state = !led_state;
	}
}
