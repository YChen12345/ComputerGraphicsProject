#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <cstdio>

void Texture::init(Core* core, const std::string& filename)
{
    // ====================== 1. Use stb_image load file ======================
    unsigned char* texels = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!texels)
    {
        char buf[512];
        sprintf_s(buf, "Texture::init - FAILED to load image [%s]\n", filename.c_str());
        OutputDebugStringA(buf);

        width = height = channels = 0;
        tex = nullptr;
        return;
    }
    // GPU-- RGBA 8-bit
    unsigned char* srcData = nullptr;
    int srcChannels = channels;
    if (channels == 3)
    {
        srcChannels = 4;
        unsigned char* texelsWithAlpha = new unsigned char[width * height * srcChannels];
        for (int i = 0; i < (width * height); i++)
        {
            texelsWithAlpha[i * 4 + 0] = texels[i * 3 + 0];
            texelsWithAlpha[i * 4 + 1] = texels[i * 3 + 1];
            texelsWithAlpha[i * 4 + 2] = texels[i * 3 + 2];
            texelsWithAlpha[i * 4 + 3] = 255;
        }
        srcData = texelsWithAlpha;
    }
    else
    {
        srcData = texels;
    }
    channels = srcChannels;
    format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

    // ====================== 2. Create GPU texture resources ======================
    D3D12_HEAP_PROPERTIES heapDesc = {};
    heapDesc.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.MipLevels = 1;
    textureDesc.Format = format;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    HRESULT hr = core->device->CreateCommittedResource(
        &heapDesc,
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&tex));
    if (FAILED(hr))
    {
        char buf[512];
        sprintf_s(buf, "Texture::init - CreateCommittedResource FAILED for [%s], hr=0x%08X\n",
            filename.c_str(), (unsigned int)hr);
        OutputDebugStringA(buf);

        if (channels == 4 && srcData != texels)
            delete[] srcData;

        stbi_image_free(texels);
        tex = nullptr;
        return;
    }

    // ====================== 3. GetCopyableFootprints & Align the line width ======================
    D3D12_RESOURCE_DESC desc = tex->GetDesc();
    unsigned long long size = 0;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
    core->device->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, nullptr, nullptr, &size);

    unsigned int rowSize = width * channels;
    unsigned int alignedWidth = ((width * channels) + 255) & ~255u;

    std::vector<unsigned char> uploadData(alignedWidth * height);
    for (int y = 0; y < height; ++y)
    {
        unsigned char* dstRow = uploadData.data() + y * alignedWidth;
        unsigned char* srcRow = srcData + y * rowSize;
        memcpy(dstRow, srcRow, rowSize);
    }
    core->uploadResource(tex, uploadData.data(), alignedWidth * height,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &footprint);

    // ====================== 5.SRV Heap: Create Shader Resource View ======================
    D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = core->srvHeap.getNextCPUHandle();
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    core->device->CreateShaderResourceView(tex, &srvDesc, srvHandle);
    heapOffset = core->srvHeap.used - 1;

    // ====================== 6. Delete CPU data ======================
    if (channels == 4 && srcData != texels)
    {
        delete[] srcData;
    }
    stbi_image_free(texels);

    char buf[512];
    sprintf_s(buf, "Texture::init - SUCCESS [%s], %dx%d, channels=%d, heapOffset=%d\n",
        filename.c_str(), width, height, channels, heapOffset);
    //OutputDebugStringA(buf);
}