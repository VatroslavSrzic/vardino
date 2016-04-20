// ErrorBase.h

#ifndef _ERRORBASE_h
#define _ERRORBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class ErrorBaseClass
{
public:
	bool InError();
	String GetErrorText();

protected:
	void ClearErrr();
	void SetError(String errorText);

private:
	bool inError = false;
	String errorText = "";
};

#endif
