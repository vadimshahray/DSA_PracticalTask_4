#ifndef H_TABLE
#define H_TABLE

#include <windows.h>
#include <functional>
#include "kv_pair.h"

using namespace std;

const UCHAR Nmax = 10;

template <typename V>
struct table
{
   private:
   ULONGLONG _size = 0;
   kv_pair<V> *data[Nmax] = { };

   /// <summary>
   /// ����� ������� �������� �� �����
   /// </summary>
   /// <param name="key">����, �� �������� �������������� �����</param>
   /// <returns>���� ������� ����� ������� � ������ key, �� ������ ��� ������, ����� - ������ ���������� ������������ ��������</returns>
   ULONGLONG index_of(const ULONGLONG &key);

   public:
   /// <summary>
   /// ���������� ���������� ��������� � �������
   /// </summary>
   ULONGLONG size();
   /// <summary>
   /// ���������, ����� �� �������
   /// </summary>
   bool empty();

   /// <summary>
   /// ��������� ������� � ������������� �������
   /// </summary>
   void insert(const ULONGLONG key, const V &value);

   /// <summary>
   /// ���� ������� �� ����� key
   /// </summary>
   /// <returns>��������� �� ��������� �������</returns>
   V *find(const ULONGLONG key);

   /// <summary>
   /// ���������� ��� �������� ������� � �������� �� �������-����������� f
   /// </summary>
   void for_each(const function<void(kv_pair<V>)> &f);
};
#endif