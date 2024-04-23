/*----------------------  Класс МЕСТОПОЛОЖЕНИЕ ------------------------*/
class Location
{
protected:		//предоставляет возможность потомкам (производному
	//классу) иметь доступ к частным данным
	int X;		//координата Х
	int Y;		//координата Y

public:			//эти методы доступны извне всем в программе
	Location(int x, int y);	//конструктор
	~Location();					//деструктор
	int GetX();						//получить Х координату точки
	int GetY();						//получить Y координату точки
};//class Location

/*-----------------------  Класс ТОЧКА ---------------------------------*/
class Point : public Location
{
protected:							//классам, производным от Point, потребуется доступ public
	bool IsVisible;					//светимость точки
public:
	Point(int x, int y);	//конструктор класса
	~Point();						//деструктор
	bool CheckIsVisible();				//узнать про светимость точки
	void MoveTo(int NewX, int NewY);//переместить фигуру
	void Drag(int step);			//буксировка фигуры

	//статические методы (ранне связывание)
	//void Show();					//
	//void Hide();					//

	//виртуальные методы (позднее связывание)
	virtual void Show();			// показать фигуру ТОЧКА
	virtual void Hide();			// скрыть фигуру ТОЧКА
};//класс Point

/*-----------------------  Класс телевизор ----------------------------------*/
class TV : public Point
{
private:
	int ScreenHeight;				// высота экрана
	int ScreenWidth;				// ширина экрана
	int StandHeight;				// высота 
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);	//конструктор
	~TV();				//деструктор

	//void Drag(int step);		//перемещение фигуры
	void Show();				//показать фигуру
	void Hide();				//скрыть фигуру
	//void MoveTo(int NewX, int NewY); //переместить фигуру
};//класс TV