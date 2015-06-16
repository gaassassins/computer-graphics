#pragma once
#include "stdafx.h"
#include <algorithm>
#include "Transform.h"

using namespace std;

void Clip1Left(point &a, float dx, float dy, float dxL) { //отсечение начальной точки левой границей
	a.x += dxL;
	a.y += dxL * (dy / dx);
}

void Clip1Top(point &a, float dx, float dy, float dyT) { //отсечение начальной точкой верхней границей
	a.x += dyT * (dx / dy);
	a.y += dyT;
}

void Clip1Bottom(point &a, float dx, float dy, float dyB) {//отсечение начальной точкой нижней границей
	a.x += dyB * (dx / dy);
	a.y += dyB;
}

void Clip2Right(point a, point &b, float dx, float dy, float dxR) {//отсечение конечной точкой правой границей
	b.x = a.x + dxR;
	b.y = a.y + dxR * (dy / dx);
}

void Clip2Top(point a, point &b, float dx, float dy, float dyT) {//отсечение конечной точкой верхней границей
	b.x = a.x + dyT * (dx / dy);
	b.y = a.y + dyT;
}

void Clip2Bottom(point a, point &b, float dx, float dy, float dyB) {//отсечение конечной точкой нижней границей
	b.x = a.x + dyB * (dx / dy);
	b.y = a.y + dyB;
}

