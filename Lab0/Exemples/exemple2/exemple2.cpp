#include <QApplication>
#include <QPushButton>
#include <QFrame>
int main(int argc, char **argv) {

	QApplication a(argc,argv);
	QFrame F(0,NULL);
	QPushButton hello("Hello world!",&F);

	a.connect(&hello, SIGNAL(clicked()), &F, SLOT(close()));

	hello.resize(200,200);
	F.show();
	return a.exec();
}
