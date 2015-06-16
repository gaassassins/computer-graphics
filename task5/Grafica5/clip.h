value struct point;

bool clip (point &a, point &b, point min, point max);

point Clip1Left(point &a, float dx, float dy, float dxL);
point Clip1Top(point &a, float dx, float dy, float dyT);
point Clip2Right(point a, point &b, float dx, float dy, float dxR);
point Clip2Top(point a, point &b, float dx, float dy, float dyT);
point Clip1Bottom(point &a, float dx, float dy, float dyB);
point Clip2Bottom(point a, point &b, float dx, float dy, float dyB);