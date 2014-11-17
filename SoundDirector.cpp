#include "SoundDirector.hpp"

SoundDirector::SoundDirector(esc::Asset<sf::SoundBuffer> & soundAssetManager)
	: soundAssets(&soundAssetManager)
{

}

SoundDirector::~SoundDirector()
{
}

void SoundDirector::playSound(const string &sfxname)
{
	if (sf::SoundBuffer * buffer = soundAssets->getResource(sfxname))
	{
		sound.setBuffer(*buffer);
		sound.play();
	}
}

void SoundDirector::setVolume(float vol)
{
	sound.setVolume(vol);
}