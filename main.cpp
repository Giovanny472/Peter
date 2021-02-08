#include <QtWidgets>

#include "PeterKeyPlot/PeterKeyPlot.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QLabel *lbl = new QLabel("hoiiiii");

  PeterKeyPlot* aPlot = new PeterKeyPlot(lbl);

  aPlot->addPoint(5,5);
  aPlot->addPoint(3,5);
  aPlot->addPoint(5,2);
  aPlot->addPoint(10,2);
  aPlot->addPoint(13,5);
  aPlot->addPoint(10,8);
  aPlot->addPoint(9,8);
  aPlot->addPoint(8,12);
  aPlot->addPoint(7,6);
  aPlot->addPoint(5,5);


  aPlot->setTitle("тест");
  aPlot->Show();
  //lbl->resize(  );
  //lbl->show();

  return a.exec();
}
