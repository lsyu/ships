#ifndef SINGLETONIMPLDEL_H
#define SINGLETONIMPLDEL_H

template <typename T>
class __CSingletonImplDel
{
public:
    explicit __CSingletonImplDel(T *ptr) : m_ptr(ptr) {}
    ~__CSingletonImplDel() {delete m_ptr;}
private:
    T *m_ptr;
}; // class __CSingletonImplDel

#endif // SINGLETONIMPLDEL_H
