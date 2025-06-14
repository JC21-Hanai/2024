#pragma once
#include <string>

/// <summary>
/// 画像、モデル、音をロードする際、一度ロードものを、
/// 再度ロードしないように、ここで保持しておく
/// 
/// DxLibの関数名と同じにしているので、その関数の前に、
/// ResourceLoaderを書けばOK
/// 
/// ReleaseAllFile()を呼ぶと、ロードしたファイルを削除する
/// </summary>
namespace ResourceLoader {
	/// <summary>
	/// 全て初期化します
	/// 最初に１回だけ呼んでください
	/// </summary>
	void Init();

	int LoadGraph(std::string filename);
	void DeleteGraph(int handle);
	int MV1LoadModel(std::string filename);
	void MV1DeleteModel(int handle);
	int LoadSoundMem(std::string filename);
	void DeleteSoundMem(int handle);

	/// <summary>
	/// 非同期読み込みをするかを設定する
	/// </summary>
	/// <param name="async">非同期読み込みする場合true</param>
	void SetAsync(bool async);

	/// <summary>
	/// 非同期でファイルを読んでいるか
	/// </summary>
	/// <returns>ファイルを読んでいる途中はtrue</returns>
	bool IsLoading();

	/// <summary>
	/// 読んだファイルを全部消す
	/// </summary>
	void ReleaseAllFile();
};