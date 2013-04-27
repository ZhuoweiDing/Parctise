#include<Windows.h>
#include<memory>
#include"ColorInversionDemo.h"

LRESULT CALLBACK WndProc ( HWND hwnd , UINT message , WPARAM wParam , LPARAM lParam  );

int WINAPI wWinMain ( HINSTANCE hInstance , HINSTANCE prevInstance , LPWSTR cmdLine , int cmdShow )
{
	UNREFERENCED_PARAMETER ( prevInstance );
	UNREFERENCED_PARAMETER ( cmdLine );

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof ( WNDCLASSEX );
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor ( NULL , IDC_ARROW );
	wndClass.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "DX11BookWindowClass";
	
	if( !RegisterClassEx( &wndClass ))
	{
		return -1;
	}

	RECT rc = { 0 , 0 , 640 , 480 };
	AdjustWindowRect( &rc , WS_OVERLAPPEDWINDOW , FALSE );

	HWND hwnd = CreateWindowEx ( WS_EX_OVERLAPPEDWINDOW, "DX11BookWindowClass" , "Blank Direct3D 11 Window" , WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT , CW_USEDEFAULT , rc.right - rc.left , rc.bottom - rc.top , NULL , NULL , hInstance , NULL );

/*
	HWND hwnd = CreateWindowA ( "DX11BookWindowClass" , "Blank Direct 3D 11 Window" , WS_OVERLAPPEDWINDOW , CW_USEDEFAULT , CW_USEDEFAULT , rc.right - rc.left , 
		rc.bottom - rc.top , NULL , NULL , hInstance , NULL );
*/


	if( !hwnd )
		return -1;

	ShowWindow( hwnd , cmdShow );

	std :: auto_ptr< Dx11DemoBase >demo ( new ColorInversionDemo());


	//Demo Initialize
	bool result = demo ->Initialize ( hInstance , hwnd );

	//Error reporting if there is an issue 
	if( result == false )
		return -1;
	MSG msg = { 0 };

	while ( msg.message != WM_QUIT )
	{
		if( PeekMessage ( &msg , 0 , 0 , 0 , PM_REMOVE ))
		{
			TranslateMessage( & msg );
			DispatchMessage ( & msg );
		}
		else 
		{
			//Update and draw
			demo ->Update (0.0f);
			demo ->Render ( );
		}
	}

	//demo shutdown
	demo ->Shutdown( );

	return static_cast<int>( msg.wParam );


}


LRESULT CALLBACK WndProc( HWND hwnd , UINT message , WPARAM wParam , LPARAM lParam )
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch ( message )
	{
	case WM_PAINT:
		hDC = BeginPaint ( hwnd , &paintStruct );
		EndPaint ( hwnd , &paintStruct );
		break;

	case WM_DESTROY:
		PostQuitMessage ( 0 );
		break;

	default:
		return DefWindowProc ( hwnd , message , wParam , lParam );
		break;
	}

	return 0;
}