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
public:
	SoundMgr();
	virtual ~SoundMgr();
	
	void SoundPlay(SoundChoice soundchoice);
	SoundChoice GetSoundChoice();
};

#define SOUNDMGR (SoundMgr::GetInstance())