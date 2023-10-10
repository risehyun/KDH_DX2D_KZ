#pragma once

class UI_NowPlayingSong : public GameEngineActor
{
public:
	UI_NowPlayingSong();
	~UI_NowPlayingSong();

	UI_NowPlayingSong(const UI_NowPlayingSong& _Other) = delete;
	UI_NowPlayingSong(UI_NowPlayingSong&& _Other) noexcept = delete;
	UI_NowPlayingSong& operator=(const UI_NowPlayingSong& _Other) = delete;
	UI_NowPlayingSong& operator=(UI_NowPlayingSong&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_SongTitleBackGround;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_SongTitle;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_SongTitleLine;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_NowPlayingText_Cyan;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_NowPlayingText_Magenta;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_NowPlayingText_All;
};