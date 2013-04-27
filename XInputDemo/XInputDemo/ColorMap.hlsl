cbuffer cbChangesPerFrame : register( b0 )
{
	float4 col;
};

float4 VS_Main( float4 Pos : POSITION ) : SV_POSITION
{
	return Pos;
}

float4 PS_Main( float4 Pos : SV_POSITION ) : SV_TARGET
{
	return col;
}