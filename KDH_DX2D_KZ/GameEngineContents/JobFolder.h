#pragma once
#include <GameEngineCore/GameEngineActor.h>

class JobFolder : public GameEngineActor
{
public:
	// constrcuter destructer
	JobFolder();
	~JobFolder();

	// delete Function
	JobFolder(const JobFolder& _Other) = delete;
	JobFolder(JobFolder&& _Other) noexcept = delete;
	JobFolder& operator=(const JobFolder& _Other) = delete;
	JobFolder& operator=(JobFolder&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> JobFolderFrontRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> JobFolderAllRenderer;
};

