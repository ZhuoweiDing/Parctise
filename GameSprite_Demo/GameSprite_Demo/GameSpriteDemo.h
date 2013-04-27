#include"base.h"
#include"GameSprite.h"

class GameSpriteDemo : public Dx11DemoBase
{
public:
	GameSpriteDemo();
	virtual ~GameSpriteDemo();

	bool LoadContent();
	void UnloadContent();

	void Update( float dt );
	void Render();


private:
	ID3D11VertexShader * solidColorVS_;
	ID3D11PixelShader * solidColorPS_;

	ID3D11InputLayout * inputLayout_;
	ID3D11Buffer * vertexBuffer_;

	ID3D11ShaderResourceView * colorMap_;
	ID3D11SamplerState * colorMapSampler_;
	ID3D11BlendState * alphaBlendState_;

	GameSprite sprites_[ 2 ];
	ID3D11Buffer * mvpCB_;
	XMMATRIX vpMatrix_;

};
