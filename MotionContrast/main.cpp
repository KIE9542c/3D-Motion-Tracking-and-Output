#include "motionContrast.h"
#include <QtWidgets/QApplication>
#include"MotionContrastor.h"
using namespace std;
int main(int argc, char *argv[])
{
	MotionContrastor contrastor;
	contrastor.contrastVnect("test\\test2_640360_vnect.json", "test\\test1_640360_vnect.json");
	QApplication a(argc, argv);
	motionContrast w;
	w.show();
	return a.exec();
}
