#pragma once
#include <ctime>
#include <string>

using namespace std;

namespace date
{
	class datetime
	{
	public:
		datetime();
		datetime(int day, int month, int year);
		datetime(int day, int month, int year, int h, int min, int sec);
		~datetime();

		int get_day() const { return day_; }
		int get_month() const { return mon_; }
		int get_year() const { return year_; }

		int get_hour() const { return hh_; }
		int get_mins() const { return min_; }
		int get_secs() const { return sec_; }

		string to_string() const;
		string to_date_string() const;

		bool is_valid() const;
	private:
		int day_, mon_, year_, hh_, min_, sec_ = 0;
	};

	bool try_parse(const tm&, datetime&);
	datetime now();
}

bool operator <(const date::datetime&, const date::datetime&);
bool operator >(const date::datetime&, const date::datetime&);
bool operator==(const date::datetime&, const date::datetime&);
bool operator!=(const date::datetime&, const date::datetime&);
