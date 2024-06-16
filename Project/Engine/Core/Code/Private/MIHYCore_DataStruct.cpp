#include "MIHYCore_PCH.h"
#include "MIHYCore_DataStruct.h"


namespace MIHYCore{
    namespace DataStruct{

        

    std::string MIHYVector_UnitTest()
    {
        
#define VECTOR_PRINT(v) std::cout << "Capacity: " << v.get_capacity() << std::endl; for(UInt32 i = 0; i < v.get_size(); ++i) std::cout << v[i] << " "; std::cout << std::endl;
        using V = MIHYVector<UInt32>;

        {//clear
            V v{2, {0, 1, 2}};
            v.clear();
            assert(v.get_size() == 0);
        }

        {//get_capacity
            V v{2};
            assert(v.get_capacity() == 2);
        }

        {//get_size
            V v{2, {0, 1, 2}};
            assert(v.get_size() == 3);
        }

        {//operator[]
            V v{2, {0, 1, 2}};
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        //생성자
        {   V v{10};   assert(v.get_capacity() == 10);  }

        {//생성자(초기화 리스트)
            V v{5, {0, 1, 2}};
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };

        {//생성자(초기화 리스트, 시작 크기보다 많은 원소가 들어올 경우)
            V v{2, {0, 1, 2}};
            assert(v.get_capacity() > 2 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };
        
        {//복사 생성자
            V o{5, {0, 1, 2}};
            V v{o};
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//이동 생성자
            V o{5, {0, 1, 2}}
            V v{std::move(v0)}; 
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//대입
            V o{5, {0, 1, 2}};
            V v{2};
            v = o;
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }
        
        {//이동
            V o{5, {0, 1, 2}}
            V v{2}; 
            v = std::move(o);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//push_back
            V v{2},
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            v.push_back(0);
            v.push_back({1, 2});
            v.push_back(v2);
            v.push_back(v3.iterator.begin());
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2 && v[3] == 3 && v[4] == 4 && v[5] == 5 && v[6] == 6);
        }

        {//push_front
            V v{2};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            v.push_front(0);
            v.push_front({1, 2});                //초기화 리스트를 통해 순서대로 넣은 의미이기에 역순으로 위치하게됨
            v.push_front(v2);                    //컨테이너 자체를 복사하는 것이기에 역순이 아닌 그대로 들어감
            v.push_front(v3.iterator.begin());   //이터레이터를 통해 하나하나 복사하는 의미이기에 반복자의 역순으로 위치하게됨
            assert(v[0] == 6 && v[1] == 5 && v[2] == 3 && v[3] == 4 && v[4] == 2 && v[5] == 1 && v[6] == 0);
        }

        {//push_at
            V v{2, {88, 99, 99, 88}};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            v.push_at(2, 0);
            v.push_at(2, {1, 2});                //초기화 리스트를 통해 순서대로 넣은 의미이기에 역순으로 위치하게됨
            v.push_at(2, v2);                    //컨테이너 자체를 복사하는 것이기에 역순이 아닌 그대로 들어감
            v.push_at(2, v3.iterator.begin());   //이터레이터를 통해 하나하나 복사하는 의미이기에 반복자의 역순으로 위치하게됨
            assert(v[0] == 88 && v[1] == 99 &&
                   v[2] == 6 && v[3] == 5 && v[4] == 3 && v[5] == 4 && v[6] == 2 && v[7] == 1 && v[8] == 0 &&
                   v[9] == 99 && v[10] == 88);
        }

        {//pop_back
            V v{2, {0, 1, 2}};
            v.pop_back();
            assert(v.get_size() == 2 && v[0] == 0 && v[1] == 1);
        }

        {//pop_front
            V v{2, {0, 1, 2}};
            v.pop_front();
            assert(v.get_size() == 2 && v[0] == 1 && v[1] == 2);
        }

        {//pop_at
            V v{2, {0, 1, 2}};
            v.pop_at(1);
            assert(v.get_size() == 2 && v[0] == 0 && v[1] == 2);
        }

        {//iterator
            V v{2, {0, 1, 2}};
            MIHYIterator<V> iterator{v};
            auto iter{iterator.begin()};
            assert(*iter == 0);
            ++iter;
            assert(*iter == 1);
            ++iter;
            assert(*iter == 2);
            --iter;
            assert(*iter == 1);
            --iter;
            assert(*iter == 0);
            iter += 2;
            assert(*iter == 2);
            iter -= 2;
            assert(*iter == 0);
        }



        return "Success";

    }


    }
}