#pragma once

namespace GameEngineDebug
{
	void DrawBox2D(const GameEngineTransform& _Trans, class GameEngineCamera* _Camera = nullptr);

	void DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, class GameEngineCamera* _Camera = nullptr);

	class GameEngineDebugCore
	{
		friend class GameEngineLevel;
		// 함수도 friend걸수 있습니다.
		friend void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, GameEngineCamera* _Camera);

	private:
		static class GameEngineLevel* CurLevel;

		static void DebugInit();
		static void DebugRender();
	};
}
