#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;
 
#define M (size_t)1000000007
#define X (size_t)29
#define MAX_LEN (size_t)20
 
class myString
{
  public:
    myString()
    {
        _str = 0;
        _capacity = 0;
        _size = 0;
        _begin = 0;
        _end = 0;
    }
    myString(const size_t &c)
    {
        _capacity = c;
        _size = 0;
        _str = new char[_capacity + 1];
        _begin = _str + _capacity / 3;
        _end = _str + _capacity / 3;
    }
    ~myString()
    {
        if (_str != 0)
            delete[] _str;
    }
 
    inline void push_front(const char &c)
    {
        *(--_begin) = c;
        _size++;
    }
 
    inline void push_back(const char &c)
    {
        *(_end++) = c;
        _size++;
    }
 
    inline size_t size() const
    {
        return _size;
    }
 
    inline size_t capacity() const
    {
        return _capacity;
    }
 
    void reserve(const size_t &c)
    {
        if (_capacity != c)
        {
            char *new_str = new char[c];
            char *_new_begin = new_str + _capacity / 3;
            char *_new_end = _new_begin + _size;
            strncpy(_new_begin, _begin, _size);
 
            _capacity = c;
            if (_str != 0)
                _str = new char[_capacity + 1];
            _begin = _new_begin;
            _end = _new_end;
        }
    }
 
    inline char &operator[](size_t i) { return *(_begin + i); }
    inline const char &operator[](size_t i) const { return *(_begin + i); }
 
  private:
    char *_str;
    char *_begin;
    char *_end;
    size_t _capacity;
    size_t _size;
};
 
class StringMatching
{
  public:
    StringMatching()
    {
        _str.reserve(300000);
        _sn.reserve(200000);
        _xn.reserve(200000);
        _ans = new unordered_map<long, unsigned int>[MAX_LEN];
        for (size_t i = 0; i != MAX_LEN; i++)
        {
            _ans[i].reserve(1000003);
        }
        _map_begin = -1;
        _map_end = 0;
    }
    ~StringMatching()
    {
        if (_ans != 0)
            delete[] _ans;
    }
 
    void build_xn()
    {
        for (size_t i = _xn.size(); i != _str.size(); i++)
        {
            if (i != 0)
                _xn.push_back((_xn[i - 1] * X) % M);
            else
                _xn.push_back(1);
        }
    }
 
    void build_sn()
    {
        _sn.resize(0);
 
        for (size_t i = 0; i != _str.size(); i++)
        {
            if (i != 0)
                _sn.push_back(((_sn[i - 1] * X) % M + char2num(_str[i])) % M);
            else
                _sn.push_back(char2num(_str[i]));
        }
        _built_sn = true;
    }
 
    void build_map()
    {
        _maxlen = _str.size();
        if (_maxlen > MAX_LEN)
            _maxlen = MAX_LEN;
 
        for (; _map_end != _str.size(); _map_end++)
        {
            long value = char2num(_str[_map_end]);
            for (long i = 1; i != _maxlen + 1; i++)
            {
                if (_map_end - i + 1 <= _map_begin)
                    break;
                else if (i == 1)
                    _ans[i - 1][value]++;
                else
                {
                    value = (value + char2num(_str[_map_end - i + 1]) * _xn[i - 1] % M) % M;
                    _ans[i - 1][value]++;
                }
            }
        }
 
        for (; _map_begin >= 0; _map_begin--)
        {
            long value = char2num(_str[_map_begin]);
            for (long i = 1; i != _maxlen + 1; i++)
            {
                if (_map_begin + i > _str.size())
                    break;
                else if (i == 1)
                    _ans[i - 1][value]++;
                else
                {
                    value = (value * X % M + char2num(_str[_map_begin + i - 1])) % M;
                    _ans[i - 1][value]++;
                }
            }
        }
 
        /*
        for (; _map_end != _str.size(); _map_end++)
        {
            for (long i = 1; i != _maxlen + 1; i++)
            {
                if (_map_end - i + 1 < 0)
                    break;
                else if (_map_end - i + 1 == 0)
                    _ans[i - 1][_sn[_map_end]]++;
                else
                    _ans[i - 1][((_sn[_map_end] + M - _xn[i] * _sn[_map_end - i] % M) % M)]++;
            }
        }
 
        for (; _map_begin >= 0; _map_begin--)
        {
            for (long i = 1; i != _maxlen + 1; i++)
            {
                if (_map_begin - i + 1 < 0)
                    break;
                else if (_map_begin - i + 1 == 0)
                    _ans[i - 1][_sn[_map_begin]]++;
                else
                    _ans[i - 1][((_sn[_map_begin] + M - _xn[i] * _sn[_map_begin - i] % M) % M)]++;
            }
        }*/
    }
 
    inline void push_front(const char &c)
    {
        _str.push_front(c);
        _map_begin++;
        _map_end++;
        _built_sn = false;
    }
    inline void push_back(const char &c)
    {
        _str.push_back(c);
        _built_sn = false;
    }
    void match(const char *p, size_t &ans)
    {
        build_xn();
        long pn = 0;
        size_t p_len = strlen(p);
        if (p_len > _str.size())
        {
            ans = 0;
        }
        else
        {
 
            for (size_t i = 0; i != p_len; i++)
            {
                pn = (pn * X % M + char2num(p[i])) % M;
            }
 
            if (p_len <= MAX_LEN)
            {
                //printf("%s ", p);
                build_map();
                ans = _ans[p_len - 1][pn];
            }
            else
            {
                if (!_built_sn)
                    build_sn();
                for (size_t i = p_len - 1; i != _str.size(); i++)
                {
                    long si_l = _sn[i];
                    if (i != p_len - 1)
                        si_l = (si_l + M - _sn[i - p_len] * _xn[p_len] % M) % M;
                    if (si_l == pn)
                        ans++;
                }
            }
        }
    }
 
  private:
    myString _str;
    int _map_begin;
    int _map_end;
    int _maxlen;
    bool _built_sn;
    vector<long> _xn;
    vector<long> _sn;
    unordered_map<long, unsigned int> *_ans;
    inline long char2num(const char &c) const
    {
        return (long)(c - 'a' + 1);
    }
};
 
int main()
{
    char *s = new char[100000];
    scanf("%s", s);
    StringMatching str_match;
 
    size_t size = strlen(s);
    for (size_t i = 0; i != size; i++)
    {
        str_match.push_back(s[i]);
    }
 
    int q = 0;
 
    scanf("%d", &q);
    for (int i = 0; i != q; i++)
    {
        int n;
        scanf("%d%s", &n, s);
        switch (n)
        {
        case 1:
            str_match.push_front(s[0]);
            break;
        case 2:
            str_match.push_back(s[0]);
            break;
        case 3:
            size_t ans = 0;
            str_match.match(s, ans);
            printf("%llu\n", ans);
            break;
        }
    }
    delete[] s;
}
