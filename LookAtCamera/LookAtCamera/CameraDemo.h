#ifndef _CAMERA_DEMO_H_
#define _CAMERA_DEMO_H_

#include"base.h"
#include"LookAtCamera.h"

class CameraDemo : public Dx11DemoBase
{
public:
	CameraDemo();
	virtual ~CameraDemo();

	bool LoadContent();
	void UnloadContent();

	void Update( float dt );
	void Render();

private:
	ID3D11VertexShader * solidColorVS_;
	ID3D11PixelShader * solidColorPS_;

	ID3D11InputLayout * inputLayout_;
	ID3D11Buffer * vertexBuffer_;
	ID3D11Buffer * indexBuffer_;

	ID3D11ShaderResourceView * colorMap_;
	ID3D11SamplerState * colorMapSampler_;

	ID3D11Buffer * viewCB_;
	ID3D11Buffer * projCB_;
	ID3D11Buffer * worldCB_;
	
	XMMATRIX projMatrix_;
	LookAtCamera camera_;



};


#endif