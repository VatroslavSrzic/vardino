#ifndef _BARRIERSTATE_h
#define _BARRIERSTATE_h

enum BarrierState
{
	Unknown = 0,
	Initializing,
	Off,
	OnAndClosed,
	OnAndOpen,
	InError,
};

#endif