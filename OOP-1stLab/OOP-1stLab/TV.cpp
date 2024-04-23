#include <Windows.h>
#include "TV.h"
extern HDC hdc;			// ���������� ��������� ����������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

Location::Location(int x, int y)
{
	//������������� �������� ���������� ������ ������
	X = x;
	Y = y;
}//Location::Location()

Location::~Location()
{
}

int Location::GetX()
{
	return X;
}//Location::GetX()	

int Location::GetY()
{
	return Y;
}//Location::GetY()	

Point::Point(int x, int y) : Location(x, y)
{
	IsVisible = false;
}

Point::~Point()
{
}

//�������� �����
void Point::Show(void)
{
	IsVisible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));//������ ������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 3, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 2, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 3, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 2, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 3, RGB(255, 0, 0));
}//end Point::Show()

//������ �����
void Point::Hide(void)
{
	IsVisible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));//������ ����� ������ ��� ����
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 2, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 3, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 2, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 3, RGB(0, 0, 255));
	SetPixel(hdc, X + 2, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 2, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 2, Y + 2, RGB(0, 0, 255));
	SetPixel(hdc, X + 2, Y + 3, RGB(0, 0, 255));
}//Point::Hide()

bool Point::CheckIsVisible()
{
	return false;
}

void Point::MoveTo(int newX, int newY)
{
	Hide();		//������� ����� ���������
	X = newX;	//�������� ���������� �����
	Y = newY;
	Show();		//�������� ����� �� ����� �����
}

void Point::Drag(int Step)
{
	int figX, figY; //����� ���������� ������

	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();

	//����������� ���� ���������� ������
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
			break;

		//����� ����������� �������� ������
		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
		{
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if
	}//while
}

TV::TV(int x, int y, int scrHeight, int scrWidth, int stHeight) : Point(x, y)
{
	ScreenHeight = scrHeight;
	ScreenWidth = scrWidth;
	StandHeight = stHeight;
}

TV::~TV()
{
}

void TV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //������� ���� ��������

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

void TV::Hide()
{
	if (IsVisible == false) return;

	IsVisible = false;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //������� ���� ��������

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

//void TV::MoveTo(int newX, int newY)
//{
//	Hide();		//������� ����� ���������
//	X = newX;	//�������� ���������� �����
//	Y = newY;
//	Show();		//�������� ����� �� ����� �����
//}
//
//void TV::Drag(int step)
//{
//	int figX, figY; //����� ���������� ������
//
//	figX = GetX(); //�������� ��������� ���������� ������
//	figY = GetY();
//
//	//����������� ���� ���������� ������
//	while (1)
//	{
//		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
//			break;
//
//		//����� ����������� �������� ������
//		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
//		{
//			figX -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
//		{
//			figX += step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
//		{
//			figY += step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_UP)) //38 ������� �����
//		{
//			figY -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//	}//while
//}