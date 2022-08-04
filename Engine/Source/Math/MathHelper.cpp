#include <Core.h>
#include "MathHelper.h"

namespace STL
{
	float MathHelper::Lerpf(float a, float b, float alpha)
	{
		alpha = std::clamp(alpha, 0.0f, 1.0f);
		return (1 - alpha) * a + alpha * b;
	}
}