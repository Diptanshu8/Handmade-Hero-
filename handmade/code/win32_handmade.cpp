#include <windows.h>

LRESULT CALLBACK MainWindowCallBack(HWND   Window,  
                            UINT   Message,
                            WPARAM WParam,
                            LPARAM LParam
)
{
  LRESULT Result=0;
  switch(Message)
  {
    case WM_CREATE:
    {
      OutputDebugStringA("WM_CREATE\n");
    }break;

    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    }break;
    
    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY\n");
    }break;
    
    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE\n");
    }break;
    
    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    }break;  

    case WM_PAINT:
    {
          PAINTSTRUCT Paint;
          HDC DeviceContext = BeginPaint( Window,&Paint);
          
          int X = Paint.rcPaint.left;
          int Y = Paint.rcPaint.top;
          LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
          LONG Width = Paint.rcPaint.right - Paint.rcPaint.left;
          
          PatBlt(DeviceContext,X,Y,Width,Height,WHITENESS);
          EndPaint( Window,&Paint);
    }break;

    default:
    {
//      OutputDebugStringA("Default\n");
      Result = DefWindowProc(Window,Message,WParam,LParam);
    }break;
  }
  return(Result);
}

int CALLBACK 
WinMain(HINSTANCE Instance,
	   	HINSTANCE PrevInstance,
	   	LPSTR CommandLine,
	   	int ShowCode)
{

  WNDCLASS WindowClass={};
  WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallBack;
  WindowClass.hInstance = Instance;
//  HICON     hIcon;
  WindowClass.lpszClassName = "HandmadeHeroWindowClass";
	
  if (RegisterClass(&WindowClass))
  {
    HWND WindowHandle=CreateWindowEx( 0,
                                      WindowClass.lpszClassName,
                                      "Handmade Window",
                                      WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      0,
                                      0,
                                      Instance,
                                      0);
      if (WindowHandle)
      {
          MSG Message;
          for(;;){
              BOOL MessageResult = GetMessage(&Message,0,0,0);
              if (MessageResult>0)
               {
                 TranslateMessage(&Message);
                 DispatchMessage(&Message);
               } 
               else
              {
                  break;
              }  
          }
          
      }
      else
      {
        //LOgging
      }
  }
  return 0;
}