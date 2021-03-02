#include <QApplication>
#include <QPushButton>
#include <QFrame>

int main(int argc, char **argv) {

	QApplication a(argc,argv);
	QPushButton hello("Hello world!", 0);
	hello.resize(200,30);
	hello.show();
	return a.exec();
}
