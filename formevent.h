/* Copyright 2016 EtlamGit*/

#ifndef FORMEVENT_H
#define FORMEVENT_H

#include <QWidget>

namespace Ui {
class FormEvent;
}

class FormEvent : public QWidget
{
	Q_OBJECT

public:
	explicit FormEvent(QWidget *parent = 0);
	~FormEvent();

	// public interface
	QString getTitle();
	bool    isLocation();
	QString getLocation();
	bool    isStartTime();
	QTime   getStartTime();
	QString getStartTimeText();
	bool    isEndTime();
	QTime   getEndTime();
	QString getEndTimeText();
	bool    isComment();
	QString getComment();
	QString getTimeZone();

private:
	Ui::FormEvent *ui;
};

#endif // FORMEVENT_H
