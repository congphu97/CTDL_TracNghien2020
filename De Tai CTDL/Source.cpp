﻿#include <iostream>
#include "Form.h"
#include <ctime>
#include "Login.h"
#include "Formteach.h"
#include "DBSet.h"
#include "EventController.h"
using namespace std;
using namespace scl;


//class a : public CompareData<int>{
//    int getId() { return  0; }
//};
//template<class T = CompareData<int>>
//class b {
//public:
//    void test() {
//        T* d = new T();
//    }
//};
int main3() {
	DBSet<std::string, char, 10, EntityMonHoc, Monhoc>* dbset = new DBSet<std::string, char, 10, EntityMonHoc, Monhoc>("MonHoc.txt");
	dbset->Add(new Monhoc("test1", "name5"));
	dbset->Add(new Monhoc("test2", "name6"));
	dbset->Add(new Monhoc("test3", "name7"));
	dbset->Add(new Monhoc("test4", "name8"));
	dbset->Add(new Monhoc("test5", "name8"));

	dbset->Update(new Monhoc("test1", "name10000"));

	dbset->Delete(new Monhoc("test2", "name6"));
	Monhoc* test = dbset->ToArray();


	for (int i = 0; i < dbset->size(); i++)
	{
		cout << &test[i] << endl;
	}

	dbset->Add(new Monhoc("test100", "name100"));

	cout << endl;

	test = dbset->ToArray();


	for (int i = 0; i < dbset->size(); i++)
	{
		cout << &test[i] << endl;
	}

	DBSet<std::string, char, 20, EntiySinhvien, Sinhvien>* dbset1 = new DBSet<std::string, char, 20, EntiySinhvien, Sinhvien>("SinhVien.txt", sizeof(Sinhvien) - sizeof(List<Monhoc>));
	dbset1->Add(new Sinhvien("sv1", "", "", true, ""));
	dbset1->Add(new Sinhvien("sv2", "", "", true, ""));
	dbset1->Add(new Sinhvien("sv3", "", "", true, ""));
	dbset1->Add(new Sinhvien("sv4", "", "", true, ""));
	cout << endl;

	Sinhvien* test1 = dbset1->ToArray();
	for (int i = 0; i < dbset1->size(); i++)
	{
		cout << &test1[i] << endl;
	}


	DBSet<int, int, 1, EntityQuestion, Question>* dbset2 = new DBSet<int, int, 1, EntityQuestion, Question>("Question.txt");
	dbset2->Add(new Question(1, "c1", "1", "", "", "1", '\0'));
	dbset2->Add(new Question(2, "c2", "2", "", "", "2", '\0'));
	dbset2->Add(new Question(3, "c3", "3", "", "", "3", '\0'));
	dbset2->Add(new Question(4, "c4", "4", "", "", "4", '\0'));
	dbset2->Add(new Question(5, "c5", "6", "", "", "5", '\0'));
	cout << endl;

	Question* test2 = dbset2->ToArray();
	for (int i = 0; i < dbset2->size(); i++)
	{
		cout << &test2[i] << endl;
	}

	delete dbset;
	delete dbset1;
	delete dbset2;
	return 0;
}
int main(int argc, char* argv[]) {
	scl::DisableMaxiMize("tainguyen");

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	Hour h{ systime.wHour,systime.wMinute,systime.wSecond - 1 };
	//Hour h{ 0,0,20 };
	TimeClock t{ h,colorbk_yellow | color_red,0,0 };
	thread th{ [&t] {t.printClock(&TimeClock::changetimeMult); } };
	EventController* HandleEventController = EventController::getInstance();
	thread* handleThreadMouse = HandleEventController->Start();

	//cac doi tuong form
	bool Checklogin;
	Login DangNhap(NULL, 40, 14, colorbk_white);
	DangNhap.show();

	/*switch (Checklogin)
	{
	case true: {
		EventConsole evt;
		FormTeach Fteach(NULL, 52, 25, colorbk_blue | color_blue);
		Fteach.show();
		Fteach.ActionFormTeach();
		break;
	}
	case false:break;
	};*/
	//------------------------

	th.join();
	t.stop();
	handleThreadMouse->join();
	return 0;
}
int main1() {
	HANDLE hStdout, hNewScreenBuffer;
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO chiBuffer[160]; // [2][80]; 
	COORD coordBufSize;
	COORD coordBufCoord;
	BOOL fSuccess;

	// Get a handle to the STDOUT screen buffer to copy from and 
	// create a new screen buffer to copy to. 

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	if (hStdout == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	// Make the new screen buffer the active screen buffer. 

	if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	// Set the source rectangle. 

	srctReadRect.Top = 0;    // top left: row 0, col 0 
	srctReadRect.Left = 0;
	srctReadRect.Bottom = 1; // bot. right: row 1, col 79 
	srctReadRect.Right = 79;

	// The temporary buffer size is 2 rows x 80 columns. 

	coordBufSize.Y = 2;
	coordBufSize.X = 80;

	// The top left destination cell of the temporary buffer is 
	// row 0, col 0. 

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	// Copy the block from the screen buffer to the temp. buffer. 

	fSuccess = ReadConsoleOutput(
		hStdout,        // screen buffer to read from 
		chiBuffer,      // buffer to copy into 
		coordBufSize,   // col-row size of chiBuffer 
		coordBufCoord,  // top left dest. cell in chiBuffer 
		&srctReadRect); // screen buffer source rectangle 
	if (!fSuccess)
	{
		printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
		return 1;
	}

	// Set the destination rectangle. 

	srctWriteRect.Top = 10;    // top lt: row 10, col 0 
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79 
	srctWriteRect.Right = 79;

	// Copy from the temporary buffer to the new screen buffer. 
	chiBuffer[0].Char.AsciiChar = 'a';
	chiBuffer[0].Attributes = 4;
	DWORD written;
	char c = 'a';
	SetConsoleTextAttribute(hNewScreenBuffer, FOREGROUND_RED);

	WriteConsole(hNewScreenBuffer, &c, 1, &written, nullptr);

	//fSuccess = WriteConsoleOutput(
	//    hNewScreenBuffer, // screen buffer to write to 
	//    chiBuffer,        // buffer to copy from 
	//    coordBufSize,     // col-row size of chiBuffer 
	//    coordBufCoord,    // top left src cell in chiBuffer 
	//    &srctWriteRect);  // dest. screen buffer rectangle 
	if (!fSuccess)
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
		return 1;
	}
	Sleep(5000);

	// Restore the original active screen buffer. 

	if (!SetConsoleActiveScreenBuffer(hStdout))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	return 0;
}
// 9 7 12 8 6 5 14 4
//#include <queue>
//int main() {
//	priority_queue<int> pq;
//
//	int l[] = { 9,7,12,8,6,5,14,4 };
//	for (int i = 0; i < 8; i++)
//	{
//		pq.push(l[i]);
//	}
//	int first, second,opt=0;
//	while (pq.size()>1)
//	{
//		first = pq.top(); pq.pop();
//		second = pq.top(); pq.pop();
//		//cout << pq.top()<<endl;
//		opt =  first + second;
//		pq.push(first + second);
//	}
//	cout << opt;
//	system("pause");
//	return 0;
//}

//struct test
//{
//	int a;
//	test *t;
//};
//#define	unt y.t->t
//int main() {
//	test y = { 1 ,NULL};
//
//	y.t = new test{2,NULL};
//	y.t->t = new test{ 3,NULL };
//
//	cout << unt->a;
//
//	return 0;
//}