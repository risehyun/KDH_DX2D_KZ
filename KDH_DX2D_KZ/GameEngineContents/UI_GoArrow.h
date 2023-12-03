#pragma once
class UI_GoArrow : public GameEngineActor
{
public:
	UI_GoArrow();
	~UI_GoArrow();

	UI_GoArrow(const UI_GoArrow& _Other) = delete;
	UI_GoArrow(UI_GoArrow&& _Other) noexcept = delete;
	UI_GoArrow& operator=(const UI_GoArrow& _Other) = delete;
	UI_GoArrow& operator=(UI_GoArrow&& _Other) noexcept = delete;


	void OnRenderer();
	void OffRenderer();

	// �� �̷��� ���� ���� ���߿� �ϳ��� ���, UI�� ���� Ŭ������ ���� �α�
	void SetGoArrowData(float4 _Dir, float4 _InitPos);
	void MovingGoArrow(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float4 Dir = float4::ZERO;
	float4 NextPos = float4::ZERO;
	float4 InitPos = float4::ZERO;

	float ArrowMoveTimer = 0.0f;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GoArrow;

};