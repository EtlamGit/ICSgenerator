/* Copyright 2016 EtlamGit*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTimeZone>
#include <QHash>
#include <stdio.h>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow( parent )
  , ui( new Ui::MainWindow )
{
  ui->setupUi(this);

  // connect GUI elements to code
  connect( ui->pushButton_save, SIGNAL( clicked          (bool) ),
           this,                SLOT  ( saveButtonPressed(bool) ) );

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::saveButtonPressed( bool )
{
  // get filename to save calendar to
  QString fileName = QFileDialog::getSaveFileName(
    this,
    tr("Save Calendar"),
        "",
        tr("ICS calendars (*.ics)") );

  // check for present filename
  if (fileName.isEmpty())
    return;

  // write calendar to file
  FILE * pFile;
  pFile = fopen( fileName.toUtf8().constData(),"w" );
  if ( pFile != NULL )
  {
    // write header
    QString calName = QFileInfo( fileName ).completeBaseName();
    write_calendar_header( pFile, calName );

    // write all events
    int N = ui->widget_recurrence->getNumDates();
    for (int i=0; i<N; ++i)
    {
      QString date = ui->widget_recurrence->getDate( i );
      write_event( pFile, date );
    }

    // write footer
    write_calendar_footer( pFile );
    fclose (pFile);
  }
}

void MainWindow::write_calendar_header( FILE * pFile, QString calName )
{
  fprintf( pFile, "BEGIN:VCALENDAR\n" );
  fprintf( pFile, "PRODID:-//Mozilla.org/NONSGML Mozilla Calendar V1.1//EN\n" );
  fprintf( pFile, "VERSION:2.0\n" );
  fprintf( pFile, "CALSCALE:GREGORIAN\n" );
  fprintf( pFile, "METHOD:PUBLISH\n" );
  fprintf( pFile, "X-WR-CALNAME:%s\n", calName.toUtf8().constData() );
//  fprintf( pFile, "X-WR-TIMEZONE:Europe/Berlin\n" );
}

void MainWindow::write_event( FILE * pFile, QString datetext )
{
    // construct start and end QDateTime point
  QDate date( datetext.mid(0,4).toInt(),
        datetext.mid(5,2).toInt(),
        datetext.mid(8,2).toInt() );
  QDateTime time0( date, ui->widget_event->getStartTime(), Qt::UTC );
  QDateTime time1( date, ui->widget_event->getEndTime(),   Qt::UTC );

  // convert from selected TimeZone to UTC
  QTimeZone timezone( QByteArray(ui->widget_event->getTimeZone().toUtf8()) );
  time0 = time0.addSecs( -timezone.offsetFromUtc( time0 ) );
  time1 = time1.addSecs( -timezone.offsetFromUtc( time1 ) );

  QString eventStart    = time0.toString("yyyyMMdd") + "T" + time0.toString("hhmmss") + "Z";
  QString eventEnd      = time1.toString("yyyyMMdd") + "T" + time1.toString("hhmmss") + "Z";
  QString eventTitle    = ui->widget_event->getTitle();
  QString eventLocation = ui->widget_event->getLocation();
  QString eventClass    = ui->widget_event->getClass();

  uint hash = qHash( eventTitle + eventStart + eventEnd + eventLocation );

  fprintf( pFile, "BEGIN:VEVENT\n" );
  fprintf( pFile, "UID:ICSgenerator%08x\n", hash );
  fprintf( pFile, "SUMMARY:%s\n", eventTitle.toUtf8().constData() );
  if (ui->widget_event->isStartTime())
    fprintf( pFile, "DTSTART:%s\n", eventStart.toUtf8().constData() );
  if (ui->widget_event->isEndTime())
    fprintf( pFile, "DTEND:%s\n",   eventEnd.toUtf8().constData() );
  if (ui->widget_event->isLocation())
    fprintf( pFile, "LOCATION:%s\n", eventLocation.toUtf8().constData() );
  if (ui->widget_event->isClass())
    fprintf( pFile, "CLASS:%s\n", eventClass.toUtf8().constData() );
  fprintf( pFile, "END:VEVENT\n" );
}

void MainWindow::write_calendar_footer( FILE * pFile )
{
  fprintf( pFile, "END:VCALENDAR\n" );
}
