#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1A_18_ナカヌマカツシ_タイトル";

// 2x2の行列を表す
struct Matrix2x2 {
	float m[2][2];
};

// 2次元ベクトルを表す
struct Vector2 {
	float x;
	float y;
};

// 行列の積を求める関数
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.m[0][0] = (matrix1.m[0][0] * matrix2.m[0][0]) + (matrix1.m[0][1] * matrix2.m[1][0]);
	result.m[0][1] = (matrix1.m[0][0] * matrix2.m[0][1]) + (matrix1.m[0][1] * matrix2.m[1][1]);

	result.m[1][0] = (matrix1.m[1][0] * matrix2.m[0][0]) + (matrix1.m[1][1] * matrix2.m[1][0]);
	result.m[1][1] = (matrix1.m[1][0] * matrix2.m[0][1]) + (matrix1.m[1][1] * matrix2.m[1][1]);

	return result;
}

// 回転行列の作成関数
Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);

	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cos(theta);
}

// 座標変換を行う関数
Vector2 WorldToScreen(Vector2 world) {
	Vector2 screen{
		world.x,
		500 - world.y
	};
	return screen;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 矩形の情報
	Vector2 centerPos = { 400.0f,100.0f };
	float width = 100.0f;
	float height = 200.0f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// 矩形を構成する4頂点
		Vector2 leftTop = { centerPos.x - width / 2,centerPos.y - height / 2 };
		Vector2 rightTop = { centerPos.x + width / 2,centerPos.y - height / 2 };
		Vector2 leftBottom = { centerPos.x - width / 2,centerPos.y + height / 2 };
		Vector2 rightBottom = { centerPos.x + width / 2,centerPos.y + height / 2 };

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
