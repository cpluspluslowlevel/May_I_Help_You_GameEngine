#include <iostream>

#include <Windows.h>

#include "MIHYCore.h"
#include "MIHYCore_DataStruct.h"
#include "MIHYPlatform_Library_Loader.h"

#include "MIHYVulkan.h"
#include "MIHYVulkan_Device.h"

LRESULT CALLBACK message_processor(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param){
    switch (message){
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(window_handle, message, w_param, l_param);
    }
    return 0;
}

INT WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE, LPSTR command, INT command_number){

    std::cout << "Test start!" << std::endl;

    MIHYCore::DataStruct::mihyvector_unittest();
    MIHYCore::DataStruct::mihylist_unittest();
    MIHYCore::DataStruct::mihyhashmap_unittest();

    std::cout << "Test end!" << std::endl;

    WNDCLASSEX window_class{};
    window_class.cbSize         = sizeof(WNDCLASSEX);
    window_class.cbClsExtra     = 0;
    window_class.cbWndExtra     = 0;
    window_class.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    window_class.hCursor        = LoadCursor(NULL, IDC_ARROW);
    window_class.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
    window_class.lpfnWndProc    = message_processor;
    window_class.hInstance      = instance_handle;
    window_class.lpszClassName  = "MIHYVulkan";
    window_class.lpszMenuName   = NULL;
    window_class.style          = CS_HREDRAW | CS_VREDRAW;
    RegisterClassEx(&window_class);

    HWND window_handle = CreateWindow("MIHYVulkan", "MIHYVulkan", WS_OVERLAPPEDWINDOW,
                                      0, 0, 800, 600,
                                      NULL, NULL, instance_handle, NULL);

    ShowWindow(window_handle, SW_SHOW);
    UpdateWindow(window_handle);

    MIHYVulkan::mihyvulkan_find_physical_device();

    MSG message{};
    ZeroMemory(&message, sizeof(message));
    while(message.message != WM_QUIT){
        if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return 0;

}