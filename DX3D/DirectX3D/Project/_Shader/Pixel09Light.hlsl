#include "Header.hlsli"



float4 main(LightVertexOutput input) : SV_TARGET
{
    LightMaterial material = GetLightMaterial(input);

    float4 ambient = CalculateAmbient(material);
    float4 color = CalculateLight(material);
    
    return ambient + color + mEmissive;
}