bool clip(point &a, point &b, point min, point max) { //сам алгоритм отсечения
	if(a.x > b.x) { //просто меняем местами значения x1 с x2 и y1 с y2
		swap(a, b);
	}
	
	int C1 = 0;
	int C2 = 0;

	if(a.x < min.x) C1++; //c1 увеличить на 1
	if(a.x > max.x) C1 += 2; //c1 увеличить на 2
	if(a.y < min.y) C1 += 4; //c1 увеличить на 4
	if(a.y > max.y) C1 += 8; //c1 увеличить на 8
		
	if(b.x < min.x) C2++; //c2 увеличить на 1
	if(b.x > max.x) C2 += 2; //c2 увеличить на 2
	if(b.y < min.y) C2 += 4; //c2 увеличить на 4
	if(b.y > max.y) C2 += 8; //c2 увеличить на 8

	if(C1 & C2) 
		return false;

	if(C1 == 0) {
		if(C2 == 0)
			return true;

		float dx = b.x - a.x;
		float dy = b.y - a.y;

		if(dy >= 0) {
			float dxR = max.x - a.x;
			float dyT = max.y - a.y;

			if(dy * dxR < dx * dyT)
				Clip2Right(a, b, dx, dy, dxR);
			else
				Clip2Top(a, b, dx, dy, dyT);
			return true;

		} 

		else {
			float dxR = max.x - a.x;
			float dyB = min.y - a.y;

			if(dy * dxR < dx * dyB)
				Clip2Bottom(a, b, dx, dy, dyB);
			else
				Clip2Right(a, b, dx, dy, dxR);
			return true;
		}
	} 
	else if(C1 == 1) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dxL = min.x - a.x;
		float dyT = max.y - a.y;

		if(C2 == 0) {
			Clip1Left(a, dx, dy, dxL);
			return true;
		}

		if(dy >= 0) {
			if(dy * dxL > dx * dyT)
				return false;

			float dxR = max.x - a.x;
			float dyT = max.y - a.y;

			if(dy * dxR < dx * dyT)
				Clip2Right(a, b, dx, dy, dxR);
			else
				Clip2Top(a, b, dx, dy, dyT);

			dx = b.x - a.x;
			dy = b.y - a.y;
			dxL = min.x - a.x;
			Clip1Left(a, dx, dy, dxL);
			return true;
		} else {
			float dxL = min.x - a.x;
			float dyB = min.y - a.y;

			if(dy * dxL < dx * dyB)
				return false;

			float dxR = max.x - a.x;
			dyB = min.y - a.y;

			if(dy * dxR < dx * dyB)
				Clip2Bottom(a, b, dx, dy, dyB);
			else
				Clip2Right(a, b, dx, dy, dxR);

			dx = b.x - a.x;
			dy = b.y - a.y;
			dxL = min.x - a.x;
			Clip1Left(a, dx, dy, dxL);
			return true;
		}
	} 
	else if(C1 == 4) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dxR = max.x - a.x;
		float dyB = min.y - a.y;

		if(C2 == 0) {
			Clip1Bottom(a, dx, dy, dyB);
			return true;
		}

		if(dy > 0) {
			if(dy * dxR < dx * dyB)
				return false;

			float dyT = max.y - a.y;
			if(dy * dxR < dx * dyT)
				Clip2Right(a, b, dx, dy, dxR);
			else
				Clip2Top(a, b, dx, dy, dyT);

			dx = b.x - a.x;
			dy = b.y - a.y;
			dyB = min.y - a.y;
			Clip1Bottom(a, dx, dy, dyB);
			return true;
		} else {
			return false;
		}
	} else if(C1 == 5) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;

		if(dy > 0) {
			float dxL = min.x - a.x;
			float dyT = max.y - a.y;

			if(dy * dxL > dx * dyT)
				return false;
			
			float dxR = max.x - a.x;
			float dyB = min.y - a.y;
			
			if(dy * dxR < dx * dyB)
				return false;

			if(dyB * dxR < dxL * dyT) {
				if(dy * dxL < dx * dyB) {
					Clip1Bottom(a, dx, dy, dyB);

					if(b.x > max.x) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dxR = max.x - a.x;
						Clip2Right(a, b, dx, dy, dxR);
					}
					return true;
				}

				Clip1Left(a, dx, dy, dxL);

				if(C2 == 0)
					return true;

				if(dy * dxR < dx * dyT && C2 != 0) {
					dx = b.x - a.x;
					dy = b.y - a.y;
					dxR = max.x - a.x;
					Clip2Right(a, b, dx, dy, dxR);
					return true;
				}

				dx = b.x - a.x;
				dy = b.y - a.y;
				dyT = max.y - a.y;
				Clip2Top(a, b, dx, dy, dyT);
				return true;
			} else {
				if(dy * dxR < dx * dyT) {
					Clip1Bottom(a, dx, dy, dyB);

					if(b.x > max.x) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dxR = max.x - a.x;
						Clip2Right(a, b, dx, dy, dxR);
					}

					return true;
				}

				if(dy * dxL < dx * dyB) {
					Clip1Bottom(a, dx, dy, dyB);

					if(C2 != 0) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dyT = max.y - a.y;
						Clip2Top(a, b, dx, dy, dyT);
					}
					
					return true;
				}

				Clip1Left(a, dx, dy, dxL);

				if(C2 == 0)
					return true;
				
				dx = b.x - a.x;
				dy = b.y - a.y;
				dyT = max.y - a.y;
				Clip2Top(a, b, dx, dy, dyT);
				return true;
			}
		} else {
			return false;
		}
	} else if(C1 == 8) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dxR = max.x - a.x;
		float dyT = max.y - a.y;

		if(C2 == 0) {
			Clip1Top(a, dx, dy, dyT);
			return true;
		}

		if(dy < 0) {
			if(dy * dxR > dx * dyT)
				return false;

			float dyB = min.y - a.y;

			if(dy * dxR > dx * dyB)
				Clip2Right(a, b, dx, dy, dxR);
			else
				Clip2Bottom(a, b, dx, dy, dyB);

			dx = b.x - a.x;
			dy = b.y - a.y;
			dyT = max.y - a.y;
			Clip1Top(a, dx, dy, dyT);
			return true;
		} else {
			return false;
		}
	} else if(C1 == 9) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;

		if(dy < 0) {
			float dxR = max.x - a.x;
			float dyT = max.y - a.y;

			if(dy * dxR > dx * dyT)
				return false;

			float dxL = min.x - a.x;
			float dyB = min.y - a.y;

			if(dy * dxL < dx * dyB)
				return false;

			if(dyT * dxR > dxL * dyB) {
				if(dy * dxL > dx * dyT) {
					Clip1Top(a, dx, dy, dyT);

					if(b.x > max.x) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dxR = max.x - a.x;
						Clip2Right(a, b, dx, dy, dxR);
					}

					return true;
				}

				Clip1Left(a, dx, dy, dxL);

				if(C2 == 0)
					return true;

				if(dy * dxR > dx * dyB) {
					dx = b.x - a.x;
					dy = b.y - a.y;
					dxR = max.x - a.x;
					Clip2Right(a, b, dx, dy, dxR);
					return true;
				}

				dx = b.x - a.x;
				dy = b.y - a.y;
				dyB = min.y - a.y;
				Clip2Bottom(a, b, dx, dy, dyB);
				return true;
			} else {
				if(dy * dxR > dx * dyB) {
					Clip1Top(a, dx, dy, dyT);

					if(b.x > max.x) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dxR = max.x - a.x;
						Clip2Right(a, b, dx, dy, dxR);
					}
					return true;
				}

				if(dy * dxL > dx * dyT) {
					Clip1Top(a, dx, dy, dyT);

					if(C2 != 0) {
						dx = b.x - a.x;
						dy = b.y - a.y;
						dyB = min.y - a.y;
						Clip2Bottom(a, b, dx, dy, dyB);
					}

					return true;
				}

				Clip1Left(a, dx, dy, dxL);
				
				if(C2 != 0) {
					dx = b.x - a.x;
					dy = b.y - a.y;
					dyB = min.y - a.y;
					Clip2Bottom(a, b, dx, dy, dyB);
				}
				return true;
			}
		} else {
			return false;
		}
	}
}










