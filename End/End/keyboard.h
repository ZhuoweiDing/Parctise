#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <dinput.h>

class Keyboard
{
public:
	typedef void KeyBoardHandle(void *);

public:
	Keyboard();
	virtual ~Keyboard();

	//��ʼ�������豸
	bool Init();

	//������ע������봦��
	void Update( float dt );

	//�ͷ������豸
	void Release();

	void Register( UINT key, KeyBoardHandle * handle );

private:
	IDirectInputDevice8 * keyboardInput_;
};

Keyboard * GetKeyboard();

#endif	//end of Keyboard.h