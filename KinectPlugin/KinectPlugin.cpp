#include <k4a/k4a.hpp>
#include <iostream>

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
bool OpenDefaultK4ADevice()
{
	if (::k4a::device::get_installed_count() <= 0)
		return false;

	::k4a::device defaultDevice = ::k4a::device::open(0);

	if (!defaultDevice)
		return false;

	k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	config.camera_fps = K4A_FRAMES_PER_SECOND_15;
	config.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
	config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	config.color_resolution = K4A_COLOR_RESOLUTION_1080P;

	try
	{
		defaultDevice.start_cameras(&config);
	}
	catch (...)
	{
		defaultDevice.close();
		return false;
	}


	return true;
}

#ifdef STANDALONE_EXECUTABLE
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void main()
{
	if (OpenDefaultK4ADevice())
		::std::cout << "OpenDefaultDevice succeeded" << ::std::endl;
	else
		::std::cout << "OpenDefaultDevice failed" << ::std::endl;

	system("pause");
}
#else
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
extern "C" __declspec(dllexport)
bool
KinectPlugin_OpenDefaultDevice()
{
	return OpenDefaultK4ADevice();
}
#endif
