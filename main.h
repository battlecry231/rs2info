#include <OpenNI.h>
//#include <PS1080.h>
#include <string>
#include <iostream>
//#include <algorithm>
//#include <map>*/
#include <libudev.h>

class RecorderRS2
{
public:
    RecorderRS2()
    {
        deviceURI = openni::ANY_DEVICE;
        // loading all driver
        rc = openni::OpenNI::initialize();
    }

    explicit RecorderRS2(const char *uri)
    {
        deviceURI = uri;
        // loading all driver
        rc = openni::OpenNI::initialize();
    }
    ~RecorderRS2()
    {
        openni::OpenNI::shutdown();
    }
    void setup()
    {
        // setup camera
	    rc = device.open(deviceURI);
        // catch errors
        if (rc != openni::STATUS_OK)
        {
            printf("Recorder: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
            openni::OpenNI::shutdown();
            exit(1);
        }
    }

    void depth(int i = 10)
    {
        if (!depthSetup)
        {
            // depth modes
            const openni::Array<openni::VideoMode> &modesDepth = device.getSensorInfo(openni::SENSOR_DEPTH)->getSupportedVideoModes();
            openni::VideoMode depthMode(modesDepth[i]);

            // create depth stream
            rc = _depth.create(device, openni::SENSOR_DEPTH);
            // catch errors
            if (rc == openni::STATUS_OK)
            {
                rc = _depth.setVideoMode(depthMode);
                if (rc != openni::STATUS_OK)
                {
                    printf("Recorder: Couldn't find depth mode:\n%s\n", openni::OpenNI::getExtendedError());
                    _depth.destroy();
                }
            }
            else
            {
                printf("Recorder: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
            }
            depthSetup = true;
        }
    }

    void color(int i = 45)
    {
        if (!colorSetup)
        {
            // color modes
            const openni::Array<openni::VideoMode> &modesColor = device.getSensorInfo(openni::SENSOR_COLOR)->getSupportedVideoModes();
            openni::VideoMode colorMode(modesColor[i]);

            // create depth stream
            rc = _color.create(device, openni::SENSOR_COLOR);
            // catch errors
            if (rc == openni::STATUS_OK)
            {
                rc = _color.setVideoMode(colorMode);
                if (rc != openni::STATUS_OK)
                {
                    printf("Recorder: Couldn't find color mode:\n%s\n", openni::OpenNI::getExtendedError());
                    _color.destroy();
                }
            }
            else
            {
                printf("Recorder: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
            }
            colorSetup = true;
        }
    }

    void both()
    {
        if (!depthSetup){this->depth();}
        else {printf("Depth stream is already setup.");}
        if (!colorSetup){this->color();}
        else {printf("Color stream is already setup.");}
    }

    void startStream()
    {
        // start depth stream
        rc = _depth.start();
            if (rc != openni::STATUS_OK)
            {
                printf("Recorder: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
                _depth.destroy();
            }
        _depth.setMirroringEnabled(false);

        // start color stream
        rc = _color.start();
            if (rc != openni::STATUS_OK)
            {
                printf("Recorder: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
                _color.destroy();
            }
        // Settings from Logger2
        _color.setMirroringEnabled(false);
        _color.getCameraSettings()->setAutoExposureEnabled(false);
        _color.getCameraSettings()->setAutoWhiteBalanceEnabled(false);
    }

    void startRecorder(const char* filepath){
        recorder.create(filepath);
        recorder.attach(_depth);
        recorder.attach(_color);
        recorder.start();
    }

    void stop()
    {
        recorder.stop();
        recorder.destroy();
        device.close();
        //std::cout << "Closed sucessfuly" << std::endl;
    }
private:
    bool depthSetup = false;
    bool colorSetup = false;
    openni::Status rc = openni::STATUS_OK;
	openni::Device device;
	openni::VideoStream _depth, _color;
    openni::Recorder recorder;
	const char* deviceURI;
    
};
