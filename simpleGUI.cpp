/*
──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
───▄▄██▌█ Beeep Beep-------------      ENG Yousef Osama
▄▄▄▌▐██▌█ Gamer_is_coding--------       ECU Student
███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
▀(@)▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀(@)▀
*/
#include <windows.h>
#include <string>
#include <sstream>
#include "chain.h" 

// Global variables
Chain<int> linkedList;
HWND hListDisplay, hInputBox, hPositionBox; // Handles for input fields and list display

// Function prototypes
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void InsertElement(HWND hwnd);
void DeleteElement(HWND hwnd);
void ShowList();
void ShowAverage(HWND hwnd);
void SearchElement(HWND hwnd);
void UpdateElement(HWND hwnd);
void ShowHelp(HWND hwnd);

// Entry point for the application
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"LinkedList GUI";

    // Define the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Linked List GUI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 500,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Process messages sent to the window
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Static text labels
        CreateWindow(L"STATIC", L"Enter Value:", WS_VISIBLE | WS_CHILD, 50, 20, 100, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(L"STATIC", L"Enter Index:", WS_VISIBLE | WS_CHILD, 50, 50, 100, 20, hwnd, NULL, NULL, NULL);

        // Input fields
        hInputBox = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 20, 100, 20, hwnd, NULL, NULL, NULL);
        hPositionBox = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 50, 100, 20, hwnd, NULL, NULL, NULL);

        // Buttons
        CreateWindow(L"BUTTON", L"Insert", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(L"BUTTON", L"Delete", WS_VISIBLE | WS_CHILD, 200, 100, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(L"BUTTON", L"Display", WS_VISIBLE | WS_CHILD, 50, 150, 100, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow(L"BUTTON", L"Average", WS_VISIBLE | WS_CHILD, 200, 150, 100, 30, hwnd, (HMENU)4, NULL, NULL);
        CreateWindow(L"BUTTON", L"Search", WS_VISIBLE | WS_CHILD, 50, 200, 100, 30, hwnd, (HMENU)5, NULL, NULL);
        CreateWindow(L"BUTTON", L"Update", WS_VISIBLE | WS_CHILD, 200, 200, 100, 30, hwnd, (HMENU)6, NULL, NULL);

        // Help button
        CreateWindow(L"BUTTON", L"Help", WS_VISIBLE | WS_CHILD, 350, 100, 100, 30, hwnd, (HMENU)7, NULL, NULL);

        // Real-time list display
        hListDisplay = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 250, 400, 150, hwnd, NULL, NULL, NULL);
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1: // Insert button
            InsertElement(hwnd);
            break;
        case 2: // Delete button
            DeleteElement(hwnd);
            break;
        case 3: // Display button
            ShowList();
            break;
        case 4: // Average button
            ShowAverage(hwnd);
            break;
        case 5: // Search button
            SearchElement(hwnd);
            break;
        case 6: // Update button
            UpdateElement(hwnd);
            break;
        case 7: // Help button
            ShowHelp(hwnd);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Function to insert an element
void InsertElement(HWND hwnd)
{
    wchar_t valueBuffer[10];
    GetWindowText(hInputBox, valueBuffer, 10);
    int value = _wtoi(valueBuffer); // Convert to integer

    linkedList.Insert(linkedList.Length(), value);
    ShowList();
    MessageBox(hwnd, L"Element inserted!", L"Success", MB_OK);
}

// Function to delete an element by position
void DeleteElement(HWND hwnd)
{
    wchar_t posBuffer[10];
    GetWindowText(hPositionBox, posBuffer, 10);
    int position = _wtoi(posBuffer);

    int deletedValue;
    try
    {
        linkedList.Delete(position, deletedValue);
        ShowList();
        MessageBox(hwnd, (L"Deleted value: " + std::to_wstring(deletedValue)).c_str(), L"Deleted", MB_OK);
    }
    catch (...)
    {
        MessageBox(hwnd, L"Invalid position!", L"Error", MB_OK);
    }
}

// Function to display the list
void ShowList()
{
    std::wstringstream ss;
    int value;

    ss << L"List elements: ";
    for (int i = 1; i <= linkedList.Length(); i++)
    {
        linkedList.Find(i, value);
        ss << value << L" ";
    }

    if (linkedList.Length() == 0)
        ss << L"List is empty.";

    SetWindowText(hListDisplay, ss.str().c_str());
}

// Function to show the average
void ShowAverage(HWND hwnd)
{
    if (linkedList.Length() == 0)
    {
        MessageBox(hwnd, L"The list is empty.", L"Average", MB_OK);
        return;
    }

    double average = linkedList.CalculateAverage();
    std::wstring message = L"Average: " + std::to_wstring(average);
    MessageBox(hwnd, message.c_str(), L"Average", MB_OK);
}

// Function to search for an element
void SearchElement(HWND hwnd)
{
    wchar_t valueBuffer[10];
    GetWindowText(hInputBox, valueBuffer, 10);
    int value = _wtoi(valueBuffer);

    int position = linkedList.Search(value);
    if (position)
    {
        MessageBox(hwnd, (L"Value found at position: " + std::to_wstring(position)).c_str(), L"Search", MB_OK);
    }
    else
    {
        MessageBox(hwnd, L"Value not found.", L"Search", MB_OK);
    }
}

// Function to update an element at a position
void UpdateElement(HWND hwnd)
{
    wchar_t posBuffer[10], valueBuffer[10];
    GetWindowText(hPositionBox, posBuffer, 10);
    GetWindowText(hInputBox, valueBuffer, 10);

    int position = _wtoi(posBuffer);
    int newValue = _wtoi(valueBuffer);

    if (linkedList.Update(position, newValue))
    {
        ShowList();
        MessageBox(hwnd, L"Value updated!", L"Update", MB_OK);
    }
    else
    {
        MessageBox(hwnd, L"Invalid position!", L"Error", MB_OK);
    }
}

// Function to show help message
void ShowHelp(HWND hwnd)
{
    std::wstring helpMessage = L"Insert: Adds a value to the list.\n"
        L"Delete: Deletes an element at a given position.\n"
        L"Display: Shows the list elements.\n"
        L"Average: Displays the average of all elements.\n"
        L"Search: Searches for a value in the list.\n"
        L"Update: Updates the value at a given position.\n\n"
        L"Enter:\n"
        L"- Input field for entering values to insert or search.\n"
        L"- Position input is used for Delete, Update, and finding specific elements.\n\n"
        L"List:\n"
        L"- Displays the current linked list elements below the buttons.\n"
        L"- You can see the list's content after each operation.\n";

    MessageBox(hwnd, helpMessage.c_str(), L"Help", MB_OK);
}

/*
The Output (Assumption):
------------------------
Inserting elements: 10, 20, 30, 40, 50
Deleting element at position 3
Updating element at position 2 with value 25
Searching for element 40 in the list (position 4)
Calculating average of elements in the list (10, 25, 40, 50) -> 31.25
Displaying the list elements after each operation (Insert, Delete, Update, Search, Average) using the GUI.
*/