
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class heap
{
  public:
  heap(bool ismin=true): ismin(ismin), length(0) {}

	heap(const vector<T> &d, const bool ismin = true): ismin(ismin),
										   data(d),
										   length(d.size())
    {
	  for (int i = length / 2 - 1; i >= 0; i--)
	    fix_down(i);
    }

	heap &push(const T &t)
	{
	  length++;
	  if (length <= data.size())
		data[length-1] = t;
	  else
		data.push_back(t);
	  fix_up(length - 1);

	  return *this;
	}

	heap &pop()
	{
	  swap(data[0], data[--length]);
	  fix_down(0);
	  return *this;
	}

	const T& top()
	{
	  return data[0];
	}

	static void sort(vector<T> &d, bool reversed=false)
	{
	  heap<T> h(d, reversed);
	  for (int i = 0; i < d.size(); i++) {
		d[i] = h.top();
		h.pop();
	  }
	}

private:
	bool ismin;
	vector<T> data;
	int length;
	bool greater(const T& t1, const T& t2)
	{
	  if (ismin)
		return t1 < t2;
	  else
		return t1 > t2;
	}

	int left(int i) { return 2*i + 1;}
	int right(int i) { return 2*i + 2;}
	int parent(int i) { return (i-1)/2;}

	void fix_up(int i)
	{
	  for (int j = parent(i); (j>=0) && greater(data[j], data[i]); i=j,j=parent(i))
		swap(data[i], data[j]);
	}

	void fix_down(int i)
	{
	  T tmp = data[i];
	  int j = left(i);

	  while (j < length) {
		if(j+1 < length && greater(data[j], data[j+1])) j++;

		if (greater(tmp, data[j])) {
		  data[i] = data[j];
		  i = j;
		  j = left(i);
		} else {
		  break;
		}
	  }
	  data[i] = tmp;
	}
};

int main() {
    int test[10] = {5,1,3,7,8,10,4,-9,54,12};
    int i;
    vector<int> intv;
    for (i = 0; i < 10; i++) {
    cout << test[i] << " ";
        intv.push_back(test[i]);
    }
    cout << endl;
    heap<int>::sort(intv);
    for (vector<int>::iterator it=intv.begin(); it != intv.end(); it++)
        cout << *it << " ";
    cout << endl;
    return 0;
}