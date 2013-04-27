Texture2D colorMap_ : register( t0 );
SamplerState colorSampler_ : register( s0 );


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
	float4 Pos : POSITION;
	float2 Tex0 : TEXCOORD0;
} ;

struct PS_Input
{
	float4 Pos : SV_POSITION;
	float2 Tex0 : TEXCOORD0;
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
	return colorMap_.Sample( colorSampler_ , frag.Tex0 );
}
