#pragma once
#include "Core.h"
#include <d3d12.h>
#include <string>

class Texture
{
public:
	int width = 0;
	int height = 0;
	int channels = 0;
	ID3D12Resource* tex = nullptr;
	int heapOffset;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	void init(Core* core, const std::string& filename);
	void free()
	{
		if (tex)
		{
			tex->Release();
			tex = nullptr;
		}
	};
};
