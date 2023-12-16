#include <windows.h>
#include "AudioManager.h"

void AudioManager::PlayJumpSound()
{
	Beep(4000, 30);
}

void AudioManager::PlayLandingSound()
{
	Beep(2000, 20);
}

void AudioManager::PlaySwichSideSound()
{
	Beep(1500, 20);
}

void AudioManager::PlayEnteringBattle()
{
	Beep(300, 20);
	Beep(800, 25);
}

void AudioManager::PlayExitingBattle()
{
	Beep(800, 20);
	Beep(300, 25);
}

void AudioManager::PlayAttack()
{
	Beep(1000, 50);
	Beep(2000, 50);
}

void AudioManager::PlayGuard()
{
	Beep(1000, 25);
	Beep(300, 40);
}

void AudioManager::PlayHeal()
{
	Beep(1500, 20);
	Beep(400, 20);
	Beep(1500, 20);
	Beep(400, 20);
}

void AudioManager::PlayWinBattle()
{
	Beep(400, 20);
	Beep(400, 20);
	Beep(1500, 20);
	Beep(1500, 20);
}

void AudioManager::PlayLooseBattle()
{
	Beep(800, 20);
	Beep(600, 20);
	Beep(400, 20);
	Beep(200, 20);
}