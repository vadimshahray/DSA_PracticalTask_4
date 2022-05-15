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
   /// Поиск индекса элемента по ключу
   /// </summary>
   /// <param name="key">Ключ, по которому осуществляется поиск</param>
   /// <returns>Если удалось найти элемент с ключом key, то вернет его индекс, иначе - индекс последнего проверенного элемента</returns>
   ULONGLONG index_of(const ULONGLONG &key);

   public:
   /// <summary>
   /// Возвращает количество элементов в таблице
   /// </summary>
   ULONGLONG size();
   /// <summary>
   /// Проверяет, пуста ли таблица
   /// </summary>
   bool empty();

   /// <summary>
   /// Добавляет элемент в упорядоченную таблицу
   /// </summary>
   void insert(const ULONGLONG key, const V &value);

   /// <summary>
   /// Ищет элемент по ключу key
   /// </summary>
   /// <returns>Указатель на найденный элемент</returns>
   V *find(const ULONGLONG key);

   /// <summary>
   /// Перебирает все элементы таблицы и передает их функции-обработчику f
   /// </summary>
   void for_each(const function<void(kv_pair<V>)> &f);
};
#endif