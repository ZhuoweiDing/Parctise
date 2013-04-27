/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    Multi-Texturing Shader
*/


Texture2D colorMap : register( t0 );
Texture2D secondMap : register( t1 );
SamplerState colorSampler : register( s0 );


cbuffer cbChangesEveryFrame : register( b0 )
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register( b1 )
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register( b2 )
{
    matrix projMatrix;
};


struct VS_Input
{
    float4 Pos  : POSITION;
    float2 Tex0 : TEXTURE0;
};

struct PS_Input
{
    float4 Pos  : SV_POSITION;
    float2 Tex0 : TEXTURE0;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    vsOut.Pos = mul( vertex.Pos, worldMatrix );
    vsOut.Pos = mul( vsOut.Pos, viewMatrix );
    vsOut.Pos = mul( vsOut.Pos, projMatrix );
    vsOut.Tex0 = vertex.Tex0;

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
    float4 col = colorMap.Sample( colorSampler, frag.Tex0 );
    float4 col2 = secondMap.Sample( colorSampler, frag.Tex0 );

    return col * col2;
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