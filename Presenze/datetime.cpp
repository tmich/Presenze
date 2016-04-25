#include "stdafx.h"
#include "datetime.h"
#include <sstream>
#include <iomanip>

date::datetime::datetime()
	: datetime(0, 0, 0, 0, 0, 0)
{
}

date::datetime::datetime(int day, int month, int year)
	: datetime(day, month, year, 0, 0, 0)
{
}

date::datetime::datetime(int day, int month, int year, int h, int min, int sec)
	: day_{ day }, mon_{ month }, year_{ year }, hh_{ h }, min_{ min }, sec_{ sec }
{
}

date::datetime::~datetime()
{
}

string date::datetime::to_string() const
{
	stringstream ss;
	ss << to_date_string() << " " << to_time_long_string();
	
	return ss.str();
}

string date::datetime::to_date_string() const
{
	string sep = "/";
	stringstream ss;
	ss << setw(2) << setfill('0') << get_day() << sep << setw(2) << setfill('0') << get_month() << sep << get_year();

	return ss.str();
}

string date::datetime::to_time_string() const
{
	string seph = ":";
	stringstream ss;

	ss << setw(2) << setfill('0') << get_hour() << seph << setw(2) << setfill('0') << get_mins();

	return ss.str();
}

string date::datetime::to_time_long_string() const
{
	string seph = ":";
	stringstream ss;

	ss << to_time_string() << seph << setw(2) << setfill('0') << get_secs();

	return ss.str();
}

bool date::datetime::is_valid() const
{
	// This function will check the given date is valid or not.
	// If the date is not valid then it will return the value false.
	// Need some more checks on the year, though
	if (year_ < 0) return false;
	if (mon_ > 12 || mon_ < 1) return false;
	if (day_ > 31 || day_ < 1) return false;
	if ((day_ == 31 &&
		(mon_ == 2 || mon_ == 4 || mon_ == 6 || mon_ == 9 || mon_ == 11)))
		return false;

	if (day_ == 30 && mon_ == 2) return false;

	if (year_ < 2000)
		if ((day_ == 29 && mon_ == 2) && !((year_ - 1900) % 4 == 0)) return false;

	if (year_ > 2000)
		if ((day_ == 29 && mon_ == 2) && !((year_ - 2000) % 4 == 0)) return false;

	return true;
}

bool date::try_parse(const tm& tm, datetime& dt)
{
	datetime dt_{ tm.tm_mday ,tm.tm_mon + 1 ,tm.tm_year + 1900 ,tm.tm_hour ,tm.tm_min ,tm.tm_sec };
	if (dt_.is_valid())
	{
		dt = dt_;
		return true;
	}
	return false;
}

date::datetime date::now()
{
	tm now;
	time_t raw = time(nullptr);
	localtime_s(&now, &raw);
	datetime dt;
	if (try_parse(now, dt))
	{
		return dt;
	}
	return datetime();
}

bool operator<(const date::datetime& d1, const date::datetime& d2)
{
	if (d1.get_year() < d2.get_year()) { return true; }
	else if (d1.get_year() > d2.get_year()) { return false; }
	else { // same year
		if (d1.get_month() < d2.get_month()) { return true; }
		else if (d1.get_month() > d2.get_month()) { return false; }
		else { // same month
			if (d1.get_day() < d2.get_day()) { return true; }
			else if (d1.get_day() > d2.get_day()) { return false; }
			else { // same day
				if (d1.get_hour() < d2.get_hour()) { return true; }
				if (d1.get_hour() > d2.get_hour()) { return false; }
				else {	// same hour
					if (d1.get_mins() < d2.get_mins()) { return true; }
					if (d1.get_mins() > d2.get_mins()) { return false; }
					else { // same minutes
						if (d1.get_secs() < d2.get_secs()) { return true; }
						else { return false; }
					}
				}
			}
		}
	}
	return false;
}

bool operator> (const date::datetime& d1, const date::datetime& d2) {
	if (d1 == d2) { return false; } // this is strict inequality
	if (d1 < d2) { return false; }
	return true;
}

bool operator==(const date::datetime& d1, const date::datetime& d2)
{
	return d1.get_secs() == d2.get_secs()
		&& d1.get_mins() == d2.get_mins()
		&& d1.get_hour() == d2.get_hour()
		&& d1.get_day() == d2.get_day()
		&& d1.get_month() == d2.get_month()
		&& d1.get_year() == d2.get_year();
}

bool operator!=(const date::datetime& d1, const date::datetime& d2)
{
	return !(d1 == d2);
}