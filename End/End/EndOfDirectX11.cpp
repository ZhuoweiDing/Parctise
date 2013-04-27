#include "EndOfDirectX11.h"

struct VertexPos
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

#define KEYDOWN( name, key ) ( name[key] & 0x80 )

EndOfDirectX11::EndOfDirectX11() : Dx11DemoBase(), effect_(0),inputLayout_(0),
	vertexBuffer_(0), indexBuffer_(0), colorMap_(0), secondMap_(0), 
	samplerState_(0), worldCB_(0), viewCB_(0), projCB_(0)
{

}

EndOfDirectX11::~EndOfDirectX11()
{
	Dx11DemoBase::Shutdown();
}

bool EndOfDirectX11::LoadContent()
{
	HRESULT result = 0;

	ID3DBlob* buffer = 0;
	ID3DBlob* vsBuffer = 0;
	ID3DBlob* psBuffer = 0;

    bool compileResult = CompileD3DShader( "MultiTexture.fx", 0, "fx_5_0", &buffer );

    if( compileResult == false )
    {
        DXTRACE_MSG( "Error compiling the effect shader!" );
        return false;
    }

	result = D3DX11CreateEffectFromMemory( buffer->GetBufferPointer( ),
        buffer->GetBufferSize( ), 0, d3dDevice_, &effect_ );

	if( FAILED(result) )
	{
		DXTRACE_MSG( "error creating the effect shader" );
		if( buffer )
		{
			buffer->Release();
		}
		return false;
	}

	buffer->Release();

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, 
			D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

	ID3DX11EffectTechnique * colorInvTechnique = 0;
	colorInvTechnique = effect_->GetTechniqueByName( "MultiTexture" );
	ID3DX11EffectPass * effectPass = colorInvTechnique->GetPassByIndex( 0 );

	D3DX11_PASS_SHADER_DESC passDesc;
	D3DX11_EFFECT_SHADER_DESC shaderDesc;
	effectPass->GetVertexShaderDesc( &passDesc );
	passDesc.pShaderVariable->GetShaderDesc( passDesc.ShaderIndex, &shaderDesc );

	result = d3dDevice_->CreateInputLayout( solidColorLayout, totalLayoutElements,
		shaderDesc.pBytecode, shaderDesc.BytecodeLength, &inputLayout_ );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error creating the input layout" );
		return false;
	}

	VertexPos vertices[] =
    {
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

    D3D11_BUFFER_DESC vertexDesc;
    ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof( VertexPos ) * 24;

    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory( &resourceData, sizeof( resourceData ) );
    resourceData.pSysMem = vertices;

    result = d3dDevice_->CreateBuffer( &vertexDesc, &resourceData, &vertexBuffer_ );

    if( FAILED( result ) )
    {
        DXTRACE_MSG( "Failed to create vertex buffer!" );
        return false;
    }

    WORD indices[] =
    {
        3,   1,  0,  2,  1,  3,
        6,   4,  5,  7,  4,  6,
        11,  9,  8, 10,  9, 11,
        14, 12, 13, 15, 12, 14,
        19, 17, 16, 18, 17, 19,
        22, 20, 21, 23, 20, 22
    };

    D3D11_BUFFER_DESC indexDesc;
    ZeroMemory( &indexDesc, sizeof( indexDesc ) );
    indexDesc.Usage = D3D11_USAGE_DEFAULT;
    indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexDesc.ByteWidth = sizeof( WORD ) * 36;
    indexDesc.CPUAccessFlags = 0;
    resourceData.pSysMem = indices;

    result = d3dDevice_->CreateBuffer( &indexDesc, &resourceData, &indexBuffer_ );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating index buffer" );
		return false;
	}

	result = D3DX11CreateShaderResourceViewFromFile( d3dDevice_, "decal.dds", 0, 0,
		&colorMap_, 0 );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating ShaderResource by decal.dds" );
		return false;
	}

	result = D3DX11CreateShaderResourceViewFromFile( d3dDevice_, "decal2.dds", 0, 0,
		&secondMap_, 0 );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating shader resource by decal2.dds" );
		return false;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = d3dDevice_->CreateSamplerState( &colorMapDesc, &samplerState_ );

	if( FAILED(result) )
	{
		return false;
	}

	D3D11_BUFFER_DESC constDesc;
	ZeroMemory( &constDesc, sizeof( constDesc ) );
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof( XMMATRIX );
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	result = d3dDevice_->CreateBuffer( &constDesc, 0, &worldCB_ );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating world constant buffer" );
		return false;
	}

	result = d3dDevice_->CreateBuffer( &constDesc, 0, &viewCB_ );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating view constant buffer" );
		return false;
	}

	result = d3dDevice_->CreateBuffer( &constDesc, 0, &projCB_ );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Error in creating project constant buffer" );
		return false;
	}

	viewMatrix_ = XMMatrixIdentity();
	projMatrix_ = XMMatrixPerspectiveFovLH( XM_PIDIV4, 800.0f / 600.0f, 
		0.01f, 100.0f );

	XMMATRIX rotationMat = XMMatrixRotationY( XM_PIDIV4 * 0.5 );
	XMMATRIX translationMat = XMMatrixTranslation( 0.0f, 0.0f, 6.0f );
	worldMat_ = rotationMat * translationMat;

	return true;
}

