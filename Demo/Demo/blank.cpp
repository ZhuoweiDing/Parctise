#include"blank.h"

BlankDemo::BlankDemo()
{

}

BlankDemo::~BlankDemo()
{

}

bool BlankDemo::LoadContent()
{
	return true;
}

void BlankDemo::Render()
{
	if( d3dContext_ == 0 )
	{
		return ;
	}


	//�����ǰ��Ļ�������µ���Ļ
	float clearColor[4] = { 0.0f , 0.0f , 0.65f , 1.0f };
	d3dContext_->ClearRenderTargetView( backBufferTarget_ , clearColor );

	swapChain_->Present( 0 , 0 );
}

void BlankDemo::UnloadContent()
{

}

void BlankDemo::Update( float dt )
{

}