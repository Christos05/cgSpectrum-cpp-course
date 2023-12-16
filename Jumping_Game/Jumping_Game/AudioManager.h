#pragma once

class AudioManager
{
public:
	void PlayJumpSound();
	void PlayLandingSound();
	void PlaySwichSideSound();
	void PlayEnteringBattle();
	void PlayExitingBattle();
	void PlayAttack();
	void PlayGuard();
	void PlayHeal();
	void PlayWinBattle();
	void PlayLooseBattle();
};