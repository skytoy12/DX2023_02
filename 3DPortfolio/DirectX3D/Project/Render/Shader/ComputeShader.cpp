#include "Framework.h"
#include "ComputeShader.h"

ComputeShader::ComputeShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "cs_5_0",
        flags,
        0,
        &blob,
        nullptr
    );

    DEVICE->CreateComputeShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
}

ComputeShader::~ComputeShader()
{
    shader->Release();
}

void ComputeShader::SetShader()
{
    DC->CSSetShader(shader, nullptr, 0);
}
