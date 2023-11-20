#pragma once

enum class EFx_Type
{
	Explosion,
	LandCloud,
	JumpCloud,
	DustCloud,
	Default,
};

class Fx : public GameEngineActor
{
public:
	// constrcuter destructer
	Fx();
	~Fx();

	// delete Function
	Fx(const Fx& _Other) = delete;
	Fx(Fx&& _Other) noexcept = delete;
	Fx& operator=(const Fx& _Other) = delete;
	Fx& operator=(Fx&& _Other) noexcept = delete;

	void SetFxData(EFx_Type _Type, float4 _Dir);

	EFx_Type FxType = EFx_Type::Default;

	std::string_view FxName;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FxRenderer;
	float4 Dir = float4::ZERO;
	float Speed = 100.0f;
};

