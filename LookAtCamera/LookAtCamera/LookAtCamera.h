#ifndef _LOOK_AT_CAMERA_H_
#define _LOOK_AT_CAMERA_H_

#include<xnamath.h>

class LookAtCamera
{
public:
	LookAtCamera();
	LookAtCamera( XMFLOAT3 pos , XMFLOAT3 target );
	~LookAtCamera();

	void SetPositions( XMFLOAT3 pos , XMFLOAT3 target );
	XMMATRIX GetViewMatrix();

private:
	XMFLOAT3 position_;
	XMFLOAT3 target_;
	XMFLOAT3 up_;
};


#endif