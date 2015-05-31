value struct point { //структура точки
 float x, y;
};

value struct line { //структура линии
 point start, end;
 System::String^ name;
};

#define M 3 //ѕор€док матрицы (2-х мерное изображение)
typedef float vec[M]; //¬ектор размерности
typedef float mat[M][M]; //ћатрица

extern mat T; //ћатрица совмещенного преобразовани€

void times(mat a, mat b, mat c); //a*b=c
void timesMatVec(mat a, vec b, vec c); //a*b=c
void set(mat a, mat b); //a переписываем в b
void point2vec(point a, vec b); //декартовы координаты из point в в однородные координаты vec
void vec2point(vec a, point &b); //наоборот
void makeHomogenVec(float x, float y, vec c); //x и y в c
void unit(mat a); //свой аргумент в единичную матрицу
void rotate(float phi, float x, float y, mat c); //поворот
void scale(float Sx, float Sy, mat c); //масштабирование

void move(float Tx, float Ty, mat c); //T,G,F,H
void z_goriz(mat c); //U
void z_vert(mat c); //J
void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat c);




