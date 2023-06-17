#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <tchar.h>
using namespace std;

#define FILE_MENU_ABOUT 99  //defining program resources/constants
#define FILE_MENU_EXIT 98
#define FILE_MENU_SAVE 97
#define BUTTON_DISPLAYINCOME 96
#define BUTTON_DISPLAYEXPENSES 95
#define BUTTON_BREAKDOWN 94
#define INCOME_INPUT 93
#define EXPENSES_INPUT 92
#define BUTTON_ALLOWANCE 91
#define BUTTON_SALARY 90
#define BUTTON_INVESTMENT 89
#define BUTTON_COUPONS 88
#define EDIT_BGCOLOR1 87
#define EDIT_BGCOLOR2 86
#define EDIT_BGCOLOR3 85
#define BUTTON_FOOD 84
#define BUTTON_UTILITIES 83
#define BUTTON_GROCERY 82
#define BUTTON_RENT 81
#define BUTTON_LOADEXISTING 80
#define BUTTON_PRESS1 1
#define BUTTON_PRESS2 2
#define BUTTON_PRESS3 3


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void AddMenus(HWND);
void loadImages();
void AppendText(HWND, LPCTSTR);
void registerDialogIncome(HINSTANCE);
void displayDialogIncome(HWND);
void AddIncomeControls(HWND);
void registerDialogExpenses(HINSTANCE);
void displayDialogExpenses(HWND);
void AddExpensesControls(HWND);
void open_file(HWND);
void open_file2(HWND);

void registerDialogBreakdown(HINSTANCE);
void displayDialogBreakdown(HWND);
void AddBreakdownControls(HWND);
void AddMenusIncEx(HWND);


HMENU hMenu;

HWND hIncome, hExpenses, hBalance, hSFontI, hSFontE, hSFontB, hBSFontI, hBSFontE, hPhp, hIncBreakdown, hExpBreakdown,
    hSFontIncome, hSFontExpenses, hMainWindow, hIncomeOutput, hExpensesOutput, hBreakdownIncome, hBreakdownExpenses;

HBITMAP bAddIncome, bAddExpenses, bBreakdown, bAllowance, bSalary, bInvestment, bCoupons,
    bFood, bUtilities, bGrocery, bRent, hLogoIncome, hLogoExpenses, hPhpLogo, bLoad, bInc, bExp;

