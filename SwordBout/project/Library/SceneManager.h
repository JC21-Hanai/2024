#pragma once
/// <summary>
/// シーンの切り替えを管理するクラス
/// 実際のシーンの作成部分は、SceneFactoryに書いてください
/// </summary>
/// <author>N.Hanai</author>
#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// 現在のシーンを呼び出している。
/// Sceneを切り替える時は、ChangeScene()を呼び出せばよく、
/// 呼んだ時に切り替えるのではなく、次回のUpdate()で切り替えるようにしている。
/// </summary>
namespace SceneManager
{
	void Init(); // 初期化
	void Update(); // 更新
	void Draw(); // 描画
	void Release(); // 開放

	/// <summary>
	/// シーンを切り替える。
	/// 直接ここでは切り替えず、次回Update()が呼ばれたとき、Scene処理を呼ぶ前に切り替えます。
	/// シーンの名前とクラスの関係は、SceneFactory()に記述してください。
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	void ChangeScene(const std::string& sceneName);

	/// <summary>
	/// 現在のシーンを返す
	/// SceneBase*で返すので、適宜キャストして使います
	/// </summary>
	/// <returns>現在のシーン</returns>
	SceneBase* CurrentScene();

	/// <summary>
	/// アプリを終了する
	/// </summary>
	void Exit();

	/// <summary>
	/// アプリを終了しようとしているかを判定する
	/// </summary>
	/// <returns>終了しようとしている場合にtrue</returns>
	bool IsExit();
};

template<class C>
C* GetScene() {
	return dynamic_cast<C*>(SceneManager::CurrentScene());
}