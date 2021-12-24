#include "pch.h"

template<typename T>
class CircularArray
{
private:
    unsigned short int m_Index;
    std::vector<T> m_Buffer;

public:
    CircularArray(int size)
        : m_Index(0)
    {
        m_Buffer.reserve(size);
    }

    template<typename ... Args>
    void emplace(Args&& ... args)
    {
        m_Buffer.emplace_back(std::forward<Args>(args)...);
    }

    void next() {
        if (++m_Index >= m_Buffer.size())
            m_Index = 0;
    }
    void previous() {
        if (m_Index == 0)
            m_Index = static_cast<unsigned short>(m_Buffer.size() - 1u);
        else
            --m_Index;
    }
    const T& get() const {
        return m_Buffer.at(m_Index);
    }
    T& get() {
        return m_Buffer.at(m_Index);
    }

    bool hasMembers()const {
        return m_Buffer.size() > 0;
    }

    std::vector<T>& getMembers() {
        return m_Buffer;
    }
};