#ifndef __ENDOFDIRECTX11_H__
#define __ENDOFDIRECTX11_H__

#include "base.h"
#include <d3dx11effect.h>
#include <xnamath.h>

class EndOfDirectX11 : public Dx11DemoBase
{
public:
	EndOfDirectX11();
	virtual ~EndOfDirectX11();

	bool LoadContent();
	void UnloadContent();

	void Render();
	void Update( float dt );
private:
	ID3DX11Effect * effect_;
	ID3D11InputLayout * inputLayout_;

	ID3D11Buffer * vertexBuffer_;
	ID3D11Buffer * indexBuffer_;

	ID3D11ShaderResourceView * colorMap_;
	ID3D11ShaderResourceView * secondMap_;
	ID3D11SamplerState * samplerState_;

	ID3D11Buffer * worldCB_;
	ID3D11Buffer * viewCB_;
	ID3D11Buffer * projCB_;

	XMMATRIX viewMatrix_;
	XMMATRIX projMatrix_;
	XMMATRIX worldMat_;

};

#endif	//end of EndOfDirectX11.h