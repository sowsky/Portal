#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
	soundName.push_back("Sound/fireblue.wav");
	soundName.push_back("Sound/fireorange.wav");
	soundName.push_back("Sound/footstep.wav");

	SoundBuffer soundBuffer;
	Sound sound;
	for (int i = 0; i < soundName.size(); i++)
	{
		soundBuffer.loadFromFile(soundName[i]);
		soundBuffers.push_back(soundBuffer);
	}

	for (int i = 0; i < soundBuffers.size(); i++)
	{
		sound.setBuffer(soundBuffers[i]);
		sounds.push_back(sound);
	}	
}

SoundMgr::~SoundMgr()
{
	for (auto& k : soundBuffers)
	{
		delete &k;
	}
	soundBuffers.clear();

	for (auto& k : sounds)
	{
		delete& k;
	}
	sounds.clear();

	for (auto& k : soundName)
	{
		delete& k;
	}
	soundName.clear();
}

void SoundMgr::SoundPlay(SoundChoice soundchoice)
{
	switch (soundchoice)
	{
	case SoundChoice::FireBlueSound:
		sounds[0].setVolume(volume);
		sounds[0].play();
		
		break;
	case SoundChoice::FireOrangeSound:
		sounds[1].setVolume(volume);
		sounds[1].play();
		break;
	case SoundChoice::WalkSound:
		sounds[2].play();
		break;
	default:
		break;
	}

	this->soundChoice = soundchoice;
}

SoundChoice SoundMgr::GetSoundChoice()
{
	return soundChoice;
}

void SoundMgr::SetVolumeUpDown(int a)
{
	if (volume + a > 100 && volume - a < 0)
		volume += a;
}
