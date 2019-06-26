
#include "main.h"

int main(int argc, char* argv[]){
	// create recorder obj
	RecorderRS2 rec;

	rec.setup();
    rec.depth();
	rec.color();
	//rec.both();
	rec.startStream();

	if (argc == 3)
	{
		rec.startRecorder(argv[2]);
	}
	else
	{
		rec.startRecorder("/home/phil/Downloads/record.oni");
	}
	
	printf("Press ENTER to stop");
	std::cin.ignore();
	
	rec.stop();
	
    return 0;
}
