/* Copyright 2016 EtlamGit*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  void write_calendar_header( FILE * pFile, QString calName );
  void write_event( FILE * pFile, QString date );
  void write_calendar_footer( FILE * pFile );

private slots:
  void saveButtonPressed(bool);

};

#endif // MAINWINDOW_H
