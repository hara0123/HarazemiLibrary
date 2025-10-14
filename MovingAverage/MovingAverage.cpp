// 移動平均クラス
// 20241015Ver.
// 使い方
// インスタンス作成時に移動平均の点数を与える
//   MovingAverage ma(50); // 50点で移動平均
// 移動平均をかける対象データ（例：input）をAdd関数に渡せば平滑化された値が戻される。
//   double result = ma.Add(input);
// 解放作業は不要

#include "MovingAverage.h"
#include <new>

MovingAverage::MovingAverage(int n)
{
	buffer = new(std::nothrow) double[n];
	if (buffer)
	{
		for (int i = 0; i < n; i++)
			buffer[i] = 0;
	}

	this->n = n;
	mostOldIndex = 0;
	sum = 0;
}

MovingAverage::~MovingAverage()
{
	if (buffer)
		delete[] buffer;
}

double MovingAverage::Add(double data)
{
	if (buffer)
	{
		sum -= buffer[mostOldIndex];
		sum += data;

		buffer[mostOldIndex] = data;
		mostOldIndex++;
		if (mostOldIndex == n)
			mostOldIndex = 0;

		auto value = sum / n;

		return value;
	}
	else
		return 0;
}
