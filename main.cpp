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

	// ベクトルの足し算
	Vector2 operator+(Vector2 other) {
		Vector2 ans;
		ans.x = x;
		ans.y = y;

		ans.x += other.x;
		ans.y += other.y;

		return ans;
	}
};

// ベクトルと行列の積を求める関数
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 result;
	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]);

	return result;
}

// 回転行列の作成関数
Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);

	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);

	return result;
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
	float width = 200.0f;
	float height = 100.0f;

	float theta = 0.0f;

	//白いテクスチャの読み込み
	int whiteTextureHandle = Novice::LoadTexture("white1x1.png");

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
		
		// 矩形を構成する4頂点を原点を中心に設定
		Vector2 leftTop = { -width / 2, -height / 2 };
		Vector2 rightTop = { width / 2, -height / 2 };
		Vector2 leftBottom = { -width / 2, height / 2 };
		Vector2 rightBottom = { width / 2,height / 2 };

		// 角度を毎フレーム増加
		theta += (3.0f * (float)M_PI) / 180.0f;

		// 回転行列を作成
		Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);

		// 4頂点を全て回転させる
		Vector2 rotatedLeftTop = Multiply(leftTop, rotateMatrix);

		Vector2 rotatedRightTop = Multiply(rightTop, rotateMatrix);

		Vector2 rotatedLeftBottom = Multiply(leftBottom, rotateMatrix);

		Vector2 rotatedRightBottom = Multiply(rightBottom, rotateMatrix);

		// 4頂点を移動させる
		Vector2 movedLeftTop = rotatedLeftTop + centerPos;

		Vector2 movedRightTop = rotatedRightTop + centerPos;

		Vector2 movedLeftBottom = rotatedLeftBottom + centerPos;

		Vector2 movedRightBottom = rotatedRightBottom + centerPos;

		// 4頂点の座標をスクリーン座標に変換
		Vector2 screenLeftTop = WorldToScreen(movedLeftTop);

		Vector2 screenRightTop = WorldToScreen(movedRightTop);

		Vector2 screenLeftBottom = WorldToScreen(movedLeftBottom);

		Vector2 screenRightBottom = WorldToScreen(movedRightBottom);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 矩形の描画
		Novice::DrawQuad(
			static_cast<int>(screenLeftTop.x), static_cast<int>(screenLeftTop.y),
			static_cast<int>(screenRightTop.x), static_cast<int>(screenRightTop.y),
			static_cast<int>(screenLeftBottom.x), static_cast<int>(screenLeftBottom.y),
			static_cast<int>(screenRightBottom.x), static_cast<int>(screenRightBottom.y),
			0, 0,
			static_cast<int>(width), static_cast<int>(height),
			whiteTextureHandle,
			0xFFFFFFFF
		);

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