void EndOfDirectX11::UnloadContent()
{
	if( effect_ ) effect_->Release();
	if( inputLayout_ ) inputLayout_->Release();
	if( vertexBuffer_ ) vertexBuffer_->Release();
	if( indexBuffer_ ) indexBuffer_->Release();
	if( colorMap_ ) colorMap_->Release();
	if( secondMap_ ) secondMap_->Release();
	if( samplerState_ ) samplerState_->Release();
	if( worldCB_ ) worldCB_->Release();
	if( projCB_ ) projCB_->Release();
	if( viewCB_ ) viewCB_->Release();

	effect_ = 0;
	inputLayout_ = 0;
	vertexBuffer_ = 0;
	indexBuffer_ = 0;
	colorMap_ = 0;
	secondMap_ = 0;
	samplerState_ = 0;
	worldCB_ = 0;
	projCB_ = 0;
	viewCB_ = 0;
}

void EndOfDirectX11::Render()
{
	if( d3dContext_ == 0 )
	{
		return;
	}

	float clearColor[] = { 0.0f, 0.0f, 0.25f, 1.0f };
	d3dContext_->ClearRenderTargetView( backBufferTarget_, clearColor );
	d3dContext_->ClearDepthStencilView( depthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0 );     

	unsigned int stride = sizeof( VertexPos );
	unsigned int offset = 0;

	d3dContext_->IASetInputLayout( inputLayout_ );
	d3dContext_->IASetVertexBuffers( 0, 1, &vertexBuffer_, &stride, &offset );
	d3dContext_->IASetIndexBuffer( indexBuffer_, DXGI_FORMAT_R16_UINT, 0 );
	d3dContext_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	ID3DX11EffectShaderResourceVariable * colorMap = 0;
	colorMap = effect_->GetVariableByName( "colorMap" )->AsShaderResource();
	colorMap->SetResource( colorMap_ );

	ID3DX11EffectShaderResourceVariable* colorMap2;
    colorMap2 = effect_->GetVariableByName( "secondMap" )->AsShaderResource( );
    colorMap2->SetResource( secondMap_ );

	ID3DX11EffectSamplerVariable * samplerState = 0;
	samplerState = effect_->GetVariableByName( "colorSampler" )->AsSampler();
	samplerState->SetSampler( 0, samplerState_ );

	ID3DX11EffectMatrixVariable * worldMatrix = 0;
	worldMatrix = effect_->GetVariableByName( "worldMatrix" )->AsMatrix();
	worldMatrix->SetMatrix( ( float * )&worldMat_ );

	ID3DX11EffectMatrixVariable * viewMatrix = 0;
	viewMatrix = effect_->GetVariableByName( "viewMatrix" )->AsMatrix();
	viewMatrix->SetMatrix( ( float * )&viewMatrix_ );

	ID3DX11EffectMatrixVariable * projMatrix = 0;
	projMatrix = effect_->GetVariableByName( "projMatrix" )->AsMatrix();
	projMatrix->SetMatrix( ( float * )&projMatrix_ );

	ID3DX11EffectTechnique * colorInvTechnique = 0;
	colorInvTechnique = effect_->GetTechniqueByName( "MultiTexture" );

	D3DX11_TECHNIQUE_DESC techDesc;
	colorInvTechnique->GetDesc( &techDesc );

	for( unsigned int p = 0; p < techDesc.Passes; ++p )
	{
		ID3DX11EffectPass * pass = colorInvTechnique->GetPassByIndex( p );

		if( pass != 0 )
		{
			pass->Apply( 0, d3dContext_ );
			d3dContext_->DrawIndexed( 36, 0, 0 );
		}
	}

	swapChain_->Present( 0, 0 );
}

void EndOfDirectX11::Update( float dt )
{
	keyboardDevice_->GetDeviceState( sizeof( keyboardKeys_ ), ( LPVOID )&keyboardKeys_ );

    // Button press event.
    if( GetAsyncKeyState( VK_ESCAPE ) )
	{ 
		PostQuitMessage( 0 );
	}

	static float y = 0.0;
	static float x = 0.0;

	XMMATRIX changeX, changeY;
	XMMATRIX translationMat = XMMatrixTranslation( 0.0f, 0.0f, 6.0f );

	if( KEYDOWN( keyboardKeys_, DIK_UP ) )
	{ 
		x += 0.01;
	}

	if( KEYDOWN( keyboardKeys_, DIK_DOWN ) )
	{ 
		x -= 0.01;
	}

    // Button up event.
	if( KEYDOWN( keyboardKeys_, DIK_LEFT ) )
	{ 
		y += 0.01;
	}

    // Button up event.
	if( KEYDOWN( keyboardKeys_, DIK_RIGHT ) )
	{ 
		y -= 0.01;
	}

	changeY = XMMatrixRotationY( XM_PIDIV4 * y );
	changeX = XMMatrixRotationX( XM_PIDIV4 * x );

	worldMat_ = changeX * changeY * translationMat;

	memcpy( prevKeyboardKeys_, keyboardKeys_, sizeof( keyboardKeys_ ) );
}