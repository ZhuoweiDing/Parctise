#ifndef _DEMO_BASE_H_
#define _DEMO_BASE_H_

#define KEYDOWN( name , key )( name[ key ] & 0x80 )
#define BUTTONDOWN( name , key )( name.rgbButtons[ key ] & 0x80 )

#include<D3D11.h>
#include<D3DX11.h>
#include<DxErr.h>
#include<dinput.h>


class Dx11DemoBase
{
public:
	Dx11DemoBase ();
	virtual ~Dx11DemoBase ();

	bool Initialize ( HINSTANCE hInstance , HWND hwnd );
	void Shutdown();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update ( float dt ) = 0 ;
	virtual void Render() = 0 ;

	bool CompileD3DShader( char * filePath , char * entry , char * shaderModel , ID3DBlob ** buffer );

protected:
	HINSTANCE hInstance_;
	HWND hwnd_;

	D3D_DRIVER_TYPE driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11Device * d3dDevice_;
	ID3D11DeviceContext * d3dContext_;
	IDXGISwapChain * swapChain_;
	ID3D11RenderTargetView * backBufferTarget_;

	
	LPDIRECTINPUT8 directInput_;

	//KeyBoard
	LPDIRECTINPUTDEVICE8 keyboardDevice_;
	char keyboardKeys_[ 256 ];
	char prevKeyboardKeys_[ 256 ];

	//Mouse
	LPDIRECTINPUTDEVICE8 mouseDevice_;
	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevmouseState_;
	long mousePosX_;
	long mousePosY_;
	long mouseWheel_;
};


#endif