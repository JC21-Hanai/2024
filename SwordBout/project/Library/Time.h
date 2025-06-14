#pragma once

/// <summary>
/// １フレームの時間を計測する
/// 最近の20フレームの平均時間を測定し、
/// DeltaTime()で、その時間を秒で返す
/// 60フレームの場合は、0.016が返る
/// </summary>
namespace Time {
	/// <summary>
	/// 最初に１回だけ呼んでもらう
	/// 計測のための初期化をする
	/// </summary>
	void Init();

	/// <summary>
	/// 毎フレーム１回呼んでもらう
	/// WindowMessageが入った直後がベスト
	/// </summary>
	void Refresh();

	/// <summary>
	/// １フレームの経過時間を返す
	/// ただし、最大で２フレーム分の時間
	/// </summary>
	/// <returns>経過時間（秒）</returns>
	float DeltaTime();

	/// <summary>
	/// 最後に１回だけ呼んでもらう
	/// </summary>
	void Release();
};
