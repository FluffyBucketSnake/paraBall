#pragma once
#include <stdexcept>

template<typename T> 
struct Range
{
    private:
        T _start;
        T _end;
    public:
        Range(int start, int end)
        {
            if (end < start)
                throw std::out_of_range("start & end");
            _start = start;
            _end = end;
        }

        T Start()
        {
            return _start;
        }
        T End()
        {
            return _end;
        }
        void Start(T start)
        {
            if (_end < start)
                throw std::out_of_range("start");
            _start = start;
        }
        void End(T end)
        {
            if (end < _start)
                throw std::out_of_range("end");
            _end = end;
        }
        T Distance()
        {
            return std::abs(_end-_start);
        }
        bool Contains(T value)
        {
            return (value>=_start) && (value<=_end);
        }
        T Clamp(T value)
        {
            return std::max(_start,std::min(_end,value));
        }
};