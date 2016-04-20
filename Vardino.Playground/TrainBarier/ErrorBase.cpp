//
//
//

#include "ErrorBase.h"

bool ErrorBaseClass::InError()
{
	return this->inError;
}

String ErrorBaseClass::GetErrorText()
{
	return this->errorText;
}

void ErrorBaseClass::ClearErrr()
{
	this->errorText = "";
	this->inError = false;
}

void ErrorBaseClass::SetError(String errorText)
{
	this->errorText = errorText;
	this->inError = true;
}