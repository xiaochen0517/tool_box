#include <iostream>
#include <cstring>
#include "Windows.h"

int main(int argc, char *argv[])
{
  // check arguments count
  if (argc != 2)
  {
    std::cout << "Usage: " << "2/4" << "set display" << std::endl;
    // 获取当前显示器列表
    DISPLAY_DEVICEA displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICEA);
    for (DWORD i = 0; EnumDisplayDevicesA(nullptr, i, &displayDevice, 0); i++)
    {
      std::cout << "Device Name: " << displayDevice.DeviceName << std::endl;
      std::cout << "Device String: " << displayDevice.DeviceString << std::endl;
      std::cout << "Device ID: " << displayDevice.DeviceID << std::endl;
      std::cout << "Device Key: " << displayDevice.DeviceKey << std::endl;
      std::cout << "State Flags: " << displayDevice.StateFlags << std::endl;
      std::cout << std::endl;
    }
    return 0;
  }

  // get display device name
  const char *displayDeviceName = R"(\\.\DISPLAY2)";

  // get current display settings
  DEVMODE devMode;
  devMode.dmSize = sizeof(DEVMODE);
  EnumDisplaySettingsEx(displayDeviceName, ENUM_CURRENT_SETTINGS, &devMode, 1);

  // change display settings
  std::cout << "param: " << argv[1] << std::endl;
  if (strcmp(argv[1], "4") == 0)
  {
    devMode.dmPelsWidth = 3840;  // set width
    devMode.dmPelsHeight = 2160; // set height
  } else if (strcmp(argv[1], "2") == 0)
  {
    devMode.dmPelsWidth = 2560;  // set width
    devMode.dmPelsHeight = 1440; // set height
  } else
  {
    std::cout << "Usage: 2/4 set display" << std::endl;
    return 1;
  }
  devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; // set fields

  LONG result = ChangeDisplaySettingsEx(displayDeviceName, &devMode, nullptr, CDS_UPDATEREGISTRY | CDS_RESET, nullptr);
  if (result == DISP_CHANGE_SUCCESSFUL)
  {
    // change success
    std::cout << "Change success" << std::endl;
  } else
  {
    // change failed
    std::cout << "Change failed" << std::endl;
  }

  // 等待用户输入
  std::cout << "Press any key to continue..." << std::endl;
  std::cin.get();
  return 0;
}
