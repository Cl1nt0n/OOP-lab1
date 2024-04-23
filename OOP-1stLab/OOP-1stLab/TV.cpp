#include <Windows.h>
#include "TV.h"
extern HDC hdc;			// объявление контекста устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

Location::Location(int x, int y)
{
	//инициализация закрытых переменных своего класса
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

//показать ТОЧКУ
void Point::Show(void)
{
	IsVisible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));//рисуем красным цветом
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

//скрыть ТОЧКУ
void Point::Hide(void)
{
	IsVisible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));//рисуем синим цветом или фона
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
	Hide();		//сделать точку невидимой
	X = newX;	//поменять координаты ТОЧКИ
	Y = newY;
	Show();		//показать точку на новом месте
}

void Point::Drag(int Step)
{
	int figX, figY; //новые координаты фигуры

	figX = GetX(); //получаем начальные координаты фигуры
	figY = GetY();

	//бесконечный цикл буксировки фигуры
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - конец работы
			break;

		//выбор направления движения фигуры
		if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
		{
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
		{
			figY -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
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

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //сделали перо активным

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

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //сделали перо активным

	Rectangle(hdc, X, Y, X + ScreenWidth, Y + ScreenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + ScreenWidth - 5, Y + ScreenHeight - 5);
	Rectangle(hdc, X + ScreenWidth / 2 - 10, Y + ScreenHeight, X + ScreenWidth / 2 + 10, Y + ScreenHeight + StandHeight);
	Rectangle(hdc, X + ScreenWidth * 0.2, Y + ScreenHeight + StandHeight, X + ScreenWidth * 0.8, Y + ScreenHeight + StandHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

//void TV::MoveTo(int newX, int newY)
//{
//	Hide();		//сделать точку невидимой
//	X = newX;	//поменять координаты ТОЧКИ
//	Y = newY;
//	Show();		//показать точку на новом месте
//}
//
//void TV::Drag(int step)
//{
//	int figX, figY; //новые координаты фигуры
//
//	figX = GetX(); //получаем начальные координаты фигуры
//	figY = GetY();
//
//	//бесконечный цикл буксировки фигуры
//	while (1)
//	{
//		if (KEY_DOWN(VK_ESCAPE)) //27 esc - конец работы
//			break;
//
//		//выбор направления движения фигуры
//		if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
//		{
//			figX -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
//		{
//			figX += step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
//		{
//			figY += step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
//		{
//			figY -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//	}//while
//}