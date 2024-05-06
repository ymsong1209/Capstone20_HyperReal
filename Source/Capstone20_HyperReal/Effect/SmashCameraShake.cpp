// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCameraShake.h"

USmashCameraShake::USmashCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.1f;

	LocOscillation.Z.Amplitude = 10.f;
	LocOscillation.Z.Frequency = 10.f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;

	LocOscillation.Y.Amplitude = 5.f;
	LocOscillation.Y.Frequency = 5.f;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;

	bSingleInstance = true;
}
