#include "Wave.h"
#include "../Manager/ResourceMgr.h"

Wave::Wave()
{
	shader.loadFromFile("Shader/wave.frag", Shader::Fragment);

	distortionMap = *RESOURCEMGR->GetTexture("Graphics/Shader/distortion_map.png");
	distortionMap.setRepeated(true);
	distortionMap.setSmooth(true);

	shader.setParameter("currentTexture", Shader::CurrentTexture);
	shader.setParameter("distortionMapTexture", distortionMap);
}

void Wave::Update(float dt)
{
	shader.setParameter("time", time += dt);
	shader.setParameter("distortionFactor", distortionFactor);
	shader.setParameter("riseFactor", riseFactor);
}
