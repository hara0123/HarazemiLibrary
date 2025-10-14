// 移動平均クラス
// 20241015Ver.
// 使い方
// インスタンス作成時に移動平均の点数を与える
//   MovingAverage ma(50); // 50点で移動平均
// 移動平均をかける対象データ（例：input）をAdd関数に渡せば平滑化された値が戻される。
//   double result = ma.Add(input);
// 解放作業は不要

#ifndef __MOVINGAVERAGE_H_
#define __MOVINGAVERAGE_H_

class MovingAverage
{
	double* buffer;
	double sum;
	int n;
	int mostOldIndex;
public:
	MovingAverage(int n);
	~MovingAverage();

	bool CheckBuffer() { return buffer ? true : false; };
	int GetN() { return n; };
	double Add(double data);
};

#endif
