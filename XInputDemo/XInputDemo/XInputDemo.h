

#include"base.h"
#include<XInput.h>

class XInputDemo : public Dx11DemoBase
{
public:
	XInputDemo();
	virtual ~XInputDemo();

	bool LoadContent();
	void UnloadContent();

	void Update( float dt );
	void Render();

private:
	ID3D11VertexShader * customColorVS_;
	ID3D11PixelShader * customColorPS_;

	ID3D11InputLayout * inputLayout_;
	ID3D11Buffer * vertexBuffer_;

	ID3D11Buffer * colorCB_;
	int selectedColor_;

	XINPUT_STATE controller1State_;
	XINPUT_STATE prevControllerState_;

};