HFONT hFont = CreateFont (20, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
HDC hdc;
HBRUSH hbrBkgnd;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){     //creating the parent window


    WNDCLASSW wc = {0};         //creating the window class

    HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));

    wc.hbrBackground = hb; //background color
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);  //window cursor
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";        //defining class name
    wc.lpfnWndProc = WindowProcedure;           //calling window procedure

    if(!RegisterClassW(&wc))
        return -1;

    registerDialogIncome(hInst);
    registerDialogExpenses(hInst);
    registerDialogBreakdown(hInst);

    hMainWindow = CreateWindowW(L"myWindowClass", L"DIGITAL BUDGET PLANNER", WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE | ES_LEFT,
                  400, 100, 415, 480, NULL, NULL, NULL, NULL);   //parent window

    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

    int mbVal;
    double txtIncomeVal, txtExpensesVal, txtBalanceVal, txtValueI, txtValueE, txtValueB;
    char screenValInc[100], screenValEx[100], screenValBal[100];
    TCHAR szBufferIncome[16], szBufferExpenses[16], szBufferBalance[16];

    vector<string> lines;
    string line;
    switch(msg){
        case WM_COMMAND:
            switch(wp){

                    case BUTTON_DISPLAYINCOME:
                        displayDialogIncome(hWnd);
                        break;
                    case BUTTON_DISPLAYEXPENSES:
                        displayDialogExpenses(hWnd);
                        break;
                    case BUTTON_LOADEXISTING:{

                        ifstream fin("Income-Value.txt");
                        static double incomeValue;
                        fin >> incomeValue;

                        sprintf(szBufferIncome, "%.3f", incomeValue);
                        SetWindowText(hIncome, szBufferIncome);

                        fin.close();

                        ifstream fin1("Expenses-Value.txt");
                        static double expensesValue;
                        fin1 >> expensesValue;

                        sprintf(szBufferExpenses, "%.3f", expensesValue);
                        SetWindowText(hExpenses, szBufferExpenses);

                        fin1.close();

                        ifstream fin2("Balance-Value.txt");
                        static double balanceValue;
                        fin2 >> balanceValue;

                        sprintf(szBufferBalance, "%.3f", balanceValue);
                        SetWindowText(hBalance, szBufferBalance);

                        fin2.close();

                        }break;
                    case BUTTON_BREAKDOWN:{
                    static char inc[100], ex[100], bal[100];
                    GetWindowText(hIncome, inc, 100);
                    GetWindowText(hIncome, ex, 100);
                    GetWindowText(hIncome, bal, 100);

                    if (strcmp(inc,"") == 0 && strcmp(ex,"") == 0 && strcmp(bal,"") == 0 || strcmp(inc,"0.000") == 0 || strcmp(ex,"0.000") == 0 || strcmp(bal,"0.000") == 0){
                        mbVal = MessageBoxW(hWnd, L"Empty Data Recorded!\n\nDo you want to load existing data?", L"Empty Data", MB_YESNO | MB_ICONEXCLAMATION);
                        if (mbVal == IDYES){            //built in IDs for Message Boxes

                            ifstream fin("Income-Value.txt");
                            static double incomeValue;
                            fin >> incomeValue;

                            sprintf(szBufferIncome, "%.3f", incomeValue);
                            SetWindowText(hIncome, szBufferIncome);

                            fin.close();

                            ifstream fin1("Expenses-Value.txt");
                            static double expensesValue;
                            fin1 >> expensesValue;

                            sprintf(szBufferExpenses, "%.3f", expensesValue);
                            SetWindowText(hExpenses, szBufferExpenses);

                            fin1.close();

                            ifstream fin2("Balance-Value.txt");
                            static double balanceValue;
                            fin2 >> balanceValue;

                            sprintf(szBufferBalance, "%.3f", balanceValue);
                            SetWindowText(hBalance, szBufferBalance);

                            fin2.close();

                            static ofstream ofs1, ofs2, ofs3, ofs4, ofs5;
                            ofs1.open("Income-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs1.close();
                            ofs2.open("Expenses-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs2.close();
                            ofs3.open("Balance-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs3.close();
                            ofs4.open("Breakdown-Expenses.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs4.close();
                            ofs5.open("Breakdown-Income.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs5.close();
                            MessageBoxW(hWnd, L"No Data Detected", L"No Data", MB_OK | MB_ICONINFORMATION);
                        }

                        else if (mbVal == IDNO){
                            static ofstream ofs1, ofs2, ofs3, ofs4, ofs5;
                            ofs1.open("Income-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs1.close();
                            ofs2.open("Expenses-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs2.close();
                            ofs3.open("Balance-Value.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs3.close();
                            ofs4.open("Breakdown-Expenses.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs4.close();
                            ofs5.open("Breakdown-Income.txt", std::ofstream::out | std::ofstream::trunc); //trunc method to clear txt file
                            ofs5.close();
                            displayDialogBreakdown(hWnd);
                            MessageBoxW(hWnd, L"No Data Detected", L"No Data", MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    displayDialogBreakdown(hWnd);
                    }break;
                    case FILE_MENU_ABOUT:              //about menu
                        MessageBoxW(hWnd, L"Digital Budget Planner using WIN32 API \n\nby \nDalangin, John Rey G.\nFajel, Kenneth Q. \nRacelis, Glorie Alynna C\nRobles, John Joe Rimuel P.\nSiochi, Jamie Anne S.", L"About Digital Budget Planner", MB_OK | MB_ICONINFORMATION);
                        break;
                    case FILE_MENU_SAVE:              //about menu
                        MessageBoxW(hWnd, L"Data Successfully Saved!", L"Save File", MB_OK | MB_ICONINFORMATION);

                        GetWindowText(hIncome, screenValInc, 100);
                        GetWindowText(hExpenses, screenValEx, 100);
                        GetWindowText(hBalance, screenValBal, 100);

                        static ofstream openIncome("Income-Value.txt");
                        static ofstream openExpenses("Expenses-Value.txt");
                        static ofstream openBalance("Balance-Value.txt");

                        openIncome << screenValInc;
                        openExpenses << screenValEx;
                        openBalance << screenValBal;

                        openIncome.close();
                        openExpenses.close();
                        openBalance.close();

                        break;

                    case FILE_MENU_EXIT:               //program exit menu
                        mbVal = MessageBoxW(hWnd, L"Exit Program?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
                        if (mbVal == IDYES)             //built in IDs for Message Boxes
                            DestroyWindow(hWnd);
                        else if (mbVal == IDNO)
                        break;
            }
            break;


            case WM_CTLCOLORSTATIC:
            {
                HDC hdcStatic = (HDC) wp;
                SetTextColor(hdcStatic, RGB(0, 0, 0));
                if (GetDlgItem(hWnd, EDIT_BGCOLOR1) == (HWND)lp){
                    SetTextColor(hdcStatic, RGB(0, 128, 0));}
                if (GetDlgItem(hWnd, EDIT_BGCOLOR2) == (HWND)lp){
                    SetTextColor(hdcStatic, RGB(178, 34, 34));}
                if (GetDlgItem(hWnd, EDIT_BGCOLOR3) == (HWND)lp){
                    SetTextColor(hdcStatic, RGB(255, 69, 0));}


                SetBkColor(hdcStatic, RGB(252, 252, 252));

                if (hbrBkgnd == NULL)
                {
                    hbrBkgnd = CreateSolidBrush(RGB(252, 252, 252));
                }
                return (INT_PTR)hbrBkgnd;
            } break;

            case WM_CREATE:        //executed once the window is created
                loadImages();
                AddMenus(hWnd);
                AddControls(hWnd);
                break;

            case WM_DESTROY:       //exiting session
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddMenus(HWND hWnd){       //add menu function that accepts the window handler as the parameter

    hMenu = CreateMenu();       //creating menus using HMENU

    AppendMenu(hMenu, MF_STRING, FILE_MENU_ABOUT, "About");     //menus
    AppendMenu(hMenu, MF_STRING, FILE_MENU_SAVE, "Save");
    AppendMenu(hMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd){


    hSFontI = CreateWindowW(L"Static", L"Income", WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
                  30, 75, 100, 90, hWnd, NULL, NULL, NULL);
    hIncome = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_CENTER | ES_READONLY,
                  31, 113, 98, 40, hWnd, (HMENU)EDIT_BGCOLOR1, NULL, NULL);

    hSFontE = CreateWindowW(L"Static", L"Expenses", WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
                  150, 75, 100, 90, hWnd, NULL, NULL, NULL);
    hExpenses = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_CENTER | ES_READONLY,
                  151, 113, 98, 40, hWnd, (HMENU)EDIT_BGCOLOR2, NULL, NULL);

    hSFontB = CreateWindowW(L"Static", L"Balance", WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
                  270, 75, 100, 90, hWnd, NULL, NULL, NULL);
    hBalance = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_CENTER | ES_READONLY,
                  271, 113, 98, 40, hWnd, (HMENU)EDIT_BGCOLOR3, NULL, NULL);



    SendMessage(hSFontI, WM_SETFONT, (LPARAM)hFont, TRUE);
    SendMessage(hSFontE, WM_SETFONT, (LPARAM)hFont, TRUE);
    SendMessage(hSFontB, WM_SETFONT, (LPARAM)hFont, TRUE);

    HFONT hFontBox = CreateFont (17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    SendMessage(hIncome, WM_SETFONT, (LPARAM)hFontBox, TRUE);
    SendMessage(hExpenses, WM_SETFONT, (LPARAM)hFontBox, TRUE);
    SendMessage(hBalance, WM_SETFONT, (LPARAM)hFontBox, TRUE);

    HWND hLoadExisting = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  220, 30, 150, 20, hWnd, (HMENU)BUTTON_LOADEXISTING, NULL, NULL);
    SendMessageW(hLoadExisting, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bLoad);

    HWND hAddIncome = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  80, 215, 240, 40, hWnd, (HMENU)BUTTON_DISPLAYINCOME, NULL, NULL);
    SendMessageW(hAddIncome, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bAddIncome);

    HWND hAddExpenses = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  80, 275, 240, 40, hWnd, (HMENU)BUTTON_DISPLAYEXPENSES, NULL, NULL);
    SendMessageW(hAddExpenses, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bAddExpenses);

    HWND hBreakdown = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  100, 335, 200, 30, hWnd, (HMENU)BUTTON_BREAKDOWN, NULL, NULL);
    SendMessageW(hBreakdown, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bBreakdown);

}

void loadImages(){                  // to load all the bitmap images. we used 24 depth bitmap for the win32api to be able to read
    bAddIncome = (HBITMAP)LoadImageW(NULL, L"B-AddIncome.bmp", IMAGE_BITMAP, 240, 40, LR_LOADFROMFILE);
    bAddExpenses = (HBITMAP)LoadImageW(NULL, L"B-AddExpenses.bmp", IMAGE_BITMAP, 240, 40, LR_LOADFROMFILE);
    bBreakdown = (HBITMAP)LoadImageW(NULL, L"B-Breakdown.bmp", IMAGE_BITMAP, 200, 30, LR_LOADFROMFILE);
    bAllowance = (HBITMAP)LoadImageW(NULL, L"B-Allowance.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bSalary = (HBITMAP)LoadImageW(NULL, L"B-Salary.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bInvestment = (HBITMAP)LoadImageW(NULL, L"B-Investment.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bCoupons = (HBITMAP)LoadImageW(NULL, L"B-Coupon.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bFood = (HBITMAP)LoadImageW(NULL, L"B-Food.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bUtilities = (HBITMAP)LoadImageW(NULL, L"B-Utilities.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bGrocery = (HBITMAP)LoadImageW(NULL, L"B-Grocery.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    bRent = (HBITMAP)LoadImageW(NULL, L"B-Rent.bmp", IMAGE_BITMAP, 85, 85, LR_LOADFROMFILE);
    hLogoIncome = (HBITMAP)LoadImageW(NULL, L"Income.bmp", IMAGE_BITMAP, 130, 40, LR_LOADFROMFILE);
    hLogoExpenses = (HBITMAP)LoadImageW(NULL, L"expenses.bmp", IMAGE_BITMAP, 130, 40, LR_LOADFROMFILE);
    hPhpLogo = (HBITMAP)LoadImageW(NULL, L"peso.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
    bLoad = (HBITMAP)LoadImageW(NULL, L"LOAD_EXISTING_DATA.bmp", IMAGE_BITMAP, 150, 20, LR_LOADFROMFILE);
    bInc = (HBITMAP)LoadImageW(NULL, L"income_breakdown.bmp", IMAGE_BITMAP, 300, 40, LR_LOADFROMFILE);
    bExp = (HBITMAP)LoadImageW(NULL, L"expenses_breakdown.bmp", IMAGE_BITMAP, 300, 40, LR_LOADFROMFILE);
}

LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp ){

    int mbVal;
    char incomeInput[100], screenVal[100], message[100];
    double firstVal, secondVal, newVal, getExpenses, setBalance;
    TCHAR szBuffer[16];
    switch(msg){
    case WM_COMMAND:
        switch(wp){

                case BUTTON_ALLOWANCE:
                    GetWindowText(hIncome, screenVal, 100);
                    firstVal = static_cast<double>(atof(screenVal));
                    GetWindowText(hIncomeOutput, incomeInput, 100);
                    secondVal = static_cast<double>(atof(incomeInput));
                    if (strcmp(incomeInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                    }
                    sprintf(message,"Add Php %s on your Income (Allowance)?", incomeInput);
                    mbVal = MessageBox(hWnd, TEXT(message),TEXT("Allowance"), MB_YESNO | MB_ICONQUESTION);
                    if (mbVal == IDYES){
                        newVal = firstVal + secondVal;
                        sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                        SetWindowText(hIncome, szBuffer);

                        SetWindowText(hIncomeOutput, "");

                        GetWindowText(hExpenses, screenVal, 100);
                        getExpenses = static_cast<double>(atof(screenVal));
                        setBalance = newVal - getExpenses;
                        sprintf(szBuffer, "%.3f", setBalance);
                        SetWindowText(hBalance, szBuffer);

                        static ofstream outfile;

                        outfile.open("Breakdown-Income.txt", ios_base::app); // append instead of overwrite
                        outfile << "  Allowance           --->          Php " << incomeInput << "\n";
                        outfile.close();

                        MessageBox(hWnd, TEXT("Successfully Added to Income!"),TEXT("Success!"), MB_OK);
                        char screenVal[100];
                        int converted;
                    }
                    else if (mbVal == IDNO){}
                    break;

                    case BUTTON_SALARY:
                    GetWindowText(hIncome, screenVal, 100);
                    firstVal = static_cast<double>(atof(screenVal));
                    GetWindowText(hIncomeOutput, incomeInput, 100);
                    secondVal = static_cast<double>(atof(incomeInput));
                    if (strcmp(incomeInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                    }
                    sprintf(message,"Add Php %s on your Income (Salary)?", incomeInput);
                    mbVal = MessageBox(hWnd, TEXT(message),TEXT("Salary"), MB_YESNO | MB_ICONQUESTION);
                    if (mbVal == IDYES){
                        newVal = firstVal + secondVal;
                        sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                        SetWindowText(hIncome, szBuffer);

                        SetWindowText(hIncomeOutput, "");

                        GetWindowText(hExpenses, screenVal, 100);
                        getExpenses = static_cast<double>(atof(screenVal));
                        setBalance = newVal - getExpenses;
                        sprintf(szBuffer, "%.3f", setBalance);
                        SetWindowText(hBalance, szBuffer);

                        static ofstream outfile2;

                        outfile2.open("Breakdown-Income.txt", ios_base::app); // append instead of overwrite
                        outfile2 << "  Salary                 --->          Php " << incomeInput << "\n";
                        outfile2.close();

                        MessageBox(hWnd, TEXT("Successfully Added to Income!"),TEXT("Success!"), MB_OK);
                    }
                    else if (mbVal == IDNO){}
                    break;

                    case BUTTON_INVESTMENT:
                    GetWindowText(hIncome, screenVal, 100);
                    firstVal = static_cast<double>(atof(screenVal));
                    GetWindowText(hIncomeOutput, incomeInput, 100);
                    secondVal = static_cast<double>(atof(incomeInput));
                    if (strcmp(incomeInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                    }
                    sprintf(message,"Add Php %s on your Income (Investment)?", incomeInput);
                    mbVal = MessageBox(hWnd, TEXT(message),TEXT("Investment"), MB_YESNO | MB_ICONQUESTION);
                    if (mbVal == IDYES){
                        newVal = firstVal + secondVal;
                        sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                        SetWindowText(hIncome, szBuffer);

                        SetWindowText(hIncomeOutput, "");

                        GetWindowText(hExpenses, screenVal, 100);
                        getExpenses = static_cast<double>(atof(screenVal));
                        setBalance = newVal - getExpenses;
                        sprintf(szBuffer, "%.3f", setBalance);
                        SetWindowText(hBalance, szBuffer);

                        static ofstream outfile3;

                        outfile3.open("Breakdown-Income.txt", ios_base::app); // append instead of overwrite
                        outfile3 << "  Investment          --->          Php " << incomeInput << "\n";
                        outfile3.close();

                        MessageBox(hWnd, TEXT("Successfully Added to Income!"),TEXT("Success!"), MB_OK);
                    }
                    else if (mbVal == IDNO){}
                    break;

                    case BUTTON_COUPONS:
                    GetWindowText(hIncome, screenVal, 100);
                    firstVal = static_cast<double>(atof(screenVal));
                    GetWindowText(hIncomeOutput, incomeInput, 100);
                    secondVal = static_cast<double>(atof(incomeInput));
                    if (strcmp(incomeInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                    }
                    sprintf(message,"Add Php %s on your Income (Coupons)?", incomeInput);
                    mbVal = MessageBox(hWnd, TEXT(message),TEXT("Coupons"), MB_YESNO | MB_ICONQUESTION);
                    if (mbVal == IDYES){
                        newVal = firstVal + secondVal;
                        sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                        SetWindowText(hIncome, szBuffer);

                        SetWindowText(hIncomeOutput, "");

                        GetWindowText(hExpenses, screenVal, 100);
                        getExpenses = static_cast<double>(atof(screenVal));
                        setBalance = newVal - getExpenses;
                        sprintf(szBuffer, "%.3f", setBalance);
                        SetWindowText(hBalance, szBuffer);

                        static ofstream outfile4;

                        outfile4.open("Breakdown-Income.txt", ios_base::app); // append instead of overwrite
                        outfile4 << "  Coupons              --->          Php " << incomeInput << "\n";
                        outfile4.close();

                        MessageBox(hWnd, TEXT("Successfully Added to Income!"),TEXT("Success!"), MB_OK);
                    }
                    else if (mbVal == IDNO){}
                    break;
                    case FILE_MENU_ABOUT:              //about menu
                        MessageBoxW(hWnd, L"Digital Budget Planner using WIN32 API \n\nby \nDalangin, John Rey G.\nFajel, Kenneth Q. \nRacelis, Glorie Alynna C\nRobles, John Joe Rimuel P.\nSiochi, Jamie Anne S.", L"About Digital Budget Planner", MB_OK | MB_ICONINFORMATION);
                        break;
                    case FILE_MENU_EXIT:               //program exit menu
                        mbVal = MessageBoxW(hWnd, L"Exit Window?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
                        if (mbVal == IDYES)             //built in IDs for Message Boxes
                            DestroyWindow(hWnd);
                        else if (mbVal == IDNO)
                        break;
        }
    break;
    case WM_CTLCOLOREDIT://Set Edit color

        if (GetDlgItem(hWnd, INCOME_INPUT) == (HWND)lp)//1 here is the ID of the static text box
        {
			SetTextColor((HDC)wp, RGB(50, 205,50));
			return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
			//return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
		}
		break;

    case WM_CLOSE:
        EnableWindow(hMainWindow, TRUE);
        DestroyWindow(hWnd);
        break;
    case WM_CREATE:
        AddMenusIncEx(hWnd);
        AddIncomeControls(hWnd);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }

}

void registerDialogIncome(HINSTANCE hInst){

    WNDCLASSW dialog = {0};

    HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));

    dialog.hbrBackground = hb;
    dialog.hCursor = LoadCursor (NULL, IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
}

void displayDialogIncome(HWND hWnd){

    CreateWindowW(L"myDialogClass", L"ADD INCOME", WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU,
                  850, 100, 415, 480, hWnd, NULL, NULL, NULL);

    EnableWindow(hWnd, TRUE);
}

void AddIncomeControls(HWND hWnd){

    HFONT hFontInput = CreateFont (45, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    hPhp = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  40, 35, 150, 90, hWnd, NULL, NULL, NULL);
    SendMessage(hPhp, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hPhpLogo);

    hIncomeOutput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_RIGHT | WS_BORDER, //declaring the editable text box (the user can input or press the button if they want)
                  90, 30, 280, 50, hWnd, (HMENU)INCOME_INPUT, NULL, NULL);
    SendMessage(hIncomeOutput, WM_SETFONT, (LPARAM)hFontInput, TRUE);

    hBSFontI = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  135, 100, 150, 90, hWnd, NULL, NULL, NULL);
    SendMessage(hBSFontI, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoIncome);

    HFONT hFont = CreateFont (35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));



    hSFontIncome = CreateWindowW(L"Static", L"Allowance", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  95, 242, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hAllowance = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  95, 155, 85, 85, hWnd, (HMENU)BUTTON_ALLOWANCE, NULL, NULL);

    HFONT hFontInside = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    SendMessage(hSFontIncome, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hAllowance, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bAllowance);

    hSFontIncome = CreateWindowW(L"Static", L"Salary", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  215, 242, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hSalary = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  215, 155, 85, 85, hWnd, (HMENU)BUTTON_SALARY, NULL, NULL);

    SendMessage(hSFontIncome, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hSalary, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bSalary);

    hSFontIncome = CreateWindowW(L"Static", L"Investment", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  95, 362, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hInvestment = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  95, 275, 85, 85, hWnd, (HMENU)BUTTON_INVESTMENT, NULL, NULL);

    SendMessage(hSFontIncome, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hInvestment, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bInvestment);

    hSFontIncome = CreateWindowW(L"Static", L"Coupons", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  215, 362, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hCoupons = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  215, 275, 85, 85, hWnd, (HMENU)BUTTON_COUPONS, NULL, NULL);

    SendMessage(hSFontIncome, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hCoupons, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bCoupons);
}

LRESULT CALLBACK DialogProcedureExpenses(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp ){

    int mbVal;
    char expensesInput[100], screenVal[100], message[100];
    double firstVal, secondVal, newVal, getIncome, setBalance;
    TCHAR szBuffer[16];
    switch(msg){
    case WM_COMMAND:
        switch(wp){
            case BUTTON_FOOD:
                GetWindowText(hExpenses, screenVal, 100);
                firstVal = static_cast<double>(atof(screenVal));
                GetWindowText(hExpensesOutput, expensesInput, 100);
                secondVal = static_cast<double>(atof(expensesInput));

                if (strcmp(expensesInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                }
                sprintf(message,"Add Php %s on your Expenses (Food)?", expensesInput);
                mbVal = MessageBox(hWnd, TEXT(message),TEXT("Food"), MB_YESNO | MB_ICONQUESTION);
                if (mbVal == IDYES){
                    newVal = firstVal + secondVal;
                    sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                    SetWindowText(hExpenses, szBuffer);

                    SetWindowText(hExpensesOutput, "");

                    GetWindowText(hIncome, screenVal, 100);
                    getIncome = static_cast<double>(atof(screenVal));
                    setBalance = getIncome - newVal;
                    sprintf(szBuffer, "%.3f", setBalance);
                    SetWindowText(hBalance, szBuffer);

                    static ofstream outfile;

                    outfile.open("Breakdown-Expenses.txt", ios_base::app); // append instead of overwrite
                    outfile << "  Food            --->          Php " << expensesInput << "\n";
                    outfile.close();

                    MessageBox(hWnd, TEXT("Successfully Added to Expenses!"),TEXT("Success!"), MB_OK);
                }
                else if (mbVal == IDNO){}
                break;

            case BUTTON_UTILITIES:
                GetWindowText(hExpenses, screenVal, 100);
                firstVal = static_cast<double>(atof(screenVal));
                GetWindowText(hExpensesOutput, expensesInput, 100);
                secondVal = static_cast<double>(atof(expensesInput));

                if (strcmp(expensesInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                }
                sprintf(message,"Add Php %s on your Expenses (Utilities)?", expensesInput);
                mbVal = MessageBox(hWnd, TEXT(message),TEXT("Utilities"), MB_YESNO | MB_ICONQUESTION);
                if (mbVal == IDYES){
                    newVal = firstVal + secondVal;
                    sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                    SetWindowText(hExpenses, szBuffer);

                    SetWindowText(hExpensesOutput, "");

                    GetWindowText(hIncome, screenVal, 100);
                    getIncome = static_cast<double>(atof(screenVal));
                    setBalance = getIncome - newVal;
                    sprintf(szBuffer, "%.3f", setBalance);
                    SetWindowText(hBalance, szBuffer);

                    static ofstream outfile;

                    outfile.open("Breakdown-Expenses.txt", ios_base::app); // append instead of overwrite
                    outfile << "  Utilities           --->          Php " << expensesInput << "\n";
                    outfile.close();

                    MessageBox(hWnd, TEXT("Successfully Added to Expenses!"),TEXT("Success!"), MB_OK);
                }
                else if (mbVal == IDNO){}
                break;

            case BUTTON_GROCERY:

                GetWindowText(hExpenses, screenVal, 100);
                firstVal = static_cast<double>(atof(screenVal));
                GetWindowText(hExpensesOutput, expensesInput, 100);
                secondVal = static_cast<double>(atof(expensesInput));

                if (strcmp(expensesInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                }
                sprintf(message,"Add Php %s on your Expenses (Grocery)?", expensesInput);
                mbVal = MessageBox(hWnd, TEXT(message),TEXT("Grocery"), MB_YESNO | MB_ICONQUESTION);
                if (mbVal == IDYES){
                    newVal = firstVal + secondVal;
                    sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                    SetWindowText(hExpenses, szBuffer);

                    SetWindowText(hExpensesOutput, "");

                    GetWindowText(hIncome, screenVal, 100);
                    getIncome = static_cast<double>(atof(screenVal));
                    setBalance = getIncome - newVal;
                    sprintf(szBuffer, "%.3f", setBalance);
                    SetWindowText(hBalance, szBuffer);

                    static ofstream outfile;

                    outfile.open("Breakdown-Expenses.txt", ios_base::app); // append instead of overwrite
                    outfile << "  Grocery           --->          Php " << expensesInput << "\n";
                    outfile.close();

                    MessageBox(hWnd, TEXT("Successfully Added to Expenses!"),TEXT("Success!"), MB_OK);
                }
                break;

            case BUTTON_RENT:
                GetWindowText(hExpenses, screenVal, 100);
                firstVal = static_cast<double>(atof(screenVal));
                GetWindowText(hExpensesOutput, expensesInput, 100);
                secondVal = static_cast<double>(atof(expensesInput));

                if (strcmp(expensesInput,"") == 0){
                        mbVal = MessageBoxW(hWnd, L"Please Enter an Amount!", L"Input Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
                        switch(mbVal){
                            case IDABORT:
                                DestroyWindow(hWnd);
                                break;
                            case IDRETRY:
                                return 0;
                            case IGNORE:
                                break;
                        }
                }

                sprintf(message,"Add Php %s on your Expenses (Rent)?", expensesInput);
                mbVal = MessageBox(hWnd, TEXT(message),TEXT("Rent"), MB_YESNO | MB_ICONQUESTION);
                if (mbVal == IDYES){
                    newVal = firstVal + secondVal;
                    sprintf(szBuffer, "%.3f", newVal);        //converting a double into a LPWSTR for the text box
                    SetWindowText(hExpenses, szBuffer);

                    SetWindowText(hExpensesOutput, "");

                    GetWindowText(hIncome, screenVal, 100);
                    getIncome = static_cast<double>(atof(screenVal));
                    setBalance = getIncome - newVal;
                    sprintf(szBuffer, "%.3f", setBalance);
                    SetWindowText(hBalance, szBuffer);

                    static ofstream outfile;

                    outfile.open("  Breakdown-Expenses.txt", ios_base::app); // append instead of overwrite
                    outfile << "Rent                --->          Php " << expensesInput << "\n";
                    outfile.close();

                    MessageBox(hWnd, TEXT("Successfully Added to Expenses!"),TEXT("Success!"), MB_OK);
                }
                break;
                case FILE_MENU_ABOUT:              //about menu
                    MessageBoxW(hWnd, L"Digital Budget Planner using WIN32 API \n\nby \nDalangin, John Rey G.\nFajel, Kenneth Q. \nRacelis, Glorie Alynna C\nRobles, John Joe Rimuel P.\nSiochi, Jamie Anne S.", L"About Digital Budget Planner", MB_OK | MB_ICONINFORMATION);
                    break;
                case FILE_MENU_EXIT:               //program exit menu
                    mbVal = MessageBoxW(hWnd, L"Exit Window?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
                    if (mbVal == IDYES)             //built in IDs for Message Boxes
                            DestroyWindow(hWnd);
                    else if (mbVal == IDNO)
                    break;
        }
    break;

    case WM_CTLCOLOREDIT://Set Edit color

        if (GetDlgItem(hWnd, EXPENSES_INPUT) == (HWND)lp)//1 here is the ID of the static text box
		{
			SetTextColor((HDC)wp, RGB(250, 128, 114));
			return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
			//return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
		}
		break;

    case WM_CLOSE:
        EnableWindow(hMainWindow, TRUE);
        DestroyWindow(hWnd);
        break;
    case WM_CREATE:
        AddMenusIncEx(hWnd);
        AddExpensesControls(hWnd);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void registerDialogExpenses(HINSTANCE hInst){

    WNDCLASSW dialog = {0};

    HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));

    dialog.hbrBackground = hb;
    dialog.hCursor = LoadCursor (NULL, IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"myDialogClassExpenses";
    dialog.lpfnWndProc = DialogProcedureExpenses;

    RegisterClassW(&dialog);
}

void displayDialogExpenses(HWND hWnd){

    CreateWindowW(L"myDialogClassExpenses", L"ADD EXPENSES", WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU ,
                  850, 100, 415, 480, hWnd, NULL, NULL, NULL);

    EnableWindow(hWnd, TRUE);
}

void AddExpensesControls(HWND hWnd){

    HFONT hFontInput = CreateFont (45, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    hPhp = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  40, 35, 150, 90, hWnd, NULL, NULL, NULL);
    SendMessage(hPhp, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hPhpLogo);

    hExpensesOutput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_RIGHT | WS_BORDER, //declaring the editable text box (the user can input or press the button if they want)
                  90, 30, 280, 50, hWnd, (HMENU)EXPENSES_INPUT, NULL, NULL);
    SendMessage(hExpensesOutput, WM_SETFONT, (LPARAM)hFontInput, TRUE);

    hBSFontE = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  135, 100, 150, 90, hWnd, NULL, NULL, NULL);
    SendMessage(hBSFontE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoExpenses);

    HFONT hFont = CreateFont (35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));


    hSFontExpenses = CreateWindowW(L"Static", L"Food", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  95, 242, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hAllowance = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  95, 155, 85, 85, hWnd, (HMENU)BUTTON_FOOD, NULL, NULL);

    HFONT hFontInside = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    SendMessage(hSFontExpenses, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hAllowance, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bFood);

    hSFontExpenses = CreateWindowW(L"Static", L"Utilities", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  215, 242, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hSalary = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  215, 155, 85, 85, hWnd, (HMENU)BUTTON_UTILITIES, NULL, NULL);

    SendMessage(hSFontExpenses, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hSalary, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bUtilities);

    hSFontExpenses = CreateWindowW(L"Static", L"Grocery", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  95, 362, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hInvestment = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  95, 275, 85, 85, hWnd, (HMENU)BUTTON_GROCERY, NULL, NULL);

    SendMessage(hSFontExpenses, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hInvestment, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bGrocery);

    hSFontExpenses = CreateWindowW(L"Static", L"Rent", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  215, 362, 85, 20, hWnd, NULL, NULL, NULL);
    HWND hCoupons = CreateWindowW(L"Button", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP,
                  215, 275, 85, 85, hWnd, (HMENU)BUTTON_RENT, NULL, NULL);

    SendMessage(hSFontExpenses, WM_SETFONT, (LPARAM)hFontInside, TRUE);
    SendMessageW(hCoupons, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bRent);

}

LRESULT CALLBACK DialogProcedureBreakdown(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp ){

    int mbVal;
    char expensesInput[100], screenVal[100], message[100];
    double firstVal, secondVal, newVal, getIncome, setBalance;
    TCHAR szBuffer[16];
    switch(msg){
    case WM_COMMAND:
        switch(wp){
            case FILE_MENU_ABOUT:              //about menu
                    MessageBoxW(hWnd, L"Digital Budget Planner using WIN32 API \n\nby \nDalangin, John Rey G.\nFajel, Kenneth Q. \nRacelis, Glorie Alynna C\nRobles, John Joe Rimuel P.\nSiochi, Jamie Anne S.", L"About Digital Budget Planner", MB_OK | MB_ICONINFORMATION);
                    break;
            case FILE_MENU_EXIT:               //program exit menu
                    mbVal = MessageBoxW(hWnd, L"Exit Window?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
                    if (mbVal == IDYES)             //built in IDs for Message Boxes
                            DestroyWindow(hWnd);
                    else if (mbVal == IDNO)
                    break;
        }
    break;

    case WM_CTLCOLOREDIT://Set Edit color

        if (GetDlgItem(hWnd, EXPENSES_INPUT) == (HWND)lp)//1 here is the ID of the static text box
		{
			SetTextColor((HDC)wp, RGB(250, 128, 114));
			return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
			//return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
		}
		break;

    case WM_CLOSE:
        EnableWindow(hMainWindow, TRUE);
        DestroyWindow(hWnd);
        break;
    case WM_CREATE:

        AddMenusIncEx(hWnd);
        AddBreakdownControls(hWnd);
        open_file(hWnd);
        open_file2(hWnd);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void display_file(char* path){


    FILE *file;
    file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    int _size = ftell(file);
    rewind(file);

    char *data = new char[_size+1];
    fread(data, _size, 1, file);
    data[_size] = '\0';

    SetWindowText(hBreakdownIncome, data);

}

void display_file2(char* path){


    FILE *file;
    file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    int _size = ftell(file);
    rewind(file);

    char *data = new char[_size+1];
    fread(data, _size, 1, file);
    data[_size] = '\0';

    SetWindowText(hBreakdownExpenses, data);

}

void open_file( HWND hWnd){

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = "Breakdown-Income.TXT";

    GetOpenFileName(&ofn);
    display_file(ofn.lpstrFile);

}

void open_file2(HWND hWnd){

    OPENFILENAME ofn2;
    ZeroMemory(&ofn2, sizeof(OPENFILENAME));

    ofn2.lStructSize = sizeof(OPENFILENAME);
    ofn2.hwndOwner = hWnd;
    ofn2.lpstrFile = "Breakdown-Expenses.TXT";

    GetOpenFileName(&ofn2);
    display_file2(ofn2.lpstrFile);

}


void registerDialogBreakdown(HINSTANCE hInst){

    WNDCLASSW dialog = {0};

    HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));

    dialog.hbrBackground = hb;
    dialog.hCursor = LoadCursor (NULL, IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"myDialogClassBreakdown";
    dialog.lpfnWndProc = DialogProcedureBreakdown;

    RegisterClassW(&dialog);
}

void displayDialogBreakdown(HWND hWnd){

    CreateWindowW(L"myDialogClassBreakdown", L"BREAKDOWN", WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU ,
                  850, 100, 415, 480, hWnd, NULL, NULL, NULL);

    EnableWindow(hWnd, TRUE);
}

void AddBreakdownControls(HWND hWnd){

    hIncBreakdown = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  55, 10, 305, 35, hWnd, NULL, NULL, NULL);
    SendMessage(hIncBreakdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bInc);

    hExpBreakdown = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
                  55, 210, 325, 40, hWnd, NULL, NULL, NULL);
    SendMessage(hExpBreakdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bExp);

    hBreakdownIncome = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_MULTILINE | ES_LEFT | WS_BORDER | ES_READONLY, //declaring the editable text box (the user can input or press the button if they want)
                  45, 50, 325, 150, hWnd, NULL, NULL, NULL);
    hBreakdownExpenses = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE | ES_LEFT | WS_BORDER | ES_READONLY, //declaring the editable text box (the user can input or press the button if they want)
                  45, 250, 325, 150, hWnd, NULL, NULL, NULL);

    HFONT hFontBox = CreateFont (17, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,                // loading font style using HFONT
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    SendMessage(hBreakdownIncome, WM_SETFONT, (LPARAM)hFontBox, TRUE);
    SendMessage(hBreakdownExpenses, WM_SETFONT, (LPARAM)hFontBox, TRUE);
}

void AddMenusIncEx(HWND hWnd){       //add menu function that accepts the window handler as the parameter

    hMenu = CreateMenu();       //creating menus using HMENU

    AppendMenu(hMenu, MF_STRING, FILE_MENU_ABOUT, "About");     //menus
    AppendMenu(hMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    SetMenu(hWnd, hMenu);
}

