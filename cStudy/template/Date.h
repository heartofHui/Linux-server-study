class Date
{
    private:
        int month;
        int day;
        int year;
    public:
        Date(void)
        {
            month=0;
            day=0;
            year=0;
        }
        Date(int a,int b,int c)
        {
            year=a;
            month=b;
            day=c;
        }
        int getMonth()
        {
            return month;
        }
        int getYear()
        {
            return year;
        }
        int getDay()
        {
            return day;
        }
        bool operator<(const Date & other)
        {
            if(year<other.year)
                return true;
            else if(year>other.year)
                return false;
            else if(month<other.month)
                return true;
            else if(month>other.month)
                return false;
            else if(day<other.day)
                return true;
            else if(day>other.day)
                return false;
            else
                return false;
        }
        bool operator>(const Date & other)
        {
            if(year>other.year)
                return true;
            else if(year<other.year)
                return false;
            else if(month>other.month)
                return true;
            else if(month<other.month)
                return false;
            else if(day>other.day)
                return true;
            else if(day<other.day)
                return false;
            else
                return false;
        }
        bool operator==(const Date & other)
        {
            if(year==other.year && month==other.month && day==other.day)
                return true;
            else
                return false;
        }

};