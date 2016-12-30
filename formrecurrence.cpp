/* Copyright 2016 EtlamGit*/

#include "formrecurrence.h"
#include "ui_formrecurrence.h"

#include <QDate>
#include <QShortcut>


FormRecurrence::FormRecurrence(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormRecurrence)
{
	ui->setupUi(this);

	// connect GUI elements to code
	connect( ui->comboBox_Select,   SIGNAL( currentIndexChanged      (const QString &) ),
             this,                  SLOT  ( recurrenceSelectorChanged(const QString &) ) );
	connect( ui->comboBox_WeekDay,  SIGNAL( currentIndexChanged      (int) ),
             this,                  SLOT  ( recurrenceWeekdayChanged (int) ) );
	connect( ui->comboBox_MonthDay, SIGNAL( currentIndexChanged      (int) ),
             this,                  SLOT  ( recurrenceMonthChanged   (int) ) );

	connect( ui->pushButton_Generate, SIGNAL( clicked              (bool) ),
             this,                    SLOT  ( generateButtonPressed(bool) ) );

	// pressing DEL activates the slots only when list widget has focus
   QShortcut* shortcut = new QShortcut( QKeySequence(Qt::Key_Delete), ui->listWidget_Dates );
   connect( shortcut, SIGNAL( activated () ),
			this,     SLOT  ( deleteItem() ) );

   // fill year combobox
   int currentyear = QDate::currentDate().year();
   ui->comboBox_Year->clear();
   ui->comboBox_Year->addItem(QString::QString("%1").arg( currentyear,    4, 10), currentyear  );
   ui->comboBox_Year->addItem(QString::QString("%1").arg( currentyear+1 , 4, 10), currentyear+1);
}

FormRecurrence::~FormRecurrence()
{
	delete ui;
}

// public interface

int FormRecurrence::getNumDates()
{
	return ui->listWidget_Dates->count();
}

QString FormRecurrence::getDate( int idx )
{
	return ui->listWidget_Dates->item(idx)->text();
}


// actions based on GUI interaction

// private slot
void FormRecurrence::recurrenceSelectorChanged( const QString & text )
{
	if (text == "daily")
	{
		ui->comboBox_WeekDay->setEnabled( false );
		ui->comboBox_MonthDay->setEnabled( false );
	}
	if (text == "weekly")
	{
		ui->comboBox_WeekDay ->setEnabled( true );
		ui->comboBox_MonthDay->setEnabled( false );
	}
	if (text == "monthly")
	{
		ui->comboBox_WeekDay ->setEnabled( false );
		ui->comboBox_MonthDay->setEnabled( true );
	}
}

// private slot
void FormRecurrence::recurrenceWeekdayChanged( int index )
{}

// private slot
void FormRecurrence::recurrenceMonthChanged( int index )
{}

// private slot
void FormRecurrence::generateButtonPressed( bool checked )
{
  // get year
  int year = ui->comboBox_Year->currentData().toInt();
	QDate date  = QDate::QDate( year,   1, 1 );
	QDate edate = QDate::QDate( year+1, 1, 1 );

	QString text = ui->comboBox_Select->currentText();
	if (text == "daily")
	{
		// loop over all days in year
		while (date<edate)
		{
			QString dtext = date.toString("yyyy-MM-dd");
			ui->listWidget_Dates->addItem( dtext );
			date = date.addDays(1);
		}
	}
	if (text == "weekly")
	{
		// advance to first occurance of this weekday in year
		int idx = 1 + ui->comboBox_WeekDay->currentIndex();
		while (date.dayOfWeek() != idx)
		{
			date = date.addDays(1);
		}
		// loop over all weeks in year
		while (date<edate)
		{
			QString dtext = date.toString("yyyy-MM-dd");
			ui->listWidget_Dates->addItem( dtext );
			date = date.addDays(7);
		}
	}
	if (text == "monthly")
	{
		// advance to first occurance of this weekday in year
		int idx = 1 + ui->comboBox_MonthDay->currentIndex();
		for (int i=1; i<=12; ++i)
		{
			QDate date  = QDate::QDate( year, i, idx );
			// remove day overlapping to next month (e.g. 31.Feb)
			if (date.day() == idx)
			{
				QString dtext = date.toString("yyyy-MM-dd");
				ui->listWidget_Dates->addItem( dtext );
			}
		}
	}

}

void FormRecurrence::deleteItem()
{
    qDeleteAll( ui->listWidget_Dates->selectedItems() );
}
