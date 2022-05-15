#include <windows.h>
#include "table.h"
#include "kv_pair.h"
#include "vote.h"

template <typename V>
ULONGLONG table<V>::index_of(const ULONGLONG &key)
{
   if (empty())
      return 0;

   ULONGLONG left = 0, right = _size - 1;

   while (right > left)                   // Пока интервал поиска не пуст
   {
      ULONGLONG mid = (right + left) / 2;

      if (key < data[mid]->key && mid)    // Обрабатываем левую половину
         right = mid - 1;
      else if (key > data[mid]->key)      // Обрабатываем правую половину
         left = mid + 1;
      else
         return mid;
   }

   return left;
}

template <typename V>
ULONGLONG table<V>::size()
{
   return _size;
}

template <typename V>
bool table<V>::empty()
{
   return _size == 0;
}

template <typename V>
void table<V>::insert(const ULONGLONG key, const V &value)
{
   if (_size == Nmax)
      return;

   ULONGLONG i = index_of(key);

   if (data[i] != NULL && data[i]->key < key) // Если ключ i-ого элемента < key, то ключ i + 1 точно не меньше (см. index_of)
      i++;

   for (ULONGLONG j = _size; j > i; j--) // Смещение элементов, которые больше i-ого
      data[j] = data[j - 1];

   data[i] = new kv_pair<V>(key, value);
   _size++;
}

template <typename V>
V *table<V>::find(const ULONGLONG key)
{
   if (_size == 0) return NULL;

   ULONGLONG i = index_of(key);
   return key == data[i]->key ? &data[i]->value : NULL;
}

template <typename V>
void table<V>::for_each(const function<void(kv_pair<V>)> &f)
{
   for (UCHAR i = 0; i < _size; i++)
      f(*data[i]);
}

template struct table<vote>;