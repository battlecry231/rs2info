#include <OpenNI.h>
//#include <PS1080.h>
#include <string>
#include <iostream>
//#include <algorithm>
//#include <map>*/
#include <libudev.h>

int main(int argc, char** argv){
    openni::Status rc = openni::STATUS_OK;

	openni::Device device;
	openni::VideoStream depth, color;
	const char* deviceURI = openni::ANY_DEVICE;
	if (argc > 1)
	{
		deviceURI = argv[1];
	}

    // loading all driver
	rc = openni::OpenNI::initialize();

    // catch errors
	printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());

    // setup camera
	rc = device.open(deviceURI);

    // catch errors
    if (rc != openni::STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}

    // create depth stream
	rc = depth.create(device, openni::SENSOR_DEPTH);
    // catch errors
	if (rc == openni::STATUS_OK)
	{
		rc = depth.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
			depth.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	// depth modes
	const openni::Array<openni::VideoMode> &modesDepth = device.getSensorInfo(openni::SENSOR_DEPTH)->getSupportedVideoModes();

	for (int i = 0; i < (modesDepth.getSize()); i++){
		printf("%i: %ix%i, %i fps, %i format\n", i, modesDepth[i].getResolutionX(), modesDepth[i].getResolutionY(),
            modesDepth[i].getFps(), modesDepth[i].getPixelFormat());
	}
	
	// RGB modes
	const openni::Array<openni::VideoMode> &modesRGB = device.getSensorInfo(openni::SENSOR_COLOR)->getSupportedVideoModes();

	for (int i = 0; i < (modesRGB.getSize()); i++){
		printf("%i: %ix%i, %i fps, %i format\n", i, modesRGB[i].getResolutionX(), modesRGB[i].getResolutionY(),
            modesRGB[i].getFps(), modesRGB[i].getPixelFormat());
	}
	/*
	SENSOR_DEPTH
	0:  1280 x 720, 30 fps, 100 format
	1:  1280 x 720, 15 fps, 100 format
	2:  1280 x 720,  6 fps, 100 format
	3:  848  x 480, 90 fps, 100 format
	4:  848  x 480, 60 fps, 100 format
	5:  848  x 480, 30 fps, 100 format
	6:  848  x 480, 15 fps, 100 format
	7:  848  x 480,  6 fps, 100 format
	8:  640  x 480, 90 fps, 100 format
	9:  640  x 480, 60 fps, 100 format
	10: 640  x 480, 30 fps, 100 format
	11: 640  x 480, 15 fps, 100 format
	12: 640  x 480,  6 fps, 100 format
	13: 640  x 360, 90 fps, 100 format
	14: 640  x 360, 60 fps, 100 format
	15: 640  x 360, 30 fps, 100 format
	16: 640  x 360, 15 fps, 100 format
	17: 640  x 360,  6 fps, 100 format
	18: 480  x 270, 90 fps, 100 format
	19: 480  x 270, 60 fps, 100 format
	20: 480  x 270, 30 fps, 100 format
	21: 480  x 270, 15 fps, 100 format
	22: 480  x 270,  6 fps, 100 format
	23: 424  x 240, 90 fps, 100 format
	24: 424  x 240, 60 fps, 100 format
	25: 424  x 240, 30 fps, 100 format
	26: 424  x 240, 15 fps, 100 format
	27: 424  x 240,  6 fps, 100 format
	
	PIXEL_FORMAT_DEPTH_1_MM = 100
	*/

	/*
	0:  1920 x 1080, 30 fps, 200 format
	1:  1920 x 1080, 30 fps, 203 format
	2:  1920 x 1080, 30 fps, 205 format
	3:  1920 x 1080, 15 fps, 200 format
	4:  1920 x 1080, 15 fps, 203 format
	5:  1920 x 1080, 15 fps, 205 format
	6:  1920 x 1080,  6 fps, 200 format
	7:  1920 x 1080,  6 fps, 203 format
	8:  1920 x 1080,  6 fps, 205 format
	9:  1280 x  720, 30 fps, 200 format
	10: 1280 x  720, 30 fps, 203 format
	11: 1280 x  720, 30 fps, 205 format
	12: 1280 x  720, 15 fps, 200 format
	13: 1280 x  720, 15 fps, 203 format
	14: 1280 x  720, 15 fps, 205 format
	15: 1280 x  720,  6 fps, 200 format
	16: 1280 x  720,  6 fps, 203 format
	17: 1280 x  720,  6 fps, 205 format
	18:  960 x  540, 60 fps, 200 format
	19:  960 x  540, 60 fps, 203 format
	20:  960 x  540, 60 fps, 205 format
	21:  960 x  540, 30 fps, 200 format
	22:  960 x  540, 30 fps, 203 format
	23:  960 x  540, 30 fps, 205 format
	24:  960 x  540, 15 fps, 200 format
	25:  960 x  540, 15 fps, 203 format
	26:  960 x  540, 15 fps, 205 format
	27:  960 x  540,  6 fps, 200 format
	28:  960 x  540,  6 fps, 203 format
	29:  960 x  540,  6 fps, 205 format
	30:  848 x  480, 60 fps, 200 format
	31:  848 x  480, 60 fps, 203 format
	32:  848 x  480, 60 fps, 205 format
	33:  848 x  480, 30 fps, 200 format
	34:  848 x  480, 30 fps, 203 format
	35:  848 x  480, 30 fps, 205 format
	36:  848 x  480, 15 fps, 200 format
	37:  848 x  480, 15 fps, 203 format
	38:  848 x  480, 15 fps, 205 format
	39:  848 x  480,  6 fps, 200 format
	40:  848 x  480,  6 fps, 203 format
	41:  848 x  480,  6 fps, 205 format
	42:  640 x  480, 60 fps, 200 format
	43:  640 x  480, 60 fps, 203 format
	44:  640 x  480, 60 fps, 205 format
	45:  640 x  480, 30 fps, 200 format
	46:  640 x  480, 30 fps, 203 format
	47:  640 x  480, 30 fps, 205 format
	48:  640 x  480, 15 fps, 200 format
	49:  640 x  480, 15 fps, 203 format
	50:  640 x  480, 15 fps, 205 format
	51:  640 x  480,  6 fps, 200 format
	52:  640 x  480,  6 fps, 203 format
	53:  640 x  480,  6 fps, 205 format
	54:  640 x  360, 60 fps, 200 format
	55:  640 x  360, 60 fps, 203 format
	56:  640 x  360, 60 fps, 205 format
	57:  640 x  360, 30 fps, 200 format
	58:  640 x  360, 30 fps, 203 format
	59:  640 x  360, 30 fps, 205 format
	60:  640 x  360, 15 fps, 200 format
	61:  640 x  360, 15 fps, 203 format
	62:  640 x  360, 15 fps, 205 format
	63:  640 x  360,  6 fps, 200 format
	64:  640 x  360,  6 fps, 203 format
	65:  640 x  360,  6 fps, 205 format
	66:  424 x  240, 60 fps, 200 format
	67:  424 x  240, 60 fps, 203 format
	68:  424 x  240, 60 fps, 205 format
	69:  424 x  240, 30 fps, 200 format
	70:  424 x  240, 30 fps, 203 format
	71:  424 x  240, 30 fps, 205 format
	72:  424 x  240, 15 fps, 200 format
	73:  424 x  240, 15 fps, 203 format
	74:  424 x  240, 15 fps, 205 format
	75:  424 x  240,  6 fps, 200 format
	76:  424 x  240,  6 fps, 203 format
	77:  424 x  240,  6 fps, 205 format
	78:  320 x  240, 60 fps, 200 format
	79:  320 x  240, 60 fps, 203 format
	80:  320 x  240, 60 fps, 205 format
	81:  320 x  240, 30 fps, 200 format
	82:  320 x  240, 30 fps, 203 format
	83:  320 x  240, 30 fps, 205 format
	84:  320 x  240,  6 fps, 200 format
	85:  320 x  240,  6 fps, 203 format
	86:  320 x  240,  6 fps, 205 format
	87:  320 x  180, 60 fps, 200 format
	88:  320 x  180, 60 fps, 203 format
	89:  320 x  180, 60 fps, 205 format
	90:  320 x  180, 30 fps, 200 format
	91:  320 x  180, 30 fps, 203 format
	92:  320 x  180, 30 fps, 205 format
	93:  320 x  180,  6 fps, 200 format
	94:  320 x  180,  6 fps, 203 format
	95:  320 x  180,  6 fps, 205 format
	*/
    device.close();
	
	openni::OpenNI::shutdown();
    return 0;
}
