/* Copyright 2016 EtlamGit*/

#include "formevent.h"
#include "ui_formevent.h"

#include <iostream>
#include <QTimeZone>


FormEvent::FormEvent(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormEvent)
{
  ui->setupUi(this);

  // fill time zones
  QList<QByteArray> ids = QTimeZone::availableTimeZoneIds();
    foreach (QByteArray id, ids)
  {
        ui->comboBox_TimeZone->addItem(id);
    }

  // find & select local (=system) Time Zone
  QString    sysTimeZone = QTimeZone::systemTimeZoneId();
  int index = ui->comboBox_TimeZone->findText( sysTimeZone );
  if ( index != -1 ) { // -1 for not found
     ui->comboBox_TimeZone->setCurrentIndex( index );
  }
}

FormEvent::~FormEvent()
{
  delete ui;
}

// public interface
QString FormEvent::getTitle()
{
  return ui->lineEdit_Title->text();
}

bool FormEvent::isLocation()
{
  return ui->groupBox_Location->isChecked();
}

QString FormEvent::getLocation()
{
  return ui->lineEdit_Location->text();
}

bool FormEvent::isStartTime()
{
  return ui->checkBox_Start->isChecked();
}

QTime FormEvent::getStartTime()
{
  return ui->timeEdit_Start->time();
}

QString FormEvent::getStartTimeText()
{
  return ui->timeEdit_Start->text();
}

bool FormEvent::isEndTime()
{
  return ui->checkBox_End->isChecked();
}

QTime FormEvent::getEndTime()
{
  return ui->timeEdit_End->time();
}

QString FormEvent::getEndTimeText()
{
  return ui->timeEdit_End->text();
}

bool FormEvent::isComment()
{
  return ui->groupBox_Comment->isChecked();
}

QString FormEvent::getComment()
{
  return ui->plainTextEdit->toPlainText();
}

QString FormEvent::getTimeZone()
{
  return ui->comboBox_TimeZone->currentText();
}


