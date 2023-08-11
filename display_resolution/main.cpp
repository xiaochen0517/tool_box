#include <iostream>
#include "Windows.h"

int main(int argc, char *argv[])
{
  // check arguments count
  if (argc != 2)
  {
    std::cout << "Usage: " << "2/4" << "set display" << std::endl;
    return 0;
  }

  // get display device name
  const char *displayDeviceName = "\\\\.\\DISPLAY2";

  // get current display settings
  DEVMODE devMode;
  devMode.dmSize = sizeof(DEVMODE);
  EnumDisplaySettingsEx(displayDeviceName, ENUM_CURRENT_SETTINGS, &devMode, 1);

  // change display settings
  std::cout << "param: " << argv[1] << std::endl;
  if (std::strcmp(argv[1], "4") == 0)
  {
    devMode.dmPelsWidth = 3840;  // set width
    devMode.dmPelsHeight = 2160; // set height
  } else if (std::strcmp(argv[1], "2") == 0)
  {
    devMode.dmPelsWidth = 2560;  // set width
    devMode.dmPelsHeight = 1440; // set height
  } else
  {
    std::cout << "Usage: " << "2/4" << "set display" << std::endl;
    return 1;
  }
  devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; // set fields

  LONG result = ChangeDisplaySettingsEx(displayDeviceName, &devMode, NULL, CDS_UPDATEREGISTRY | CDS_RESET, NULL);
  if (result == DISP_CHANGE_SUCCESSFUL)
  {
    // change success
    std::cout << "Change success" << std::endl;
    return 0;
  } else
  {
    // change failed
    std::cout << "Change failed" << std::endl;
    return 1;
  }
}
