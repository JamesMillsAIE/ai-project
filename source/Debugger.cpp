#include "Debugger.h"

#include <raylib.h>

#include "Utility/Config.h"

Debugger& Debugger::Instance()
{
	static Debugger debugger;

	return debugger;
}

void Debugger::Initialise(Config* config)
{
	m_debugKey     = config->Get<int32>("debugger.enableKey");
	m_sphereSlices = config->Get<int32>("debugger.spheres.slices");
	m_sphereRings  = config->Get<int32>("debugger.spheres.rings");
}

void Debugger::DrawDebugCapsule(const vec3 location, const vec3 up, const float halfHeight, const float radius,
                                const Color color) const
{
	if (!m_enabled)
	{
		return;
	}

	const Vector3 startLocation = ToRaylib(location + up * halfHeight);
	const Vector3 endLocation   = ToRaylib(location - up * halfHeight);

	DrawCapsule(startLocation, endLocation, radius, m_sphereSlices, m_sphereRings, color);
}

void Debugger::TickEnabledFlag()
{
	if (IsKeyPressed(m_debugKey))
	{
		m_enabled = !m_enabled;
	}
}
