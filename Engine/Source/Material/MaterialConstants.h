#pragma once

#include <Core/Core.h>
#include <Math/Vector3f.h>

namespace STL
{
	struct MaterialData
	{
		MaterialData()
			: shiness(32.0f), padding()
		{
		}

		float shiness;
		Vector3f padding;
	};

	struct RimData
	{
		RimData()
			: color(1.0f, 1.0f, 1.0f), constant(3.0f)
		{
		}

		Vector3f color;
		float constant;
	};
}