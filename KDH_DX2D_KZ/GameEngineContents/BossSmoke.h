#pragma once
class BossSmoke : public GameEngineActor
{
public:
	// constrcuter destructer
	BossSmoke();
	~BossSmoke();

	// delete Function
	BossSmoke(const BossSmoke& _Other) = delete;
	BossSmoke(BossSmoke&& _Other) noexcept = delete;
	BossSmoke& operator=(const BossSmoke& _Other) = delete;
	BossSmoke& operator=(BossSmoke&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

