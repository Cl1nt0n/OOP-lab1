/*----------------------  ����� �������������� ------------------------*/
class Location
{
protected:		//������������� ����������� �������� (������������
	//������) ����� ������ � ������� ������
	int X;		//���������� �
	int Y;		//���������� Y

public:			//��� ������ �������� ����� ���� � ���������
	Location(int x, int y);	//�����������
	~Location();					//����������
	int GetX();						//�������� � ���������� �����
	int GetY();						//�������� Y ���������� �����
};//class Location

/*-----------------------  ����� ����� ---------------------------------*/
class Point : public Location
{
protected:							//�������, ����������� �� Point, ����������� ������ public
	bool IsVisible;					//���������� �����
public:
	Point(int x, int y);	//����������� ������
	~Point();						//����������
	bool CheckIsVisible();				//������ ��� ���������� �����
	void MoveTo(int NewX, int NewY);//����������� ������
	void Drag(int step);			//���������� ������

	//����������� ������ (����� ����������)
	//void Show();					//
	//void Hide();					//

	//����������� ������ (������� ����������)
	virtual void Show();			// �������� ������ �����
	virtual void Hide();			// ������ ������ �����
};//����� Point

/*-----------------------  ����� ��������� ----------------------------------*/
class TV : public Point
{
private:
	int ScreenHeight;				// ������ ������
	int ScreenWidth;				// ������ ������
	int StandHeight;				// ������ 
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);	//�����������
	~TV();				//����������

	//void Drag(int step);		//����������� ������
	void Show();				//�������� ������
	void Hide();				//������ ������
	//void MoveTo(int NewX, int NewY); //����������� ������
};//����� TV