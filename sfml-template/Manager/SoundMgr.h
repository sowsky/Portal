#pragma once
#include <SFML/Audio.hpp>
#include <list>
#include "../3rd/Singleton.h"
using namespace std;
using namespace sf;

enum class SoundChoice
{
	FireBlueSound,
	FireOrangeSound,
	WalkSound,
};

class SoundMgr : public Singleton<SoundMgr>
{
private:
	vector<SoundBuffer> soundBuffers;
	vector<Sound> sounds;
	vector<string> soundName;	

	SoundChoice soundChoice;

	int volume;
public:
	SoundMgr();
	virtual ~SoundMgr();
	
	void SoundPlay(SoundChoice soundchoice);
	SoundChoice GetSoundChoice();
	void SetVolumeUpDown(int a);//input int argument(+/-)

	void Setvolume(int a) { volume = a; }
	String GetVolume() { return to_string(volume); }
};

#define SOUNDMGR (SoundMgr::GetInstance())