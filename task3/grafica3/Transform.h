value struct point { //��������� �����
 float x, y;
};

value struct line { //��������� �����
 point start, end;
 System::String^ name;
};

#define M 3 //������� ������� (2-� ������ �����������)
typedef float vec[M]; //������ �����������
typedef float mat[M][M]; //�������

extern mat T; //������� ������������ ��������������
extern vec A,B;

void times(mat a, mat b, mat c); //a*b=c
void timesMatVec(mat a, vec b, vec c); //a*b=c
void set(mat a, mat b); //a ������������ � b
void point2vec(point a, vec b); //��������� ���������� �� point � � ���������� ���������� vec
void vec2point(vec a, point &b); //��������
void makeHomogenVec(float x, float y, vec c); //x � y � c
void unit(mat a); //���� �������� � ��������� �������
void rotate(float phi, mat c); //�������
void scale(float Sx, float Sy, mat c); //���������������


void rotate_p(float phi, mat c); //Q
void move(float Tx, float Ty, mat c); //T,G,F,H
void z_goriz(float Tx, mat c); //U
void z_vert(float Tx, mat c); //J



