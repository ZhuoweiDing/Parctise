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

	//初始化输入设备
	bool Init();

	//更新已注册的输入处理
	void Update( float dt );

	//释放输入设备
	void Release();

	void Register( UINT key, KeyBoardHandle * handle );

private:
	IDirectInputDevice8 * keyboardInput_;
};

Keyboard * GetKeyboard();

#endif	//end of Keyboard.h