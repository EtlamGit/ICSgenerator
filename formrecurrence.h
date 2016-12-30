/* Copyright 2016 EtlamGit*/

#ifndef FORMRECURRENCE_H
#define FORMRECURRENCE_H

#include <QWidget>

namespace Ui {
class FormRecurrence;
}

class FormRecurrence : public QWidget
{
	Q_OBJECT

public:
	explicit FormRecurrence(QWidget *parent = 0);
	~FormRecurrence();

	int     getNumDates();
	QString getDate( int idx );

private:
	Ui::FormRecurrence *ui;


	// actions based on GUI interaction
private slots:
	void recurrenceSelectorChanged( const QString & text );
	void recurrenceWeekdayChanged( int index );
	void recurrenceMonthChanged( int index );

	void generateButtonPressed( bool checked );

	void deleteItem();

};

#endif // FORMRECURRENCE_H
