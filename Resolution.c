#include "Resolution.h"

int ResolutionX;
int ResolutionY;

int SetResX(const int x)
{
	ResolutionX = x;
}

int SetResY(const int y)
{
	ResolutionY = y;
}

int GetResX()
{
	return ResolutionX;
}

int GetResY()
{
	return ResolutionY;
}

