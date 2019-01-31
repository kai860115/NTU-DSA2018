#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace std;
 
class Data
{
  public:
    Data(const float &low, const float &high, const long long int &cap)
    {
        _low = low;
        _high = high;
        _cap = cap;
    }
    Data()
    {
        _low = 0;
        _high = 0;
        _cap = 0;
    }
    Data(const Data &d)
    {
        _low = d._low;
        _high = d._high;
        _cap = d._cap;
    }
    float _low;
    float _high;
    long long int _cap;
};
 
class QueryKey
{
  public:
    QueryKey(const string &date, const string ¤cy, const string &exchange)
    {
        _date = date;
        _currency = currency;
        _exchange = exchange;
    }
    QueryKey()
    {
        _date = "";
        _currency = "";
        _exchange = "";
    }
    QueryKey(const QueryKey &q)
    {
        _date = q._date;
        _currency = q._currency;
        _exchange = q._exchange;
    }
 
    bool operator==(const QueryKey &q) const
    {
        return ((_date == q._date) && (_currency == q._currency) && (_exchange == q._exchange));
    }
 
    bool operator<(const QueryKey &q) const
    {
        if (_date == q._date)
        {
            if (_currency == q._currency)
            {
                return _exchange < q._exchange;
            }
            return _currency < q._currency;
        }
        return _date < q._date;
    }
    string _date;
    string _currency;
    string _exchange;
};
 
class MinMaxKey
{
  public:
    MinMaxKey(const string &date, const string ¤cy)
    {
        _date = date;
        _currency = currency;
    }
    MinMaxKey()
    {
        _date = "";
        _currency = "";
    }
    MinMaxKey(const MinMaxKey &m)
    {
        _date = m._date;
        _currency = m._currency;
    }
 
    bool operator==(const MinMaxKey &m) const
    {
        return ((_date == m._date) && (_currency == m._currency));
    }
 
    bool operator<(const MinMaxKey &m) const
    {
        if (_date == m._date)
        {
            return _currency < m._currency;
        }
        return _date < m._date;
    }
    string _date;
    string _currency;
};
 
class CapKey
{
  public:
    CapKey(const string &date, const string &exchange)
    {
        _date = date;
        _exchange = exchange;
    }
    CapKey()
    {
        _date = "";
        _exchange = "";
    }
    CapKey(const CapKey &c)
    {
        _date = c._date;
        _exchange = c._exchange;
    }
 
    bool operator==(const CapKey &c) const
    {
        return ((_date == c._date) && (_exchange == c._exchange));
    }
 
    bool operator<(const CapKey &c) const
    {
        if (_date == c._date)
        {
            return _exchange < c._exchange;
        }
        return _date < c._date;
    }
    string _date;
    string _exchange;
};
 
struct KeyComparer
{
    bool operator()(const QueryKey &k1, const QueryKey &k2) const
    {
        return k1 < k2;
    }
    bool operator()(const MinMaxKey &k1, const MinMaxKey &k2) const
    {
        return k1 < k2;
    }
    bool operator()(const CapKey &k1, const CapKey &k2) const
    {
        return k1 < k2;
    }
};
 
struct KeyHasher
{
    size_t operator()(const QueryKey &k) const
    {
        return ((hash<string>()(k._date)) ^ (hash<string>()(k._exchange) << 1) >> 1) ^ (hash<string>()(k._currency) << 1);
    }
    size_t operator()(const MinMaxKey &k) const
    {
        return (hash<string>()(k._date)) ^ (hash<string>()(k._currency) << 1);
    }
    size_t operator()(const CapKey &k) const
    {
        return (hash<string>()(k._date)) ^ (hash<string>()(k._exchange) << 1);
    }
};
 
int main(int argc, char **argv)
{
    ifstream infile(argv[1]);
    string line;
    unordered_map<QueryKey, Data, KeyHasher> queryMap;
    unordered_map<MinMaxKey, float, KeyHasher> minMap;
    unordered_map<MinMaxKey, float, KeyHasher> maxMap;
    unordered_map<CapKey, long long int, KeyHasher> capMap;
    if (infile)
    {
        while (getline(infile, line))
        {
            istringstream s(line);
            string date, currency, exchange;
            float low, high;
            long long int cap;
 
            s >> date >> currency >> exchange >> low >> high >> cap;
            Data d(low, high, cap);
            QueryKey q(date, currency, exchange);
            MinMaxKey m(date, currency);
            CapKey c(date, exchange);
 
            queryMap[q] = d;
            if (minMap.find(m) == minMap.end())
            {
                minMap[m] = low;
            }
            else
            {
                if (minMap[m] > low)
                {
                    minMap[m] = low;
                }
            }
 
            if (maxMap[m] < high)
            {
                maxMap[m] = high;
            }
 
            capMap[c] += cap;
        }
    }
    infile.close();
    string command;
    while (getline(cin, line))
    {
        istringstream s(line);
        s >> command;
        if (command == "end")
            break;
        else if (command == "query")
        {
            string date, currency, exchange;
            s >> date >> currency >> exchange;
            QueryKey q(date, currency, exchange);
 
            if (queryMap.find(q) == queryMap.end())
                cout << "none" << endl;
            else
            {
                Data d = queryMap[q];
                cout << fixed << setprecision(4) << d._low << " " << d._high << " " << d._cap << endl;
            }
        }
        else if (command == "price")
        {
            s >> command;
            string date, currency;
            s >> date >> currency;
            MinMaxKey m(date, currency);
            if (command == "min")
            {
                if (minMap.find(m) == minMap.end())
                    cout << "none" << endl;
                else
                    cout << fixed << setprecision(4) << minMap[m] << endl;
            }
            else if (command == "max")
            {
                if (maxMap.find(m) == maxMap.end())
                    cout << "none" << endl;
                else
                    cout << fixed << setprecision(4) << maxMap[m] << endl;
            }
        }
        else if (command == "cap")
        {
            string date, exchange;
            s >> date >> exchange;
            CapKey c(date, exchange);
            if (capMap[c] == 0)
                cout << "none" << endl;
            else
                cout << capMap[c] << endl;
        }
    }
 
    return 0;
}
