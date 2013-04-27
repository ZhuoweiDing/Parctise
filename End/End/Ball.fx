/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    Multi-Texturing Shader
*/

cbuffer cbChangesEveryFrame : register( b0 )
{
    matrix worldMatrix;
};

struct VS_Input
{
    float4 pos  : POSITION;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    vsOut.pos = mul( vertex.pos, worldMatrix );

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{

    return float4( 0.0f, 0.0f, 0.0f, 1.0f );
}


technique11 MultiTexture
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}