#pragma once
#include "../Library/myDxLib.h"

/// <summary>
/// 3Dの変形パラメーター
/// </summary>
struct Transform {
public:
	VECTOR3 position; // 位置
	VECTOR3 rotation; // 軸ごとの回転
	VECTOR3 scale; // 軸ごとの拡縮

	Transform() {
		position = VZero;
		rotation = VZero;
		scale = VECTOR3(1.0f, 1.0f, 1.0f);
		rotMatrix = MGetIdent();
		localMatrix = MGetIdent();
	}
	~Transform() {}

	/// <summary>
	/// 位置・回転・拡縮を使った行列を求める
	/// </summary>
	/// <returns>計算結果</returns>
	const MATRIX& MakeLocalMatrix();

	/// <summary>
	/// 位置・回転・拡縮を使った行列を返す
	/// ここでは計算していなくて、MakeLocalMatrix()で計算した時の値を使う
	/// </summary>
	/// <returns>変形行列</returns>
	const MATRIX& GetLocalMatrix() const { return localMatrix; }

	/// <summary>
	/// 回転と拡縮を使った行列を返す
	/// 位置は含まないので、主にベクトルの計算で使う
	/// ここでは計算していなくて、MakeLocalMatrix()内で計算した時の値を使う
	/// </summary>
	/// <returns>回転行列</returns>
	const MATRIX& GetRotationMatrix() const { return rotMatrix; }
private:
	MATRIX rotMatrix;
	MATRIX localMatrix;
};