#pragma once
#include "XPlatform.h"


namespace XPlatform
{
	union Vector3f
	{
		struct
		{
			float X;
			float Y;
			float Z;
		};

		float Value[3];
	};
}